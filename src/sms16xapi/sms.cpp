#include <sstream>
#include <stdexcept>
#include <sms16xapi/constants.h>
#include <sms16xapi/sms.h>

namespace sms16xapi
{

Sms::Sms():
    operator_id("-"),
    parts("-"),
    originator("-"),
    text("-"),
    recipient("-"),
    operator_text("-"),
    date(DEFAULT_DATE)
{
    type = "sms";
    position_sms_in_query = 0;
}

Sms* Sms::set_originator(const string &val)
{
    originator = val;
    return this;
}

Sms* Sms::set_text(const string &val)
{
    text = val;
    return this;
}

Sms* Sms::set_recipient(const string &val)
{
    recipient = val;
    return this;
}

Sms* Sms::set_date(const string &val)
{
    date = val;
    return this;
}

string Sms::render()
{
    ostringstream out;
    if (0 >= position_sms_in_query)
        throw invalid_argument("Requered attribute 'position_sms_in_query' not set");

    out << "<message " << "type=\"" << type << "\">"
        << "<sender>" << originator << "</sender>"
        << "<text>" << text << "</text>"

        << "<abonent "
            << "phone=\"" << recipient << "\" "
            << "number_sms=\"" << position_sms_in_query << "\" " ;
        if (0 != date.compare(DEFAULT_DATE)) {
            out << "time_send=\"" << date << "\" ";
        }
        out << "/>";

    out << "</message>";

    return out.str();
}

Sms* Sms::set_position(int p)
{
    position_sms_in_query = p;
    return this;
}

}
