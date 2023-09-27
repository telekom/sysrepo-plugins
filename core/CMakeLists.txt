#
# Copyright (c) 2022 Deutsche Telekom AG.
#
# This source code is licensed under BSD 3-Clause License (the "License").
# You may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     https://opensource.org/licenses/BSD-3-Clause
#
# SPDX-FileCopyrightText: 2022 Deutsche Telekom AG
# SPDX-FileContributor: Sartura Ltd.
#
# SPDX-License-Identifier: BSD-3-Clause
#
cmake_minimum_required(VERSION 3.0.0)
project(sysrepo-plugins-core VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)
set(CORE_LIBRARY_NAME ${PROJECT_NAME})
set(CORE_LIBRARY_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/src")

SET(
    CORE_SOURCES

    src/srpcpp/common.cpp
    src/srpcpp/context.cpp

    # netlink wrapper
    src/srpcpp/netlink/nl.cpp
    src/srpcpp/netlink/cache.cpp
    src/srpcpp/netlink/address.cpp
    src/srpcpp/netlink/neighbor.cpp
    src/srpcpp/netlink/interface.cpp
)

find_package(LIBYANG REQUIRED)
find_package(SYSREPO REQUIRED)
find_package(SYSREPOCPP REQUIRED)
find_package(LIBYANGCPP REQUIRED)
find_package(NL REQUIRED)

add_library(${CORE_LIBRARY_NAME} STATIC ${CORE_SOURCES})

target_include_directories(
    ${CORE_LIBRARY_NAME}

    PRIVATE ${LIBYANG_INCLUDE_DIRS}
    PRIVATE ${SYSREPO_INCLUDE_DIRS}
    PRIVATE ${LIBYANGCPP_INCLUDE_DIRS}
    PRIVATE ${SYSREPOCPP_INCLUDE_DIRS}
    PRIVATE ${NL_INCLUDE_DIRS}
    PRIVATE ${CORE_LIBRARY_INCLUDE_DIRS}
)

target_compile_options(
    ${CORE_LIBRARY_NAME}
    PRIVATE
    -fPIC
)

# project version
set_target_properties(
    ${CORE_LIBRARY_NAME}
    PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
)
