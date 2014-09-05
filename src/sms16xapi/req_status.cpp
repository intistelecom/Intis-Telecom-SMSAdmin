#include <stdexcept>
#include <tinyxml.h>
#include <sms16xapi/status.h>
#include <sms16xapi/req_status.h>

namespace sms16xapi
{

ReqStatus::ReqStatus(const string& tkn) : Request(tkn)
{
    tags = "get_state";
}

void ReqStatus::parse(const string &xml)
{
    TiXmlDocument *doc = _check_incoming_xml(xml);
    vector<TiXmlElement*> items = getElementsByName(doc, "state");

    if (!items.empty()) {
        Status *sms;
        TiXmlElement *el;
        string pos;
        for (vector<TiXmlElement*>::iterator i = items.begin(); i < items.end(); ++i) {
            el = dynamic_cast<TiXmlElement*>((*i));
            pos = el->Attribute("id_sms");
            try {
                sms = dynamic_cast<Status*>(status_by_operator[pos]);
                if (NULL != el->GetText())
                    sms->set_status(el->GetText());
                if (NULL != el->Attribute("time"))
                    sms->set_crt_time(el->Attribute("time"));
                if (NULL != el->Attribute("err"))
                    sms->set_operator_err(el->Attribute("err"));
            } catch (exception &e) {}
        }
        items.clear();
    }
    delete doc;
}

ReqStatus& ReqStatus::add(Status* item)
{
    status_by_operator[item->operator_id] = item;
    Request::add(item);
    return *this;
}

}
