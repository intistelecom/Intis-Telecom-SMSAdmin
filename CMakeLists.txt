project(smsadmin)
cmake_minimum_required(VERSION 2.6)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}")
aux_source_directory(. SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST})
include_directories("./include/")

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif(NOT CMAKE_BUILD_TYPE)
message(STATUS "Set build type to ${CMAKE_BUILD_TYPE}")

find_package(LibXML++ REQUIRED)
find_package(Curl REQUIRED)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    find_package(Cppunit REQUIRED)
endif(CMAKE_BUILD_TYPE STREQUAL "Debug")
