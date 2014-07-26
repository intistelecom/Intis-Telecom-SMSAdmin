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

#include <string>
#include <boost/program_options.hpp>

namespace po = boost::program_options;

namespace smsadmin {
namespace config {

/**
 * Implements configuration aspect of smsadmin. Use Sigletone pattern
 *
 */
class Config
{
    public:
        static Config& get_instance();

        void parse_cmd_params(int, char**);

        /**
         * Parse configuration file
         */
        void parse_config_file(const std::string&);

        const po::variable_value& get(const std::string&);

        const po::variable_value& operator[](const std::string&);

        const po::variables_map&  operator()();

        std::string help();

        bool has_error();

    protected:
        po::options_description all,
                                general,
                                send,
                                state,
                                balance,
                                hidden;
        po::positional_options_description numeric;
        po::variables_map vm;

        bool is_error;

    private:
        Config();
        Config(Config const&);
        void operator=(Config const&);
};

}}
#endif // CONFIG_H
