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

#include <fstream>
#include <sstream>
#include <stdexcept>
#include "global.h"
#include "config.h"
#include "translation.h"
#include "smsadmin_general.h"

namespace smsadmin {

using namespace std;

string help()
{
    ostringstream help;
    help << endl
         << tr("Smsadmin version: ") << SMSADMIN_VER_STRING << " \""
         << SMSADMIN_VER_NAME << "\"" << endl
         << tr("Build date: ") << SMSADMIN_BUILD_DATE << endl << endl
         << config::Config::get_instance().help()
         << endl
         ;

    return help.str();
}

int writer(char *data, unsigned long size, unsigned long nmemb, string *buffer)
{
    int result = 0;
    if (NULL != buffer) {
        buffer->append(data, size * nmemb);
        result = size * nmemb;
    }
    return result;
}

string get_message_from_file(const string &name)
{
    ostringstream out;
    ifstream file;
    file.open(name.c_str(), ios_base::out);
    if (!file.is_open()) {
        throw runtime_error(tr("Message file is not available: not found or has no read permissions"));
    }

    out << file.rdbuf();
    file.close();
    return out.str();
}

}
