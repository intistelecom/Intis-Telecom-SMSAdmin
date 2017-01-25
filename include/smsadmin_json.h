/**
 * Header file of smsadmin json
 * Contains all json functions of packege
 *
 * @date 06/07/2015
 * @time 07:05:00
 * @version 2.0.0
 * @task #45
 * @author Alexander M Artamonov <art.alex.m@gmail.com>
 * @package manager
 */

#ifndef SMSADMIN_JSON_INCLUDED
#define SMSADMIN_JSON_INCLUDED

namespace smsadmin {
namespace json {

std::string balance(); /// Returns balance for the given account
std::string send();    /// Process send sms scenario
std::string state();   /// Get state for sms
std::string operator_info(); /// Get operator informatopn by phone number

}
}
#endif // SMSADMIN_H_INCLUDED
