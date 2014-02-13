#ifndef CONSTANTS_H_INCLUDED
#define CONSTANTS_H_INCLUDED

#include <glibmm/ustring.h>

namespace sms16xapi {

using namespace Glib;

const ustring API_VERSION = "1.4";
const ustring VERSION     = "1.0";

/**
 * Default urls for sms16.ru
 */
const ustring BALANCE_URL = "https://xml.sms16.ru/xml/balance.php";
const ustring SMS_URL     = "https://xml.sms16.ru/xml/index.php";
const ustring STATE_URL   = "https://xml.sms16.ru/xml/state.php";

/**
 * Message states
 */
const ustring DELIVER = "deliver";
const ustring REJECT  = "reject";
const ustring EXPIRED = "expired";
const ustring PARTLY_DELIVER = "partly_deliver";
const ustring NOT_DELIVER    = "not_deliver";
const ustring NEW  = "new";
const ustring RECEIVED = "recieved";
const ustring SEND = "send";

}

#endif // CONSTANTS_H_INCLUDED
