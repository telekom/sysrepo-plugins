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

#include "component_data.hpp"

#include <sysrepo.h>

namespace ietf::hw {

ComponentList ComponentData::hwConfigData;

/**
 * @brief Construct a threshold with the given name.
 *
 * @param newName Threshold name.
 */
SensorThreshold::SensorThreshold(std::string_view newName)
    : name(newName)
    , value(0)
    , rising(false)
    , falling(false)
{
}

/**
 * @brief Construct a component.
 *
 * @param compName Component name.
 * @param compClass Component class identity.
 */
ComponentData::ComponentData(std::string_view compName, std::string const& compClass)
    : name(compName)
    , classType(compClass)
    , pollInterval(DEFAULT_POLL_INTERVAL)
{
}

/**
 * @brief Set all component nodes in the operational data tree.
 *
 * @param parent Operational data tree.
 * @param mainXpath XPath of the hardware container.
 * @param setPhysicalID Whether the physical-index node should be set (entity-mib feature).
 */
void ComponentData::setXpathForAllMembers(std::optional<libyang::DataNode>& parent, std::string const& mainXpath, bool setPhysicalID) const
{
    std::string componentPath(mainXpath + "/component[name='" + name + "']");
    SRPLG_LOG_DBG(getModuleLogPrefix(), "%s", ("Setting values for component: " + name).c_str());
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
    parent->newPath(componentPath + "/class", classType);

    if (description) {
        parent->newPath(componentPath + "/description", description.value());
    }
    if (physicalID && setPhysicalID) {
        parent->newPath(componentPath + "/physical-index",
            std::to_string(physicalID.value()));
    }
    if (parentName) {
        parent->newPath(componentPath + "/parent", parentName.value());
    }
    if (parent_rel_pos) {
        parent->newPath(componentPath + "/parent-rel-pos",
            std::to_string(parent_rel_pos.value()));
    }
    // childlist to value
    for (auto const& elem : children) {
        parent->newPath(componentPath + "/contains-child", elem);
    }
    if (hardwareRev) {
        parent->newPath(componentPath + "/hardware-rev", hardwareRev.value());
    }
    if (firmwareRev) {
        parent->newPath(componentPath + "/firmware-rev", firmwareRev.value());
    }
    if (softwareRev) {
        parent->newPath(componentPath + "/software-rev", softwareRev.value());
    }
    if (serial) {
        parent->newPath(componentPath + "/serial-num", serial.value());
    }
    if (mfgName) {
        parent->newPath(componentPath + "/mfg-name", mfgName.value());
    }
    if (modelName) {
        parent->newPath(componentPath + "/model-name", modelName.value());
    }
    if (alias) {
        parent->newPath(componentPath + "/alias", alias.value());
    }
    if (assetID) {
        parent->newPath(componentPath + "/asset-id", assetID.value());
    }
    // uri to value
    for (auto const& elem : uri) {
        parent->newPath(componentPath + "/uri", elem);
    }
    if (uuid) {
        parent->newPath(componentPath + "/uuid", uuid.value());
    }
}

/**
 * @brief Set a component value from its lshw node.
 *
 * @param node lshw node name.
 * @param value Node value.
 */
void ComponentData::setValueFromLSHWmap(std::string node, std::string value)
{
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

/**
 * @brief Check if a configured component matches this component (same class, parent and parent-rel-pos).
 *
 * @param component Configured component.
 *
 * @return True if the components match.
 */
bool ComponentData::checkForConfigMatch(std::shared_ptr<ComponentData> component)
{
    // We can't compare optionals w/o checking if values are present because of the following
    // supposition: lhs is considered equal to rhs if, and only if, both lhs and rhs do not
    // contain a value. Given this we can't have nodes with no 'parents' be considered equal.
    if (component->parentName && component->parent_rel_pos && parentName && parent_rel_pos) {
        return (component->classType == classType) && (component->parentName == parentName) && (component->parent_rel_pos == parent_rel_pos);
    }
    return false;
}

/**
 * @brief Replace the writable values of this component with the configured ones.
 *
 * @param component Configured component.
 */
void ComponentData::replaceWritableValues(std::shared_ptr<ComponentData> component)
{
    name = component->name;
    alias = component->alias;
    assetID = component->assetID;
    uri = component->uri;
}

/**
 * @brief Parse and set the physical index from the lshw physid.
 *
 * @param physid lshw physid value.
 */
void ComponentData::parseAndSetPhysicalID(std::string physid)
{
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
        SRPLG_LOG_WRN(getModuleLogPrefix(), "%s", (std::string("Couldn't convert physical-id: ") + e.what()).c_str());
    }
}

/**
 * @brief Load the configured components from the datastore into hwConfigData.
 *
 * @param session Session to use for retreiving datastore data.
 * @param module_name Module name.
 */
void ComponentData::populateConfigData(Session& session, std::string_view module_name)
{
    std::string const data_xpath(std::string("/") + std::string(module_name) + ":hardware");
    auto const& data(session.getData(data_xpath));
    if (!data) {
        SRPLG_LOG_ERR(getModuleLogPrefix(), "No data found for population.");
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

} // namespace ietf::hw
