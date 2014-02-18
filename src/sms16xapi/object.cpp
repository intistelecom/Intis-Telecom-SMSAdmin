#include <sstream>
#include <sms16xapi/object.h>
#include <sms16xapi/constants.h>

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

}
