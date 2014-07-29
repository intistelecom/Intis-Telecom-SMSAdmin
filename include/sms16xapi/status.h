/**
 * Retuns status object as xml string
 *
 * @author Alexander M Artamonov <art.alex.m@gmail.com>
 * @version 1.0.0
 * @date 2014/07/29
 * @time 20:30
 * @package sms16xapi
 */

#ifndef STATUS_H
#define STATUS_H

#include <sms16xapi/object.h>

namespace sms16xapi
{

class Status : public Object
{
    friend class ReqStatus;

    public:
        /** Default constructor */
        Status();

        /** Render object as xml text */
        virtual string render();

        /** Access operator_id
         * \return The current value of operator_id
         */
        string get_operator_id() { return operator_id; }

        /** Set operator_id
         * \param val New value to set
         */
        Status* set_operator_id(const string &val) { operator_id = val; return this; }

        /** Access status
         * \return The current value of status
         */
        string get_status() { return status; }

        /** Set status
         * \param val New value to set
         */
        Status* set_status(const string &val) { status = val; return this; }

        /** Access crt_time
         * \return The current value of crt_time
         */
        string get_crt_time() { return crt_time; }

        /** Set crt_time
         * \param val New value to set
         */
        Status* set_crt_time(const string &val) { crt_time = val; return this; }

        /** Access operator_err
         * \return The current value of operator_err
         */
        string get_operator_err() { return operator_err; }

        /** Set operator_err
         * \param val New value to set
         */
        Status* set_operator_err(const string &val) { operator_err = val; return this; }

    protected:
        string operator_id; //!< Member variable "operator_id"
        string status; //!< Member variable "status"
        string crt_time; //!< Member variable "crt_time"
        string operator_err; //!< Member variable "operator_err"
};

}

#endif // STATUS_H
