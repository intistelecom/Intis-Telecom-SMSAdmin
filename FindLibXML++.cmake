# locate libxml++ library

# This module defines
# LIBXMLPP_LIBRARIES
# LIBXMLPP_FOUND
# LIBXMLPP_INCLUDE_DIRS
# LIBXMLPP_MIN_VERSION

set(LIBXMLPP_MIN_VERSION 2.6)
set(LIBXMLPP_FOUND FALSE)

find_path(LIBXMLPP_INCLUDE_DIRS
  NAMES tinyxml.h
  PATHS "include;/usr/include;/usr/local/include"
)

find_library(LIBXMLPP_LIBRARIES
  NAMES tinyxml
  PATHS ".;c:/windows/system32;lib;/usr/lib;/usr/lib64;/usr/local/lib;/usr/local/lib64"
)

if (LIBXMLPP_INCLUDE_DIRS AND LIBXMLPP_LIBRARIES)
    set(LIBXMLPP_FOUND TRUE)
endif (LIBXMLPP_INCLUDE_DIRS AND LIBXMLPP_LIBRARIES)

if (LIBXMLPP_FOUND)
    message(STATUS "Found tinyxml: -I${LIBXMLPP_INCLUDE_DIRS} -L${LIBXMLPP_LIBRARIES}")
    include_directories(${LIBXMLPP_INCLUDE_DIRS})
    target_link_libraries(${SMS16XAPI} ${LIBXMLPP_LIBRARIES})
else (LIBXMLPP_FOUND)
    message(FATAL_ERROR "Required library tinyxml not found")
endif (LIBXMLPP_FOUND)
