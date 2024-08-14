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

if (SYSREPOCPP_LIBRARIES AND SYSREPOCPP_INCLUDE_DIRS)
    set(SYSREPOCPP_FOUND TRUE)
else ()

    find_path(
        SYSREPOCPP_INCLUDE_DIR
        NAMES sysrepo-cpp/Connection.hpp
        PATHS /usr/include /usr/local/include /opt/local/include /sw/include ${CMAKE_INCLUDE_PATH} ${CMAKE_INSTALL_PREFIX}/include
    )

    find_library(
        SYSREPOCPP_LIBRARY
        NAMES sysrepo-cpp
        PATHS /usr/lib /usr/lib64 /usr/local/lib /usr/local/lib64 /opt/local/lib /sw/lib ${CMAKE_LIBRARY_PATH} ${CMAKE_INSTALL_PREFIX}/lib
    )

    if (SYSREPOCPP_INCLUDE_DIR AND SYSREPOCPP_LIBRARY)
        set(SYSREPOCPP_FOUND TRUE)
    else (SYSREPOCPP_INCLUDE_DIR AND SYSREPOCPP_LIBRARY)
        set(SYSREPOCPP_FOUND FALSE)
    endif (SYSREPOCPP_INCLUDE_DIR AND SYSREPOCPP_LIBRARY)

    set(SYSREPOCPP_INCLUDE_DIRS ${SYSREPOCPP_INCLUDE_DIR})
    set(SYSREPOCPP_LIBRARIES ${SYSREPOCPP_LIBRARY})
endif ()