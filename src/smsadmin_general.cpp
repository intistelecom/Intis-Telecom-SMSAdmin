#include <fstream>
#include <sstream>
#include <stdexcept>
#include "translation.h"
#include "smsadmin_general.h"

namespace smsadmin {

using namespace std;

int writer(char *data, unsigned long size, unsigned long nmemb, string *buffer)
{
    int result = 0;
    if (NULL != buffer) {
        buffer->append(data, size * nmemb);
        result = size * nmemb;
    }
    return result;
}

string get_message_from_file(const string &name)
{
    ostringstream out;
    ifstream file;
    file.open(name.c_str(), ios_base::out);
    if (!file.is_open()) {
        throw runtime_error(tr("Message file is not available: not found or has no read permissions"));
    }

    out << file.rdbuf();
    file.close();
    return out.str();
}

}
