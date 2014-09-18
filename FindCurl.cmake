# locate CURL library

if(UNIX)
    set(CURL_MIN_VERSION 7.19)
    include(FindPkgConfig)
    pkg_check_modules(CURL libcurl>=${CURL_MIN_VERSION} REQUIRED)
    include_directories(BEFORE ${CURL_INCLUDE_DIRS})
    target_link_libraries(${TARGET} ${CURL_LIBRARIES})
endif(UNIX)

if(WIN32)
    find_path(LIBCURL_INCLUDE_DIRS
      NAMES curl.h
      PATHS "include;/usr/include;/usr/local/include"
    )

    set(LIBCURL_INCLUDE_DIRS /opt/mingw-w32/include)

    find_library(LIBCURL_LIBRARIES
      NAMES curl
      PATHS ".;c:/windows/system32;/usr/lib;/usr/local/lib"
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
endif(WIN32)
