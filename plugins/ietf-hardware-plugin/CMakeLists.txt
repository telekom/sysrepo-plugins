#
# telekom / ietf-hardware-plugin
#
# This program is made available under the terms of the
# BSD 3-Clause license which is available at
# https://opensource.org/licenses/BSD-3-Clause
#
# SPDX-FileCopyrightText: 2026 Deutsche Telekom AG
# SPDX-FileContributor: Sartura d.d.
#
# SPDX-License-Identifier: BSD-3-Clause
#
cmake_minimum_required(VERSION 3.12)
project(ietf-hardware-plugin)

set(PLUGIN_LIRBARY_NAME srplg-ietf-hardware)
set(PLUGIN_EXECUTABLE_NAME ietf-hardware-plugin)
set(PLUGIN_CORE_LIBRARY_NAME ietf-hardware-plugin-core)

find_package(PkgConfig REQUIRED)
find_package(LIBYANG REQUIRED)
find_package(SYSREPO REQUIRED)
find_package(LIBYANGCPP REQUIRED)
find_package(SYSREPOCPP REQUIRED)
find_library(libsensors sensors)

set(
    PLUGIN_CORE_SOURCES

    src/plugin/context.cpp
)

set(
    MODULE_SOURCES

    src/plugin/modules/hardware.cpp
    src/plugin/modules/hardware/oper.cpp
    src/plugin/modules/hardware/change.cpp
    src/plugin/modules/hardware/api/component_data.cpp
    src/plugin/modules/hardware/api/sensor_data.cpp
    src/plugin/modules/hardware/api/hardware_sensors.cpp
)

set(
    PLUGIN_SOURCES

    src/plugin.cpp
)

set(
    EXECUTABLE_SOURCES

    src/main.c
    src/plugin.cpp
)

# core library
add_library(
    ${PLUGIN_CORE_LIBRARY_NAME}
    STATIC
    ${PLUGIN_CORE_SOURCES}
    ${MODULE_SOURCES}
)

target_include_directories(
    ${PLUGIN_CORE_LIBRARY_NAME}

    PRIVATE ${LIBYANG_INCLUDE_DIRS}
    PRIVATE ${SYSREPO_INCLUDE_DIRS}
    PRIVATE ${LIBYANGCPP_INCLUDE_DIRS}
    PRIVATE ${SYSREPOCPP_INCLUDE_DIRS}
    PRIVATE ${CORE_LIBRARY_INCLUDE_DIRS}
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/
)

target_compile_options(
    ${PLUGIN_CORE_LIBRARY_NAME}
    PRIVATE
    -fPIC
)

# plugin as an executable
add_executable(
    ${PLUGIN_EXECUTABLE_NAME}
    ${EXECUTABLE_SOURCES}
)

target_include_directories(
    ${PLUGIN_EXECUTABLE_NAME}

    PRIVATE ${LIBYANG_INCLUDE_DIRS}
    PRIVATE ${SYSREPO_INCLUDE_DIRS}
    PRIVATE ${LIBYANGCPP_INCLUDE_DIRS}
    PRIVATE ${SYSREPOCPP_INCLUDE_DIRS}
    PRIVATE ${CORE_LIBRARY_INCLUDE_DIRS}
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/
)

target_link_libraries(
    ${PLUGIN_EXECUTABLE_NAME}

    ${PLUGIN_CORE_LIBRARY_NAME}

    ${SYSREPO_LIBRARIES}
    ${LIBYANG_LIBRARIES}
    ${SYSREPOCPP_LIBRARIES}
    ${LIBYANGCPP_LIBRARIES}
    ${CORE_LIBRARY_NAME}
    sensors
)

# plugin as a library
add_library(
    ${PLUGIN_LIRBARY_NAME}
    MODULE
    ${PLUGIN_SOURCES}
)

target_include_directories(
    ${PLUGIN_LIRBARY_NAME}

    PRIVATE ${LIBYANG_INCLUDE_DIRS}
    PRIVATE ${SYSREPO_INCLUDE_DIRS}
    PRIVATE ${LIBYANGCPP_INCLUDE_DIRS}
    PRIVATE ${SYSREPOCPP_INCLUDE_DIRS}
    PRIVATE ${CORE_LIBRARY_INCLUDE_DIRS}
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/
)

target_link_libraries(
    ${PLUGIN_LIRBARY_NAME}

    ${PLUGIN_CORE_LIBRARY_NAME}
    ${SYSREPO_LIBRARIES}
    ${LIBYANG_LIBRARIES}
    ${SYSREPOCPP_LIBRARIES}
    ${LIBYANGCPP_LIBRARIES}
    ${CORE_LIBRARY_NAME}
    sensors
)
