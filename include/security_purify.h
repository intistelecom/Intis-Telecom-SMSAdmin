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
