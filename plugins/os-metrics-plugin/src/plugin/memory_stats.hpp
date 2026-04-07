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

#ifndef MEMORY_STATS_H
#define MEMORY_STATS_H

#include "utils/globals.h"

#include <fstream>
#include <functional>
#include <iomanip>
#include <map>
#include <mutex>
#include <numeric>
#include <sstream>

namespace metrics {

struct MemoryStats {

    static MemoryStats& getInstance()
    {
        static MemoryStats instance;
        return instance;
    }

    MemoryStats(MemoryStats const&) = delete;
    void operator=(MemoryStats const&) = delete;

    void setXpathValues(std::optional<libyang::DataNode>& parent,
        std::string_view moduleName)
    {
        std::lock_guard lk(mMtx);
        SRPLG_LOG_DBG(PLUGIN_NAME, "Setting xpath values for memory statistics");
        std::string memoryPath("/" + std::string(moduleName) + ":system-metrics/memory/statistics/");
        parent->newPath(memoryPath + "free", std::to_string(mFree / 1024ULL));
        parent->newPath(memoryPath + "swap-free-mb", std::to_string(mSwapFree / 1024ULL));
        parent->newPath(memoryPath + "swap-total", std::to_string(mSwapTotal / 1024ULL));
        parent->newPath(memoryPath + "swap-used", std::to_string(mSwapUsed / 1024ULL));
        parent->newPath(memoryPath + "total", std::to_string(mTotal / 1024ULL));
        parent->newPath(memoryPath + "usable-mb", std::to_string(mUsable / 1024ULL));
        parent->newPath(memoryPath + "used-buffers",
            std::to_string(mUsedBuffers / 1024ULL));
        parent->newPath(memoryPath + "used-cached",
            std::to_string(mUsedCached / 1024ULL));
        parent->newPath(memoryPath + "used-shared",
            std::to_string(mUsedShared / 1024ULL));
        parent->newPath(memoryPath + "hugepages-total", std::to_string(mHugePagesTotal));
        parent->newPath(memoryPath + "hugepages-free", std::to_string(mHugePagesFree));
        parent->newPath(memoryPath + "hugepage-size", std::to_string(mHugePageSize));

        if (mTotal != 0) {
            long double usable = mUsable / static_cast<long double>(mTotal) * 100.0;
            std::stringstream stream;
            stream << std::fixed << std::setprecision(2) << usable;
            parent->newPath(memoryPath + "usable-perc", stream.str());
        }
        if (mSwapTotal != 0) {
            long double swapFree = mSwapFree / static_cast<long double>(mSwapTotal) * 100.0;
            std::stringstream stream;
            stream << std::fixed << std::setprecision(2) << swapFree;
            parent->newPath(memoryPath + "swap-free-perc", stream.str());
        }
    }

    void readMemoryStats()
    {
        std::lock_guard lk(mMtx);
        std::string token;
        std::ifstream file("/proc/meminfo");
        while (file >> token) {
            auto const& itr = assignMap.find(token);
            if (itr != assignMap.end()) {
                uint64_t mem;
                if (file >> mem) {
                    assignMap[token](mem);
                }
            }
            // ignore rest of the line
            file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        mSwapUsed = mSwapTotal - mSwapFree;
    }

    long double getUsage()
    {
        readMemoryStats();
        std::lock_guard lk(mMtx);
        return 100.0 - (mUsable / static_cast<long double>(mTotal) * 100.0);
    }

private:
    MemoryStats()
        : mFree(0)
        , mSwapFree(0)
        , mSwapTotal(0)
        , mSwapUsed(0)
        , mTotal(0)
        , mUsable(0)
        , mUsedBuffers(0)
        , mUsedCached(0)
        , mUsedShared(0)
        , mHugePagesTotal(0)
        , mHugePagesFree(0)
        , mHugePageSize(0)
    {
        assignMap = { { "MemTotal:", [this](uint64_t value) { mTotal = value; } },
            { "MemFree:", [this](uint64_t value) { mFree = value; } },
            { "MemAvailable:", [this](uint64_t value) { mUsable = value; } },
            { "SwapTotal:", [this](uint64_t value) { mSwapTotal = value; } },
            { "SwapFree:", [this](uint64_t value) { mSwapFree = value; } },
            { "Shmem:", [this](uint64_t value) { mUsedShared = value; } },
            { "Cached:", [this](uint64_t value) { mUsedCached = value; } },
            { "Buffers:", [this](uint64_t value) { mUsedBuffers = value; } },
            { "HugePages_Total:", [this](uint64_t value) { mHugePagesTotal = value; } },
            { "HugePages_Free:", [this](uint64_t value) { mHugePagesFree = value; } },
            { "Hugepagesize:", [this](uint64_t value) { mHugePageSize = value; } } };
    }

    std::unordered_map<std::string, std::function<void(uint64_t)>> assignMap;
    std::mutex mMtx;

public:
    uint64_t mFree;
    uint64_t mSwapFree;
    uint64_t mSwapTotal;
    uint64_t mSwapUsed;
    uint64_t mTotal;
    uint64_t mUsable;
    uint64_t mUsedBuffers;
    uint64_t mUsedCached;
    uint64_t mUsedShared;
    uint64_t mHugePagesTotal;
    uint64_t mHugePagesFree;
    uint64_t mHugePageSize;
};

} // namespace metrics

#endif // MEMORY_STATS_H
