# Try to find libboost_program_options
set(Boost_MIN_VERSION 1.53)

set(SAVED_SUF ${CMAKE_FIND_LIBRARY_SUFFIXES})

if (NOT SMSADMIN_MAKE_SHARED)
    set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
endif()

find_package(Boost ${Boost_MIN_VERSION} REQUIRED COMPONENTS program_options)
include_directories(${Boost_INCLUDE_DIRS})

if (NOT SMSADMIN_MAKE_SHARED)
    set(BOOST_PO "boost_po")
    add_library(${BOOST_PO} STATIC IMPORTED)
    set_target_properties(${BOOST_PO} PROPERTIES IMPORTED_LOCATION ${Boost_LIBRARIES})
    target_link_libraries(${TARGET} ${BOOST_PO})
else()
    target_link_libraries(${TARGET} ${Boost_LIBRARIES})
endif()

set(CMAKE_FIND_LIBRARY_SUFFIXES ${SAVED_SUF})

message(STATUS "-L${Boost_LIBRARIES} -I${Boost_INCLUDE_DIRS}")
