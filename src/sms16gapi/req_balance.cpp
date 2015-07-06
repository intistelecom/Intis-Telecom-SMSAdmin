#include <sstream>
#include <sms16gapi/req_balance.h>
#include "../md5/md5.h"

namespace sms16gapi {

using namespace std;

ReqBalance::ReqBalance(const std::string &l,
                       const std::string &t,
                       const std::string &a
                       ): Request(l, t, a)
{}

string
ReqBalance::render()
{
    ostringstream out;
    out << "login=" << login
        << "&"
        << "return=" << api
        << "&"
        << "signature=" << signature()
        << "&"
        << "timestamp=" << last_timestamp
        ;

    return out.str();
}

string
ReqBalance::signature()
{
    ostringstream out;
    out << login << api << generate_utc_timestamp() << token;
    m_signature = md5(out.str());
    return m_signature;
}

}
