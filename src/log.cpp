#include <stdexcept>
#include <iostream>
#include "log.h"

namespace smsadmin {
namespace log {

Log::Log() : inited(false), buffer(50), verbose(false)
{
    set_level();
    set_package("main");
    buffer.clear();
}

Log& Log::debug(const std::string &str, ...)
{
    va_list args;
    va_start (args, str);
    _write(new Entity(DEBUG), str, args);
    va_end(args);

    return *(this);
}

Log& Log::error(const std::string &str, ...)
{
    va_list args;
    va_start (args, str);
    _write(new Entity(ERROR), str, args);
    va_end(args);

    return *(this);
}

Log& Log::info (const std::string &str, ...)
{
    va_list args;
    va_start(args, str);
    _write(new Entity(INFO), str, args);
    va_end(args);

    return *(this);
}

Log& Log::dump()
{
    if (!inited)
        throw std::runtime_error("Storage is not initialized yet");

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
    if (verbose and ent->level->level >= level)
        std::cout << ent->to_string() << std::endl;
}

Log::~Log()
{
    buffer.clear();
}

Log& Log::get_instance()
{
    static Log instance;
    return instance;
}

}}
