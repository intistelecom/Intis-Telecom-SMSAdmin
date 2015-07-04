#include <sstream>
#include <map>
#include <exception>
#include <curl/curl.h>
#include "smsadmin_json.h"
#include "translation.h"
#include "smsadmin_general.h"

#include <sms16xapi/sms16xapi> /// FIXME: Remove

namespace smsadmin {
namespace json {

using namespace std;

static char error_buffer[CURL_ERROR_SIZE];
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
    string url(conf["balanceurl"].as<string>());

    logger.debug(xml);
    CURLcode result = send_xml_request(url, xml);

    if (CURLE_OK == result) {
        xml.clear();
        xml.append(buffer);
        buffer.clear();
        logger.debug(xml);

        try {
            req.parse(xml); /// Sets attrs 'money', 'currency' for Balance *b
            logger.info(tr("Balance for account by token %s is: %s %s"),
                        token.c_str(),
                        b->get_money().c_str(),
                        b->get_currency().c_str()
            );
            answer  = tr("Balance for account is: ");
            answer += b->get_money() + " " + b->get_currency() + "\n";
        } catch (exception &e) {
            logger.set_verbose(1).error(tr("Catch error on parse: %s"), e.what());
        }
    } else {  
        logger.set_verbose(1).error(tr("Network error: %s"), error_buffer);
    }

    logger.set_package(opkg);
    answer += "API: json\n" ;
    return answer;
}

string send()
{
    config::Config &conf = config::Config::get_instance();
    log::Log &logger = log::Log::get_instance();
    string opkg(logger.set_package("send"));

    ostringstream out;
    bool good = true;
    string token(conf["token"].as<string>());
    string url(conf["smsurl"].as<string>());
    string answer;
    string text;

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
        namespace sx = sms16xapi;
        string xml;
        sx::ReqSms request(token);
        sx::Sms *message;

        for(vector<string>::iterator p = params.begin(); p < params.end(); ++p) {
            message = (new sx::Sms())
                ->set_originator(conf["originator"].as<string>())
                ->set_text(text)
                ->set_recipient((*p))
                ->set_date(conf["date"].as<string>())
                ;
            request.add(message);
        }
        message = NULL;
        xml = request.render();
        logger.debug(xml);
        logger.info(tr("Try send sms: originator '%s', text '%s', date '%s'"),
            conf["originator"].as<string>().c_str(),
            text.c_str(),
            conf["date"].as<string>().c_str()
        );

        CURLcode result = send_xml_request(url, xml);

        if (CURLE_OK == result) {
            xml.clear();
            xml.append(buffer);
            buffer.clear();
            logger.debug(xml);

            try {
                request.parse(xml);
                vector<sx::Object*> items = request.get_children();
                for (vector<sx::Object*>::iterator sms = items.begin(); sms < items.end(); ++sms) {
                    message = dynamic_cast<sx::Sms*>((*sms));
                    logger.info(
                        tr("phone %s, id sms %s, parts %s, send status '%s'"),
                        message->recipient.c_str(),
                        message->get_operator_id().c_str(),
                        message->get_parts().c_str(),
                        message->get_operator_text().c_str()
                    );
                    out << tr("sms. ")
                        << tr("phone: ") << message->recipient << ", "
                        << tr("id sms: ") << message->get_operator_id() << ", "
                        << tr("sms parts: ") << message->get_parts() << ", "
                        << tr("send status: ") << message->get_operator_text()
                        << endl;
                }
            } catch (exception &e) {
                logger.set_verbose(1).error(tr("Catch error on parse: %s"), e.what());
            }
        } else {            
            logger.set_verbose(1).error(tr("Network error: %s"), error_buffer);
        }
    }

    logger.set_package(opkg);
    return out.str();
}

string state()
{
    config::Config &conf = config::Config::get_instance();
    log::Log &logger = log::Log::get_instance();
    string opkg(logger.set_package("state"));

    ostringstream out;
    bool good = true;
    string token(conf["token"].as<string>());
    string url(conf["stateurl"].as<string>());
    string answer;

    if (!conf().count("params")) {
        good = false;
        answer = tr("Expected at least 1 sms id");
        logger.set_verbose(1).error(answer);
    }

    if (good) {
        vector<string> params = conf["params"].as< vector<string> >();
        namespace sx = sms16xapi;
        string xml;
        sx::ReqStatus request(token);
        sx::Status *sts;

        for (vector<string>::iterator operator_id = params.begin();
             operator_id < params.end(); ++operator_id) {
            sts = (new sx::Status())
                ->set_operator_id((*operator_id));
            request.add(sts);
        }
        sts = NULL;
        xml = request.render();
        logger.debug(xml);

        CURLcode result = send_xml_request(url, xml);

        if (CURLE_OK == result) {
            xml.clear();
            xml.append(buffer);
            buffer.clear();
            logger.debug(xml);

            try {
                request.parse(xml);
                vector<sx::Object*> items = request.get_children();
                for (vector<sx::Object*>::iterator s = items.begin(); s < items.end(); ++s) {
                    sts = dynamic_cast<sx::Status*>((*s));
                    logger.info(
                        tr("status '%s', id %s, time '%s', error code %s"),
                        sts->get_status().c_str(),
                        sts->get_operator_id().c_str(),
                        sts->get_crt_time().c_str(),
                        sts->get_operator_err().c_str()
                    );
                    out << tr("status. ")
                        << tr("sms state: ")   << sts->get_status().c_str() << ", "
                        << tr("sms id: ")      << sts->get_operator_id().c_str() << ", "
                        << tr("state time: ")  << sts->get_crt_time().c_str() << ", "
                        << tr("error code: ")  << sts->get_operator_err().c_str()
                        << endl;
                }
            } catch (exception &e) {
                logger.error(tr("Catch error on parse: %s"), e.what());
                out << e.what();
            }
        } else {
            out << error_buffer;
            logger.error(tr("Network error: %s"), error_buffer);
        }
    }

    logger.set_package(opkg);
    return out.str();
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
}
}