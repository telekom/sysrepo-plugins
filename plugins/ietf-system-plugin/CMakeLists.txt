#
# telekom / sysrepo-plugin-system
#
# This program is made available under the terms of the
# BSD 3-Clause license which is available at
# https://opensource.org/licenses/BSD-3-Clause
#
# SPDX-FileCopyrightText: 2024 Deutsche Telekom AG
# SPDX-FileContributor: Sartura d.d.
#
# SPDX-License-Identifier: BSD-3-Clause
#
cmake_minimum_required(VERSION 3.0)
project(ietf-system-plugin)

set(CMAKE_CXX_STANDARD 20)

set(PLUGIN_LIRBARY_NAME srplg-ietf-system)
set(PLUGIN_EXECUTABLE_NAME ietf-system-plugin)
set(PLUGIN_CORE_LIBRARY_NAME ietf-system-plugin-core)

# module select options
option(SYSTEM_MODULE "Registers the System module" ON)
option(HOSTNAME_MODULE "Registers the Hostname module" ON)
option(TIMEZONE_MODULE "Registers the Timezone module" ON)
option(DNS_MODULE "Registers the DNS module" ON)
option(NTP_MODULE "Registers the NTP module" ON)
option(AUTH_MODULE "Registers the Authentication module" ON)

find_package(PkgConfig REQUIRED)
find_package(SYSREPOCPP REQUIRED)
find_package(LIBYANGCPP REQUIRED)
find_package(SYSREPO REQUIRED)
find_package(LIBYANG REQUIRED)
find_package(LIBSYSTEMD REQUIRED)
find_package(LIBSDBUSCPP REQUIRED)
find_package(UMGMT REQUIRED)

set(
    MODULE_SOURCES

    # modules
    src/plugin/modules/system.cpp
    src/plugin/modules/hostname.cpp
    src/plugin/modules/timezone-name.cpp
    src/plugin/modules/dns.cpp
    src/plugin/modules/ntp.cpp
    src/plugin/modules/auth.cpp
    src/plugin/ntp.cpp
)

set(
    PLUGIN_CORE_SOURCES

    src/plugin/context.cpp
    src/plugin/ip.cpp

    ${MODULE_SOURCES}
)

set(
    PLUGIN_HEADERS

    src/plugin.hpp
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

# add compile definitions for the enabled modules

# System module
if(SYSTEM_MODULE)
    add_compile_definitions(SYSTEM_MODULE)
endif(SYSTEM_MODULE)

# Hostname module
if(HOSTNAME_MODULE)
    add_compile_definitions(HOSTNAME_MODULE)
endif(HOSTNAME_MODULE)

# Timezone module
if(TIMEZONE_MODULE)
    add_compile_definitions(TIMEZONE_MODULE)
endif(TIMEZONE_MODULE)

# DNS module
if(DNS_MODULE)
    add_compile_definitions(DNS_MODULE)
endif(DNS_MODULE)

# NTP module
if(NTP_MODULE)
    add_compile_definitions(NTP_MODULE)
endif(NTP_MODULE)

# Authentication module
if(AUTH_MODULE)
    add_compile_definitions(AUTH_MODULE)
endif(AUTH_MODULE)

# check for systemd flag
if(DEFINED SYSTEMD_IFINDEX)
    add_compile_definitions(SYSTEMD_IFINDEX=${SYSTEMD_IFINDEX})
else()
    message(SEND_ERROR "No SYSTEMD_IFINDEX value set for default interface index to use with systemd... Unable to build without it")
endif()

# core library
add_library(
    ${PLUGIN_CORE_LIBRARY_NAME}
    STATIC
    ${PLUGIN_CORE_SOURCES}
)

target_include_directories(
    ${PLUGIN_CORE_LIBRARY_NAME}

    PRIVATE ${SYSREPOCPP_INCLUDE_DIRS}
    PRIVATE ${LIBYANGCPP_INCLUDE_DIRS}
    PRIVATE ${UMGMT_INCLUDE_DIRS}
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
    PRIVATE ${SDBUS_CPP_INCLUDE_DIRS}
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
    ${EXECUTABLE_SOURCES}
)

target_include_directories(
    ${PLUGIN_EXECUTABLE_NAME}

    PRIVATE ${SYSREPOCPP_INCLUDE_DIRS}
    PRIVATE ${LIBYANGCPP_INCLUDE_DIRS}
    PRIVATE ${UMGMT_INCLUDE_DIRS}
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
    PRIVATE ${SDBUS_CPP_INCLUDE_DIRS}
    PRIVATE ${CORE_LIBRARY_INCLUDE_DIRS}
)

target_link_libraries(
    ${PLUGIN_EXECUTABLE_NAME}

    ${PLUGIN_CORE_LIBRARY_NAME}

    ${SYSREPO_LIBRARIES}
    ${LIBYANG_LIBRARIES}
    ${SYSREPOCPP_LIBRARIES}
    ${LIBYANGCPP_LIBRARIES}
    ${UMGMT_LIBRARIES}
    ${SDBUSCPP_LIBRARIES}
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

    PRIVATE ${SYSREPOCPP_INCLUDE_DIRS}
    PRIVATE ${LIBYANGCPP_INCLUDE_DIRS}
    PRIVATE ${UMGMT_INCLUDE_DIRS}
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
    PRIVATE ${SDBUS_CPP_INCLUDE_DIRS}
    PRIVATE ${CORE_LIBRARY_INCLUDE_DIRS}
)

target_link_libraries(
    ${PLUGIN_LIRBARY_NAME}

    ${PLUGIN_CORE_LIBRARY_NAME}
    ${SYSREPO_LIBRARIES}
    ${LIBYANG_LIBRARIES}
    ${SYSREPOCPP_LIBRARIES}
    ${LIBYANGCPP_LIBRARIES}
    ${UMGMT_LIBRARIES}
    ${SDBUSCPP_LIBRARIES}
    ${CORE_LIBRARY_NAME}
)
