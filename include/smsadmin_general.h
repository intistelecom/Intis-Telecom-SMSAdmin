#ifndef SMSADMIN_GENETAL_H
#define SMSADMIN_GENETAL_H

#include <string>

namespace smsadmin {

static std::string buffer;
int writer(char *data, unsigned long size, unsigned long nmemb, std::string *buffer);
std::string get_message_from_file(const std::string&);

}

#endif // SMSADMIN_GENETAL_H
