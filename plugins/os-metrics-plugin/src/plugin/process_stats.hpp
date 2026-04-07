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

#ifndef PROCESS_STATS_H
#define PROCESS_STATS_H

#include "utils/globals.h"

#include <cstring>
#include <map>
#include <optional>
#include <proc/readproc.h>
#include <sys/resource.h>
#include <tuple>

namespace metrics {

struct ProcessStats {
    using setFunction_t = const std::function<void(uint64_t,
        std::optional<libyang::DataNode>&,
        std::string const&,
        int32_t)>;

    static ProcessStats& getInstance()
    {
        static ProcessStats instance;
        return instance;
    }

    ProcessStats(ProcessStats const&) = delete;
    void operator=(ProcessStats const&) = delete;

    static setFunction_t getSetFunction(std::string const& token)
    {
        static std::unordered_map<std::string, setFunction_t> _ {
            { "syscr:",
                [](uint64_t value, std::optional<libyang::DataNode>& parent,
                    std::string const& path, int32_t tid) {
                    parent->newPath(path + "/io/read-count", std::to_string(value));
                } },
            { "syscw:",
                [](uint64_t value, std::optional<libyang::DataNode>& parent,
                    std::string const& path, int32_t tid) {
                    parent->newPath(path + "/io/write-count", std::to_string(value));
                } },
            { "read_bytes:",
                [](uint64_t value, std::optional<libyang::DataNode>& parent,
                    std::string const& path, int32_t tid) {
                    parent->newPath(path + "/io/read-kbytes", std::to_string(value / 1024));
                } },
            { "write_bytes:",
                [](uint64_t value, std::optional<libyang::DataNode>& parent,
                    std::string const& path, int32_t tid) {
                    parent->newPath(path + "/io/write-kbytes", std::to_string(value / 1024));
                } },
            { "voluntary_ctxt_switches:",
                [](uint64_t value, std::optional<libyang::DataNode>& parent,
                    std::string const& path, int32_t tid) {
                    parent->newPath(path + "/voluntary-ctx-switches", std::to_string(value));
                } },
            { "nonvoluntary_ctxt_switches:",
                [](uint64_t value, std::optional<libyang::DataNode>& parent,
                    std::string const& path, int32_t tid) {
                    parent->newPath(path + "/involuntary-ctx-switches",
                        std::to_string(value));
                } },
            { "FDSize:",
                [](uint64_t value, std::optional<libyang::DataNode>& parent,
                    std::string const& path, int32_t tid) {
                    parent->newPath(path + "/open-file-descriptors", std::to_string(value));
                    struct rlimit maxFDs;
                    if (!prlimit(tid, RLIMIT_NOFILE, nullptr, &maxFDs)) {
                        std::stringstream stream;
                        stream << std::fixed << std::setprecision(2)
                               << static_cast<double>(value) * 100.0 / static_cast<long double>(maxFDs.rlim_cur);
                        parent->newPath(path + "/open-file-descriptors-perc", stream.str());
                    }
                } }
        };
        if (_.find(token) != _.end()) {
            return _.at(token);
        }
        return nullptr;
    }

    static std::optional<size_t> getCpuTimes()
    {
        std::ifstream proc_stat("/proc/stat");
        proc_stat.ignore(5, ' '); // Skip the 'cpu' prefix.
        std::vector<size_t> cpu_times;
        for (size_t time; proc_stat >> time; cpu_times.push_back(time))
            ;
        if (cpu_times.size() < 4)
            return std::nullopt;
        return accumulate(cpu_times.begin(), cpu_times.end(), 0);
    }

    static std::optional<std::tuple<size_t, size_t>> getProcessCpuTimes(int32_t tid)
    {
        std::ifstream proc_stat("/proc/" + std::to_string(tid) + "/stat");
        proc_stat.ignore(std::numeric_limits<std::streamsize>::max(), ')')
            .ignore(2, ' ')
            .ignore(2, ' ');
        std::vector<size_t> proc_data;
        for (size_t time; proc_stat >> time; proc_data.push_back(time))
            ;
        if (proc_data.size() < 12) {
            return std::nullopt;
        }
        size_t utime = proc_data[10];
        size_t stime = proc_data[11];
        return std::make_tuple(utime, stime);
    }

