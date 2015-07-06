/**
 * Main header file of smsadmin
 * Contains all global functions of packet
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

namespace smsadmin {

std::string help();    /// Creates formated string with help
std::string balance(); /// Returns balance for the given account
std::string send();    /// Process send sms scenario
std::string state();   /// Get state for sms

}

#endif // SMSADMIN_H_INCLUDED
