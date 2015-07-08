#include <sstream>
#include <map>
#include <exception>
#include <curl/curl.h>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>
#include <sms16gapi/sms16gapi>
#include "global.h" /// Generated by cmake
#include "config.h"
#include "log.h"
#include "smsadmin_general.h"
#include "smsadmin_json.h"
#include "translation.h"

namespace smsadmin {
namespace json {

using namespace std;
namespace pt = boost::property_tree;
namespace sg = sms16gapi;

static char error_buffer[CURL_ERROR_SIZE];
CURLcode send_get_request(const string &url);

string balance()
{
    config::Config &conf = config::Config::get_instance();
    log::Log &logger = log::Log::get_instance();
    string opkg(logger.set_package("json::balance"));
    ostringstream out;
    stringstream ss;
    string token(conf["token"].as<string>());
    string url(conf["balanceurl"].as<string>());
    string login(conf["login"].as<string>());
    string query;
    string answer;
    pt::ptree responce;

    sg::ReqBalance rb(login, token, "json");
    query = url + "?" + rb.render();

    logger.debug(query);
    CURLcode result = send_get_request(query);

    if (CURLE_OK == result) {
        query.clear();
        ss << buffer;
        buffer.clear();
        logger.debug(ss.str());
        answer.empty();

        try {
            responce.clear();
            pt::read_json(ss, responce);
            query = responce.get<string>("error", "NULL");

            if (0 != query.compare("NULL")) {
                try {
                    answer = sg::ERROR_CODES.at(query);
                    answer.insert(0, " \"");
                    answer.append("\"");
                } catch (...) {}

                query.append(answer);

                throw runtime_error("Server responce has error #" + query);
            }

            out << tr("Balance for account is: ")
                << responce.get<string>("money", "-")
                << responce.get<string>("currency", "-")                
                << endl
                ;
        } catch (exception &e) {
            logger.set_verbose(1).error(tr("Catch error on parse: %s")) << e.what();
        }
    } else {
        logger.set_verbose(1).error(tr("Network error: %s")) << error_buffer;
    }

    logger.set_package(opkg);    
    return out.str();
}

string send()
{
    config::Config &conf = config::Config::get_instance();
    log::Log &logger = log::Log::get_instance();
    string opkg(logger.set_package("json::send"));

    ostringstream out;
    bool good = true;
    string token(conf["token"].as<string>());
    string url(conf["smsurl"].as<string>());
    string answer;
    string text; 
    stringstream ss;
    string login(conf["login"].as<string>());
    string query;
    pt::ptree responce;

    if (!conf().count("params")) {
        good = false;
        answer = tr("Expected at least 1 phone numder");
        logger.set_verbose(1).error(answer);
    }

    if (!conf().count("msgfile")) {
        if (conf().count("text")) {
            text = conf["text"].as<string>();
        }
    } else
        try {
            text = get_message_from_file(conf["msgfile"].as<string>());
        } catch (exception &e) {
            good = false;
            logger.set_verbose(1).error(e.what());
        }

    if (text.empty()) {
        good = false;
        answer = tr("Text should be set");
        logger.set_verbose(1).error(answer);
    }

    if (!conf().count("originator")) {
        good = false;
        answer = tr("Originator should be set");
        logger.set_verbose(1).error(answer);
    }

    if (good) {
        vector<string> params = conf["params"].as< vector<string> >();
        sg::ReqSend request(login, token);

        request.set_text(text).set_sender(conf["originator"].as<string>());

        for(vector<string>::iterator p = params.begin(); p < params.end(); ++p) {
            request.add_phone((*p));
        }

        query = url + "?" + request.render();
        logger.debug(query);
        logger.info(tr("Try send sms: originator '%s', text '%s', date '%s'"))
                << conf["originator"].as<string>()
                << text
                << conf["date"].as<string>()
                   ;

        CURLcode result = send_get_request(query);

        if (CURLE_OK == result) {
            query.clear();
            ss << buffer;
            buffer.clear();
            logger.debug(ss.str());
            answer.empty();

            try {
                responce.clear();
                pt::read_json(ss, responce);
                map<string, string> info;
                query = responce.get<string>("error", "NULL");

                if (0 != query.compare("NULL")) {
                    try {
                        answer = sg::ERROR_CODES.at(query);
                        answer.insert(0, " \"");
                        answer.append("\"");
                    } catch (...) {}

                    query.append(answer);

                    throw runtime_error("Server responce has error #" + query);
                }

                BOOST_FOREACH(pt::ptree::value_type &ch, responce) {
                    BOOST_FOREACH(pt::ptree::value_type &op, ch.second) {
                        info["phone"] = op.first;
                        info["id_sms"] = op.second.get<string>("id_sms", "-");
                        info["count_sms"] = op.second.get<string>("count_sms", "-");
                        info["error"] = op.second.get<string>("error", "-");
                        info["cost"] = op.second.get<string>("cost", "-");
                    }

                    out << tr("sms. ")
                        << tr("phone: ") << info["phone"] << ", "
                        << tr("id sms: ") << info["id_sms"] << ", "
                        << tr("sms parts: ") << info["count_sms"] << ", "
                        << tr("send status: ") << info["error"] << ", "
                        << tr("cost: ") << info["cost"]
                        << endl;

                    logger.info(
                        tr("phone %s, id sms %s, parts %s, send status '%s', cost %s"))
                            << info["phone"]
                            << info["id_sms"]
                            << info["count_sms"]
                            << info["error"]
                            << info["cost"]
                            ;

                    info.clear();
                }

            } catch (exception &e) {
                logger.set_verbose(1).error(tr("Catch error on parse: %s")) << e.what();
            }
        } else {            
            logger.set_verbose(1).error(tr("Network error: %s")) << error_buffer;
        }
    }

    logger.set_package(opkg);
    return out.str();
}

string state()
{
    config::Config &conf = config::Config::get_instance();
    log::Log &logger = log::Log::get_instance();
    string opkg(logger.set_package("json::state"));

    ostringstream out;
    bool good = true;
    string token(conf["token"].as<string>());
    string url(conf["stateurl"].as<string>());
    string answer;
    stringstream ss;
    string login(conf["login"].as<string>());
    string query;
    pt::ptree responce;

    if (!conf().count("params")) {
        good = false;
        answer = tr("Expected at least 1 sms id");
        logger.set_verbose(1).error(answer);
    }

    if (good) {
        vector<string> params = conf["params"].as< vector<string> >();
        sg::ReqState request(login, token, "json");

        for (vector<string>::iterator operator_id = params.begin();
             operator_id < params.end(); ++operator_id) {
            request.add_state((*operator_id));
        }

        query = url + "?" + request.render();
        logger.debug(query);

        CURLcode result = send_get_request(query);

        if (CURLE_OK == result) {
            query.clear();
            logger.debug(buffer);
            ss << buffer;
            buffer.clear();
            answer.empty();

            try {
                responce.clear();
                pt::read_json(ss, responce);
                map<string, string> info;
                query = responce.get<string>("error", "NULL");

                if (0 != query.compare("NULL")) {

                    try {
                        answer = sg::ERROR_CODES.at(query);
                        answer.insert(0, " \"");
                        answer.append("\"");
                    } catch (...) {}

                    query.append(answer);

                    throw runtime_error("Server responce has error #" + query);
                }

                BOOST_FOREACH(pt::ptree::value_type &op, responce) {
                    info["id_sms"] = op.first;
                    info["status"] = op.second.get<string>("status", "-");
                    info["time"] = op.second.get<string>("time", "-");

                    logger.info(
                        tr("status '%s', id %s, time '%s', error code %s"))
                            << info["status"]
                            << info["id_sms"]
                            << info["time"]
                            << "0"
                               ;
                    out << tr("status. ")
                        << tr("sms state: ")   << info["status"] << ", "
                        << tr("sms id: ")      << info["id_sms"] << ", "
                        << tr("state time: ")  << info["time"] << ", "
                        << tr("error code: ")  << "0"
                        << endl;
                }
            } catch (exception &e) {
                logger.error(tr("Catch error on parse: %s")) << e.what();
                out << e.what() << endl;
            }
        } else {
            out << error_buffer;
            logger.error(tr("Network error: %s")) << error_buffer;
        }
    }

    logger.set_package(opkg);
    return out.str();
}

CURLcode send_get_request(const string &url)
{
    CURL *curl;
    CURLcode result;
    curl = curl_easy_init();

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, error_buffer);
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_HEADER, 0);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writer);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);

        result = curl_easy_perform(curl);
    }
    curl_easy_cleanup(curl);
    return result;
}
}
}