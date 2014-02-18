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

    cout << endl;
    cout << help() << endl;

    return 0;
}
