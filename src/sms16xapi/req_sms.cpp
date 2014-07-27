#include <stdlib.h>
#include <stdexcept>
#include <sms16xapi/req_sms.h>
#include <sms16xapi/sms.h>
#include <tinyxml.h>

namespace sms16xapi
{

ReqSms::ReqSms(const string& tkn) : Request(tkn), position_sms_in_query(0)
{}

void ReqSms::parse (const string& xml)
{
    TiXmlDocument *doc = _check_incoming_xml(xml);
    vector<TiXmlElement*> *items = getElementsByName(doc, "information");

    if (NULL != items) {
        Sms *sms;
        TiXmlElement *el;
        int pos;
        for (vector<TiXmlElement*>::iterator i = items->begin(); i < items->end(); ++i) {
            el = dynamic_cast<TiXmlElement*>((*i));
            pos = atoi(el->Attribute("number_sms")) -1;
            try {
                sms = dynamic_cast<Sms*>(children.at(pos));
                if (NULL != el->GetText())
                    sms->operator_text = el->GetText();
                if (NULL != el->Attribute("parts"))
                    sms->parts = el->Attribute("parts");
                if (NULL != el->Attribute("id_sms"))
                    sms->operator_id = el->Attribute("id_sms");
            } catch (exception &e) {}
        }
        items->clear();
    }
    delete doc;
}

ReqSms& ReqSms::add(Sms *ch)
{
    position_sms_in_query += 1;
    ch->set_position(position_sms_in_query);
    Request::add(ch);

    return *(this);
}

}
