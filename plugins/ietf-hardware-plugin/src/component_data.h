// telekom / sysrepo-plugin-hardware
//
// This program is made available under the terms of the
// BSD 3-Clause license which is available at
// https://opensource.org/licenses/BSD-3-Clause
//
// SPDX-FileCopyrightText: 2021 Deutsche Telekom AG
//
// SPDX-License-Identifier: BSD-3-Clause

#ifndef COMPONENT_DATA_H
#define COMPONENT_DATA_H

#include <stdint.h>
#include <utils/globals.h>

#include <iostream>
#include <list>
#include <memory>
#include <optional>
#include <string>
#include <unordered_map>

namespace hardware {

struct ComponentData;
struct SensorThreshold;

using ComponentMap = std::unordered_map<std::string, std::shared_ptr<ComponentData>>;
using ComponentList = std::list<std::shared_ptr<ComponentData>>;
using SensorThresholdList = std::list<std::shared_ptr<SensorThreshold>>;

struct SensorThreshold {

    SensorThreshold(std::string_view newName)
        : name(newName), value(0), rising(false), falling(false){};

    void printSensorThreshold() {
        std::cout << "(" << name << ", " << value << ", " << rising << ", " << falling << ")"
                  << std::endl;
    }

    std::string name;
    int32_t value;
    bool rising;
    bool falling;
};

struct ComponentData {

    using Session = sysrepo::Session;

    ComponentData(std::string_view compName, std::string const& compClass = "iana-hardware:unknown")
        : name(compName), classType(compClass), pollInterval(DEFAULT_POLL_INTERVAL){};

    virtual ~ComponentData() = default;

    virtual void setXpathForAllMembers(Session& session,
                                       std::optional<libyang::DataNode>& parent,
                                       std::string const& mainXpath,
                                       bool setPhysicalID = false) const {
        std::string componentPath(mainXpath + "/component[name='" + name + "']");
        logMessage(SR_LL_DBG, "Setting values for component: " + name);
        // +--rw name              string
        // +--rw class             identityref
        // +--ro physical-index?   int32 {entity-mib}?
        // +--ro description?      string
        // +--rw parent?           -> ../../component/name
        // +--rw parent-rel-pos?   int32
        // +--ro contains-child*   -> ../../component/name
        // +--ro hardware-rev?     string
        // +--ro software-rev?     string
        // +--ro firmware-rev?     string
        // +--ro serial-num?       string
        // +--ro mfg-name?         string
        // +--ro model-name?       string
        // +--rw alias?            string
        // +--rw asset-id?         string
        // +--rw uri*              inet:uri
        // +--ro uuid?             yang:uuid
        setXpath(session, parent, componentPath + "/class", classType);

        if (description) {
            setXpath(session, parent, componentPath + "/description", description.value());
        }
        if (physicalID && setPhysicalID) {
            setXpath(session, parent, componentPath + "/physical-index",
                     std::to_string(physicalID.value()));
        }
        if (parentName) {
            setXpath(session, parent, componentPath + "/parent", parentName.value());
        }
        if (parent_rel_pos) {
            setXpath(session, parent, componentPath + "/parent-rel-pos",
                     std::to_string(parent_rel_pos.value()));
        }
        // childlist to value
        for (auto const& elem : children) {
            setXpath(session, parent, componentPath + "/contains-child", elem);
        }
        if (hardwareRev) {
            setXpath(session, parent, componentPath + "/hardware-rev", hardwareRev.value());
        }
        if (firmwareRev) {
            setXpath(session, parent, componentPath + "/firmware-rev", firmwareRev.value());
        }
        if (softwareRev) {
            setXpath(session, parent, componentPath + "/software-rev", softwareRev.value());
        }
        if (serial) {
            setXpath(session, parent, componentPath + "/serial-num", serial.value());
        }
        if (mfgName) {
            setXpath(session, parent, componentPath + "/mfg-name", mfgName.value());
        }
        if (modelName) {
            setXpath(session, parent, componentPath + "/model-name", modelName.value());
        }
        if (alias) {
            setXpath(session, parent, componentPath + "/alias", alias.value());
        }
        if (assetID) {
            setXpath(session, parent, componentPath + "/asset-id", assetID.value());
        }
        // uri to value
        for (auto const& elem : uri) {
            setXpath(session, parent, componentPath + "/uri", elem);
        }
        if (uuid) {
            setXpath(session, parent, componentPath + "/uuid", uuid.value());
        }
    }

