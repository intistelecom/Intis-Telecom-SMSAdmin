#include <iostream>
#include "smsadmin.h"

using namespace std;
using namespace smsadmin;

int main(int argc, char **argv)
{
    log::Log &logger     = log::Log::get_instance();       /// init logging system
    config::Config &conf = config::Config::get_instance(); /// init config system

    logger.set_level(log::DEBUG)
          .set_package("init");

    conf.parse_cmd_params(argc, argv);

    if (conf().count("conf")) { /// Configuration file detected
        conf.parse_config_file(conf["conf"].as<string>());
    }

    int verbose = conf.has_error() ? 1 : conf["verbose"].as<int>();
    int result  = conf.has_error();

    logger
        .set_verbose(verbose)
        .set_inited(true)
        .dump();

    if (conf().count("action") and !conf.has_error()) {
        string action(conf["action"].as<string>());

        if (ACTION_HELP == action) {
            cout << help();
        } else if (conf().count("token")) {
            if (ACTION_BALANCE == action)
                cout << balance() << endl;
            if (ACTION_SEND == action)
                cout << send() << endl;
            if (ACTION_STATE == action)
                cout << state() << endl;
        } else {
            logger.set_verbose(1).error("Required parameter 'token' not set");
            result = 1;
        }
    }

    return result;
}
