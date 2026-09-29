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

#include "sensor_data.hpp"

#include <array>
#include <chrono>
#include <cmath>
#include <unordered_map>

#include <sysrepo.h>

namespace ietf::hw {

/**
 * @brief Construct a sensor.
 *
 * @param sensorName Sensor name (<chip prefix>/<feature name>).
 */
Sensor::Sensor(std::string const& sensorName)
    : ComponentData(sensorName, "iana-hardware:sensor")
    , value(0)
    , valueType(ValueType::unknown)
    , valueScale(ValueScale::units)
    , valuePrecision(0)
    , valueTimestamp(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()))
{
}

/**
 * @brief Get the YANG value-scale enum string.
 */
std::string Sensor::getValueScaleString(ValueScale inputScale)
{
    static std::array<std::string, 18> _ { "units", // unused
        "yocto", "zepto", "atto", "femto", "pico", "nano",
        "micro", "milli", "units", "kilo", "mega", "giga",
        "tera", "peta", "exa", "zetta", "yotta" };
    return _[static_cast<size_t>(inputScale)];
}

/**
 * @brief Get the YANG value-type enum string.
 */
std::string Sensor::getValueTypeString(ValueType inputType)
{
    std::string returnedType;
    static std::unordered_map<ValueType, std::string> _ {
        { ValueType::other, "other" },
        { ValueType::unknown, "unknown" },
        { ValueType::volts_ac, "volts-AC" },
        { ValueType::volts_dc, "volts-DC" },
        { ValueType::amperes, "amperes" },
        { ValueType::watts, "watts" },
        { ValueType::hertz, "hertz" },
        { ValueType::celsius, "celsius" },
        { ValueType::percent_rh, "percent-RH" },
        { ValueType::rpm, "rpm" },
        { ValueType::cmm, "cmm" },
        { ValueType::truth_value, "truth-value" }
    };
    if (_.find(inputType) != _.end()) {
        returnedType = _.at(inputType);
    }
    return returnedType;
}

/**
 * @brief Set all sensor nodes in the operational data tree.
 *
 * @param parent Operational data tree.
 * @param mainXpath XPath of the hardware container.
 */
void Sensor::setXpathForAllMembers(std::optional<libyang::DataNode>& parent, std::string const& mainXpath, bool /*setPhysicalID*/) const
{
    std::string sensorPath = mainXpath + "/component[name='" + name + "']";
    SRPLG_LOG_DBG(getModuleLogPrefix(), "%s", ("Setting values for component: " + name).c_str());

    parent->newPath(sensorPath + "/class", classType);
    parent->newPath(sensorPath + "/sensor-data/value", std::to_string(value));
    parent->newPath(sensorPath + "/sensor-data/value-type",
        getValueTypeString(valueType));
    parent->newPath(sensorPath + "/sensor-data/value-scale",
        getValueScaleString(valueScale));
    parent->newPath(sensorPath + "/sensor-data/value-precision",
        std::to_string(valuePrecision));
    parent->newPath(sensorPath + "/sensor-data/oper-status", "ok");
    if (valueScale == Sensor::ValueScale::units) {
        parent->newPath(sensorPath + "/sensor-data/units-display",
            getValueTypeString(valueType));
    } else {
        std::string const unit = getValueScaleString(valueScale) + " " + getValueTypeString(valueType);
        parent->newPath(sensorPath + "/sensor-data/units-display", unit);
    }
    // date-and-time with a "Z" suffix has to be UTC
    std::tm utcTime {};
    char timeString[100];
    if (gmtime_r(&valueTimestamp, &utcTime) && std::strftime(timeString, sizeof(timeString), "%FT%TZ", &utcTime)) {
        parent->newPath(sensorPath + std::string("/sensor-data/value-timestamp"),
            timeString);
    }
    parent->newPath(sensorPath + std::string("/sensor-data/value-update-rate"), "0");
    if (!sensorThresholds.empty()) {
        parent->newPath(
            sensorPath + std::string("/sensor-notifications-augment:sensor-notifications/poll-interval"),
            std::to_string(ComponentData::pollInterval));
        std::string sensorThresholdPath(
            sensorPath + "/sensor-notifications-augment:sensor-notifications/threshold[name='");
        for (auto const& sens : sensorThresholds) {
            parent->newPath(sensorThresholdPath + sens->name + "']/value",
                std::to_string(sens->value));
        }
    }
}

/**
 * @brief Read a sensor subfeature value, scaled by 10^precision.
 *
 * @return Value or std::nullopt if the value could not be read.
 */
std::optional<int32_t> Sensor::getValueFromSubfeature(sensors_chip_name const* cn, sensors_feature const* feature, sensors_subfeature_type type, int32_t precision)
{
    double val;
    std::optional<int32_t> result;
    sensors_subfeature const* subf = sensors_get_subfeature(cn, feature, type);
    if (!subf) {
        return result;
    }
    if (subf->flags & SENSORS_MODE_R) {
        int rc = sensors_get_value(cn, subf->number, &val);
        if (rc < 0) {
            SRPLG_LOG_WRN(getModuleLogPrefix(), "%s", (std::string("Couldn't get sensor value. Error code: ") + std::to_string(rc)).c_str());
        } else {
            SRPLG_LOG_DBG(getModuleLogPrefix(), "%s", (std::string("Got sensor: ") + cn->prefix + "/" + feature->name + " value " + std::to_string(val)).c_str());
            result = val * std::pow(10, precision);
        }
    } else {
        SRPLG_LOG_WRN(getModuleLogPrefix(), "%s", (std::string("Couldn't read sensor: ") + cn->prefix + "/" + feature->name + "/" + subf->name).c_str());
    }

    return result;
}

/**
 * @brief Read a sensor subfeature value into this sensor.
 *
 * @return True if the value was read.
 */
bool Sensor::setValueFromSubfeature(sensors_chip_name const* cn, sensors_feature const* feature, sensors_subfeature_type type, int32_t precision)
{
    std::optional<int32_t> val = getValueFromSubfeature(cn, feature, type, precision);
    if (!val) {
        return false;
    } else {
        value = val.value();
    }

    return true;
}

} // namespace ietf::hw
