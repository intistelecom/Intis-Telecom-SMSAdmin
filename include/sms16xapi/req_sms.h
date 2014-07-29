/**
 * Class to genarate send sms xml document
 *
 * @author Alexander M Artamonov <art.alex.m@gmail.com>
 * @version 1.0.0
 * @date 28/08/2014
 * @time 08:38
 * @package sms16xapi
 */

#ifndef REQSMS_H
#define REQSMS_H

#include <sms16xapi/object.h>

namespace sms16xapi
{

using namespace std;

class Sms;

class ReqSms : public Request
{
    public:
        ReqSms(const string&);

        /** Do some tasks. Add position sms in query */
        ReqSms& add( Sms* );

        virtual void parse(const string&);
    protected:
        int position_sms_in_query; /// Increment on add()
};

}
#endif // REQSMS_H
