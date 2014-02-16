#include "config.h"

namespace smsadmin {
namespace config {

Config::Config()
{
    //ctor
}

Config::~Config()
{
    //dtor
}

Config& Config::get_instance()
{
    static Config instance;
    return instance;
}

}}
