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

#include "hardware_sensors.hpp"

#include <chrono>

#include <sysrepo.h>

namespace ietf::hw {

/**
 * @brief Return the singleton instance.
 */
HardwareSensors& HardwareSensors::getInstance()
{
    static HardwareSensors instance;
    return instance;
}

/**
 * @brief Set the connection used for sending threshold notifications.
 */
void HardwareSensors::injectConnection(Connection conn)
{
    mConn = std::make_shared<Connection>(conn);
}

HardwareSensors::HardwareSensors()
{
    if (sensors_init(nullptr) != 0) {
        throw SensorsInitFail();
    }
}

void HardwareSensors::checkAndTriggerNotification(std::string const& componentName, std::shared_ptr<SensorThreshold> sensThr, int32_t sensorValue)
{
    bool const nowAbove = sensorValue > sensThr->value;

    // notify only when the value crosses the threshold - the first poll reports the side the value is on
    if ((nowAbove && sensThr->rising) || (!nowAbove && sensThr->falling)) {
        return;
    }
    sensThr->rising = nowAbove;
    sensThr->falling = !nowAbove;

    SRPLG_LOG_INF(getModuleLogPrefix(), "%s", ("Sensor threshold triggered for: " + componentName + " value " + std::to_string(sensorValue) + ". Sending Notification...").c_str());

    std::string notifPath("/ietf-hardware:hardware/component[name='");
    notifPath += componentName + "']/sensor-notifications-augment:sensor-threshold-crossed";

    /* start session */
    if (!mConn) {
        return;
    }
    auto sess = mConn->sessionStart();

    auto input = sess.getContext().newPath((notifPath + "/threshold-name"), sensThr->name);
    input.newPath((notifPath + "/threshold-value"), std::to_string(sensThr->value));
    if (nowAbove) {
        input.newPath((notifPath + "/rising"), std::nullopt);
    } else {
        input.newPath((notifPath + "/falling"), std::nullopt);
    }

    input.newPath((notifPath + "/sensor-value"), std::to_string(sensorValue));

    sess.sendNotification(input, sysrepo::Wait::No);
}

void HardwareSensors::runFunc(std::shared_ptr<ComponentData> component)
{
    // TSAN falsely reports double lock on the mutex here for some compiler versions
    std::unique_lock<std::mutex> lk(mNotificationMtx);
    // wait with a predicate so a stop request is never missed (and a spurious wakeup does not end the thread)
    while (!mCV.wait_for(lk, std::chrono::seconds(component->pollInterval), [this] { return mStopThreads; })) {
        std::optional<int32_t> value = getValue(component->name);
        if (!value) {
            continue;
        }
        for (auto const& sensThr : component->sensorThresholds) {
            try {
                checkAndTriggerNotification(component->name, sensThr, value.value());
            } catch (std::exception& ex) {
                SRPLG_LOG_WRN(getModuleLogPrefix(), "%s", ("Sending notification failed: " + std::string(ex.what())).c_str());
            }
        }
    }
    SRPLG_LOG_DBG(getModuleLogPrefix(), "%s", ("Thread for component: " + component->name + " ended.").c_str());
}

HardwareSensors::~HardwareSensors()
{
    notifyAndJoin();
    sensors_cleanup();
}

/**
 * @brief Wake up all polling threads.
 */
void HardwareSensors::notify()
{
    mCV.notify_all();
}

/**
 * @brief Wake up and join all polling threads.
 */
void HardwareSensors::notifyAndJoin()
{
    {
        std::lock_guard lk(mNotificationMtx);
        mStopThreads = true;
    }
    mCV.notify_all();
    stopThreads();

    std::lock_guard lk(mNotificationMtx);
    mStopThreads = false;
}

/**
 * @brief Join all polling threads.
 */
void HardwareSensors::stopThreads()
{
    int32_t numThreadsStopped(0);
    for (auto& [_, thread] : mThreads) {
        if (thread.joinable()) {
            thread.join();
            numThreadsStopped++;
        }
    }
    SRPLG_LOG_DBG(getModuleLogPrefix(), "%s", (std::to_string(numThreadsStopped) + " threads stopped, out of: " + std::to_string(mThreads.size()) + " started.").c_str());
    mThreads.clear();
}

/**
 * @brief Start a polling thread for each configured component with thresholds.
 */
void HardwareSensors::startThreads()
{
    for (auto const& configData : ComponentData::hwConfigData) {
        if (configData && !configData->sensorThresholds.empty()) {
            SRPLG_LOG_DBG(getModuleLogPrefix(), "%s", ("Starting thread for component: " + configData->name + ".").c_str());
            mThreads[configData->name] = std::thread(&HardwareSensors::runFunc, this, configData);
        }
    }
}

/**
 * @brief Read the current value of a sensor.
 *
 * @param sensorName Sensor name (<chip prefix>/<feature name>).
 */
std::optional<int32_t> HardwareSensors::getValue(std::string const& sensorName)
{
    std::lock_guard lk(mSensorDataMtx);
    sensors_chip_name const* cn = nullptr;
    int c = 0;
    std::optional<int32_t> value;
    while ((cn = sensors_get_detected_chips(0, &c))) {
        sensors_feature const* feature = nullptr;
        int f = 0;
        while ((feature = sensors_get_features(cn, &f))) {
            if (sensorName != (std::string(cn->prefix) + "/" + feature->name)) {
                continue;
            }
            switch (feature->type) {
            case SENSORS_FEATURE_IN:
                value = Sensor::getValueFromSubfeature(cn, feature, SENSORS_SUBFEATURE_IN_INPUT, 3);
                break;
            case SENSORS_FEATURE_CURR:
                value = Sensor::getValueFromSubfeature(cn, feature,
                    SENSORS_SUBFEATURE_CURR_INPUT, 3);
                break;
            case SENSORS_FEATURE_TEMP:
                value = Sensor::getValueFromSubfeature(cn, feature,
                    SENSORS_SUBFEATURE_TEMP_INPUT, 0);
                break;
            case SENSORS_FEATURE_FAN:
                value = Sensor::getValueFromSubfeature(cn, feature,
                    SENSORS_SUBFEATURE_FAN_INPUT, 0);
                break;
            case SENSORS_FEATURE_POWER:
                value = Sensor::getValueFromSubfeature(cn, feature,
                    SENSORS_SUBFEATURE_POWER_INPUT, 0);
                break;
            case SENSORS_FEATURE_HUMIDITY:
                value = Sensor::getValueFromSubfeature(cn, feature,
                    SENSORS_SUBFEATURE_HUMIDITY_INPUT, 0);
                break;
            default:
                break;
            }

            if (value) {
                return value;
            }
        }
    }
    return value;
}

/**
 * @brief Add all detected sensors to the component map.
 *
 * @param hwComponents Component map.
 */
void HardwareSensors::parseSensorData(ComponentMap& hwComponents)
{
    std::lock_guard lk(mSensorDataMtx);
    sensors_chip_name const* cn = nullptr;
    int c = 0;
    while ((cn = sensors_get_detected_chips(0, &c))) {
        sensors_feature const* feature = nullptr;
        int f = 0;
        while ((feature = sensors_get_features(cn, &f))) {
            Sensor tempSensor(std::string(cn->prefix) + "/" + feature->name);
            bool result(false);
            switch (feature->type) {
            case SENSORS_FEATURE_IN:
                tempSensor.valueType = Sensor::ValueType::volts_dc;
                tempSensor.valuePrecision = 3;
                result = tempSensor.setValueFromSubfeature(
                    cn, feature, SENSORS_SUBFEATURE_IN_INPUT, tempSensor.valuePrecision);
                break;
            case SENSORS_FEATURE_CURR:
                tempSensor.valueType = Sensor::ValueType::amperes;
                tempSensor.valuePrecision = 3;
                result = tempSensor.setValueFromSubfeature(
                    cn, feature, SENSORS_SUBFEATURE_CURR_INPUT, tempSensor.valuePrecision);
                break;
            case SENSORS_FEATURE_TEMP:
                tempSensor.valueType = Sensor::ValueType::celsius;
                result = tempSensor.setValueFromSubfeature(
                    cn, feature, SENSORS_SUBFEATURE_TEMP_INPUT, tempSensor.valuePrecision);
                break;
            case SENSORS_FEATURE_FAN:
                tempSensor.valueType = Sensor::ValueType::rpm;
                result = tempSensor.setValueFromSubfeature(
                    cn, feature, SENSORS_SUBFEATURE_FAN_INPUT, tempSensor.valuePrecision);
                break;
            case SENSORS_FEATURE_POWER:
                tempSensor.valueType = Sensor::ValueType::watts;
                result = tempSensor.setValueFromSubfeature(
                    cn, feature, SENSORS_SUBFEATURE_POWER_INPUT, tempSensor.valuePrecision);
                break;
            case SENSORS_FEATURE_HUMIDITY:
                tempSensor.valueType = Sensor::ValueType::percent_rh;
                result = tempSensor.setValueFromSubfeature(
                    cn, feature, SENSORS_SUBFEATURE_HUMIDITY_INPUT, tempSensor.valuePrecision);
                break;
            default:
                tempSensor.valueType = Sensor::ValueType::other;
                break;
            }
            if (result) {
                hwComponents.emplace(std::string(tempSensor.name),
                    std::make_shared<Sensor>(tempSensor));
            }
        }
    }
    for (auto const& configData : ComponentData::hwConfigData) {
        if (configData) {
            auto const& component = hwComponents.find(configData->name);
            if (component == hwComponents.end()) {
                // configured component is not present on the system
                continue;
            }
            component->second->sensorThresholds = configData->sensorThresholds;
        }
    }
}

} // namespace ietf::hw
