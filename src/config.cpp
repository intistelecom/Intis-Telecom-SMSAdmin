#include <vector>
#include <sstream>
#include <exception>
#include <typeinfo>
#include "smsadmin.h"

namespace smsadmin {
namespace config {

using namespace std;

string Config::help()
{
    ostringstream help;
    help << "Usage: smsadmin <action> [options] [params]" << endl
         << "Avalible actions:" << endl
         << "  balance - shows balance for account by token" << endl
         << "  send    - sends sms" << endl
         << "  state   - get sms delivery state" << endl
         << endl
         << general
         << endl
         << send
         << endl
         << state
         << endl
         << balance
         ;

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

void Config::parse_config_file(const string &file_name)
{
    log::Log &logger = log::Log::get_instance();
    string opkg(logger.set_package("config"));

    try {
        po::parsed_options parsed = po::parse_config_file<char>(file_name.c_str(), all, true);
        po::store(parsed, vm);
        po::notify(vm);
    } catch (exception &e) {
        is_error = true;
        logger.error("Catch config file parser error: %s", e.what());
    }

    logger.set_package(opkg);
}

Config::Config():
    general("Global options"),
    send("Send action options"),
    state("State action options"),
    balance("Balance action options"),
    is_error(false)
{
    log::Log &logger = log::Log::get_instance();
    string opkg(logger.set_package("config"));
    try
    {
        general.add_options()
            ("verbose,w", "Verbose output. Dumps log in console")
            ("help,h", "Produce this help")
            ("token,t", po::value<string>(), "Token for requested account. See your provider help to choose token")
            ("log,l", po::value<string>()->default_value(SMSADMIN_DEFAULT_LOG_FILE), "Log file name")
            ("conf,c", po::value<string>()->implicit_value(SMSADMIN_DEFAULT_CONF_FILE), "Configuration file")
            ("ignore-log", "Ignore file log")
            ("level", po::value<string>()->default_value(log::DEBUG.name), "Log level: debug, info, warn, error")
            ;

        send.add_options()
            ("originator,o", po::value<string>(), "Sender name")
            ("text,x", po::value<string>(), "Text sms")
            ("date,d", po::value<string>()->default_value(sms16xapi::DEFAULT_DATE), "Send date. If not set, sms will be send immediately")
            ("tpl,m", po::value<string>(), "Config template. Use with -c option")
            ("smsurl", po::value<string>()->default_value(sms16xapi::SMS_URL), "Url for sending sms")
            ;

        state.add_options()
            ("stateurl", po::value<string>()->default_value(sms16xapi::STATE_URL), "Url to get sent sms status")
            ;

        balance.add_options()
            ("balanceurl", po::value<string>()->default_value(sms16xapi::BALANCE_URL), "Url to get account balance")
            ;

        hidden.add_options()
            ("action", po::value<string>()->default_value(ACTION_HELP), "Action to execute")
            ("params", po::value< vector<string> >(), "Explicit command line params")
            ;

        numeric.add("action", 1).add("params", -1);

        all.add(general).add(send).add(balance).add(state).add(hidden);
    } catch (exception &e) {
        logger.error("Catch exception on config init: %s, %s", typeid(e).name(), e.what());
    }
    logger.set_package(opkg);
}

Config& Config::get_instance()
{
    static Config instance;
    return instance;
}

}}
