#ifndef SMSADMIN_GENETAL_H
#define SMSADMIN_GENETAL_H

#include <string>

namespace smsadmin {

const std::string API_XML = "xml";
const std::string API_JSON = "json";

const std::string ACTION_BALANCE = "balance";
const std::string ACTION_SEND    = "send";
const std::string ACTION_STATE   = "state";
const std::string ACTION_HELP    = "help";

static std::string buffer;
int writer(char *data, unsigned long size, unsigned long nmemb, std::string *buffer);
std::string get_message_from_file(const std::string&);

}

#endif // SMSADMIN_GENETAL_H
