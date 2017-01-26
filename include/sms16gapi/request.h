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

#ifndef SMS16GAPI_REQUEST_H
#define SMS16GAPI_REQUEST_H

#include <string>
#include <vector>

namespace sms16gapi {

/// @abstract
class Request
{
public:
    Request(const std::string &lgn, /// login
            const std::string &tkn, /// token
            const std::string &api_type = "json" /// return responce type "xml", "json"
            );

    /// Generate query GET string
    /// ?login=test&signature=70a0a*****ff60681c&state=409129,401297&return=json&timestamp=1409887191
    virtual std::string render() = 0;

    /// Set expected timestamp and ignore generate_utc_timestamp() logic
    Request& set_timestamp(const std::string &t);

protected:
    std::string login; /// user login
    std::string token; /// user api token
    std::string m_signature; /// request signature based on api
    std::string api; /// responce type "json"
    std::string last_timestamp;  /// request Unix timestamp in UTC
    bool use_local_time; /// use generate_utc_timestamp() if true

    std::string generate_utc_timestamp(); /// return UTC timestamp and set last_timestamp

    /// Implode vector strings to one string with "," delimiter
    std::string implode_string_array(std::vector<std::string> &arr);

    /// Generate md5 signature for request.
    /// NOTE: Make generate_utc_timestamp() call
    virtual std::string signature() = 0;

    /// Urlescape characters in string
    std::string url_escape(const std::string& param);
};

}

#endif // REQUEST_H
