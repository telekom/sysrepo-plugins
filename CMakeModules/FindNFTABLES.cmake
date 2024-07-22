if(NFTABLES_LIBRARIES AND NFTABLES_INCLUDE_DIRS)
    set(NFTABLES_FOUND TRUE)
else()
    find_path(
        NFTABLES_INCLUDE_DIR
        NAMES nftables/libnftables.h
        PATHS /usr/include /usr/local/include /opt/local/include /sw/include ${CMAKE_INCLUDE_PATH} ${CMAKE_INSTALL_PREFIX}/include
    )

    find_library(
        NFTABLES_LIBRARY
        NAMES nftables
        PATHS /usr/lib /usr/lib64 /usr/local/lib /usr/local/lib64 /opt/local/lib /sw/lib ${CMAKE_LIBRARY_PATH} ${CMAKE_INSTALL_PREFIX}/lib
    )

    if(NFTABLES_INCLUDE_DIR AND NFTABLES_LIBRARY)
        set(NFTABLES_FOUND TRUE)
        set(NFTABLES_INCLUDE_DIRS ${NFTABLES_INCLUDE_DIR})
        set(NFTABLES_LIBRARIES ${NFTABLES_LIBRARY})
    else()
        set(NFTABLES_FOUND FALSE)
    endif()

    if(NOT NFTABLES_FOUND)
        message(FATAL_ERROR "Could not find libnftables. Please install libnftables-dev or set NFTABLES_INCLUDE_DIR and NFTABLES_LIBRARY manually.")
    endif()
endif()

mark_as_advanced(NFTABLES_INCLUDE_DIR NFTABLES_LIBRARY)
