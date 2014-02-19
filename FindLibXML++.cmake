# locate libxml++ library

# This module defines
# LIBXMLPP_LIBRARIES
# LIBXMLPP_FOUND
# LIBXMLPP_INCLUDE_DIRS
# LIBXMLPP_CFLAGS
# LIBXMLPP_LINKFLAGS
# LIBXMLPP_MIN_VERSION

#set(LIBXMLPP_MIN_VERSION 2.35)
#include(FindPkgConfig)
#pkg_check_modules(LIBXMLPP libxml++-2.6>=${LIBXMLPP_MIN_VERSION})
#message(STATUS "Found LibXml++: ${LIBXMLPP_LIBRARIES}")
#include_directories(BEFORE ${LIBXMLPP_INCLUDE_DIRS})
#target_link_libraries(smsadmin ${LIBXMLPP_LIBRARIES})

set(LIBXMLPP_MIN_VERSION 2.6)
set(LIBXMLPP_FOUND FALSE)

find_path(LIBXMLPP_INCLUDE_DIRS
  NAMES tinyxml.h
  PATHS "/usr/include;/usr/local/include"
)

find_library(LIBXMLPP_LIBRARIES
  NAMES tinyxml
  PATHS "/usr/lib;/usr/lib64;/usr/local/lib;/usr/local/lib64"
)

if (LIBXMLPP_INCLUDE_DIRS AND LIBXMLPP_LIBRARIES)
    set(LIBXMLPP_FOUND TRUE)
endif (LIBXMLPP_INCLUDE_DIRS AND LIBXMLPP_LIBRARIES)

if (LIBXMLPP_FOUND)
    message(STATUS "Found tinyxml: headers ${LIBXMLPP_INCLUDE_DIRS}, libs ${LIBXMLPP_LIBRARIES}")
    include_directories(BEFORE ${LIBXMLPP_INCLUDE_DIRS})
    target_link_libraries(${TARGET} ${LIBXMLPP_LIBRARIES})
else (LIBXMLPP_FOUND)
    message(FATAL_ERROR "Required library tinyxml not found")
endif (LIBXMLPP_FOUND)
