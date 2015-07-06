#ifndef SMS16GAPI_REQUEST_H
#define SMS16GAPI_REQUEST_H

#include <string>
#include <vector>

namespace sms16gapi {

/// @abstract
class Request
{
public:
    Request(const std::string &lgn, /// login
            const std::string &tkn, /// token
            const std::string &api_type = "json" /// return responce type "xml", "json"
            );

    /// Generate query GET string
    /// ?login=test&signature=70a0a*****ff60681c&state=409129,401297&return=json&timestamp=1409887191
    virtual std::string render() = 0;

protected:
    std::string login; /// user login
    std::string token; /// user api token
    std::string m_signature; /// request signature based on api
    std::string api; /// responce type "json"
    std::string last_timestamp;  /// request Unix timestamp in UTC

    std::string generate_utc_timestamp(); /// return UTC timestamp and set last_timestamp

    /// Implode vector strings to one string with "," delimiter
    std::string implode_string_array(std::vector<std::string> &arr);

    /// Generate md5 signature for request.
    /// NOTE: Make generate_utc_timestamp() call
    virtual std::string signature() = 0;

    /// Urlescape characters in string
    std::string url_escape(const std::string& param);
};

}

#endif // REQUEST_H
