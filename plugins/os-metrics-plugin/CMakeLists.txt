#
# telekom / os-metrics-plugin
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
project(os-metrics-plugin)

set(PLUGIN_LIRBARY_NAME srplg-os-metrics)
set(PLUGIN_EXECUTABLE_NAME os-metrics-plugin)
set(PLUGIN_CORE_LIBRARY_NAME os-metrics-plugin-core)

find_package(PkgConfig REQUIRED)
find_package(LIBYANG REQUIRED)
find_package(SYSREPO REQUIRED)
find_package(LIBYANGCPP REQUIRED)
find_package(SYSREPOCPP REQUIRED)
find_package(PROCPS REQUIRED)

set(
    PLUGIN_SOURCES

    src/plugin/callback.hpp
    src/plugin/cpu_stats.hpp
    src/plugin/filesystem_stats.hpp
    src/plugin/memory_stats.hpp
    src/plugin/process_stats.hpp
    src/plugin/threshold_manager.hpp
    src/plugin.cpp
)

set(
    EXECUTABLE_SOURCES

    src/main.c
)

# core library
add_library(
    ${PLUGIN_CORE_LIBRARY_NAME}
    STATIC
    ${PLUGIN_SOURCES}
)

target_include_directories(
    ${PLUGIN_CORE_LIBRARY_NAME}

    PRIVATE ${LIBYANGCPP_INCLUDE_DIRS}
    PRIVATE ${SYSREPOCPP_INCLUDE_DIRS}
    PRIVATE ${PROCPS_INCLUDE_DIRS}
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/
    PRIVATE ${CORE_LIBRARY_INCLUDE_DIRS}
)

target_compile_options(
    ${PLUGIN_CORE_LIBRARY_NAME}
    PRIVATE
    -fPIC
)

# plugin as an executable
add_executable(
    ${PLUGIN_EXECUTABLE_NAME}
    ${PLUGIN_SOURCES} ${EXECUTABLE_SOURCES}
)

target_include_directories(
    ${PLUGIN_EXECUTABLE_NAME}

    PRIVATE ${LIBYANG_INCLUDE_DIRS}
    PRIVATE ${SYSREPO_INCLUDE_DIRS}
    PRIVATE ${LIBYANGCPP_INCLUDE_DIRS}
    PRIVATE ${SYSREPOCPP_INCLUDE_DIRS}
    PRIVATE ${PROCPS_INCLUDE_DIRS}
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/
    PRIVATE ${CORE_LIBRARY_INCLUDE_DIRS}
)

target_link_libraries(
    ${PLUGIN_EXECUTABLE_NAME}

    ${PLUGIN_CORE_LIBRARY_NAME}

    ${SYSREPO_LIBRARIES}
    ${LIBYANG_LIBRARIES}
    ${SYSREPOCPP_LIBRARIES}
    ${LIBYANGCPP_LIBRARIES}
    ${PROCPS_LIBRARIES}
    ${CORE_LIBRARY_NAME}
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
    PRIVATE ${PROCPS_INCLUDE_DIRS}
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/
    PRIVATE ${CORE_LIBRARY_INCLUDE_DIRS}
)

target_link_libraries(
    ${PLUGIN_LIRBARY_NAME}

    ${PLUGIN_CORE_LIBRARY_NAME}
    ${SYSREPO_LIBRARIES}
    ${LIBYANG_LIBRARIES}
    ${SYSREPOCPP_LIBRARIES}
    ${LIBYANGCPP_LIBRARIES}
    ${PROCPS_LIBRARIES}
    ${CORE_LIBRARY_NAME}
)
