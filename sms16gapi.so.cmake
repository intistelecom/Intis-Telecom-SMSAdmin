set(SMS16GAPI "sms16gapi")
set(SMS16GAPI_VER_MAJOR 3)
set(SMS16GAPI_VER_MINOR 0)
set(SMS16GAPI_VER_PATCH 0)
set(SMS16GAPI_VER_STRING "${SMS16GAPI_VER_MAJOR}.${SMS16GAPI_VER_MINOR}.${SMS16GAPI_VER_PATCH}")
set(SMS16GAPI_HDR
    "./include/sms16gapi/sms16gapi"
    "./include/sms16gapi/sms16gapi.h"
    "./include/sms16gapi/constants.h"
    "./include/sms16gapi/error_codes.h"
    "./include/sms16gapi/request.h"
    "./include/sms16gapi/req_balance.h"
    "./include/sms16gapi/req_send.h"
    "./include/sms16gapi/req_state.h"
    )
set(SMS16GAPI_SRC
    "./md5/md5.cpp"
    "./src/sms16gapi/request.cpp"
    "./src/sms16gapi/req_balance.cpp"
    "./src/sms16gapi/req_send.cpp"
    "./src/sms16gapi/req_state.cpp"
    "./src/sms16gapi/error_codes.cpp"
    )

add_library(${SMS16GAPI}
            ${SMSADMIN_MAKE_SCENARIO}
            ${SMS16GAPI_SRC}
            ${SMS16AXPI_HDR}
            )
set_target_properties(
    ${SMS16GAPI} PROPERTIES
    VERSION ${SMS16GAPI_VER_STRING}
    SOVERSION ${SMS16GAPI_VER_MAJOR}
    )

find_package(Boost REQUIRED)

set_target_properties(${SMS16GAPI}
   PROPERTIES BUILD_WITH_INSTALL_RPATH OFF
   INSTALL_RPATH ${CMAKE_INSTALL_PREFIX}/${INSTALL_LIB_DIR}
   PUBLIC_HEADER "${SMS16GAPI_HDR}"
   )

install(TARGETS ${SMS16GAPI}
   LIBRARY DESTINATION ${INSTALL_LIB_DIR}
   ARCHIVE DESTINATION ${INSTALL_LIB_DIR}
   PUBLIC_HEADER DESTINATION "include/${SMS16GAPI}"
   )
