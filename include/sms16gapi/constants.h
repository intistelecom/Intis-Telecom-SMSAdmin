#ifndef SMS16GAPI_CONSTANTS_H
#define SMS16GAPI_CONSTANTS_H

#include <string>
#include <map>

namespace sms16gapi {

using namespace std;

const string STAMP_URL   = "https://xml.sms16.ru/xml/state.php";

/// Init ERROR_CODES constant
map<string, string> init_error_codes() {
    map<string, string> errors;

    errors["000"] = "Service unavailable";
    errors["1"]   = "Signature not specified";
    errors["2"]   = "Login not specified";
    errors["3"]   = "Text not specified";
    errors["4"]   = "Phone number not specified";
    errors["5"]   = "Sender not specified";
    errors["6"]   = "Invaild signature";
    errors["7"]   = "Invalid login";
    errors["8"]   = "Invalid sender name";
    errors["9"]   = "Sender name not registered";
    errors["10"]  = "Sender name not approved";
    errors["11"]  = "There are forbidden words in the text";
    errors["12"]  = "Error in SMS sending";
    errors["13"]  = "Phone number is in the stop list. SMS sending to this number is forbidden";
    errors["14"]  = "There are more than 50 numbers in the request";
    errors["15"]  = "List not specified";
    errors["16"]  = "Invalid phone number";
    errors["17"]  = "SMS ID not specified";
    errors["18"]  = "Status not obtained";
    errors["19"]  = "Empty response";
    errors["20"]  = "The number already exists";
    errors["21"]  = "No name";
    errors["22"]  = "Template already exists";
    errors["23"]  = "Month not specifies (Format: YYYY-MM)";
    errors["24"]  = "Timestamp not specified";
    errors["25"]  = "Error in access to the list";
    errors["26"]  = "There are no numbers in the list";
    errors["27"]  = "No valid numbers";
    errors["28"]  = "Date of start not specified (Format: YYYY-MM-DD)";
    errors["29"]  = "Date of end not specified (Format: YYYY-MM-DD)";
    errors["30"]  = "No date (format: YYYY-MM-DD)";

    return errors;
}

const map<string, string> ERROR_CODES = init_error_codes();


}


#endif // CONSTANTS_H
