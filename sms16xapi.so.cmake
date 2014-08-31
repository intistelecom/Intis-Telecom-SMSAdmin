set(SMS16XAPI "sms16xapi")
set(SMS16XAPI_VER_MAJOR 1)
set(SMS16XAPI_VER_MINOR 0)
set(SMS16XAPI_VER_PATCH 0)
set(SMS16XAPI_VER_STRING "${SMS16XAPI_VER_MAJOR}.${SMS16XAPI_VER_MINOR}.${SMS16XAPI_VER_PATCH}")
set(SMS16XAPI_HDR
    "./include/sms16xapi/sms16xapi"
    "./include/sms16xapi/sms16xapi.h"
    "./include/sms16xapi/balance.h"
    "./include/sms16xapi/constants.h"
    "./include/sms16xapi/object.h"
    "./include/sms16xapi/req_balance.h"
    "./include/sms16xapi/sms.h"
    "./include/sms16xapi/req_sms.h"
    "./include/sms16xapi/status.h"
    "./include/sms16xapi/req_status.h"
    )
set(SMS16XAPI_SRC
    "./src/sms16xapi/object.cpp"
    "./src/sms16xapi/req_balance.cpp"
    "./src/sms16xapi/balance.cpp"
    "./src/sms16xapi/sms.cpp"
    "./src/sms16xapi/req_sms.cpp"
    "./src/sms16xapi/status.cpp"
    "./src/sms16xapi/req_status.cpp"
    )

add_library(${SMS16XAPI}
            ${SMSADMIN_MAKE_SCENARIO}
            ${SMS16XAPI_SRC}
            ${SMS16AXPI_HDR}
            )
set_target_properties(
    ${SMS16XAPI} PROPERTIES
    VERSION ${SMS16XAPI_VER_STRING}
    SOVERSION ${SMS16XAPI_VER_MAJOR}
    )

find_package(LibXML++ REQUIRED)

set_target_properties(${SMS16XAPI}
   PROPERTIES BUILD_WITH_INSTALL_RPATH OFF
   INSTALL_RPATH ${CMAKE_INSTALL_PREFIX}/${INSTALL_LIB_DIR}
   PUBLIC_HEADER "${SMS16XAPI_HDR}"
   )

install(TARGETS ${SMS16XAPI}
   LIBRARY DESTINATION ${INSTALL_LIB_DIR}
   ARCHIVE DESTINATION ${INSTALL_LIB_DIR}
   PUBLIC_HEADER DESTINATION "include/${SMS16XAPI}"
   )
