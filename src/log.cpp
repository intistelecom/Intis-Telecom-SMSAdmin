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

#include <stdexcept>
#include <iostream>
#include "log.h"
#include "translation.h"

namespace smsadmin {
namespace log {

Log::Log() : inited(false), buffer(50), verbose(false), ignore_log(false)
{
    set_level();
    set_package("main");
    buffer.clear();

    level_map[DEBUG.name] = DEBUG;
    level_map[INFO.name]  = INFO;
    level_map[WARN.name]  = WARN;
    level_map[ERROR1.name] = ERROR1;
}

Entity& Log::debug(const std::string &str)
{
    buffer.push_back(new Entity(DEBUG, package, str));
    return *(buffer.back());
}

Entity& Log::error(const std::string &str)
{

    buffer.push_back(new Entity(ERROR1, package, str));
    return *(buffer.back());
}

Entity& Log::info (const std::string &str)
{
    buffer.push_back(new Entity(INFO, package, str));
    return *(buffer.back());
}

Entity& Log::warn (const std::string &str)
{
    buffer.push_back(new Entity(WARN, package, str));
    return *(buffer.back());
}

Log& Log::dump()
{
    if (!inited)
        throw std::runtime_error(tr("Log storage is not initialized yet"));

    for (unsigned i=0; i<buffer.size(); i++)
    {
        _write(buffer.at(i));
    }
    buffer.clear();

    return *(this);
}

Log& Log::set_verbose(bool v)
{
    verbose = v;
    return *(this);
}

Log& Log::set_inited (bool i)
{
    inited = i;
    return *(this);
}

Log& Log::set_level (const Level &l)
{
    level = l.level;
    return *(this);
}

Log& Log::set_level(const std::string &name)
{
    if (level_map.find(name) != level_map.end()) {
        level = level_map[name].level;
    }
    return *(this);
}

Log& Log::set_ignore_log (bool i)
{
    ignore_log = i;
    return *(this);
}

Log& Log::set_file (const std::string &file_name)
{
    Entity* ent;
    if (!ignore_log) {
        file.open(file_name.c_str(), std::ofstream::app);
        if (!file.is_open()) {
            error(tr("Log file %s is not available: not found or has no write permissions"))(file_name);
        }
    }
    return *(this);
}

bool Log::is_open()
{
    return file.is_open();
}

bool Log::is_log_ignore()
{
    return ignore_log;
}

std::string Log::set_package(const std::string &p)
{
    std::string old(package);
    package = p;
    return old;
}

void Log::_write(Entity *ent, const std::string &str, va_list &args)
{
    ent->set_desc(format(str.c_str(), args))
       ->set_cmd(package);

    if (inited)
    {
        _write(ent);
        delete ent;
    } else {
        buffer.push_back(ent);
    }
}

void Log::_write(Entity *ent)
{
    if (ent->level->level >= level) {
        if (verbose)
            std::cout << ent->to_string() << std::endl;
        if (is_open() and !ignore_log)
            file << ent->to_string() << std::endl;
    }
}

Log::~Log()
{
    buffer.clear();
    file.close();
}

Log& Log::get_instance()
{
    static Log instance;
    return instance;
}

}}
