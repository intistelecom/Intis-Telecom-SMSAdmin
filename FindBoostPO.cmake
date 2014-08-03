# Try to find libboost_program_options
set(Boost_MIN_VERSION 1.53)

set(SAVED_SUF ${CMAKE_FIND_LIBRARY_SUFFIXES})

if (NOT SMSADMIN_MAKE_SHARED)
    set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
endif()

find_package(Boost ${Boost_MIN_VERSION} REQUIRED COMPONENTS program_options regex)
include_directories(${Boost_INCLUDE_DIRS})

if (NOT SMSADMIN_MAKE_SHARED)
    set(index 0)
    foreach (BLIB ${Boost_LIBRARIES})
        MATH(EXPR index "${index}+1")
        set(MY_BOOST_LIB "my_boost_lib_${index}")
        add_library(${MY_BOOST_LIB} STATIC IMPORTED)
        set_target_properties(${MY_BOOST_LIB} PROPERTIES IMPORTED_LOCATION ${BLIB})
        target_link_libraries(${TARGET} ${MY_BOOST_LIB})
    endforeach (BLIB)
else()
    target_link_libraries(${TARGET} ${Boost_LIBRARIES})
endif()

set(CMAKE_FIND_LIBRARY_SUFFIXES ${SAVED_SUF})

message(STATUS "-L${Boost_LIBRARIES} -I${Boost_INCLUDE_DIRS}")
