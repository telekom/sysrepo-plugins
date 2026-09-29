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

#pragma once

#include "../common.hpp"

#include <cstdint>
#include <list>
#include <memory>
#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>

#include <libyang-cpp/DataNode.hpp>
#include <sysrepo-cpp/Session.hpp>

namespace ietf::hw {

struct ComponentData;
struct SensorThreshold;

using ComponentMap = std::unordered_map<std::string, std::shared_ptr<ComponentData>>;
using ComponentList = std::list<std::shared_ptr<ComponentData>>;
using SensorThresholdList = std::list<std::shared_ptr<SensorThreshold>>;

/**
 * @brief Sensor threshold configured through the sensor-notifications-augment module.
 */
struct SensorThreshold {
    /**
     * @brief Construct a threshold with the given name.
     *
     * @param newName Threshold name.
     */
    SensorThreshold(std::string_view newName);

    std::string name;
    int32_t value;
    bool rising; ///< Last reported value was above the threshold.
    bool falling; ///< Last reported value was below or equal to the threshold.
};

/**
 * @brief Hardware component data, used for both the operational (lshw) and the configuration data.
 */
struct ComponentData {
    using Session = sysrepo::Session;

    /**
     * @brief Construct a component.
     *
     * @param compName Component name.
     * @param compClass Component class identity.
     */
    ComponentData(std::string_view compName, std::string const& compClass = "iana-hardware:unknown");

    virtual ~ComponentData() = default;

    /**
     * @brief Set all component nodes in the operational data tree.
     *
     * @param parent Operational data tree.
     * @param mainXpath XPath of the hardware container.
     * @param setPhysicalID Whether the physical-index node should be set (entity-mib feature).
     */
    virtual void setXpathForAllMembers(std::optional<libyang::DataNode>& parent, std::string const& mainXpath, bool setPhysicalID = false) const;

    /**
     * @brief Set a component value from its lshw node.
     *
     * @param node lshw node name.
     * @param value Node value.
     */
    void setValueFromLSHWmap(std::string node, std::string value);

    /**
     * @brief Check if a configured component matches this component (same class, parent and parent-rel-pos).
     *
     * @param component Configured component.
     *
     * @return True if the components match.
     */
    bool checkForConfigMatch(std::shared_ptr<ComponentData> component);

    /**
     * @brief Replace the writable values of this component with the configured ones.
     *
     * @param component Configured component.
     */
    void replaceWritableValues(std::shared_ptr<ComponentData> component);

    /**
     * @brief Parse and set the physical index from the lshw physid.
     *
     * @param physid lshw physid value.
     */
    void parseAndSetPhysicalID(std::string physid);

    /**
     * @brief Load the configured components from the datastore into hwConfigData.
     *
     * @param session Session to use for retreiving datastore data.
     * @param module_name Module name.
     */
    static void populateConfigData(Session& session, std::string_view module_name);

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

    static ComponentList hwConfigData; ///< Components loaded from the running datastore.
};

} // namespace ietf::hw
