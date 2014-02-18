#include <sms16xapi/req_balance.h>
#include <sms16xapi/balance.h>
#include <stdexcept>
#include <tinyxml.h>

namespace sms16xapi {

TiXmlElement* getElementByName(TiXmlDocument &doc, std::string const &elemt_value)
{
    TiXmlElement *elem = doc.RootElement()->FirstChildElement(); //Tree root

    while (elem) {
        if (!std::string(elem->Value()).compare(elemt_value))
            return (elem);
        elem = elem->NextSiblingElement();
    }
    return (NULL);
}

ReqBalance::ReqBalance(const string& tkn): Request(tkn)
{}

void ReqBalance::parse(const string& xml)
{
    if (children.empty())
        throw runtime_error("No Balance object was set");

    TiXmlDocument doc;
	doc.Parse(xml.c_str(), 0, TIXML_ENCODING_UTF8);

	if (doc.Error())
		throw runtime_error(doc.ErrorDesc());

    TiXmlElement *el = getElementByName(doc, "error");

    if (NULL != el)
        throw runtime_error(el->GetText());

    Balance *bl = dynamic_cast<Balance*>(children.at(0));
    el = getElementByName(doc, "money");

    if (NULL == el)
        throw runtime_error("Expected tag 'money' not found in response");

    bl->set_money(el->GetText())
      ->set_currency(el->Attribute("currency"))
      ;
}

}
