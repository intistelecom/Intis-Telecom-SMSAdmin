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

    int verbose = conf.has_error() ? 1 : conf["verbose"].as<int>();

    logger
        .set_verbose(verbose)
        .set_inited(true)
        .dump();

    if (conf().count("action")) {
        string action(conf["action"].as<string>());

        if ("balance" == action) {
            if (!conf().count("token")) {
                logger.set_verbose(1).error("Required parameter 'token' not set");
            } else {
                cout << "Balance for account is: " << balance() << endl;
                return 0;
            }
        }
    }

    cout << help();
    return 1;
}
