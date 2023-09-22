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

include(GNUInstallDirs)
set(CMAKE_CXX_STANDARD 20)

SET(
    SRPCPP_SOURCES

    src/srpcpp/common.cpp
    src/srpcpp/context.cpp
)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/../CMakeModules")
find_package(LIBYANG REQUIRED)
find_package(SYSREPO REQUIRED)
find_package(SYSREPOCPP REQUIRED)
find_package(LIBYANGCPP REQUIRED)

include_directories(src)
include_directories(${LIBYANG_INCLUDE_DIRS})
include_directories(${SYSREPO_INCLUDE_DIRS})
include_directories(${LIBYANGCPP_INCLUDE_DIRS})
include_directories(${SYSREPOCPP_INCLUDE_DIRS})

add_library(${PROJECT_NAME} SHARED ${SRPCPP_SOURCES})

# project version
set_target_properties(
    ${PROJECT_NAME}
    PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
)

install(
    TARGETS ${PROJECT_NAME}
    DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(
    FILES ${PROJECT_SOURCE_DIR}/src/srpcpp.hpp
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(
    FILES
    ${PROJECT_SOURCE_DIR}/src/srpcpp/common.hpp
    ${PROJECT_SOURCE_DIR}/src/srpcpp/context.hpp
    ${PROJECT_SOURCE_DIR}/src/srpcpp/callbacks.hpp
    ${PROJECT_SOURCE_DIR}/src/srpcpp/module.hpp
    ${PROJECT_SOURCE_DIR}/src/srpcpp/module-registry.hpp
    ${PROJECT_SOURCE_DIR}/src/srpcpp/datastore.hpp
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/srpcpp
)

add_custom_target(uninstall COMMAND xargs rm < ${PROJECT_SOURCE_DIR}/build/install_manifest.txt)
