#include <sstream>
#include <sms16gapi/req_operator.h>
#include "../md5/md5.h"

namespace sms16gapi {

using namespace std;

ReqOperator::ReqOperator(const std::string &l,
                       const std::string &t,
                       const std::string &a
                       ): Request(l, t, a)
{
}

string
ReqOperator::render()
{
    ostringstream out;
    out << "login=" << login
        << "&"
        << "phone=" << phone
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
ReqOperator::signature()
{
    ostringstream out;
    out << login
        << phone
        << api /// "return"
        << generate_utc_timestamp() /// "timestamp"
        << token;

    m_signature = md5(out.str());
    return m_signature;
}

ReqOperator&
ReqOperator::set_phone(const string &ph)
{
    phone = ph;
    return *this;
}
}
