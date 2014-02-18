#include <sms16xapi/balance.h>

namespace sms16xapi {

Balance::Balance(): money(""), currency("")
{}

string Balance::render()
{
    return "";
}

string Balance::get_money()
{
    return money;
}

string Balance::get_currency()
{
    return currency;
}

Balance* Balance::set_money(const string& m)
{
    money = m;
    return this;
}

Balance* Balance::set_currency(const string &c)
{
    currency = c;
    return this;
}

}
