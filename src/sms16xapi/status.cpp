#include <sstream>
#include <stdexcept>
#include <sms16xapi/constants.h>
#include <sms16xapi/status.h>

namespace sms16xapi
{

Status::Status() :
    operator_id("-"),
    status("-"),
    crt_time(DEFAULT_DATE),
    operator_err("-")
{}

string Status::render()
{
    ostringstream out;

    out << "<id_sms>"
        << operator_id
        << "</id_sms>";

    return out.str();
}

}
