#ifndef SMS16GAPI_SEND_H
#define SMS16GAPI_SEND_H

#include <string>
#include <vector>
#include <sms16gapi/request.h>

namespace sms16gapi {

/// Generate send message request
class ReqSend : public Request
{
public:
    ReqSend(const std::string &, /// login
               const std::string &, /// token
               const std::string & = "json"  /// return responce type "xml", "json"
              );
    virtual std::string render();

    /// Add on or more recipients
    ReqSend& add_phone(const std::string &recipient);

    /// Set sender name
    ReqSend& set_sender(const std::string &originator);

    /// Set message text
    ReqSend& set_text(const std::string &message);

protected:
    virtual std::string signature();
    std::string sender; /// Message sender name
    std::string text; /// Message text
    std::vector<std::string>phone; /// Message recipients
};

}

#endif // SMS16GAPI_SEND_H
