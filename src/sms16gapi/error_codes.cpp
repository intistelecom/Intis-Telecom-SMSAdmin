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

#include <string>
#include <map>
#include <sms16gapi/errors_codes.h>

namespace sms16gapi {

using namespace std;

map<string, string> init_error_codes() {
    map<string, string> errors;

    errors["000"] = "Service unavailable";
    errors["1"]   = "Signature not specified";
    errors["2"]   = "Login not specified";
    errors["3"]   = "Text not specified";
    errors["4"]   = "Phone number not specified";
    errors["5"]   = "Sender not specified";
    errors["6"]   = "Invaild signature";
    errors["7"]   = "Invalid login";
    errors["8"]   = "Invalid sender name";
    errors["9"]   = "Sender name not registered";
    errors["10"]  = "Sender name not approved";
    errors["11"]  = "There are forbidden words in the text";
    errors["12"]  = "Error in SMS sending";
    errors["13"]  = "Phone number is in the stop list. SMS sending to this number is forbidden";
    errors["14"]  = "There are more than 50 numbers in the request";
    errors["15"]  = "List not specified";
    errors["16"]  = "Invalid phone number";
    errors["17"]  = "SMS ID not specified";
    errors["18"]  = "Status not obtained";
    errors["19"]  = "Empty response";
    errors["20"]  = "The number already exists";
    errors["21"]  = "No name";
    errors["22"]  = "Template already exists";
    errors["23"]  = "Month not specifies (Format: YYYY-MM)";
    errors["24"]  = "Timestamp not specified";
    errors["25"]  = "Error in access to the list";
    errors["26"]  = "There are no numbers in the list";
    errors["27"]  = "No valid numbers";
    errors["28"]  = "Date of start not specified (Format: YYYY-MM-DD)";
    errors["29"]  = "Date of end not specified (Format: YYYY-MM-DD)";
    errors["30"]  = "No date (format: YYYY-MM-DD)";

    return errors;
}


}
