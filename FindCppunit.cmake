# locate cpp unit library

set(CPPUNIT_MIN_VERSION 1.12)
include(FindPkgConfig)
pkg_check_modules(CPPUNIT cppunit>=${CPPUNIT_MIN_VERSION})
include_directories(${CPPUNIT_INCLUDE_DIRS})
target_link_libraries(smsadmin ${CPPUNIT_LIBRARIES})
