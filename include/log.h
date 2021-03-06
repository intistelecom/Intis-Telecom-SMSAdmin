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

#ifndef LOG_H
#define LOG_H

#include <string>
#include <ctime>
#include <vector>
#include <cstdarg>
#include <fstream>
#include <map>

namespace smsadmin {
namespace log {

#ifdef __unix__
const std::string ISO8601 = "%FT%T%z"; /// ISO 8601 Time format
#elif defined(WIN32)
const std::string ISO8601 = "%Y-%m-%dT%X";
#endif

/**
 * Init log levels
 *
 */
struct Level
{
    int level;
    std::string name;
};
const Level DEBUG  = {1, "debug"};
const Level INFO   = {2, "info"};
const Level WARN   = {3, "warn"};
const Level ERROR1 = {4, "error"};

/**
 * Implements replace string logic
 */
std::string str_replace(const std::string&);

/**
 * Implements string formating as fprintf() or same
 *
 */
std::string format(const char* fmt, ...);
std::string format(const char* fmt, va_list&);

class Entity;

/**
 * Implements logging aspect of smsadmin. Use Sigletone pattern
 *
 */
class Log
{
    public:
        ~Log();

        static Log& get_instance();

        Entity& debug(const std::string&);
        Entity& error(const std::string&);
        Entity& info (const std::string&);
        Entity& warn (const std::string&);

        /**
         * Save buffer to inited storage
         *
         * @throws std::runtime_error Storage is not initialized yet
         */
        Log& dump();

        Log& set_verbose(bool = true);
        Log& set_inited (bool = false);
        Log& set_level  (const Level& = DEBUG);
        Log& set_level  (const std::string&);
        Log& set_file   (const std::string&);
        Log& set_ignore_log (bool);

        /**
         * Set command option to Entity
         *
         * @return std::string previose value
         */
        std::string set_package(const std::string&);

        /**
         * Check if log has opened file
         */
        bool is_open();

        /**
         * Check if log file is ignore by option 'ignore_log'
         */
        bool is_log_ignore();

    protected:
        bool inited;                 /// Set to true on inited config. Until use buffer to push log
        std::vector<Entity*> buffer; /// Use this buffer to store log entities, before init config
        bool verbose;                /// Dublicate log to console, std::cout
        int  level;                  /// Log level to filter entries
        std::ofstream file;          /// File stream for write log
        std::string package;
        bool ignore_log;             /// Ignore write to file log
        std::map<std::string, Level> level_map; /// Map for string usage

        void _write(Entity*, const std::string&, va_list&);
        void _write(Entity*);
    private:
        Log();
        Log(Log const&);
        void operator=(Log const&);
};

/**
 * Implements the presentation of log entry. Example:
 * time ISO8601             | log level | programm part | text description |
 * 2014-02-14T18:38:07+0400 | debug     | init          | some text        |
 *
 * Use only heap based objects or define other functions with Entity& return value
 *
 * @throws std::invalid_argument Requered command parameter not set
 * @throws std::invalid_argument Requered description parameter not set
 *
 */
class Entity
{
    friend class Log;

    public:
        Entity(const Level&, std::string, std::string = "");
        Entity(const Level&);

        std::string to_string();
        Entity* set_cmd(const std::string&);
        Entity* set_desc(const std::string&);
        Entity& operator()(const std::string &);
        Entity& operator<< (const std::string &arg);
    private:
        time_t rawtime;
        Level *level;
        std::string cmd;
        std::string desc;

        void _check_null_cmd();
        void _check_null_desc();
};

}}
#endif // LOG_H
