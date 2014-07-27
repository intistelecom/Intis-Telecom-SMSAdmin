#include <sstream>
#include <sms16xapi/object.h>
#include <sms16xapi/constants.h>
#include <tinyxml.h>
#include <stdexcept>

namespace sms16xapi {

Object::~Object() {}

Request::Request(const string& tkn): token(tkn), children(), tags("")
{}

Request::~Request()
{
    children.clear();
}

string Request::render()
{
    ostringstream req;
    req << "<?xml version=\"1.0\" encoding=\"utf-8\" ?>"
        << "<request " << "version=\"" << API_VERSION << "\">"
        << "<security>"
        << "<token value=\"" << token << "\" />"
        << "</security>"
        ;
    req << _tags_before_children();

    for (vector<Object*>::iterator ch = children.begin(); ch != children.end(); ++ch) {
        req << (*ch)->render();
    }

    req << _tags_after_children();
    req << "</request>";

    return req.str();
}

string Request::_tags_before_children()
{
    ostringstream tag;
    if (!tags.empty())
        tag << "<" << tags << ">";
    return tag.str();
}

string Request::_tags_after_children()
{
    ostringstream tag;
    if (!tags.empty())
        tag << "</" << tags << ">";
    return tag.str();
}

Request& Request::add(Object *ch)
{
    children.push_back(ch);
    return *this;
}

TiXmlDocument* Request::_check_incoming_xml(const string &xml)
{
    if (children.empty())
        throw runtime_error("No child object was set");

    TiXmlDocument *doc = new TiXmlDocument;
	doc->Parse(xml.c_str(), 0, TIXML_ENCODING_UTF8);

	if (doc->Error())
		throw runtime_error(doc->ErrorDesc());

    TiXmlElement *el = getElementByName(doc, "error");

    if (NULL != el)
        throw runtime_error(el->GetText());

    return doc;
}

TiXmlElement* getElementByName(TiXmlDocument *doc, string const &elemt_value)
{
    TiXmlElement *elem = doc->RootElement()->FirstChildElement(); //Tree root

    while (elem) {
        if (!string(elem->Value()).compare(elemt_value))
            return (elem);
        elem = elem->NextSiblingElement();
    }
    return (NULL);
}

vector<TiXmlElement*>* getElementsByName(TiXmlDocument *doc, string const &elemt_value)
{
    TiXmlElement *elem = doc->RootElement()->FirstChildElement(); //Tree root

    vector<TiXmlElement*> *found = new vector<TiXmlElement*>();

    while (elem) {
        if (!string(elem->Value()).compare(elemt_value))
            found->push_back(elem);
        elem = elem->NextSiblingElement();
    }

    if (found->empty())
        return NULL;
    else
        return found;
}

}
