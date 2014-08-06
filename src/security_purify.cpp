#include <exception>
#include <sstream>
#include "global.h"
#include "security_purify.h"

namespace smsadmin {
namespace log {

SecurityPurify::SecurityPurify()
{}

SecurityPurify::~SecurityPurify()
{
    replaces.clear();
}

SecurityPurify& SecurityPurify::get_instance()
{
    static SecurityPurify instance;
    return instance;
}

SecurityPurify& SecurityPurify::content(const string &c)
{
    in = c;
    return *this;
}

string SecurityPurify::str()
{
    return out;
}


SecurityPurify& SecurityPurify::clear()
{
    in.clear();
    out.clear();
    return *this;
}

SecurityPurify& SecurityPurify::run()
{
    out = in;
    if (1 == SMSADMIN_SECURITY_PURIFY) {
        for(unsigned i = 0; i < replaces.size(); ++i) {
            out = boost::regex_replace(out, replaces[i].first, replaces[i].second);
        }
    }
    return *this;
}

SecurityPurify& SecurityPurify::add(const string &e, const string &r)
{
    ostringstream rep;
    rep << "$&";
    if (e.size() == 40) {
        rep.str("");
        rep << e.substr(0, 8) << r << e.substr(32, 8);
    }
    boost::regex exp(e);
    replaces.push_back(make_pair<boost::regex, string>(exp, rep.str()));
    return *this;
}

}}
