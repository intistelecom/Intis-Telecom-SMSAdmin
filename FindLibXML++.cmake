# locate libxml++ library

# This module defines
# LIBXMLPP_LIBRARIES
# LIBXMLPP_FOUND
# LIBXMLPP_INCLUDE_DIRS
# LIBXMLPP_CFLAGS
# LIBXMLPP_LINKFLAGS
# LIBXMLPP_MIN_VERSION

set(LIBXMLPP_MIN_VERSION 2.35)
include(FindPkgConfig)
pkg_check_modules(LIBXMLPP libxml++-2.6>=${LIBXMLPP_MIN_VERSION})
message(STATUS "Found LibXml++: ${LIBXMLPP_LIBRARIES}")
include_directories(BEFORE ${LIBXMLPP_INCLUDE_DIRS})
target_link_libraries(smsadmin ${LIBXMLPP_LIBRARIES})
