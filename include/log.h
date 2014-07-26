/**
 * Define log package logic
 *
 * @date 14/02/2014
 * @time 13:02:00
 * @version 0.1
 * @task #8
 * @author Alexander M Artamonov <art.alex.m@gmail.com>
 * @package log
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

const std::string ISO8601 = "%FT%T%z"; /// ISO 8601 Time format

/**
 * Init log levels
 *
 */
struct Level
{
    int level;
    std::string name;
};
const Level DEBUG = {1, "debug"};
const Level INFO  = {2, "info"};
const Level WARN  = {3, "warn"};
const Level ERROR = {4, "error"};

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

        Log& debug(const std::string&, ...);
        Log& error(const std::string&, ...);
        Log& info (const std::string&, ...);
        Log& warn (const std::string&, ...);

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
