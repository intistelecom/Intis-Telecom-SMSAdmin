#include <sstream>
#include <sms16gapi/req_send.h>
#include <sms16gapi/constants.h>
#include "../md5/md5.h"

namespace sms16gapi {

using namespace std;

ReqSend::ReqSend(const std::string &l,
                       const std::string &t,
                       const std::string &a
                       ): Request(l, t, a), phone()
{
    sending_time = "";
}

string
ReqSend::render()
{
    ostringstream out;
    out << "login=" << login
        << "&"
        << "phone=" << implode_string_array(phone)
        << "&"
        << "return=" << api
        << "&"
        << "sender=" << sender
        << "&"
        << "signature=" << signature()
        << "&"
        << "text=" << url_escape(text)
        << "&"
        << "timestamp=" << last_timestamp
        ;

    if (!sending_time.empty()) {
        out << "&"
            << "sendingTime="
            << url_escape(sending_time);
    }

    return out.str();
}

string
ReqSend::signature()
{
    ostringstream out;
    out << login
        << implode_string_array(phone)
        << api /// "return"
        << sender
        << sending_time
        << text
        << generate_utc_timestamp() /// "timestamp"
        << token;

    m_signature = md5(out.str());
    return m_signature;
}


ReqSend&
ReqSend::add_phone(const string &recipient)
{
    phone.push_back(recipient);
    return *this;
}

ReqSend&
ReqSend::set_sender(const string &originator)
{
    sender = originator;
    return *this;
}

ReqSend&
ReqSend::set_text(const string &message)
{
    text = message;
    return *this;
}

ReqSend&
ReqSend::set_sending_time(const string &st)
{
    if (0 != st.compare(DEFAULT_DATE))
    {
        sending_time = st;
    }
    return *this;
}

}
