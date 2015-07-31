set(TARGET "smsadmin")
project(${TARGET})
cmake_minimum_required(VERSION 2.8)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR})
set(INSTALL_LIB_DIR lib CACHE PATH "Installation directory for libraries")

include_directories("./include/")
aux_source_directory("./src" SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST})

set(SMSADMIN_VER_NAME   "Positive get/json")
set(SMSADMIN_VER_MAJOR  2)
set(SMSADMIN_VER_MINOR  0)
set(SMSADMIN_VER_PATCH  1)
set(SMSADMIN_VER_STRING "${SMSADMIN_VER_MAJOR}.${SMSADMIN_VER_MINOR}.${SMSADMIN_VER_PATCH}")
set(SMSADMIN_BUILD_DATE "0000-00-00T00:00:00+0000")
if (UNIX)
    execute_process(COMMAND "date" "+%FT%T%z" OUTPUT_VARIABLE SMSADMIN_BUILD_DATE)
    string(REGEX REPLACE "(\r?\n)+$" "" SMSADMIN_BUILD_DATE "${SMSADMIN_BUILD_DATE}")
endif (UNIX)

## Define default configs
if (WIN32)
    set(SMSADMIN__CONF_FILE "./smsadmin.cfn")
    set(SMSADMIN__LOG_FILE  "./smsadmin.log")
endif(WIN32)
if (UNIX)
    set(SMSADMIN__CONF_FILE "/etc/smsadmin.cfn")
    set(SMSADMIN__LOG_FILE  "/var/log/smsadmin.log")
endif(UNIX)

if (NOT SMSADMIN_DEFAULT_CONF_FILE)
    set(SMSADMIN_DEFAULT_CONF_FILE ${SMSADMIN__CONF_FILE})
endif()

if (NOT SMSADMIN_DEFAULT_LOG_FILE)
    set(SMSADMIN_DEFAULT_LOG_FILE ${SMSADMIN__LOG_FILE})
endif()

set(SMSADMIN_MAKE_SCENARIO STATIC)
if (SMSADMIN_MAKE_SHARED)
    set(SMSADMIN_MAKE_SCENARIO SHARED)
else()
    #set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
endif()

if (NOT SMSADMIN_SECURITY_PURIFY_DISABLE)
    set(SMSADMIN_SECURITY_PURIFY 1)
else()
    set(SMSADMIN_SECURITY_PURIFY 0)
endif()

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif(NOT CMAKE_BUILD_TYPE)
message(STATUS "Set build type to ${CMAKE_BUILD_TYPE}")

find_package(BoostPO REQUIRED)
find_package(Curl REQUIRED)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    find_package(Cppunit REQUIRED)
endif(CMAKE_BUILD_TYPE STREQUAL "Debug")

include(./sms16xapi.so.cmake)
target_link_libraries(${TARGET} ${SMS16XAPI})

include(./sms16gapi.so.cmake)
target_link_libraries(${TARGET} ${SMS16GAPI})

set_target_properties(${TARGET}
   PROPERTIES BUILD_WITH_INSTALL_RPATH OFF
   INSTALL_RPATH ${CMAKE_INSTALL_PREFIX}/${INSTALL_LIB_DIR}
   INSTALL_NAME_DIR bin
   )

install(TARGETS ${TARGET}
   RUNTIME DESTINATION bin
   )

add_custom_target(uninstall COMMAND "./delete.me") # Command to remove installation

configure_file(
    "${CMAKE_SOURCE_DIR}/global.cmake.h"
    "${CMAKE_SOURCE_DIR}/include/global.h"
)
