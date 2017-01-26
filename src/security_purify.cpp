/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2017 Intis Telecom
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

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
