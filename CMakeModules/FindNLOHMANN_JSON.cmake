if(NLOHMANN_JSON_INCLUDE_DIRS)
    set(NLOHMANN_JSON_FOUND TRUE)
else()
    find_path(
        NLOHMANN_JSON_INCLUDE_DIR
        NAMES nlohmann/json.hpp
        PATHS /usr/include /usr/local/include /opt/local/include /sw/include ${CMAKE_INCLUDE_PATH} ${CMAKE_INSTALL_PREFIX}/include
    )

    if(NLOHMANN_JSON_INCLUDE_DIR)
        set(NLOHMANN_JSON_FOUND TRUE)
        set(NLOHMANN_JSON_INCLUDE_DIRS ${NLOHMANN_JSON_INCLUDE_DIR})
    else()
        set(NLOHMANN_JSON_FOUND FALSE)
        message(FATAL_ERROR "Could not find nlohmann-json. Please install nlohmann-json or set NLOHMANN_JSON_INCLUDE_DIR manually.")
    endif()
endif()

mark_as_advanced(NLOHMANN_JSON_INCLUDE_DIR)
