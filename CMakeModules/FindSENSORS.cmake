#
# telekom / sysrepo-plugins
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

if(SENSORS_LIBRARIES AND SENSORS_INCLUDE_DIRS)
    set(SENSORS_FOUND TRUE)
else()
    find_path(
        SENSORS_INCLUDE_DIR
        NAMES sensors/sensors.h
        PATHS /usr/include /usr/local/include /opt/local/include /sw/include ${CMAKE_INCLUDE_PATH} ${CMAKE_INSTALL_PREFIX}/include
    )

    find_library(
        SENSORS_LIBRARY
        NAMES sensors
        PATHS /usr/lib /usr/lib64 /usr/local/lib /usr/local/lib64 /opt/local/lib /sw/lib ${CMAKE_LIBRARY_PATH} ${CMAKE_INSTALL_PREFIX}/lib
    )

    if(SENSORS_INCLUDE_DIR AND SENSORS_LIBRARY)
        set(SENSORS_FOUND TRUE)
        set(SENSORS_INCLUDE_DIRS ${SENSORS_INCLUDE_DIR})
        set(SENSORS_LIBRARIES ${SENSORS_LIBRARY})
    else()
        set(SENSORS_FOUND FALSE)
    endif()

    if(NOT SENSORS_FOUND)
        message(FATAL_ERROR "Could not find libsensors. Please install libsensors-dev or set SENSORS_INCLUDE_DIR and SENSORS_LIBRARY manually.")
    endif()
endif()

mark_as_advanced(SENSORS_INCLUDE_DIR SENSORS_LIBRARY)
