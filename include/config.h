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

namespace smsadmin {
namespace config {

/**
 * Implements configuration aspect of smsadmin. Use Sigletone pattern
 *
 */
class Config
{
    public:
        ~Config();

        static Config& get_instance();

    protected:
    private:
        Config();
        Config(Config const&);
        void operator=(Config const&);
};

}}
#endif // CONFIG_H
