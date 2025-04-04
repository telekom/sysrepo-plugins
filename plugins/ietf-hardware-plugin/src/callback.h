// telekom / sysrepo-plugin-hardware
//
// This program is made available under the terms of the
// BSD 3-Clause license which is available at
// https://opensource.org/licenses/BSD-3-Clause
//
// SPDX-FileCopyrightText: 2021 Deutsche Telekom AG
//
// SPDX-License-Identifier: BSD-3-Clause

#ifndef CALLBACK_H
#define CALLBACK_H

#include <component_data.h>
#include <sensor_data.h>
#include <utils/rapidjson/document.h>
#include <utils/rapidjson/istreamwrapper.h>

#include <chrono>
#include <fstream>
#include <hardware_sensors.h>
#include <mutex>
#include <sysrepo-cpp/Enum.hpp>

namespace hardware {

struct Callback {
    using Session = sysrepo::Session;
    using ErrorCode = sysrepo::ErrorCode;
    using Event = sysrepo::Event;
    using Value = rapidjson::Value;
    using Document = rapidjson::Document;
    using IStreamWrapper = rapidjson::IStreamWrapper;

    static ErrorCode configurationCallback(Session session,
                                           uint32_t subscriptionId,
                                           std::string_view moduleName,
                                           std::optional<std::string_view> /* subXPath */,
                                           Event /* event */,
                                           uint32_t /* request_id */) {
        printCurrentConfig(session, moduleName);
        logMessage(SR_LL_DBG, "Processing received configuration.");
        HardwareSensors::getInstance().notifyAndJoin();
        ComponentData::populateConfigData(session, moduleName);
        HardwareSensors::getInstance().startThreads();
        return ErrorCode::Ok;
    }

    static ErrorCode operationalCallback(Session session,
                                         uint32_t subscriptionId,
                                         std::string_view moduleName,
                                         std::optional<std::string_view> /* subXPath */,
                                         std::optional<std::string_view> /* requestXPath */,
                                         uint32_t /* requestId */,
                                         std::optional<libyang::DataNode>& parent) {

        int rc = system("/usr/bin/lshw -json > " COMPONENTS_LOCATION);
        if (rc == -1) {
            logMessage(SR_LL_ERR, "lshw command failed");
            return ErrorCode::CallbackFailed;
        }
        logMessage(SR_LL_DBG, "lshw command returned:" + std::to_string(rc));
        std::string const set_xpath("/ietf-hardware:hardware");

        // +--ro last-change?   yang:date-and-time
        std::time_t lastChange(
            std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()));
        char timeString[100];
        if (std::strftime(timeString, sizeof(timeString), "%FT%TZ", std::localtime(&lastChange))) {
            setXpath(session, parent, set_xpath + "/last-change", timeString);
        }

        std::ifstream ifs(COMPONENTS_LOCATION, std::ifstream::in);
        if (ifs.fail()) {
            logMessage(SR_LL_ERR, "Can't open: " COMPONENTS_LOCATION);
            return ErrorCode::CallbackFailed;
        }
        IStreamWrapper isw(ifs);
        Document doc;
        doc.ParseStream(isw);
        if (!doc.IsObject() && !doc.IsArray()) {
            logMessage(SR_LL_ERR, "lshw json root-node is not an object or array");
            return ErrorCode::CallbackFailed;
        }

        ComponentMap hwComponents;
        parseAndSetComponents(doc, hwComponents, std::string());

        auto const& modules = session.getContext().modules();
        auto module = std::find_if(
            modules.begin(), modules.end(),
            [moduleName](libyang::Module const& module) { return moduleName == module.name(); });

        try {
            if (module != std::end(modules) && module->featureEnabled("hardware-sensor")) {
                HardwareSensors::getInstance().parseSensorData(hwComponents);
            }
        } catch (std::exception const& e) {
            logMessage(SR_LL_WRN, "hardware-sensors nodes failure: " + std::string(e.what()));
        }

        for (auto const& c : hwComponents) {
            c.second->setXpathForAllMembers(session, parent, set_xpath,
                                            (module != std::end(modules)) &&
                                                module->featureEnabled("entity-mib"));
        }

        if (!parent) {
            logMessage(SR_LL_ERR, "No nodes were set");
            return ErrorCode::CallbackFailed;
        }
        return ErrorCode::Ok;
    }

    static std::string toIANAclass(std::string const& inputClass) {
        std::string returnedClass("iana-hardware:unknown");
        static std::unordered_map<std::string, std::string> _{
            {"storage", "iana-hardware:storage-drive"},
            {"power", "iana-hardware:battery"},
            {"processor", "iana-hardware:cpu"},
            {"network", "iana-hardware:port"}};

        if (_.find(inputClass) != _.end()) {
            returnedClass = _.at(inputClass);
        }
        return returnedClass;
    }

