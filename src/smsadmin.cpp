#include <iomanip>
#include <sstream>
#include "smsadmin.h"

namespace smsadmin {

std::string help()
{
    using namespace std;
    int fcolumn = 20, scolumn = 50;
    std::ostringstream help;
    help.setf(ios::left);
    help << "Smsadmin version: " << VERSION << " \"Could Start\"" << endl
         << "Sms16.ru API version: " << sms16xapi::API_VERSION << endl
         << "Build date: 2014-02-14 14:58:00" << endl << endl
         << "Usage: smsadmin command [options] [params]" << endl << endl
         << "Avalible commands:" << endl
         << setw(fcolumn) << "   balance" << setw(scolumn) << "Check balance for requered account" << endl
         << setw(fcolumn) << "   help"    << setw(scolumn) << "This help" << endl
         << endl;

    /// Output global options and params
    help << "Global options:" << endl
         << setw(fcolumn) << "   -v"      << setw(scolumn) << "Verbouse output. Dumps log in console" << endl
         << endl;

    /// Output options and params for balance
    help << "Balance command options:" << endl
         << setw(20) << "   -t <token>"   << setw(50) << "Token for requested account. See your provider help to choose token"
         << endl
         << endl;

    return help.str();
}
}
