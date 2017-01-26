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

#include <ctime>
#include <sstream>
#include <curl/curl.h>
#include <sms16gapi/request.h>

namespace sms16gapi {

using namespace std;

Request::Request(const string &lgn,
                 const string &tkn,
                 const string &api_type)
{
    login = lgn;
    token = tkn;
    api = api_type;
    use_local_time = true;
    last_timestamp = "-1";
}

string
Request::generate_utc_timestamp()
{
    if (use_local_time) {
        ostringstream out;
        time_t rawtime, utctime;
        struct tm * ptm;

        time(&rawtime);
        ptm = gmtime (&rawtime);
        utctime = mktime(ptm);

        out << utctime;
        last_timestamp = out.str();
    }

    return last_timestamp;
}

Request&
Request::set_timestamp(const std::string &t)
{
    last_timestamp = t;
    use_local_time = false;
    return *this;
}

string
Request::implode_string_array(vector<string> &arr)
{
    ostringstream out;

    for (unsigned i = 0, e = arr.size(); i < e; ++i)
    {
        out << arr.at(i);
        if (i < e-1) out << ",";
    }

    return out.str();
}

string
Request::url_escape(const string& param)
{
    CURL *curl = curl_easy_init();
    string out;
    if(curl) {
          char *output = curl_easy_escape(curl, param.data(), param.length());
          out = output;
          curl_free(output);
    }
    curl_easy_cleanup(curl);
    return out;
}

}
