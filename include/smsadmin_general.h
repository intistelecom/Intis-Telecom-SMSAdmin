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

#ifndef SMSADMIN_GENETAL_H
#define SMSADMIN_GENETAL_H

#include <string>

namespace smsadmin {

const std::string API_JSON = "json";

const std::string ACTION_BALANCE = "balance";
const std::string ACTION_SEND    = "send";
const std::string ACTION_STATE   = "state";
const std::string ACTION_HELP    = "help";
const std::string ACTION_OPERATOR = "operator";

static std::string buffer;
int writer(char *data, unsigned long size, unsigned long nmemb, std::string *buffer);
std::string get_message_from_file(const std::string&);

std::string help();    /// Creates formated string with help

}

#endif // SMSADMIN_GENETAL_H
