#include <cstdio>
#include <stdexcept>
#include <boost/regex.hpp>
#include "log.h"
#include "security_purify.h"

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
        throw std::invalid_argument("Requered command parameter not set");
}

void Entity::_check_null_desc()
{
    if (desc.empty())
        throw std::invalid_argument("Requered description parameter not set");
}

std::string format(const char* fmt, ...)
{
    va_list vl;
    va_start(vl, fmt);
    std::string frmd(format(fmt, vl));
    va_end(vl);
    return frmd;
}

std::string format(const char* fmt, va_list &vl)
{
    int size = 1024;
    char* buffer = 0;
    buffer = new char[size];
    int nsize = vsnprintf(buffer, size, fmt, vl);
    if(size<=nsize) /// fail delete buffer and try again
    {
        delete[] buffer;
        buffer = 0;
        buffer = new char[nsize+1]; //+1 for /0
        nsize = vsnprintf(buffer, size, fmt, vl);
    }
    std::string ret(buffer);
    delete[] buffer;
    return ret;
}

std::string str_replace(std::string &subject)
{
    std::string exp = "[\\r\\n]";
    std::string rep = "";
    boost::regex e(exp);
    return
            boost::regex_replace(subject, e, rep);
}

}}
