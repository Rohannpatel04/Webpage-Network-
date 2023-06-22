#ifndef WEBPAGENODE_h
#define WEBPAGENODE_h
#include <cstdlib>
#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

class WebpageNode {
  friend ostream &operator<<(ostream &output, const WebpageNode &node);

 public:
  // Constructs a new WebPage node
  WebpageNode();

  // destructor
  ~WebpageNode();

  // gets the body of the webpage
  // Precondition: The HTML has been parsed and the Current Node pointer is set
  // Postcondition: The body of the HTML is returned as a string without
  // the HTML tags
  string getBody() const;

  // gets the title of the webpage
  // Precondition: The HTML has been parsed and the Current Node pointer is set
  // Postcondition: The Title of the HTML is returned as a string without
  // the HTML tags
  string getTitle() const;

  // gets the links to the other webpages
  // Precondition: none
  // Postcondition: Links are returned as strings
  vector<WebpageNode *> getLinks() const;

  // gets the pointer at i thats located in the parent nodes nodes vector
  // Precondition: none
  // Postcondition: Link is returned as a node
  WebpageNode *getLinksAt(int i) const;

  // Removes a node at the index i within a nodes nodes vector
  // Precondition: a node should exist in the vector
  // Postcondition: the node at index i will be removed
  void removeFromLinksAt(int i);

  // gets the the size of the vector that holds pointers loacted in each node
  // Precondition: none
  // Postcondition: Links are returned as strings
  int getLinksSize() const;

  // sets the title and body of the node
  // Precondition: none
  // The title and body within a node are
  // updated
  void setNode(string title1, string body1);

  vector<WebpageNode *> &addLink();

 private:
  string title;                 // webpage title
  string body;                  // webpage body
  vector<WebpageNode *> nodes;  // links to other WebPageNodes
};
#endif