/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2017 Intis Telecom
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

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
