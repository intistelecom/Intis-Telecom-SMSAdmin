set(TARGET "smsadmin")
project(${TARGET})
cmake_minimum_required(VERSION 2.6)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR})
set(INSTALL_LIB_DIR lib CACHE PATH "Installation directory for libraries")

include_directories("./include/")
aux_source_directory("./src" SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST})

set(SMSADMIN_VER_NAME   "Cold Start")
set(SMSADMIN_VERSION    "0.1")
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
find_package(Curl REQUIRED)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    find_package(Cppunit REQUIRED)
endif(CMAKE_BUILD_TYPE STREQUAL "Debug")

include(./sms16xapi.so.cmake)
target_link_libraries(${TARGET} ${SMS16XAPI})

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
