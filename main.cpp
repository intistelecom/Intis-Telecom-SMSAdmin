#include <iostream>
#include <libxml++/libxml++.h>

using namespace std;
using namespace Glib;
using namespace xmlpp;

int main()
{
    // Parse the file
    DomParser parser;
    parser.parse_file("file.xml");
    Node* rootNode = parser.get_document()->get_root_node();

    // Xpath query
    NodeSet result = rootNode->find("/root/a/b/@attr");

    // Get first node from result
    Node *firstNodeInResult = result.at(0);
    // Cast to Attribute node (dynamic_cast on reference can throw [fail fast])
    Attribute &attribute = dynamic_cast<Attribute&>(*firstNodeInResult);

    // Get value of the attribute
    ustring attributeValue = attribute.get_value();

    // Print attribute value
    cout << attributeValue << endl;
    return 0;
}

