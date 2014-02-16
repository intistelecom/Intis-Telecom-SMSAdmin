/**
 * Main header file of smsadmin
 * Contains all gloabal functions of packet
 *
 * @date 16/02/2014
 * @time 13:02:00
 * @version 0.1
 * @task #9
 * @author Alexander M Artamonov <art.alex.m@gmail.com>
 * @package manager
 */

#ifndef SMSADMIN_H_INCLUDED
#define SMSADMIN_H_INCLUDED

#include <sms16xapi/sms16xapi>
#include "config.h"
#include "log.h"

namespace smsadmin {

const std::string VERSION = "0.1";

std::string help();    /// Creates formated string with help
std::string balance(); /// Returns balance for the given account

}

#endif // SMSADMIN_H_INCLUDED
