/**
 * Render object as sms xml string
 *
 * @author Alexander M Artamonov <art.alex.m@gmail.com>
 * @version 1.0.1
 * @date 28/07/2014
 * @time 09:14
 * @package sms16xapi
 */

#ifndef SMS_H
#define SMS_H

#include <sms16xapi/object.h>

namespace sms16xapi
{

using namespace std;

class Sms : public Object
{
    friend class ReqSms;

    public:
        /** Default constructor */
        Sms();

        /** Render object as xml text */
        virtual string render();

        /** Access operator_id
         * \return The current value of operator_id
         */
        string get_operator_id() { return operator_id; }

        /** Access parts
         * \return The current value of parts
         */
        string get_parts() { return parts; }

        /** Access type
         * \return The current value of type
         */
        string get_type() { return type; }

        /** Access operator_text. Fill on parse server response
         * \return The current value of operator_text
         */
        string get_operator_text() { return operator_text; }

        /** Access sms date
         * \return The current value of date
         */
        string get_date() { return date; }

        Sms* set_originator(const string &val);
        Sms* set_text(const string &val);
        Sms* set_recipient(const string &val);
        Sms* set_date(const string &val);

        string originator; //!< Member variable "originator"
        string text; //!< Member variable "text"
        string recipient; //!< Member variable "recipient"

    protected:

        string operator_id; //!< Member variable "operator_id"
        string parts; //!< Member variable "parts"
        string type; //!< Member variable "type"
        int position_sms_in_query;
        string operator_text; /// Text in operators response
        string date; /// Date to shedule sms in oprerator server YYYY-mm-dd HH:MM:ss

        Sms* set_position(int p);
};

}

#endif // SMS_H
