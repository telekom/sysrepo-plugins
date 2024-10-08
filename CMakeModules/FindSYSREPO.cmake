#
# telekom / sysrepo-plugins
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

if (SYSREPO_LIBRARIES AND SYSREPO_INCLUDE_DIRS)
    set(SYSREPO_FOUND TRUE)
else ()

    find_path(
        SYSREPO_INCLUDE_DIR
        NAMES sysrepo.h
        PATHS /usr/include /usr/local/include /opt/local/include /sw/include ${CMAKE_INCLUDE_PATH} ${CMAKE_INSTALL_PREFIX}/include
    )

    find_library(
        SYSREPO_LIBRARY
        NAMES sysrepo
        PATHS /usr/lib /usr/lib64 /usr/local/lib /usr/local/lib64 /opt/local/lib /sw/lib ${CMAKE_LIBRARY_PATH} ${CMAKE_INSTALL_PREFIX}/lib
    )

    if (SYSREPO_INCLUDE_DIR AND SYSREPO_LIBRARY)
        set(SYSREPO_FOUND TRUE)
    else (SYSREPO_INCLUDE_DIR AND SYSREPO_LIBRARY)
        set(SYSREPO_FOUND FALSE)
    endif (SYSREPO_INCLUDE_DIR AND SYSREPO_LIBRARY)

    set(SYSREPO_INCLUDE_DIRS ${SYSREPO_INCLUDE_DIR})
    set(SYSREPO_LIBRARIES ${SYSREPO_LIBRARY})
endif ()