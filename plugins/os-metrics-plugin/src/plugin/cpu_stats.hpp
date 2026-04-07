// telekom / sysrepo-plugin-os-metrics
//
// This program is made available under the terms of the
// BSD 3-Clause license which is available at
// https://opensource.org/licenses/BSD-3-Clause
//
// SPDX-FileCopyrightText: 2026 Deutsche Telekom AG
// SPDX-FileContributor: Sartura d.d.
//
// SPDX-License-Identifier: BSD-3-Clause

#ifndef CPU_STATS_H
#define CPU_STATS_H

#include "utils/globals.h"

#include <fstream>
#include <iomanip>
#include <numeric>
#include <optional>
#include <sstream>
#include <vector>

namespace metrics {

struct CoreStats {

    CoreStats()
        : mUser(0)
        , mNice(0)
        , mSystem(0)
        , mIdle(0)
        , mIowait(0)
        , mIrq(0)
        , mSoftirq(0)
        , mStolen(0)
        , mTotal(1) { };

    CoreStats(std::vector<size_t> const& cpu_times)
    {
        populateValues(cpu_times);
    }

    void setXpathValues(std::optional<libyang::DataNode>& parent,
        std::string_view moduleName,
        std::optional<size_t> index)
    {
        std::string basePath("/" + std::string(moduleName) + ":system-metrics/cpu-statistics");
        std::string cpuPath;
        if (index) {
            cpuPath = "/cpu[id='" + std::to_string(index.value()) + "']";
        }
        std::stringstream stream;
        stream << std::fixed << std::setprecision(2)
               << mUser / static_cast<long double>(mTotal) * 100.0;
        parent->newPath(basePath + cpuPath + "/user", stream.str());
        stream = std::stringstream();
        stream << std::fixed << std::setprecision(2)
               << mSystem / static_cast<long double>(mTotal) * 100.0;
        parent->newPath(basePath + cpuPath + "/sys", stream.str());
        stream = std::stringstream();
        stream << std::fixed << std::setprecision(2)
               << mNice / static_cast<long double>(mTotal) * 100.0;
        parent->newPath(basePath + cpuPath + "/nice", stream.str());
        stream = std::stringstream();
        stream << std::fixed << std::setprecision(2)
               << mIdle / static_cast<long double>(mTotal) * 100.0;
        parent->newPath(basePath + cpuPath + "/idle", stream.str());
        stream = std::stringstream();
        stream << std::fixed << std::setprecision(2)
               << mIowait / static_cast<long double>(mTotal) * 100.0;
        parent->newPath(basePath + cpuPath + "/wait", stream.str());
        stream = std::stringstream();
        stream << std::fixed << std::setprecision(2)
               << mIrq / static_cast<long double>(mTotal) * 100.0;
        parent->newPath(basePath + cpuPath + "/irq", stream.str());
        stream = std::stringstream();
        stream << std::fixed << std::setprecision(2)
               << mSoftirq / static_cast<long double>(mTotal) * 100.0;
        parent->newPath(basePath + cpuPath + "/softirq", stream.str());
        stream = std::stringstream();
        stream << std::fixed << std::setprecision(2)
               << mStolen / static_cast<long double>(mTotal) * 100.0;
        parent->newPath(basePath + cpuPath + "/stolen", stream.str());
    }

    void populateValues(std::vector<size_t> const& cpu_times)
    {
        mUser = cpu_times[0];
        mNice = cpu_times[1];
        mSystem = cpu_times[2];
        mIdle = cpu_times[3];
        mIowait = cpu_times[4];
        mIrq = cpu_times[5];
        mSoftirq = cpu_times[6];
        mStolen = cpu_times[7];

        mTotal = accumulate(cpu_times.begin(), cpu_times.end(), 0);
    }

protected:
    size_t mUser;
    size_t mNice;
    size_t mSystem;
    size_t mIdle;
    size_t mIowait;
    size_t mIrq;
    size_t mSoftirq;
    size_t mStolen;
    size_t mTotal;
};

struct CpuStats : public CoreStats {

    CpuStats() = default;

    CpuStats(std::vector<size_t> const& cpu_times)
        : CoreStats(cpu_times) { };

    void setXpathValues(std::optional<libyang::DataNode>& parent,
        std::string_view moduleName)
    {
        SRPLG_LOG_DBG(PLUGIN_NAME, "Setting xpath values for cpu statistics");
        CoreStats::setXpathValues(parent, moduleName, std::nullopt);
        for (size_t i = 0; i < mCoreTimes.size(); i++) {
            mCoreTimes[i].setXpathValues(parent, moduleName, i);
        }
    }

    void readCpuTimes()
    {
        std::ifstream proc_stat("/proc/stat");
        std::string line;
        std::vector<size_t> cpu_times;
        std::getline(proc_stat, line);
        std::istringstream stream(line);
        stream.ignore(5, ' '); // ignore cpu keyword
        for (size_t time; stream >> time; cpu_times.push_back(time))
            ;
        CoreStats::populateValues(cpu_times);

        std::getline(proc_stat, line);
        while (std::string(line).find("cpu") != std::string::npos) {
            stream = std::istringstream(line);
            stream.ignore(5, ' '); // ignore cpu keyword
            std::vector<size_t> core_times;
            for (size_t time; stream >> time; core_times.push_back(time))
                ;
            CpuStats coreStats(core_times);
            mCoreTimes.emplace_back(coreStats);
            std::getline(proc_stat, line);
        }
    }

    std::vector<CoreStats> mCoreTimes;
};

} // namespace metrics

#endif // CPU_STATS_H
