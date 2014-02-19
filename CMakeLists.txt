project(smsadmin)
cmake_minimum_required(VERSION 2.6)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR})

include_directories("./include/")
aux_source_directory("./src" SRC_LIST)
aux_source_directory("./src/sms16xapi" SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST})

#add_library("sms16xapi"
#            SHARED
#            "./src/sms16xapi/object.cpp"
#            "./src/sms16xapi/req_balance.cpp"
#            "./src/sms16xapi/balance.cpp"
#            )

set(SMSADMIN_BUILD_DATE "0000-00-00T00:00:00+0000")
if (UNIX)
    execute_process(COMMAND "date" "+%FT%T%z" OUTPUT_VARIABLE SMSADMIN_BUILD_DATE)
    string(REGEX REPLACE "(\r?\n)+$" "" SMSADMIN_BUILD_DATE "${SMSADMIN_BUILD_DATE}")
endif (UNIX)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif(NOT CMAKE_BUILD_TYPE)
message(STATUS "Set build type to ${CMAKE_BUILD_TYPE}")

find_package(BoostPO REQUIRED)
find_package(LibXML++ REQUIRED)
find_package(Curl REQUIRED)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    find_package(Cppunit REQUIRED)
endif(CMAKE_BUILD_TYPE STREQUAL "Debug")

configure_file(
    "${CMAKE_SOURCE_DIR}/global.cmake.h"
    "${CMAKE_SOURCE_DIR}/include/global.h"
)
