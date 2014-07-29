/**
 * Class to generate state sms response
 *
 * @author Alexander M Artamonov <art.alex.m@gmail.com>
 * @version 1.0.0
 * @date 29/07/2014
 * @time 20:57
 * @package sms16xapi
 */

#ifndef REQ_STATUS_H
#define REQ_STATUS_H

#include <sms16xapi/object.h>
#include <map>

namespace sms16xapi
{

using namespace std;

class Status;

class ReqStatus : public Request
{
    public:
        /** Default constructor */
        ReqStatus(const string& tkn);

        ReqStatus& add( Status* );

        virtual void parse(const string&);
    protected:
    private:
        map<string, Status*> status_by_operator; /// Use to find expect object by operator_id
};

}

#endif // REQ_STATUS_H
