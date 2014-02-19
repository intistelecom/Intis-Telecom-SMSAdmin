# locate CURL library

set(CURL_MIN_VERSION 7.19)
include(FindPkgConfig)
pkg_check_modules(CURL libcurl>=${CURL_MIN_VERSION})
include_directories(BEFORE ${CURL_INCLUDE_DIRS})
target_link_libraries(smsadmin ${CURL_LIBRARIES})
