#include <vector>
#include <sstream>
#include <exception>
#include <typeinfo>
#include "config.h"
#include "log.h"

namespace smsadmin {
namespace config {

using namespace std;

string Config::help()
{
    ostringstream help;
    help << "Usage: smsadmin <action> [options] [params]" << endl
         << "Avalible actions:" << endl
         << "  balance - shows balance for account by token" << endl << endl
         << general;

    return help.str();
}

const po::variables_map& Config::operator()()
{
    return vm;
}

const po::variable_value&
Config::get(const string &opt)
{
    return vm[opt];
}

const po::variable_value&
Config::operator[](const string &opt)
{
    return get(opt);
}

bool Config::has_error()
{
    return is_error;
}

void Config::parse_cmd_params(int ac, char** av)
{
    Config &data = Config::get_instance();
    log::Log &logger = log::Log::get_instance();
    string opkg(logger.set_package("config"));
    vector<string> to_pass_further;

    try
    {
        po::parsed_options parsed = po::command_line_parser(ac, av)
                                    .options(all)
                                    .positional(numeric)
                                    .allow_unregistered()
                                    .run();

        to_pass_further = po::collect_unrecognized(parsed.options, po::exclude_positional);
        po::store(parsed, vm);
        po::notify(vm);

    } catch (exception &e) {
        is_error = true;
        logger.error("Catch cmd line parameters parser error: %s", e.what());
    }

    if (!to_pass_further.empty()) {
        for (vector<string>::iterator it = to_pass_further.begin();
             it != to_pass_further.end();
             ++it)
            logger.warn("Detected unknown command line option: '%s'", (*it).c_str());
    }
    logger.set_package(opkg);
}

Config::Config(): general("Global options"), is_error(false)
{
    log::Log &logger = log::Log::get_instance();
    string opkg(logger.set_package("config"));
    try
    {
        general.add_options()
            ("verbose,v", po::value<int>()->implicit_value(1)->default_value(0), "Verbose output. Dumps log in console")
            ("help,h", "Produce this help")
            ("token,t", po::value<string>(), "Token for requested account. See your provider help to choose token")
            ;

        hidden.add_options()
            ("action", po::value<string>()->default_value("help"), "Action to execute")
            ;

        numeric.add("action", 1);

        all.add(general).add(hidden);
    } catch (exception &e) {
        logger.error("Catch exeption on config init: %s, %s", typeid(e).name(), e.what());
    }
    logger.set_package(opkg);
}

Config& Config::get_instance()
{
    static Config instance;
    return instance;
}

}}