    void setValueFromLSHWmap(std::string node, std::string value) {
        if (node == "description") {
            description = value;
        } else if (node == "serial") {
            serial = value;
        } else if (node == "version") {
            hardwareRev = value;
        } else if (node == "vendor") {
            mfgName = value;
        } else if (node == "product") {
            modelName = value;
        } else if (node == "handle") {
            alias = value;
        }
    }

    void printExistingData() const {
        std::cout << "Name: " << name << std::endl;
        std::cout << "Class: " << classType << std::endl;
        if (physicalID) {
            std::cout << "Physid: " << physicalID.value() << std::endl;
        }
        if (description) {
            std::cout << "description: " << description.value() << std::endl;
        }
        if (parentName) {
            std::cout << "parent: " << parentName.value() << std::endl;
        }
        if (parent_rel_pos) {
            std::cout << "parent_rel_pos: " << parent_rel_pos.value() << std::endl;
        }
        if (hardwareRev) {
            std::cout << "hardwareRev: " << hardwareRev.value() << std::endl;
        }
        if (firmwareRev) {
            std::cout << "firmwareRev: " << firmwareRev.value() << std::endl;
        }
        if (softwareRev) {
            std::cout << "softwareRev: " << softwareRev.value() << std::endl;
        }
        if (serial) {
            std::cout << "serial: " << serial.value() << std::endl;
        }
        if (mfgName) {
            std::cout << "mfgName: " << mfgName.value() << std::endl;
        }
        if (modelName) {
            std::cout << "modelName: " << modelName.value() << std::endl;
        }
        if (alias) {
            std::cout << "alias: " << alias.value() << std::endl;
        }
        if (assetID) {
            std::cout << "assetID: " << assetID.value() << std::endl;
        }
        if (uuid) {
            std::cout << "uuid: " << uuid.value() << std::endl;
        }
        if (!sensorThresholds.empty()) {
            std::cout << "sensor thresholds: " << std::endl;
        }
        for (auto const& c : sensorThresholds) {
            std::cout << "\t";
            c->printSensorThreshold();
        }
        if (!uri.empty()) {
            std::cout << "uri: ";
        }
        for (auto const& c : uri) {
            std::cout << c << ", ";
        }
        if (!uri.empty()) {
            std::cout << std::endl;
        }
        if (!children.empty()) {
            std::cout << std::endl << "children: ";
        }
        for (auto const& c : children) {
            std::cout << c << ", ";
        }
        if (!children.empty()) {
            std::cout << std::endl;
        }
        std::cout << "pollinterval: " << pollInterval << std::endl;
        std::cout << std::endl;
    }

    bool checkForConfigMatch(std::shared_ptr<ComponentData> component) {
        // We can't compare optionals w/o checking if values are present because of the following
        // supposition: lhs is considered equal to rhs if, and only if, both lhs and rhs do not
        // contain a value. Given this we can't have nodes with no 'parents' be considered equal.
        if (component->parentName && component->parent_rel_pos && parentName && parent_rel_pos) {
            return (component->classType == classType) && (component->parentName == parentName) &&
                   (component->parent_rel_pos == parent_rel_pos);
        }
        return false;
    }

    void replaceWritableValues(std::shared_ptr<ComponentData> component) {
        name = component->name;
        alias = component->alias;
        assetID = component->assetID;
        uri = component->uri;
    }

