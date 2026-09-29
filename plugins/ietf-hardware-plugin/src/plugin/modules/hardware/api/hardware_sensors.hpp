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

#include "sensor_data.hpp"

#include <condition_variable>
#include <exception>
#include <memory>
#include <mutex>
#include <optional>
#include <string>
#include <thread>
#include <unordered_map>

#include <sysrepo-cpp/Connection.hpp>

namespace ietf::hw {

/**
 * @brief Thrown when libsensors cannot be initialized.
 */
struct SensorsInitFail : public std::exception {
    const char* what() const throw() override
    {
        return "sensor_init() failure";
    }
};

/**
 * @brief libsensors access and per-component threshold polling threads. Singleton.
 */
struct HardwareSensors {
    using Connection = sysrepo::Connection;

    /**
     * @brief Return the singleton instance.
     */
    static HardwareSensors& getInstance();

    /**
     * @brief Set the connection used for sending threshold notifications.
     */
    void injectConnection(Connection conn);

private:
    HardwareSensors();

    void checkAndTriggerNotification(std::string const& componentName, std::shared_ptr<SensorThreshold> sensThr, int32_t sensorValue);

    void runFunc(std::shared_ptr<ComponentData> component);

public:
    HardwareSensors(HardwareSensors const&) = delete;
    void operator=(HardwareSensors const&) = delete;

    ~HardwareSensors();

    /**
     * @brief Wake up all polling threads.
     */
    void notify();

    /**
     * @brief Wake up and join all polling threads.
     */
    void notifyAndJoin();

    /**
     * @brief Join all polling threads.
     */
    void stopThreads();

    /**
     * @brief Start a polling thread for each configured component with thresholds.
     */
    void startThreads();

    /**
     * @brief Read the current value of a sensor.
     *
     * @param sensorName Sensor name (<chip prefix>/<feature name>).
     */
    std::optional<int32_t> getValue(std::string const& sensorName);

    /**
     * @brief Add all detected sensors to the component map.
     *
     * @param hwComponents Component map.
     */
    void parseSensorData(ComponentMap& hwComponents);

private:
    std::shared_ptr<Connection> mConn;
    std::mutex mNotificationMtx;
    std::condition_variable mCV;
    std::mutex mSensorDataMtx;
    std::unordered_map<std::string, std::thread> mThreads;
};

} // namespace ietf::hw
