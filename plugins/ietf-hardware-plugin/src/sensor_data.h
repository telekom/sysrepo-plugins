// telekom / sysrepo-plugin-hardware
//
// This program is made available under the terms of the
// BSD 3-Clause license which is available at
// https://opensource.org/licenses/BSD-3-Clause
//
// SPDX-FileCopyrightText: 2021 Deutsche Telekom AG
//
// SPDX-License-Identifier: BSD-3-Clause

#ifndef SENSOR_DATA_H
#define SENSOR_DATA_H

#include <component_data.h>
#include <utils/globals.h>

#include <sensors/sensors.h>

#include <chrono>
#include <map>
#include <math.h>
#include <stdint.h>
#include <vector>

namespace hardware {

struct Sensor : public ComponentData {

    Sensor(std::string const& sensorName)
        : ComponentData(sensorName, "iana-hardware:sensor"), value(0),
          valueType(ValueType::unknown), valueScale(ValueScale::units), valuePrecision(0),
          valueTimestamp(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now())){};

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

    static std::string getValueScaleString(ValueScale inputScale) {
        static std::array<std::string, 18> _{"units",  // unused
                                             "yocto", "zepto",  "atto",  "femto", "pico", "nano",
                                             "micro", "millis", "units", "kilo",  "mega", "giga",
                                             "tera",  "peta",   "exa",   "zetta", "yotta"};
        return _[static_cast<size_t>(inputScale)];
    }

    static std::string getValueTypeString(ValueType inputType) {
        std::string returnedType;
        static std::unordered_map<ValueType, std::string> _{
            {ValueType::other, "other"},
            {ValueType::unknown, "unknown"},
            {ValueType::volts_ac, "volts-AC"},
            {ValueType::volts_dc, "volts-DC"},
            {ValueType::amperes, "amperes"},
            {ValueType::watts, "watts"},
            {ValueType::hertz, "hertz"},
            {ValueType::celsius, "celsius"},
            {ValueType::percent_rh, "percent-RH"},
            {ValueType::rpm, "rpm"},
            {ValueType::cmm, "cmm"},
            {ValueType::truth_value, "truth-value"}};
        if (_.find(inputType) != _.end()) {
            returnedType = _.at(inputType);
        }
        return returnedType;
    }

    void setXpathForAllMembers(Session& session,
                               std::optional<libyang::DataNode>& parent,
                               std::string const& mainXpath,
                               bool /*setPhysicalID = false*/) const override {
        std::string sensorPath = mainXpath + "/component[name='" + name + "']";
        logMessage(SR_LL_DBG, "Setting values for component: " + name);

        setXpath(session, parent, sensorPath + "/class", classType);
        setXpath(session, parent, sensorPath + "/sensor-data/value", std::to_string(value));
        setXpath(session, parent, sensorPath + "/sensor-data/value-type",
                 getValueTypeString(valueType));
        setXpath(session, parent, sensorPath + "/sensor-data/value-scale",
                 getValueScaleString(valueScale));
        setXpath(session, parent, sensorPath + "/sensor-data/value-precision",
                 std::to_string(valuePrecision));
        setXpath(session, parent, sensorPath + "/sensor-data/oper-status", "ok");
        if (valueScale == Sensor::ValueScale::units) {
            setXpath(session, parent, sensorPath + "/sensor-data/units-display",
                     getValueTypeString(valueType));
        } else {
            std::string const unit =
                getValueScaleString(valueScale) + " " + getValueTypeString(valueType);
            setXpath(session, parent, sensorPath + "/sensor-data/units-display", unit);
        }
        char timeString[100];
        if (std::strftime(timeString, sizeof(timeString), "%FT%TZ",
                          std::localtime(&valueTimestamp))) {
            setXpath(session, parent, sensorPath + std::string("/sensor-data/value-timestamp"),
                     timeString);
        }
        setXpath(session, parent, sensorPath + std::string("/sensor-data/value-update-rate"), "0");
        if (!sensorThresholds.empty()) {
            setXpath(
                session, parent,
                sensorPath +
                    std::string("/sensor-notifications-augment:sensor-notifications/poll-interval"),
                std::to_string(ComponentData::pollInterval));
            std::string sensorThresholdPath(
                sensorPath + "/sensor-notifications-augment:sensor-notifications/threshold[name='");
            for (auto const& sens : sensorThresholds) {
                setXpath(session, parent, sensorThresholdPath + sens->name + "']/value",
                         std::to_string(sens->value));
            }
        }
    }

    static std::optional<int32_t> getValueFromSubfeature(sensors_chip_name const* cn,
                                                         sensors_feature const* feature,
                                                         sensors_subfeature_type type,
                                                         int32_t precision) {
        double val;
        std::optional<int32_t> result;
        sensors_subfeature const* subf = sensors_get_subfeature(cn, feature, type);
        if (!subf) {
            return result;
        }
        if (subf->flags & SENSORS_MODE_R) {
            int rc = sensors_get_value(cn, subf->number, &val);
            if (rc < 0) {
                logMessage(SR_LL_WRN, std::string("Couldn't get sensor value. Error code: ") +
                                          std::to_string(rc));
            } else {
                logMessage(SR_LL_DBG, std::string("Got sensor: ") + cn->prefix + "/" +
                                          feature->name + " value " + std::to_string(val));
                result = val * std::pow(10, precision);
            }
        } else {
            logMessage(SR_LL_WRN, std::string("Couldn't read sensor: ") + cn->prefix + "/" +
                                      feature->name + "/" + subf->name);
        }

        return result;
    }

    bool setValueFromSubfeature(sensors_chip_name const* cn,
                                sensors_feature const* feature,
                                sensors_subfeature_type type,
                                int32_t precision) {
        std::optional<int32_t> val = getValueFromSubfeature(cn, feature, type, precision);
        if (!val) {
            return false;
        } else {
            value = val.value();
        }

        return true;
    }

    int32_t value;
    ValueType valueType;
    ValueScale valueScale;
    int32_t valuePrecision;
    std::time_t valueTimestamp;
};

}  // namespace hardware

#endif  // SENSOR_DATA_H
