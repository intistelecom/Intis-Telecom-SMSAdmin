#include <iostream>
#include "smsadmin.h"

using namespace std;
using namespace smsadmin;

/// init logging system
log::Log &logger = log::Log::get_instance();

/// init config system
config::cfg &conf = config::get_instance();

int main(int argc, char **argv)
{

    logger.set_inited(false)
          .set_verbose(true)
          .set_level(log::DEBUG);

    logger.set_package("init");
    logger.debug("Some test");
    logger.info("Test info level with parameter %d", 100500);
    logger.error("Write some error string");
    logger.info("Проверим строки в utf-8");

    try {
        logger.dump();
    } catch (exception &e) {
        std::string old(logger.set_package("log"));
        logger.error(e.what())
              .set_package(old);
    }
    logger.info("Test other string after log error");


    config::parse_cmd_params(argc, argv);
    logger.info(conf["action"]);

    // cout << help();
    logger.set_inited(true).dump();

    return 0;
}
