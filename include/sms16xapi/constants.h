#ifndef CONSTANTS_H_INCLUDED
#define CONSTANTS_H_INCLUDED

#include <string>

namespace sms16xapi {

using namespace std;

const string API_VERSION = "1.4";
const string VERSION     = "1.0";

/**
 * Default urls for sms16.ru
 * TODO: Redefine them from configuration file and Config object
 */
const string BALANCE_URL = "https://xml.sms16.ru/xml/balance.php";
const string SMS_URL     = "https://xml.sms16.ru/xml/index.php";
const string STATE_URL   = "https://xml.sms16.ru/xml/state.php";

const string DEFAULT_DATE = "now";

/**
 * Message states
 */
const string DELIVER = "deliver";
const string REJECT  = "reject";
const string EXPIRED = "expired";
const string PARTLY_DELIVER = "partly_deliver";
const string NOT_DELIVER    = "not_deliver";
const string NEW  = "new";
const string RECEIVED = "recieved";
const string SEND = "send";

}

#endif // CONSTANTS_H_INCLUDED
