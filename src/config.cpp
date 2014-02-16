#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "config.h"
#include "log.h"

namespace smsadmin {
namespace config {

cfg& get_instance()
{
    static cfg instance;
    return instance;
}

void parse_cmd_params(int argc, char** argv)
{
    cfg &data = get_instance();
    log::Log &logger = log::Log::get_instance();
    std::string opkg = logger.set_package("config");
    int c;

    data["verbose"] = "0";
    data["action"]  = "help";

    for (int index = 0; index < argc; index++)
        logger.debug("Argument %s at index %d", argv[index], index);

    while ((c = getopt (argc, argv, "vtk:")) != -1)
    {
        switch (c)
        {
            case 'v':
                data["verbose"] = "1";
                break;
            case 't':
                if (NULL != optarg)
                    data["token"] = std::string(optarg);
                break;

            case '?':
                if (optopt == 't')
                    logger.error("Option '-t' requires an argument");
                else if (isprint (optopt))
                    logger.error("Unknown option '-%c'", optopt);
                else
                    logger.error("Unknown option character `\\x%x'", optopt);
            default:
                ;
        }
    }
    logger.set_package(opkg);

}

}}