    void parseAndSetPhysicalID(std::string physid) {
        size_t foundPos = physid.find('.');
        if (foundPos != std::string::npos) {
            physid = physid.substr(foundPos + 1, physid.length());
        }
        try {
            physicalID = std::stoi(physid, nullptr, 16);
            if (physicalID < 1) {
                physicalID = std::nullopt;
            }
        } catch (std::exception const& e) {
            logMessage(SR_LL_WRN, std::string("Couldn't convert physical-id: ") + e.what());
        }
    }

    static void populateConfigData(Session& session, std::string_view module_name) {
        std::string const data_xpath(std::string("/") + std::string(module_name) + ":hardware");
        auto const& data(session.getData(data_xpath));
        if (!data) {
            logMessage(SR_LL_ERR, "No data found for population.");
            return;
        }
        std::shared_ptr<ComponentData> component;
        std::shared_ptr<SensorThreshold> sensThreshold;
        bool isSensorNotification(false);

        hwConfigData.clear();
        for (libyang::DataNode const& node : data.value().childrenDfs()) {
            libyang::SchemaNode schema = node.schema();
            switch (schema.nodeType()) {
            case libyang::NodeType::List: {
                if (std::string(schema.name()) == "threshold") {
                    isSensorNotification = true;
                } else {
                    isSensorNotification = false;
                }
                break;
            }
            case libyang::NodeType::Leaf: {
                if (isSensorNotification) {
                    if (schema.asLeaf().isKey() && component) {
                        sensThreshold = std::make_shared<SensorThreshold>(node.asTerm().valueStr());
                        component->sensorThresholds.push_back(sensThreshold);
                    } else if (component && sensThreshold) {
                        if (std::string(schema.name()) == "value") {
                            sensThreshold->value = std::get<int32_t>(node.asTerm().value());
                        }
                    }
                } else {
                    if (schema.asLeaf().isKey()) {
                        component = std::make_shared<ComponentData>(node.asTerm().valueStr());
                        hwConfigData.push_back(component);
                    } else if (component) {
                        if (std::string(schema.name()) == "class") {
                            component->classType = node.asTerm().valueStr();
                        } else if (std::string(schema.name()) == "parent") {
                            component->parentName = node.asTerm().valueStr();
                        } else if (std::string(schema.name()) == "parent-rel-pos") {
                            component->parent_rel_pos = std::get<int32_t>(node.asTerm().value());
                        } else if (std::string(schema.name()) == "alias") {
                            component->alias = node.asTerm().valueStr();
                        } else if (std::string(schema.name()) == "asset-id") {
                            component->assetID = node.asTerm().valueStr();
                        }
                    }
                }
                if (std::string(schema.name()) == "poll-interval" && component) {
                    component->pollInterval = std::get<uint32_t>(node.asTerm().value());
                }
                break;
            }
            case libyang::NodeType::Leaflist: {
                if (!isSensorNotification && component && std::string(schema.name()) == "uri") {
                    component->uri.emplace_back(node.asTerm().valueStr());
                }
                break;
            }
            default:
                break;
            }
        }
    }

    std::string name;
    std::string classType;

    std::optional<int32_t> physicalID;
    std::optional<std::string> description;
    std::optional<std::string> parentName;
    std::optional<int32_t> parent_rel_pos;
    std::list<std::string> children;
    std::optional<std::string> hardwareRev;
    std::optional<std::string> firmwareRev;
    std::optional<std::string> softwareRev;
    std::optional<std::string> serial;
    std::optional<std::string> mfgName;
    std::optional<std::string> modelName;
    std::optional<std::string> alias;
    std::optional<std::string> assetID;
    std::optional<std::string> uuid;
    std::list<std::string> uri;
    SensorThresholdList sensorThresholds;
    uint32_t pollInterval;

    static ComponentList hwConfigData;
};

ComponentList ComponentData::hwConfigData;

}  // namespace hardware

#endif  // COMPONENT_DATA_H
