#include <iostream>
#include "global.h"
#include "log.h"
#include "config.h"
#include "translation.h"
#include "security_purify.h"
#include "smsadmin_general.h"
#include "smsadmin_json.h"

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

    if (conf().count("conf") and !conf.has_error()) { /// Configuration file detected

        string conf_file = conf["conf"].as<string>();
        if (0 == conf_file.compare("c"))
            conf_file = SMSADMIN_DEFAULT_CONF_FILE;

        conf.parse_config_file(conf_file);
        if (conf().count("tpl")) { /// Tpl option detected, join to config
            conf.join_tpl(conf["tpl"].as<string>());
        }
        conf.join_config_params();
    }

    if (conf().count("action") and !conf().count("help") and !conf.has_error()) {
        action = conf["action"].as<string>();
    }

    if (ACTION_HELP == action) {
        if (conf.has_error()) {
            logger.set_verbose(1).set_inited(true).dump();
        } else {
            cout << help();
        }
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
            log::SecurityPurify::get_instance()
                    .add(conf["token"].as<string>(), "********");

            string (*job)() = &help;

            if (!conf().count("login")) {
                logger.set_verbose(1).error(tr("Parameter --login is require with json api"));
                result = 1;
            } else {
                if (ACTION_BALANCE == action)
                    job = &json::balance;
                if (ACTION_SEND == action)
                    job = &json::send;
                if (ACTION_STATE == action)
                    job = &json::state;
            }

            cout << job();
        } else {
            string answer(tr("Required parameter '--token' not set"));
            logger.set_verbose(1).error(answer);
            result = 1;
        }
    }
    logger.dump();
    return result;
}
