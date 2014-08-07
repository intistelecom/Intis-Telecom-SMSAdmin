#include <vector>
#include <sstream>
#include <exception>
#include <boost/regex.hpp>
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

    try
    {
        po::parsed_options parsed = po::command_line_parser(ac, av)
                                    .options(all)
                                    .positional(numeric)
                                    .run();
        po::store(parsed, vm);
        po::notify(vm);
    } catch (exception &e) {
        is_error = true;
        logger.error("Catch cmd line parameters parser error: %s", e.what());
    }

    logger.set_package(opkg);
}

void Config::parse_config_file(const string &file_name)
{
    log::Log &logger = log::Log::get_instance();
    string opkg(logger.set_package("config"));

    try {
        config_parsed = new po::parsed_options(
                    po::parse_config_file<char>(file_name.c_str(), all, true));
        conf_pass_future = po::collect_unrecognized(
                    (*config_parsed).options, po::exclude_positional);
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
            ("token,t", po::value<string>(),
             "Token for requested account. See your provider help to choose token")
            ("log,l", po::value<string>()->default_value(SMSADMIN_DEFAULT_LOG_FILE), "Log file name")
            ("conf,c", po::value<string>()->implicit_value(SMSADMIN_DEFAULT_CONF_FILE),
             "Configuration file")
            ("ignore-log", "Ignore file log")
            ("level", po::value<string>()->default_value(log::DEBUG.name),
             "Log level: debug, info, warn, error")
            ;

        send.add_options()
            ("originator,o", po::value<string>(), "Sender name")
            ("text,x", po::value<string>(), "Text sms")            
            ("date,d", po::value<string>()->default_value(sms16xapi::DEFAULT_DATE)
                                          ->value_name("\"yyyy-mm-dd hh:mm:ss\""),
             "Send date. If not set, sms will be send immediately. NOTE: use qoutes for value")
            ("tpl,m", po::value<string>(), "Config template. Use with -c option")
            ("smsurl", po::value<string>()->default_value(sms16xapi::SMS_URL), "Url for sending sms")
            ("msgfile", po::value<string>(), "(Testing) Text sms from file. Option 'text' will be ignore.")
            ;

        state.add_options()
            ("stateurl", po::value<string>()->default_value(sms16xapi::STATE_URL),
             "Url to get sent sms status")
            ;

        balance.add_options()
            ("balanceurl", po::value<string>()->default_value(sms16xapi::BALANCE_URL),
             "Url to get account balance")
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

void Config::join_tpl(const string &tpl)
{
    log::Log &logger = log::Log::get_instance();
    string opkg(logger.set_package("config"));

    ostringstream epr;
    epr << "^" << tpl << "\\.(.+)";
    boost::regex prefix (epr.str());
    boost::match_results<string::const_iterator> what;
    string valueT, nameT;
    bool found = false;

    try {
        for (vector<string>::iterator op = conf_pass_future.begin();
             op != conf_pass_future.end();
             ++op)
        {
            if (boost::regex_match((*op), what, prefix))
            {
                found = true;
                valueT = (*++op);
                nameT = what[1];
                replace((*config_parsed), nameT, valueT);
            }
        }
    } catch (exception &e) {
        logger.error("Catch error while parse tpl '%s', option '%s': %s",
                     tpl.c_str(), nameT.c_str(), e.what());
        is_error = true;
        found = true;
    }

    if (!found) {
        logger.warn("Config section '%s' does not exists in config file", tpl.c_str());
    }
    logger.set_package(opkg);
}

template<class T>
void Config::replace(
        std::map<std::string, po::variable_value> &vm,
        const std::string &opt,
        const T &val
        )
{
    std::vector<T> value;
    value.push_back(val);
    const po::option_description &d = all.find(opt, false, false, false);
    static std::set<std::string> parsed;

    po::variable_value &v = vm[opt];
    if (parsed.end() == parsed.find(opt))
    {
        parsed.insert(opt);
        v = po::variable_value();
    }

    d.semantic()->parse(v.value(), value, false);
}

/**
 * This is a logic to replace only config file options
 * And command line options will be saved and used
 */
template<class T>
void Config::replace(
        po::parsed_options &options,
        const std::string &opt,
        const T &val
        )
{
    static set<string> parsed; /// save option names to avoid double replace in one iteration
    string option_name;
    bool exists = false;

    for (unsigned i = 0; i < options.options.size(); ++i)
    {
        option_name = options.options[i].string_key;
        if (0 == option_name.compare(opt)) {
            exists = true;
            if (parsed.end() == parsed.find(opt)) {
                parsed.insert(opt);
                options.options[i].value.clear();
            }
            options.options[i].value.push_back(val);
        }
    }

    if (!exists) {
        parsed.insert(opt);
        po::option new_option;
        new_option.string_key = opt;
        new_option.value.push_back(val);
        new_option.original_tokens.push_back(opt);
        options.options.push_back(new_option);
    }
}

void Config::join_config_params()
{
    log::Log &logger = log::Log::get_instance();
    string opkg(logger.set_package("config"));

    if (NULL == config_parsed) return;

    try {
        po::store((*config_parsed), vm);
        delete config_parsed;
        po::notify(vm);
    } catch (exception &e) {
        logger.error("Catch error while config file parse: %s", e.what());
        is_error = true;
    }
    logger.set_package(opkg);
}

}}
