#include <iostream>
#include "smsadmin.h"

using namespace std;
using namespace smsadmin;

int main(int argc, char **argv)
{
    log::Log &logger     = log::Log::get_instance();       /// init logging system
    config::Config &conf = config::Config::get_instance(); /// init config system

    logger
        .set_level(log::DEBUG)
        .set_package("init");

    string action(ACTION_HELP);

    conf.parse_cmd_params(argc, argv);

    if (conf().count("conf")) { /// Configuration file detected
        conf.parse_config_file(conf["conf"].as<string>());
    }

    if (conf().count("action") and !conf().count("help")) {
        action = conf["action"].as<string>();
    }

    if (ACTION_HELP == action) {
        if (conf.has_error()) logger.set_verbose(1).set_inited(true).dump();
        cout << help();
        return 0;
    }

    logger
        .set_level(conf["level"].as<string>())
        .set_ignore_log(conf().count("ignore-log"))
        .set_file(conf["log"].as<string>())
        .set_inited(true);

    int result  = conf.has_error() | !(logger.is_open() | logger.is_log_ignore());
    int verbose = result ? 1 : conf().count("verbose");

    logger
        .set_verbose(verbose)
        .dump();

    if (!result) {
        if (conf().count("token")) {
            if (ACTION_BALANCE == action)
                cout << balance() << endl;
            if (ACTION_SEND == action)
                cout << send() << endl;
            if (ACTION_STATE == action)
                cout << state();
        } else {
            logger.error("Required parameter '--token' not set");
            result = 1;
        }
    }

    return result;
}
