#include "WebpageNode.h"

#include <stack>
#include <string>
#include <unordered_map>
#include <vector>

#include "WebpageNetwork.h"
using namespace std;

// Constructs a new WebPage node
WebpageNode::WebpageNode() {}

// destructor
WebpageNode::~WebpageNode() {}

// operator overload for output
// Precondition: The HTML has been parsed and the Current Node pointer is set
// Postcondition: The body of the HTML is returned as a string without
// the HTML tags
ostream &operator<<(ostream &output, const WebpageNode &node) {
  output << "Webpage Title: " << node.getTitle();

  return output;
}

// gets the body of the webpage
// Precondition: The HTML has been parsed and the Current Node pointer is set
// Postcondition: The body of the HTML is returned as a string without
// the HTML tags
string WebpageNode::getBody() const { return body; }

// gets the title of the webpage
// Precondition: The HTML has been parsed and the Current Node pointer is set
// Postcondition: The Title of the HTML is returned as a string without
// the HTML tags
string WebpageNode::getTitle() const { return title; }

// gets the links to the other webpages
// Precondition: the node needs to exist
// Postcondition: Links are returned as strings
vector<WebpageNode *> WebpageNode::getLinks() const { return nodes; }

// gets the pointer at i thats located in the parent nodes nodes vector
// Precondition: there has to be something stored inside the node vector
// Postcondition: Link is returned as a node
WebpageNode *WebpageNode::getLinksAt(int i) const { return nodes[i]; }

// gets the the size of the vector that holds pointers loacted in each node
// Precondition: there has to be soemthing stored inside the node vector
// Postcondition: Links are returned as strings
int WebpageNode::getLinksSize() const { return nodes.size(); }

// Removes a node at the index i within a nodes nodes vector
// Precondition: a node should exist in the vector
// Postcondition: the node at index i will be removed
void WebpageNode::removeFromLinksAt(int i) { nodes.erase(nodes.begin() + i); }

// sets the title and body of the node
// Precondition: none
// Postcondition: The title and body within a node are
// updated
void WebpageNode::setNode(string title1, string body1) {
  title = title1;
  body = body1;
}

// returns the nodes vector in WebpageNode which can be modified
// Precondition: The node needs to exist
// Postcondition: The node vector is returned as a vector
vector<WebpageNode *> &WebpageNode::addLink() { return nodes; }
