#include <sms16xapi/req_balance.h>
#include <sms16xapi/balance.h>
#include <stdexcept>
#include <tinyxml.h>

namespace sms16xapi {

ReqBalance::ReqBalance(const string& tkn): Request(tkn)
{}

void ReqBalance::parse(const string& xml)
{
    TiXmlDocument *doc = _check_incoming_xml(xml);
    Balance *bl = dynamic_cast<Balance*>(children.at(0));
    TiXmlElement *el = getElementByName(doc, "money");

    if (NULL == el)
        throw runtime_error("Expected tag 'money' not found in response");

    bl->set_money(el->GetText())
      ->set_currency(el->Attribute("currency"))
      ;

    delete doc;
}

}
