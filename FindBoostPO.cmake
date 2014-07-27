# Try to find libboost_program_options
set(Boost_MIN_VERSION 1.53)

find_package(Boost ${Boost_MIN_VERSION} REQUIRED COMPONENTS program_options)
include_directories(${Boost_INCLUDE_DIRS})
target_link_libraries(${TARGET} ${Boost_LIBRARIES})

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "-L${Boost_LIBRARIES} -I${Boost_INCLUDE_DIRS}")
endif()
