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

if(PROCPS_LIBRARIES AND PROCPS_INCLUDE_DIRS)
    set(PROCPS_FOUND TRUE)
else()
    find_path(
        PROCPS_INCLUDE_DIR
        NAMES proc/procps.h
        PATHS /usr/include /usr/local/include /opt/local/include /sw/include ${CMAKE_INCLUDE_PATH} ${CMAKE_INSTALL_PREFIX}/include
    )

    find_library(
        PROCPS_LIBRARY
        NAMES procps
        PATHS /usr/lib /usr/lib64 /usr/local/lib /usr/local/lib64 /opt/local/lib /sw/lib ${CMAKE_LIBRARY_PATH} ${CMAKE_INSTALL_PREFIX}/lib
    )

    if(PROCPS_INCLUDE_DIR AND PROCPS_LIBRARY)
        set(PROCPS_FOUND TRUE)
    else(PROCPS_INCLUDE_DIR AND PROCPS_LIBRARY)
        set(PROCPS_FOUND FALSE)
    endif(PROCPS_INCLUDE_DIR AND PROCPS_LIBRARY)

    set(PROCPS_INCLUDE_DIRS ${PROCPS_INCLUDE_DIR})
    set(PROCPS_LIBRARIES ${PROCPS_LIBRARY})
endif()
