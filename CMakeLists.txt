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
project(ietf-system-plugin)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMakeModules")

option(BUILD_SYSTEM_PLUGIN "Build the ietf-system-plugin" ON)
option(BUILD_INTERFACES_PLUGIN "Build the ietf-interfaces-plugin" ON)

if(BUILD_SYSTEM_PLUGIN)
    add_subdirectory(plugins/ietf-system-plugin)
endif()

if(BUILD_INTERFACES_PLUGIN)
    add_subdirectory(plugins/ietf-interfaces-plugin)
endif()

if(BUILD_ROUTING_PLUGIN)
    add_subdirectory(plugins/ietf-routing-plugin)
endif()
