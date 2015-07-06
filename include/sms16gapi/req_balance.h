#ifndef SMS16GAPI_BALANCE_H
#define SMS16GAPI_BALANCE_H

#include <string>
#include <sms16gapi/request.h>

namespace sms16gapi {

class ReqBalance : public Request
{
public:
    ReqBalance(const std::string &, /// login
               const std::string &, /// token
               const std::string & = "json"  /// return responce type "xml", "json"
              );
    virtual std::string render();
protected:
    virtual std::string signature();
};

}

#endif // SMS16GAPI_BALANCE_H
