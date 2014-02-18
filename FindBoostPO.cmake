# Try to find libboost_program_options
set(Boost_MIN_VERSION 1.41)

find_package(Boost ${Boost_MIN_VERSION} REQUIRED COMPONENTS program_options)
include_directories(${Boost_INCLUDE_DIRS})
target_link_libraries(smsadmin ${Boost_LIBRARIES})
