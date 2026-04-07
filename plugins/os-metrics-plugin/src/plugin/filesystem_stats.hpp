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

#ifndef FILESYSTEM_STATS_H
#define FILESYSTEM_STATS_H

#include "utils/globals.h"

#include <fstream>
#include <iomanip>
#include <mutex>
#include <numeric>
#include <sstream>
#include <sys/statvfs.h>

namespace metrics {

struct Filesystem {

    void printValues() const
    {
        std::cout << "name: " << name << std::endl;
        std::cout << "mountPoint: " << mountPoint << std::endl;
        std::cout << "type: " << type << std::endl;
        std::cout << "totalBlocks: " << totalBlocks << std::endl;
        std::cout << "usedBlocks: " << usedBlocks << std::endl;
        std::cout << "availableBlocks: " << availableBlocks << std::endl;
        std::cout << "blocksize: " << blocksize << std::endl;
        std::cout << "inodeUsed: " << inodeUsed << std::endl;
        std::cout << "spaceUsed: " << spaceUsed << std::endl;
    }

    void setXpathValues(sysrepo::Session session,
        std::optional<libyang::DataNode>& parent,
        std::string_view moduleName) const
    {
        std::string filesystemPath("/" + std::string(moduleName) + ":system-metrics/filesystems/filesystem[mount-point='" + mountPoint + "']/statistics/");
        setXpath(session, parent, filesystemPath + "name", name);
        setXpath(session, parent, filesystemPath + "type", type);
        setXpath(session, parent, filesystemPath + "total-blocks", std::to_string(totalBlocks));
        setXpath(session, parent, filesystemPath + "used-blocks", std::to_string(usedBlocks));
        setXpath(session, parent, filesystemPath + "avail-blocks", std::to_string(availableBlocks));
        setXpath(session, parent, filesystemPath + "blocksize", std::to_string(blocksize));

        {
            std::stringstream stream;
            stream << std::fixed << std::setprecision(2) << spaceUsed;
            setXpath(session, parent, filesystemPath + "space-used", stream.str());
        }
        {
            std::stringstream stream;
            stream << std::fixed << std::setprecision(2) << inodeUsed;
            setXpath(session, parent, filesystemPath + "inode-used", stream.str());
        }
    }

    std::string name;
    std::string mountPoint;
    std::string type;
    uint64_t totalBlocks = 0;
    uint64_t usedBlocks = 0;
    uint64_t availableBlocks = 0;
    uint64_t blocksize = 1; // KB
    long double inodeUsed = 0;
    long double spaceUsed = 0;
};

struct FilesystemStats {

    static FilesystemStats& getInstance()
    {
        static FilesystemStats instance;
        return instance;
    }

    FilesystemStats(FilesystemStats const&) = delete;
    void operator=(FilesystemStats const&) = delete;

    void readFilesystemStats()
    {
        std::lock_guard lk(mMtx);
        int rc = system("/bin/df -T > " FILESYSTEM_STATS_LOCATION
                        "&& /bin/df -i > " FILESYSTEM_STATS_LOCATION2);
        if (rc == -1) {
            SRPLG_LOG_ERR(PLUGIN_NAME, "df command failed");
            return;
        }
        SRPLG_LOG_DBG(PLUGIN_NAME, "%s", ("df command returned:" + std::to_string(rc)).c_str());
        std::string token, inodesToken;
        std::ifstream file(FILESYSTEM_STATS_LOCATION), fileinodes(FILESYSTEM_STATS_LOCATION2);
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        fileinodes.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        while (file >> token || fileinodes >> inodesToken) {
            Filesystem fs;
            uint64_t inodesTotal;
            uint64_t inodesUsed;
            fs.name = token;
            file >> fs.type >> fs.totalBlocks >> fs.usedBlocks >> fs.availableBlocks >> token >> fs.mountPoint;
            fileinodes >> token >> inodesTotal >> inodesUsed;

            struct statvfs buf;
            if (statvfs(fs.mountPoint.c_str(), &buf) == 0) {
                fs.blocksize = buf.f_bsize / 1024; // KB
                fs.totalBlocks = buf.f_blocks;
                fs.availableBlocks = buf.f_bfree;
                fs.usedBlocks = fs.totalBlocks - fs.availableBlocks;
                inodesTotal = buf.f_files;
                inodesUsed = inodesTotal - buf.f_ffree;
            } else {
                SRPLG_LOG_ERR(PLUGIN_NAME, "statvfs call failed");
            }
            if (inodesTotal == 0) {
                fs.inodeUsed = 0;
            } else {
                fs.inodeUsed = static_cast<long double>(inodesUsed) * 100.0 / static_cast<long double>(inodesTotal);
            }
            if (fs.totalBlocks == 0) {
                fs.spaceUsed = 0;
            } else {
                fs.spaceUsed = static_cast<long double>(fs.usedBlocks) * 100.0 / static_cast<long double>(fs.totalBlocks);
            }
            fsMap.emplace(std::make_pair(fs.mountPoint, fs));
            // ignore rest of the line
            file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            fileinodes.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    std::optional<long double> getUsage(std::string mountPoint)
    {
        readFilesystemStats();
        std::lock_guard lk(mMtx);
        std::unordered_map<std::string, Filesystem>::iterator itr;
        if ((itr = fsMap.find(mountPoint)) != fsMap.end()) {
            return itr->second.spaceUsed;
        } else {
            return std::nullopt;
        }
    }

    void printValues() const
    {
        for (auto const& v : fsMap) {
            v.second.printValues();
            std::cout << std::endl;
        }
    }

    void setXpathValues(sysrepo::Session session,
        std::optional<libyang::DataNode>& parent,
        std::string_view moduleName)
    {
        std::lock_guard lk(mMtx);
        SRPLG_LOG_DBG(PLUGIN_NAME, "Setting xpath values for filesystems statistics");
        for (auto const& v : fsMap) {
            v.second.setXpathValues(session, parent, moduleName);
        }
    }

private:
    FilesystemStats() = default;
    std::mutex mMtx;
    std::unordered_map<std::string, Filesystem> fsMap;
};

} // namespace metrics

#endif // FILESYSTEM_STATS_H
