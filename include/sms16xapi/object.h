#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include <string>

namespace sms16xapi {

using namespace std;

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

    protected:
        string _tags_before_children();
        string _tags_after_children();

        vector<Object*> children;
        string token;
        string tags;
};

}
#endif // OBJECT_H
