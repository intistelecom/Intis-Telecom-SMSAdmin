#ifndef REQBALANCE_H
#define REQBALANCE_H

#include <sms16xapi/object.h>

namespace sms16xapi {

using namespace std;

class ReqBalance: public Request
{
    public:
        ReqBalance(const string&);

        /**
         * Set expected values to Balance object
         *
         * @throw std::runtime_error No Balance object was set
         * @throw std::runtime_error [Error description of xml doc parse]
         * @throw std::runtime_error [Description of server error message]
         * @throw std::runtime_error Expected tag 'money' not found in response
         */
        virtual void parse(const string&);
};

}

#endif // REQBALANCE_H
