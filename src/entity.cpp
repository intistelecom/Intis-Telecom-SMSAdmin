#include <cstdio>
#include <stdexcept>
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
    int size = 1024;
    int nsize;
    char* buffer = NULL;
    va_list args;

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

    std::string ret(buffer);
    delete[] buffer;
    return ret;
}

std::string str_replace(const std::string &subject)
{
    std::string exp = "[\\r\\n]";
    std::string rep = "";
    std::string out;
    boost::regex e(exp);
    out = boost::regex_replace(subject, e, rep);
    return out;
}

}}
