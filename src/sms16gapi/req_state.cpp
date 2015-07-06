#include <sstream>
#include <sms16gapi/req_state.h>
#include "../md5/md5.h"

namespace sms16gapi {

using namespace std;

ReqState::ReqState(const std::string &l,
                       const std::string &t,
                       const std::string &a
                       ): Request(l, t, a), state_id()
{}

string
ReqState::render()
{
    ostringstream out;
    out << "login=" << login
        << "&"
        << "return=" << api
        << "&"
        << "state=" << implode_string_array(state_id)
        << "&"
        << "signature=" << signature()
        << "&"
        << "timestamp=" << last_timestamp
        ;

    return out.str();
}

string
ReqState::signature()
{
    ostringstream out;
    out << login
        << api /// "return"
        << implode_string_array(state_id)
        << generate_utc_timestamp() /// "timestamp"
        << token;

    m_signature = md5(out.str());
    return m_signature;
}


ReqState&
ReqState::add_state(const string &id)
{
    state_id.push_back(id);
    return *this;
}

}
