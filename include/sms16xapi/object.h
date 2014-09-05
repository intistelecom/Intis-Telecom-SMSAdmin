#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include <string>

class TiXmlElement;
class TiXmlDocument;

namespace sms16xapi {

using namespace std;

TiXmlElement* getElementByName(TiXmlDocument*, string const&);
vector<TiXmlElement*> getElementsByName(TiXmlDocument*, string const &);

class Object
{
    public:
        virtual ~Object();
        virtual string render() = 0;
};

class Request: public Object
{
    public:
        Request(const string&);
        virtual ~Request();
        virtual void parse(const string&) = 0;
        virtual string render();
        Request& add(Object*);
        const vector<Object*>& get_children() { return children; }

    protected:
        string _tags_before_children();
        string _tags_after_children();

        /**
         * Throws exceptions
         */
        TiXmlDocument* _check_incoming_xml(const string &);

        vector<Object*> children;
        string token;
        string tags;
};

}
#endif // OBJECT_H
