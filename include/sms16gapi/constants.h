#ifndef SMS16GAPI_CONSTANTS_H
#define SMS16GAPI_CONSTANTS_H

#include <string>
#include <map>
#include <sms16gapi/errors_codes.h>

namespace sms16gapi {

using namespace std;

/**
 * Default urls for service
 * TODO: Redefine them from configuration file and Config object
 */
const string BALANCE_URL = "https://go.intistele.com/external/get/balance.php";
const string SMS_URL     = "https://go.intistele.com/external/get/send.php";
const string STATE_URL   = "https://go.intistele.com/external/get/status.php";
const string STAMP_URL   = "https://go.intistele.com/external/get/timestamp.php";
const string OPERATOR_URL = "https://go.intistele.com/external/get/operator.php";
const string DEFAULT_DATE = "now";

/// Init ERROR_CODES constant
const map<string, string> ERROR_CODES = init_error_codes();

}


#endif // CONSTANTS_H
