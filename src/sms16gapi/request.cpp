#include <ctime>
#include <sstream>
#include <curl/curl.h>
#include <sms16gapi/request.h>

namespace sms16gapi {

using namespace std;

Request::Request(const string &lgn,
                 const string &tkn,
                 const string &api_type)
{
    login = lgn;
    token = tkn;
    api = api_type;
}

string
Request::generate_utc_timestamp()
{
    ostringstream out;
    time_t rawtime, utctime;
    struct tm * ptm;

    time(&rawtime);
    ptm = gmtime (&rawtime);
    utctime = mktime(ptm);

    out << utctime;
    last_timestamp = out.str();

    return last_timestamp;
}

string
Request::implode_string_array(vector<string> &arr)
{
    ostringstream out;

    for (unsigned i = 0, e = arr.size(); i < e; ++i)
    {
        out << arr.at(i);
        if (i < e-1) out << ",";
    }

    return out.str();
}

string
Request::url_escape(const string& param)
{
    CURL *curl = curl_easy_init();
    string out;
    if(curl) {
          char *output = curl_easy_escape(curl, param.data(), param.length());
          out = output;
          curl_free(output);
    }
    curl_easy_cleanup(curl);
    return out;
}

}
