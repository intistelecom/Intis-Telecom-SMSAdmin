#include <sstream>
#include "smsadmin.h"

namespace smsadmin {

std::string help()
{
    using namespace std;
    ostringstream help;
    help << "Smsadmin version: " << smsadmin::VERSION << " \"Could Start\"" << endl
         << "Sms16.ru API version: " << sms16xapi::API_VERSION << endl
         << "Build date: " << SMSADMIN_BUILD_DATE << endl << endl
         << config::Config::get_instance().help()
         ;

    return help.str();
}

}
