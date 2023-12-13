#
# telekom / sysrepo-plugins
#
# This program is made available under the terms of the
# BSD 3-Clause license which is available at
# https://opensource.org/licenses/BSD-3-Clause
#
# SPDX-FileCopyrightText: 2021 Deutsche Telekom AG
# SPDX-FileContributor: Sartura Ltd.
#
# SPDX-License-Identifier: BSD-3-Clause
#
cmake_minimum_required(VERSION 3.0)
project(sysrepo-plugins)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMakeModules")

option(BUILD_SYSTEM_PLUGIN "Build the ietf-system-plugin" ON)
option(BUILD_INTERFACES_PLUGIN "Build the ietf-interfaces-plugin" ON)
option(BUILD_ROUTING_PLUGIN "Build the ietf-routing-plugin" ON)
option(BUILD_BRIDGING_PLUGIN "Build the ieee802-dot1q-bridge-plugin" ON)
option(BUILD_ACL_PLUGIN "Build the ietf-access-control-list-plugin" ON)

# build core first
add_subdirectory(core)

# get name of the core library
get_directory_property(
    CORE_LIBRARY_NAME 
    DIRECTORY core 
    DEFINITION CORE_LIBRARY_NAME
)

# get include dir for the core library
get_directory_property(
    CORE_LIBRARY_INCLUDE_DIRS
    DIRECTORY core
    DEFINITION CORE_LIBRARY_INCLUDE_DIRS
)

if(BUILD_SYSTEM_PLUGIN)
    add_subdirectory(plugins/ietf-system-plugin)
endif()

if(BUILD_INTERFACES_PLUGIN)
    add_subdirectory(plugins/ietf-interfaces-plugin)
endif()

if(BUILD_ROUTING_PLUGIN)
    add_subdirectory(plugins/ietf-routing-plugin)
endif()

if(BUILD_BRIDGING_PLUGIN)
    add_subdirectory(plugins/ieee802-dot1q-bridge-plugin)
endif()

if(BUILD_ACL_PLUGIN)
    add_subdirectory(plugins/ietf-access-control-list-plugin)
endif()