    static double calculateCpuUsage(std::optional<size_t> total_time_before,
        std::optional<size_t> total_time_after,
        std::optional<std::tuple<size_t, size_t>> proc_times_before,
        std::optional<std::tuple<size_t, size_t>> proc_times_after)
    {
        if (!total_time_before || !total_time_after || !proc_times_before || !proc_times_after) {
            return 0;
        }

        auto const [utime_before, stime_before] = proc_times_before.value();
        auto const [utime_after, stime_after] = proc_times_after.value();
        auto const proc_time_delta = utime_after + stime_after - utime_before - stime_before;
        if (proc_time_delta == 0 || total_time_after.value() - total_time_before.value() == 0)
            return 0;

        return 100.0 * (static_cast<double>(proc_time_delta) / static_cast<double>(total_time_after.value() - total_time_before.value()));
    }

    double getCpuUsage(int32_t tid)
    {
        if (cached_cpu_values_.find(tid) != cached_cpu_values_.end()) {
            auto const time_total_after = getCpuTimes();
            auto const time_proc_after = getProcessCpuTimes(tid);
            auto const [utime_after, stime_after] = time_proc_after.value();

            auto const [time_total_before, utime_before, stime_before] = cached_cpu_values_[tid];
            auto const time_proc_before = std::make_tuple(utime_before, stime_before);

            cached_cpu_values_[tid] = std::make_tuple(time_total_after.value(), utime_after, stime_after);

            return calculateCpuUsage(time_total_before, time_total_after, time_proc_before,
                time_proc_after);
        } else {
            auto const time_total_before = getCpuTimes();
            auto const time_proc_before = getProcessCpuTimes(tid);
            cached_cpu_values_[tid] = std::make_tuple(time_total_before.value(), std::get<0>(time_proc_before.value()),
                std::get<1>(time_proc_before.value()));
            return 0;
        }
    }

    void readAndSet(std::optional<libyang::DataNode>& parent,
        int32_t tid,
        std::string const& procXpath,
        std::string const& what)
    {
        std::string token;
        std::ifstream file("/proc/" + std::to_string(tid) + "/" + what);
        while (file >> token) {
            auto const& func = getSetFunction(token);
            if (func) {
                uint64_t value;
                if (file >> value) {
                    func(value, parent, procXpath, tid);
                }
            }
            // ignore rest of the line
            file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    void readAndSetAll(std::optional<libyang::DataNode>& parent,
        std::string_view moduleName)
    {
        PROCTAB* proc = openproc(PROC_FILLMEM | PROC_FILLSTAT | PROC_FILLSTATUS);

        proc_t procInfo;
        memset(&procInfo, 0, sizeof(procInfo));
        std::string const baseXpath("/" + std::string(moduleName) + ":system-metrics/processes/process[pid='");
        while (readproc(proc, &procInfo) != NULL) {
            std::string const procXpath(baseXpath + std::to_string(procInfo.tid) + "']");
            // memory stats
            parent->newPath(procXpath + "/memory/real",
                std::to_string(procInfo.vm_rss - procInfo.vm_rss_shared));
            parent->newPath(procXpath + "/memory/rss", std::to_string(procInfo.vm_rss));
            parent->newPath(procXpath + "/memory/vsz", std::to_string(procInfo.vm_size));

            // io
            readAndSet(parent, procInfo.tid, procXpath, "io");
            readAndSet(parent, procInfo.tid, procXpath, "status");

            // nlwp
            parent->newPath(procXpath + "/thread-count", std::to_string(procInfo.nlwp));

            // cpu
            std::stringstream stream;
            stream << std::fixed << std::setprecision(2) << getCpuUsage(procInfo.tid);
            parent->newPath(procXpath + "/cpu", stream.str());
        }

        closeproc(proc);
    }

    /// @brief Cached cpu usage value used where sigar is not present
    /// values are total_cpu_time, proc_user_time, proc_sys_time
    std::unordered_map<int32_t, std::tuple<size_t, size_t, size_t>> cached_cpu_values_;

private:
    ProcessStats() = default;
};

} // namespace metrics

#endif // PROCESS_STATS_H
