#ifndef SECURITY_PURIFY_H
#define SECURITY_PURIFY_H

#include <string>
#include <vector>
#include <boost/regex.hpp>

namespace smsadmin {
namespace log {

using namespace std;

typedef pair<boost::regex, string> pu_expression;
typedef vector<pu_expression> pu_templates;

class SecurityPurify
{
public:
    /**
     * Return singleton instance
     * @brief get_instance
     * @return
     */
    static SecurityPurify& get_instance();

    /**
     * Clear purified content
     * @brief clear
     * @return
     */
    SecurityPurify& clear();

    /**
     * Purify content
     * @brief run
     * @return
     */
    SecurityPurify& run();

    /**
     * Set content for purify
     * @brief content
     * @return
     */
    SecurityPurify& content(const string&);

    /**
     * Add expression to purify lists
     * @brief add
     * @return
     */
    SecurityPurify& add(const string&, const string&);

    /**
     * Get purified string
     * @brief str
     * @return
     */
    string str();

    ~SecurityPurify();

protected:
    SecurityPurify();
    SecurityPurify(const SecurityPurify&);
    void operator= (const SecurityPurify&);

    /**
     * Attribute to store input content
     * @brief in
     */
    string in;

    /**
     * Attribute to store purified content
     * @brief out
     */
    string out;

    /**
     * Vector to store expressions and replaces for matches
     * @brief replaces
     */
    pu_templates replaces;
};

}}

#endif // SECURITY_PURIFY_H
