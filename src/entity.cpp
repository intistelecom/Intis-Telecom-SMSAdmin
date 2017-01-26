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

#include <cstdio>
#include <stdexcept>
#include <sstream>
#include <stdarg.h>
#include <boost/regex.hpp>
#include "log.h"
#include "security_purify.h"
#include "translation.h"

namespace smsadmin {
namespace log {

Entity::Entity(const Level &l, std::string command, std::string description)
{
    level = const_cast<Level*>(&l);
    set_cmd(command);
    set_desc(description);
    time(&rawtime);
}

Entity::Entity(const Level &l)
{
    level = const_cast<Level*>(&l);
    time(&rawtime);
}

Entity* Entity::set_cmd(const std::string &command)
{
    cmd = command;
    return this;
}

Entity* Entity::set_desc(const std::string &description)
{
    desc = description;
    return this;
}

std::string Entity::to_string()
{
    _check_null_cmd();
    _check_null_desc();

    char buffer[25] = {'\0'};
    strftime(buffer, 25, ISO8601.c_str(), localtime(&rawtime));
    SecurityPurify &purifier = SecurityPurify::get_instance();
    string data = format(
                "%s | %s | %s | %s |",
                buffer,
                level->name.c_str(),
                cmd.c_str(),
                str_replace(desc).c_str()
            );

    return purifier.content(data).run().str();;
}

void Entity::_check_null_cmd()
{
    if (cmd.empty())
        throw std::invalid_argument(tr("Requered command parameter not set"));
}

void Entity::_check_null_desc()
{
    if (desc.empty())
        throw std::invalid_argument(tr("Requered description parameter not set"));
}

Entity& Entity::operator<< (const std::string &arg) {
    return (*this)(arg);
}

Entity& Entity::operator()(const std::string &arg) {
    using namespace std;
    string exp = "%s";
    boost::regex token(exp);
    desc = boost::regex_replace(desc, token, arg, boost::match_default | boost::format_first_only);
    return (*this);
}

std::string format(const char* fmt, ...)
{
    va_list vl;
    va_start(vl, fmt);
    std::string frmd = format(fmt, vl);
    va_end(vl);
    return frmd;
}

std::string format(const char* fmt, va_list &vl)
{
    using namespace std;

    int size = 1024;
    int nsize;
    char* buffer = NULL;
    va_list args;
    string ret = fmt;

    while (1) {
        va_copy(args, vl);
        buffer = new char[size];
        nsize = vsnprintf(buffer, size, fmt, args) +1;
        if (nsize > size) { /// fail delete buffer and try again
            size = nsize;
            delete[] buffer;
        } else {
            break;
        }
    }

    ret = buffer;
    delete[] buffer;
    return ret;
}

std::string str_replace(const std::string &subject)
{
    using namespace std;
    string exp = "[\\r\\n]";
    string rep = "";
    string out;
    boost::regex e;

    e.set_expression(exp);
    out = boost::regex_replace(subject, e, rep);

    return out;
}

}}
