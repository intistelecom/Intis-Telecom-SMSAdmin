#ifndef BALANCE_H
#define BALANCE_H

#include <sms16xapi/object.h>

namespace sms16xapi {

class Balance: public Object
{
    friend class ReqBalance;

    public:
        Balance();
        virtual string render();
        string get_money();
        string get_currency();

    protected:
        string money;
        string currency;
        Balance* set_money(const string&);
        Balance* set_currency(const string&);
};

}
#endif // BALANCE_H
