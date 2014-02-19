set(TARGET "smsadmin")
project(${TARGET})
cmake_minimum_required(VERSION 2.6)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR})

include_directories("./include/")
aux_source_directory("./src" SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST})

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

set(SMS16XAPI "sms16xapi")
set(SMS16XAPI_VER_MAJOR 0)
set(SMS16XAPI_VER_MINOR 1)
set(SMS16XAPI_VER_PATCH 0)
set(SMS16XAPI_VER_STRING "${SMS16XAPI_VER_MAJOR}.${SMS16XAPI_VER_MINOR}.${SMS16XAPI_VER_PATCH}")
set(SMS16XAPI_HDR
    "./include/sms16xapi/sms16xapi"
    "./include/sms16xapi/sms16xapi.h"
    "./include/sms16xapi/balance.h"
    "./include/sms16xapi/constants.h"
    "./include/sms16xapi/object.h"
    "./include/sms16xapi/req_balance.h"
    )
set(SMS16XAPI_SRC
    "./src/sms16xapi/object.cpp"
    "./src/sms16xapi/req_balance.cpp"
    "./src/sms16xapi/balance.cpp"
    )

add_library(${SMS16XAPI}
#            SHARED
            ${SMS16XAPI_SRC}
            ${SMS16AXPI_HDR}
            )
set_target_properties(
    ${SMS16XAPI} PROPERTIES
    VERSION ${SMS16XAPI_VER_STRING}
    SOVERSION ${SMS16XAPI_VER_MAJOR}
    )
target_link_libraries(${TARGET} ${SMS16XAPI})

configure_file(
    "${CMAKE_SOURCE_DIR}/global.cmake.h"
    "${CMAKE_SOURCE_DIR}/include/global.h"
)

set_target_properties(${TARGET}
   PROPERTIES BUILD_WITH_INSTALL_RPATH OFF
   INSTALL_RPATH ${CMAKE_INSTALL_PREFIX}/lib/
   INSTALL_NAME_DIR ${CMAKE_INSTALL_PREFIX}/bin/
#   PUBLIC_HEADER ${CMAKE_INSTALL_PREFIX}/include/
   )

install(TARGETS ${TARGET} # ${SMS16XAPI}
   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
#   PUBLIC_HEADER DESTINATION include
   )

#install(FILES ${SMS16XAPI_HDR} DESTINATION include)
