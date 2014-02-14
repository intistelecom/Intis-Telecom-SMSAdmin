#include "log.h"

using namespace std;
using namespace smsadmin;

/// Init logging system
log::Log &logger = log::Log::get_instance();

int main(int argc, char **argv)
{
    logger.set_inited(false)
          .set_verbose(true)
          .set_level(log::INFO);

    logger.set_package("init");
    logger.debug("some test");
    logger.info("test info level");
    logger.error("write some error string");

    try {
        logger.dump();
    } catch (exception &e) {
        std::string old(logger.set_package("log"));
        logger.error(e.what())
              .set_package(old);
    }
    logger.info("Test other string after log error");
    logger.set_inited(true).dump();

    return 0;
}
