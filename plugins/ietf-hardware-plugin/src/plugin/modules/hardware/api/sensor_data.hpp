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

#include "component_data.hpp"

#include <sensors/sensors.h>

#include <ctime>
#include <string>

namespace ietf::hw {

/**
 * @brief Sensor component (ietf-hardware sensor-data) read using libsensors.
 */
struct Sensor : public ComponentData {
    /**
     * @brief Construct a sensor.
     *
     * @param sensorName Sensor name (<chip prefix>/<feature name>).
     */
    Sensor(std::string const& sensorName);

    enum class ValueType {
        other = 1,
        unknown = 2,
        volts_ac = 3,
        volts_dc = 4,
        amperes = 5,
        watts = 6,
        hertz = 7,
        celsius = 8,
        percent_rh = 9,
        rpm = 10,
        cmm = 11,
        truth_value = 12
    };

    enum class ValueScale {
        yocto = 1,
        zepto = 2,
        atto = 3,
        femto = 4,
        pico = 5,
        nano = 6,
        micro = 7,
        milli = 8,
        units = 9,
        kilo = 10,
        mega = 11,
        giga = 12,
        tera = 13,
        peta = 14,
        exa = 15,
        zetta = 16,
        yotta = 17
    };

    /**
     * @brief Get the YANG value-scale enum string.
     */
    static std::string getValueScaleString(ValueScale inputScale);

    /**
     * @brief Get the YANG value-type enum string.
     */
    static std::string getValueTypeString(ValueType inputType);

    /**
     * @brief Set all sensor nodes in the operational data tree.
     *
     * @param parent Operational data tree.
     * @param mainXpath XPath of the hardware container.
     */
    void setXpathForAllMembers(std::optional<libyang::DataNode>& parent, std::string const& mainXpath, bool setPhysicalID = false) const override;

    /**
     * @brief Read a sensor subfeature value, scaled by 10^precision.
     *
     * @return Value or std::nullopt if the value could not be read.
     */
    static std::optional<int32_t> getValueFromSubfeature(sensors_chip_name const* cn, sensors_feature const* feature, sensors_subfeature_type type, int32_t precision);

    /**
     * @brief Read a sensor subfeature value into this sensor.
     *
     * @return True if the value was read.
     */
    bool setValueFromSubfeature(sensors_chip_name const* cn, sensors_feature const* feature, sensors_subfeature_type type, int32_t precision);

    int32_t value;
    ValueType valueType;
    ValueScale valueScale;
    int32_t valuePrecision;
    std::time_t valueTimestamp;
};

} // namespace ietf::hw
