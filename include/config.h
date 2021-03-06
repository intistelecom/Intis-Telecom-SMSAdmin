/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2017 Intis Telecom
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
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
                                operator_info,
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
