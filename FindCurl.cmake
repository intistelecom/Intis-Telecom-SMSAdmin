# locate CURL library

if(UNIX AND NOT CMAKE_CROSSCOMPILING)
    set(CURL_MIN_VERSION 7.19)
    include(FindPkgConfig)
    pkg_check_modules(CURL libcurl>=${CURL_MIN_VERSION} REQUIRED)
    include_directories(BEFORE ${CURL_INCLUDE_DIRS})
    target_link_libraries(${TARGET} ${CURL_LIBRARIES})
endif()

if(WIN32 OR CMAKE_CROSSCOMPILING)
    find_path(LIBCURL_INCLUDE_DIRS
      NAMES curl.h
      PATHS "include;/usr/include;/usr/local/include"
      PATH_SUFFIXES curl
    )

    find_library(LIBCURL_LIBRARIES
      NAMES curl
      PATHS ".;c:/windows/system32;lib;/usr/lib;/usr/local/lib;/usr/lib64;/usr/local/lib64"
    )

    if (LIBCURL_INCLUDE_DIRS AND LIBCURL_LIBRARIES)
        set(LIBCURL_FOUND TRUE)
    endif (LIBCURL_INCLUDE_DIRS AND LIBCURL_LIBRARIES)

    if (LIBCURL_FOUND)
        message(STATUS "Found libcurl: -I${LIBCURL_INCLUDE_DIRS} -L${LIBCURL_LIBRARIES}")
        include_directories(${LIBCURL_INCLUDE_DIRS})
        target_link_libraries(${TARGET} ${LIBCURL_LIBRARIES})
    else (LIBCURL_FOUND)
        message(FATAL_ERROR "Required library curl not found")
    endif (LIBCURL_FOUND)
endif()
