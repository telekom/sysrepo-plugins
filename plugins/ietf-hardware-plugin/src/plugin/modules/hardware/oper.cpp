//
// telekom / sysrepo-plugins
//
// This program is made available under the terms of the
// BSD 3-Clause license which is available at
// https://opensource.org/licenses/BSD-3-Clause
//
// SPDX-FileCopyrightText: 2026 Deutsche Telekom AG
// SPDX-FileContributor: Sartura d.d.
//
// SPDX-License-Identifier: BSD-3-Clause
//

#include "oper.hpp"
#include "common.hpp"
#include "api/component_data.hpp"
#include "api/hardware_sensors.hpp"
#include "api/sensor_data.hpp"

#include "plugin/utils/rapidjson/document.h"
#include "plugin/utils/rapidjson/istreamwrapper.h"

#include <algorithm>
#include <chrono>
#include <ctime>
#include <fstream>
#include <list>
#include <string>
#include <unordered_map>

#include <sysrepo.h>

namespace ietf::hw::sub::oper {

using ErrorCode = sr::ErrorCode;
using Value = rapidjson::Value;
using Document = rapidjson::Document;
using IStreamWrapper = rapidjson::IStreamWrapper;

static std::list<std::string> parseAndSetComponents(Value const& parsee, ComponentMap& hwComponents, std::string const& parentName);

/**
 * @brief Map of lshw node names to the ietf-hardware component nodes.
 */
static std::unordered_map<std::string, std::string> const& getLSHWtoIETFmap()
{
    static std::unordered_map<std::string, std::string> const _ {
        { "description", "/description" }, { "vendor", "/mfg-name" },
        { "serial", "/serial-num" }, { "product", "/model-name" },
        { "version", "/hardware-rev" }, { "handle", "/alias" }
    };
    return _;
}

/**
 * @brief Map the lshw class to an iana-hardware class identity.
 */
static std::string toIANAclass(std::string const& inputClass)
{
    std::string returnedClass("iana-hardware:unknown");
    static std::unordered_map<std::string, std::string> _ {
        { "storage", "iana-hardware:storage-drive" },
        { "power", "iana-hardware:battery" },
        { "processor", "iana-hardware:cpu" },
        { "network", "iana-hardware:port" }
    };

    if (_.find(inputClass) != _.end()) {
        returnedClass = _.at(inputClass);
    }
    return returnedClass;
}

/**
 * @brief Parse a single lshw node (and its children) into the component map.
 *
 * @return Name of the parsed component or an empty string if it was skipped.
 */
static std::string parseAndSetComponent(Value const& parsee, std::string const& parentName, Value::ConstMemberIterator itr, ComponentMap& hwComponents, int32_t& parent_rel_pos)
{
    std::shared_ptr<ComponentData> component;
    if (itr != parsee.MemberEnd()) {
        component = std::make_shared<ComponentData>(itr->value.GetString());
    } else {
        // invalid entry, go to the next one
        return std::string();
    }

    // firmware node, skip this one and set the parent's firmware-rev
    // +--ro firmware-rev?     string
    if (component->name == "firmware" && !parentName.empty() && (itr = parsee.FindMember("version")) != parsee.MemberEnd()) {
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
        hwComponents[component->name]->children = parseAndSetComponents(itr->value.GetArray(), hwComponents, component->name);
    }

    return component->name;
}

/**
 * @brief Parse an lshw node or array of nodes into the component map.
 *
 * @return Names of the parsed sibling components.
 */
static std::list<std::string> parseAndSetComponents(Value const& parsee, ComponentMap& hwComponents, std::string const& parentName)
{
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

/**
 * Default constructor.
 *
 * @param ctx Plugin operational context.
 *
 */
HardwareOperGetCb::HardwareOperGetCb(std::shared_ptr<HardwareOperationalContext> ctx) { m_ctx = ctx; }

/**
 * Operational get operator() for path /ietf-hardware:hardware.
 *
 * @param session An implicit session for the callback.
 * @param subscriptionId ID the subscription associated with the callback.
 * @param moduleName The module name used for subscribing.
 * @param subXPath The optional xpath used at the time of subscription.
 * @param requestXPath The optional xpath of the request.
 * @param requestId Request ID unique for the specific module_name.
 * @param output A handle to a tree. The callback is supposed to fill this tree with the requested data.
 *
 * @return Error code.
 *
 */
sr::ErrorCode HardwareOperGetCb::operator()(sr::Session session, uint32_t subscriptionId, std::string_view moduleName, std::optional<std::string_view> subXPath,
    std::optional<std::string_view> requestXPath, uint32_t requestId, std::optional<ly::DataNode>& output)
{

    int rc = system((std::string("/usr/bin/lshw -json > ") + COMPONENTS_LOCATION).c_str());
    if (rc == -1) {
        SRPLG_LOG_ERR(getModuleLogPrefix(), "lshw command failed");
        return ErrorCode::CallbackFailed;
    }
    SRPLG_LOG_DBG(getModuleLogPrefix(), "%s", ("lshw command returned:" + std::to_string(rc)).c_str());
    std::string const set_xpath("/ietf-hardware:hardware");

    // +--ro last-change?   yang:date-and-time
    std::time_t lastChange(
        std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()));
    char timeString[100];
    if (std::strftime(timeString, sizeof(timeString), "%FT%TZ", std::localtime(&lastChange))) {
        output = session.getContext().newPath(set_xpath + "/last-change", timeString);
    }

    std::ifstream ifs(COMPONENTS_LOCATION, std::ifstream::in);
    if (ifs.fail()) {
        SRPLG_LOG_ERR(getModuleLogPrefix(), "Can't open: %s", COMPONENTS_LOCATION);
        return ErrorCode::CallbackFailed;
    }
    IStreamWrapper isw(ifs);
    Document doc;
    doc.ParseStream(isw);
    if (!doc.IsObject() && !doc.IsArray()) {
        SRPLG_LOG_ERR(getModuleLogPrefix(), "lshw json root-node is not an object or array");
        return ErrorCode::CallbackFailed;
    }

    ComponentMap hwComponents;
    parseAndSetComponents(doc, hwComponents, std::string());

    auto const& modules = session.getContext().modules();
    auto module = std::find_if(
        modules.begin(), modules.end(),
        [moduleName](libyang::Module const& m) { return moduleName == m.name(); });

    try {
        if (module != std::end(modules) && module->featureEnabled("hardware-sensor")) {
            HardwareSensors::getInstance().parseSensorData(hwComponents);
        }
    } catch (std::exception const& e) {
        SRPLG_LOG_WRN(getModuleLogPrefix(), "%s", ("hardware-sensors nodes failure: " + std::string(e.what())).c_str());
    }

    for (auto const& c : hwComponents) {
        c.second->setXpathForAllMembers(output, set_xpath,
            (module != std::end(modules)) && module->featureEnabled("entity-mib"));
    }

    if (!output) {
        SRPLG_LOG_ERR(getModuleLogPrefix(), "No nodes were set");
        return ErrorCode::CallbackFailed;
    }
    return ErrorCode::Ok;
}

} // namespace ietf::hw::sub::oper
