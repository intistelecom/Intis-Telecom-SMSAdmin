#ifndef REQ_OPERATOR_H
#define REQ_OPERATOR_H

#include <string>
#include <sms16gapi/request.h>

namespace sms16gapi {

/**
 * Class for create operator info request
 * @brief The ReqOperator class
 */
class ReqOperator : public Request
{
public:
    ReqOperator(const std::string &, /// login
                const std::string &, /// token
                const std::string & = "json" /// return responce type
               );

    virtual std::string render();

    /**
     * Set phone parameter for request
     * @brief set_phone
     * @param const std::string &ph
     * @return ReqOperator&
     */
    ReqOperator& set_phone(const std::string &ph);
protected:
    virtual std::string signature();
    std::string phone;
};

}

#endif // REQ_OPERATOR_H
