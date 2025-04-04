// telekom / sysrepo-plugin-hardware
//
// This program is made available under the terms of the
// BSD 3-Clause license which is available at
// https://opensource.org/licenses/BSD-3-Clause
//
// SPDX-FileCopyrightText: 2021 Deutsche Telekom AG
//
// SPDX-License-Identifier: BSD-3-Clause

#ifndef HARDWARE_SENSORS_H
#define HARDWARE_SENSORS_H

#include <sensor_data.h>
#include <utils/globals.h>

#include <chrono>
#include <condition_variable>
#include <mutex>
#include <sysrepo-cpp/Connection.hpp>
#include <thread>

namespace hardware {

struct HardwareSensors {

    using Connection = sysrepo::Connection;

    static HardwareSensors& getInstance() {
        static HardwareSensors instance;
        return instance;
    }

    void injectConnection(Connection conn) {
        mConn = std::make_shared<Connection>(conn);
    }

private:
    HardwareSensors() {
        if (sensors_init(nullptr) != 0) {
            throw SensorsInitFail();
        }
    }

    void checkAndTriggerNotification(std::string const& componentName,
                                     std::shared_ptr<SensorThreshold> sensThr,
                                     int32_t sensorValue) {
        logMessage(SR_LL_INF, "Sensor threshold triggered for: " + componentName + " value " +
                                  std::to_string(sensorValue) + ". Sending Notification...");

        std::string notifPath("/ietf-hardware:hardware/component[name='");
        notifPath += componentName + "']/sensor-notifications-augment:sensor-threshold-crossed";

        /* start session */
        if (!mConn) {
            return;
        }
        auto sess = mConn->sessionStart();

        auto input = sess.getContext().newPath((notifPath + "/threshold-name"), sensThr->name);
        input.newPath((notifPath + "/threshold-value"), std::to_string(sensThr->value));
        if (sensorValue > sensThr->value) {
            input.newPath((notifPath + "/rising"), std::nullopt);
        } else {
            input.newPath((notifPath + "/falling"), std::nullopt);
        }

        input.newPath((notifPath + "/sensor-value"), std::to_string(sensorValue));

        sess.sendNotification(input, sysrepo::Wait::No);
    }

    void runFunc(std::shared_ptr<ComponentData> component) {
        // TSAN falsely reports double lock on the mutex here for some compiler versions
        std::unique_lock<std::mutex> lk(mNotificationMtx);
        while (mCV.wait_for(lk, std::chrono::seconds(component->pollInterval)) ==
               std::cv_status::timeout) {
            std::optional<int32_t> value = getValue(component->name);
            if (!value) {
                continue;
            }
            for (auto const& sensThr : component->sensorThresholds) {
                try {
                    checkAndTriggerNotification(component->name, sensThr, value.value());
                } catch (std::exception& ex) {
                    logMessage(SR_LL_WRN, "Sending notification failed: " + std::string(ex.what()));
                }
            }
        }
        logMessage(SR_LL_DBG, "Thread for component: " + component->name + " ended.");
    }

public:
    HardwareSensors(HardwareSensors const&) = delete;
    void operator=(HardwareSensors const&) = delete;

    ~HardwareSensors() {
        notifyAndJoin();
        sensors_cleanup();
    }

    void notify() {
        mCV.notify_all();
    }

    void notifyAndJoin() {
        mCV.notify_all();
        stopThreads();
    }

    void stopThreads() {
        int32_t numThreadsStopped(0);
        for (auto& [_, thread] : mThreads) {
            if (thread.joinable()) {
                thread.join();
                numThreadsStopped++;
            }
        }
        logMessage(SR_LL_DBG, std::to_string(numThreadsStopped) + " threads stopped, out of: " +
                                  std::to_string(mThreads.size()) + " started.");
        mThreads.clear();
    }

    void startThreads() {
        for (auto const& configData : ComponentData::hwConfigData) {
            if (configData && !configData->sensorThresholds.empty()) {
                logMessage(SR_LL_DBG, "Starting thread for component: " + configData->name + ".");
                mThreads[configData->name] =
                    std::thread(&HardwareSensors::runFunc, this, configData);
            }
        }
    }

    std::optional<int32_t> getValue(std::string const& sensorName) {
        std::lock_guard lk(mSensorDataMtx);
        sensors_chip_name const* cn = nullptr;
        int c = 0;
        std::optional<int32_t> value;
        while ((cn = sensors_get_detected_chips(0, &c))) {
            sensors_feature const* feature = nullptr;
            int f = 0;
            while ((feature = sensors_get_features(cn, &f))) {
                if (sensorName != (std::string(cn->prefix) + "/" + feature->name)) {
                    break;
                }
                switch (feature->type) {
                case SENSORS_FEATURE_IN:
                    value =
                        Sensor::getValueFromSubfeature(cn, feature, SENSORS_SUBFEATURE_IN_INPUT, 3);
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

    void parseSensorData(ComponentMap& hwComponents) {
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
                component->second->sensorThresholds = configData->sensorThresholds;
            }
        }
    }

private:
    std::shared_ptr<Connection> mConn;
    std::mutex mNotificationMtx;
    std::condition_variable mCV;
    std::mutex mSensorDataMtx;
    std::unordered_map<std::string, std::thread> mThreads;
};

}  // namespace hardware

#endif  // HARDWARE_SENSORS_H
