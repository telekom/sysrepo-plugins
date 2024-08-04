#
# telekom / sysrepo-plugins / ietf-access-control-list-plugin
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
project(ietf-access-control-list-plugin)

set(PLUGIN_LIRBARY_NAME srplg-ietf-access-control-list)
set(PLUGIN_EXECUTABLE_NAME ietf-access-control-list-plugin)
set(PLUGIN_CORE_LIBRARY_NAME ietf-access-control-list-plugin-core)

find_package(PkgConfig REQUIRED)
find_package(LIBYANG REQUIRED)
find_package(SYSREPO REQUIRED)
find_package(LIBYANGCPP REQUIRED)
find_package(SYSREPOCPP REQUIRED)
find_package(NL REQUIRED)
find_package(NFTABLES REQUIRED)
find_package(NLOHMANN_JSON REQUIRED)

set(
    PLUGIN_CORE_SOURCES

    src/core/context.cpp
    src/core/sub/change.cpp
    src/core/sub/oper.cpp
    src/core/sub/rpc.cpp
    src/core/sub/context.hpp
    src/core/nftables.cpp
    src/core/nft_helper.hpp
)

set(
    MODULE_SOURCES

    src/modules/acl.cpp
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
    PRIVATE ${NL_INCLUDE_DIRS}
    PRIVATE ${CORE_LIBRARY_INCLUDE_DIRS}
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/
    PRIVATE ${NFTABLES_INCLUDE_DIRS}
    PRIVATE ${NLOHMANN_JSON_INCLUDE_DIRS}

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
    PRIVATE ${NL_INCLUDE_DIRS}
    PRIVATE ${CORE_LIBRARY_INCLUDE_DIRS}
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/
    PRIVATE ${NFTABLES_INCLUDE_DIRS}
    PRIVATE ${NLOHMANN_JSON_INCLUDE_DIRS}
)

target_link_libraries(
    ${PLUGIN_EXECUTABLE_NAME}

    ${PLUGIN_CORE_LIBRARY_NAME}

    ${SYSREPO_LIBRARIES}
    ${LIBYANG_LIBRARIES}
    ${SYSREPOCPP_LIBRARIES}
    ${LIBYANGCPP_LIBRARIES}
    ${CORE_LIBRARY_NAME}
    ${NL_LIBRARIES}
    ${NFTABLES_LIBRARIES}
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
    PRIVATE ${NL_INCLUDE_DIRS}
    PRIVATE ${CORE_LIBRARY_INCLUDE_DIRS}
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/
    PRIVATE ${NFTABLES_INCLUDE_DIRS}
    PRIVATE ${NLOHMANN_JSON_INCLUDE_DIRS}
)

target_link_libraries(
    ${PLUGIN_LIRBARY_NAME}

    ${PLUGIN_CORE_LIBRARY_NAME}
    ${SYSREPO_LIBRARIES}
    ${LIBYANG_LIBRARIES}
    ${SYSREPOCPP_LIBRARIES}
    ${LIBYANGCPP_LIBRARIES}
    ${CORE_LIBRARY_NAME}
    ${NL_LIBRARIES}
    ${NFTABLES_LIBRARIES}
)