    static std::string parseAndSetComponent(Value const& parsee,
                                            std::string const& parentName,
                                            Value::ConstMemberIterator itr,
                                            ComponentMap& hwComponents,
                                            int32_t& parent_rel_pos) {
        std::shared_ptr<ComponentData> component;
        if (itr != parsee.MemberEnd()) {
            component = std::make_shared<ComponentData>(itr->value.GetString());
        } else {
            // invalid entry, go to the next one
            return std::string();
        }

        // firmware node, skip this one and set the parent's firmware-rev
        // +--ro firmware-rev?     string
        if (component->name == "firmware" && !parentName.empty() &&
            (itr = parsee.FindMember("version")) != parsee.MemberEnd()) {
            if (hwComponents.find(parentName) != hwComponents.end() && hwComponents[parentName]) {
                hwComponents[parentName]->firmwareRev = itr->value.GetString();
            }
            return std::string();
        }

        // Check if a node with the current name exists, if so rename the current one
        if (hwComponents.find(component->name) != hwComponents.end()) {
            component->name = parentName + ":" + component->name;
        }

        // +--rw class             identityref
        if ((itr = parsee.FindMember("class")) != parsee.MemberEnd()) {
            component->classType = toIANAclass(itr->value.GetString());
        }

        // +--rw name              string
        // +--ro description?      string
        // +--ro hardware-rev?     string
        // +--ro serial-num?       string
        // +--ro mfg-name?         string
        // +--ro model-name?       string
        // +--rw alias?            string
        for (auto const& mapValue : getLSHWtoIETFmap()) {
            std::string const stringValue = mapValue.first;
            if ((itr = parsee.FindMember(stringValue.c_str())) != parsee.MemberEnd()) {
                component->setValueFromLSHWmap(stringValue, itr->value.GetString());
            }
        }

        // +--ro software-rev?     string
        // +--ro uuid?             yang:uuid
        if ((itr = parsee.FindMember("configuration")) != parsee.MemberEnd()) {
            Value::ConstMemberIterator config_elem = itr->value.FindMember("uuid");
            if (config_elem != itr->value.MemberEnd()) {
                component->uuid = config_elem->value.GetString();
            }
            if ((config_elem = itr->value.FindMember("driverversion")) != itr->value.MemberEnd()) {
                component->softwareRev = config_elem->value.GetString();
            }
            if ((config_elem = itr->value.FindMember("firmware")) != itr->value.MemberEnd()) {
                component->firmwareRev = config_elem->value.GetString();
            }
        }

        // +--ro physical-index?   int32 {entity-mib}?
        if ((itr = parsee.FindMember("physid")) != parsee.MemberEnd()) {
            component->parseAndSetPhysicalID(itr->value.GetString());
        }

        // +--rw parent?           -> ../../component/name
        // +--rw parent-rel-pos?   int32
        if (!parentName.empty()) {
            component->parentName = parentName;
            component->parent_rel_pos = parent_rel_pos;
            parent_rel_pos++;
        }

        // Filter parsed component through configuration values
        for (auto const& configData : ComponentData::hwConfigData) {
            if (configData && component->checkForConfigMatch(configData)) {
                component->replaceWritableValues(configData);
            }
        }

        hwComponents.insert(std::make_pair(component->name, component));

        // +--ro contains-child*   -> ../../component/name
        if ((itr = parsee.FindMember("children")) != parsee.MemberEnd()) {
            hwComponents[component->name]->children =
                parseAndSetComponents(itr->value.GetArray(), hwComponents, component->name);
        }

        return component->name;
    }

    static std::list<std::string> parseAndSetComponents(Value const& parsee,
                                                        ComponentMap& hwComponents,
                                                        std::string const& parentName) {
        std::list<std::string> siblings;
        int32_t parent_rel_pos(0);

        if (!parsee.IsArray()) {
            std::string const name(parseAndSetComponent(parsee, parentName, parsee.MemberBegin(),
                                                        hwComponents, parent_rel_pos));
            if (!name.empty()) {
                siblings.emplace_back(name);
            }
            return siblings;
        }

        for (auto& m : parsee.GetArray()) {
            Value::ConstMemberIterator itr = m.FindMember("id");
            std::string const name(
                parseAndSetComponent(m, parentName, itr, hwComponents, parent_rel_pos));
            if (!name.empty()) {
                siblings.emplace_back(name);
            }
        }
        return siblings;
    }

    static void printCurrentConfig(Session& session, std::string_view module_name) {
        try {
            std::string xpath(std::string("/") + std::string(module_name) + std::string(":*//*"));
            auto values = session.getData(xpath);
            if (!values)
                return;

            std::string const toPrint(
                values.value()
                    .printStr(libyang::DataFormat::JSON, libyang::PrintFlags::WithSiblings)
                    .value());
            logMessage(SR_LL_DBG, toPrint);
        } catch (const std::exception& e) {
            logMessage(SR_LL_WRN, e.what());
        }
    }

    static std::unordered_map<std::string, std::string> const& getLSHWtoIETFmap() {
        static std::unordered_map<std::string, std::string> const _{
            {"description", "/description"}, {"vendor", "/mfg-name"},
            {"serial", "/serial-num"},       {"product", "/model-name"},
            {"version", "/hardware-rev"},    {"handle", "/alias"}};
        return _;
    }
};

}  // namespace hardware

#endif  // CALLBACK_H
