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
project(srpcpp VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)

SET(
    SRPCPP_SOURCES

    src/srpcpp/common.cpp
    src/srpcpp/context.cpp
)

find_package(LIBYANG REQUIRED)
find_package(SYSREPO REQUIRED)
find_package(SYSREPOCPP REQUIRED)
find_package(LIBYANGCPP REQUIRED)

add_library(${PROJECT_NAME} STATIC ${SRPCPP_SOURCES})

target_include_directories(
    ${PROJECT_NAME}

    PRIVATE ${LIBYANG_INCLUDE_DIRS}
    PRIVATE ${SYSREPO_INCLUDE_DIRS}
    PRIVATE ${LIBYANGCPP_INCLUDE_DIRS}
    PRIVATE ${SYSREPOCPP_INCLUDE_DIRS}
)

# project version
set_target_properties(
    ${PROJECT_NAME}
    PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
)
