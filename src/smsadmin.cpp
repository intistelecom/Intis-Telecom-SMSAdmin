#include <sstream>
#include <exception>
#include <curl/curl.h>
#include "smsadmin.h"

namespace smsadmin {

using namespace std;

string help()
{
    ostringstream help;
    help << endl
         << "Smsadmin version: " << smsadmin::VERSION << " \"Could Start\"" << endl
         << "Sms16.ru API version: " << sms16xapi::API_VERSION << endl
         << "Build date: " << SMSADMIN_BUILD_DATE << endl << endl
         << config::Config::get_instance().help()
         << endl
         ;

    return help.str();
}

static char error_buffer[CURL_ERROR_SIZE];
static string buffer;
static int writer(char *data, size_t size, size_t nmemb, string *buffer);
CURLcode send_xml_request(const string &url, const string &post);

string balance()
{
    config::Config &conf = config::Config::get_instance();
    log::Log &logger = log::Log::get_instance();
    string opkg(logger.set_package("balance"));

    namespace sx = sms16xapi;

    string token = conf["token"].as<string>();
    sx::ReqBalance req(token);
    sx::Balance *b = new sx::Balance();

    string xml = req.add(b).render(); /// add(b) is require to get result
    string answer;
    logger.debug(xml);
    CURLcode result = send_xml_request(sx::BALANCE_URL, xml);

    if (CURLE_OK == result) {
        xml.clear();
        xml.append(buffer);
        buffer.clear();
        logger.debug(xml);

        try {
            req.parse(xml); /// Sets attrs 'money', 'currency' for Balance *b
            logger.info("Balance for account by token %s is: %s %s",
                        token.c_str(),
                        b->get_money().c_str(),
                        b->get_currency().c_str()
            );
            answer = b->get_money() + " " + b->get_currency();
        } catch (exception &e) {
            logger.error("Catch error on parse: %s", e.what());
            answer.append(e.what());
        }
    } else {
        logger.error("Network error: %s", error_buffer);
    }

    logger.set_package(opkg);
    return answer;
}

CURLcode send_xml_request(const string &url, const string &post)
{
    CURL *curl;
    CURLcode result;
    curl = curl_easy_init();
    if (curl) {
        struct curl_slist *slist = NULL;
        slist = curl_slist_append(slist, "Content-type: text/xml; charset=utf-8");

        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, slist);
        curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, error_buffer);
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_HEADER, 0);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writer);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
        curl_easy_setopt(curl, CURLOPT_POST, 1);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post.c_str());

        result = curl_easy_perform(curl);
        curl_slist_free_all(slist);
    }
    curl_easy_cleanup(curl);
    return result;
}

static int writer(char *data, size_t size, size_t nmemb, string *buffer)
{
    int result = 0;
    if (NULL != buffer) {
        buffer->append(data, size * nmemb);
        result = size * nmemb;
    }
    return result;
}

}
