#ifndef WEBPAGENETWORK
#define WEBPAGENETWORK
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>

#include "WebpageNode.h"
using namespace std;

class WebpageNetwork {
 public:
  // create an empty webpage graph
  WebpageNetwork();

  // clean up any memory and fixes broken links
  ~WebpageNetwork();

  // creates a WebPage node for each file in the vector
  // if the file cannot be found it prints to the console saying so
  // Precondition: There needs to be a vector of file paths
  // Postcondition: Graph Nodes are made or error is printed
  void AddFiles(vector<string> inputFilenames);

  //   removes any files from the graph
  //   prints an error to the console if the file cannot be found
  //   Precondition: There needs to be a vector of files to be deleted
  //   Postcondition: Graph Nodes are deleted or error is printed
  void RemoveFiles(vector<string> inputFilenames);

  // begins interative mode at a webpage
  // Precondition: A valid starting node must be defined
  // Postcondition: Interactive mode is started on the Node. Current Node
  // is
  // set to the starting node. An error is printed if start doesnt exist
  void InteractiveMode(string start);

 private:
  WebpageNode *curr;  // curr node: interativeMode will call this nodes
                      // functions for the UI

  stack<WebpageNode *> lastVisited;  // pointers to the last webpages visited

  // Changed the value type to a vector so a page can point to multiple pages
  // compared to what my group came up with
  unordered_map<string, WebpageNode *>
      nodeMap;  // stores the WebPageNode pointers once they are made
};

#endif
