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
#include <vector>
#include <set>
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

        /**
         * Join options of config by tpl
         * @brief join_tpl
         */
        void join_tpl(const std::string&);

        /**
         * Parse commans line options
         * @brief parse_cmd_params
         */
        void parse_cmd_params(int, char**);

        /**
         * Join config file params to main config
         * @brief join_config_params
         */
        void join_config_params();

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
        std::vector<std::string> conf_pass_future;
        po::parsed_options *config_parsed;

        bool is_error;

        /// Replace options in variables map
        template<class T>
        void replace(
                std::map<std::string, po::variable_value> &vm,
                const std::string &opt,
                const T &val
                );

        /// Replace options in config_parsed
        template<class T>
        void replace(
                po::parsed_options& options,
                const std::string &opt,
                const T &val
                );

    private:
        Config();
        Config(Config const&);
        void operator=(Config const&);
};

}}
#endif // CONFIG_H
