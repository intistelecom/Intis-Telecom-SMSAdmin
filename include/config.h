/**
 * Main header file of Config
 * Contains all gloabal functions of package
 *
 * @date 16/02/2014
 * @time 15:06:00
 * @version 0.1
 * @task #10
 * @author Alexander M Artamonov <art.alex.m@gmail.com>
 * @package config
 */

#ifndef CONFIG_H
#define CONFIG_H

#include <map>
#include <string>

namespace smsadmin {
namespace config {

typedef std::map<std::string, std::string> cfg;

cfg& get_instance();

/**
 * Parse command line parameters
 *
 */
void parse_cmd_params(int, char**);

}}
#endif // CONFIG_H
