#ifndef SMS16GAPI_STATE_H
#define SMS16GAPI_STATE_H

#include <string>
#include <vector>
#include <sms16gapi/request.h>

namespace sms16gapi {

/// Generate send message request
class ReqState : public Request
{
public:
    ReqState(const std::string &, /// login
               const std::string &, /// token
               const std::string & = "json"  /// return responce type "xml", "json"
              );
    virtual std::string render();

    /// Add one or more state ids
    ReqState& add_state(const std::string &id);

protected:
    virtual std::string signature();
    std::vector<std::string>state_id; /// State ids
};

}

#endif // SMS16GAPI_STATE_H
