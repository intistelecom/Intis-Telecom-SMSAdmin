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
