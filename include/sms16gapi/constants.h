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

#ifndef SMS16GAPI_CONSTANTS_H
#define SMS16GAPI_CONSTANTS_H

#include <string>
#include <map>
#include <sms16gapi/error_codes.h>

namespace sms16gapi {

using namespace std;

/**
 * Default urls for service
 * TODO: Redefine them from configuration file and Config object
 */
const string BALANCE_URL = "https://go.intistele.com/external/get/balance.php";
const string SMS_URL     = "https://go.intistele.com/external/get/send.php";
const string STATE_URL   = "https://go.intistele.com/external/get/status.php";
const string STAMP_URL   = "https://go.intistele.com/external/get/timestamp.php";
const string OPERATOR_URL = "https://go.intistele.com/external/get/operator.php";
const string DEFAULT_DATE = "now";

/// Init ERROR_CODES constant
const map<string, string> ERROR_CODES = init_error_codes();

}


#endif // CONSTANTS_H
