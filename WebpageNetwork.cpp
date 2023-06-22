#include "WebpageNetwork.h"

#include <fstream>
#include <iostream>

#include "WebpageNode.h"
using namespace std;

// create an empty webpage graph
WebpageNetwork::WebpageNetwork() {}

// clean up any memory and fixes broken links
WebpageNetwork::~WebpageNetwork() {
  for (auto i = nodeMap.begin(); i != nodeMap.end(); i++) {
    delete i->second;
    i->second = NULL;
  }
}
// creates a WebPage node for each file in the vector
// if the file cannot be found it prints to the console saying so
// Precondition: There needs to be a vector of file paths
// Postcondition: Graph Nodes are made or error is printed
void WebpageNetwork::AddFiles(vector<string> inputFilenames) {
  cout << " " << endl;

  // for loop that treverses the vector of files being passed in
  for (int i = 0; i < inputFilenames.size(); i++) {
    string filename = inputFilenames[i];
    ifstream input;
    input.open(inputFilenames[i]);

    // check if the file exist in the folder
    if (!input.is_open()) {
      // if it doesnt exist print out saying the file doesnt exist
      cout << "File " << filename << " Not Found" << endl;

    }

    else {
      // if the file exist parse the title, body, and links
      string parentTitle;
      string parentBody;
      vector<string> links;

      while (!input.eof()) {
        string line;
        getline(input, line);

        int num = 0;
        if (line.find("<title>") != string::npos) {
          int start = line.find("<title>") +
                      7;  // the 7 represents the 7 charecters in the first tag
          int end = line.find("</title>");

          while (start != end) {
            parentTitle += line.at(start);
            start++;
          }
        }

        if (line.find("<body>") != string::npos) {
          vector<string> parsedLine;
          while (getline(input, line, '<')) {
            parsedLine.push_back(line);
          }

          for (int i = 0; i < parsedLine.size(); i++) {
            // if the line is all text
            if (parsedLine[i].find("I") != string::npos) {
              parentBody += parsedLine[i];
            }

            // When there is a " "
            if (parsedLine[i].find("\"") != string ::npos) {
              // Parse the link
              int start1 = parsedLine[i].find("\"") + 1;
              int end1 = parsedLine[i].find("\"", start1);
              string parsed;

              while (start1 < end1) {
                parsed += parsedLine[i][start1];
                start1++;
              }
              links.push_back(parsed);

              // Parse the text
              // parentBody += parsedLine[i].find(">");
              int start2 = parsedLine[i].find(">") + 1;
              int end2 = parsedLine[i].length();
              while (start2 < end2) {
                parentBody += parsedLine[i][start2];
                start2++;
              }
            }

            if (parsedLine[i].find("/a") != string ::npos) {
              // Parse the text
              int start1 = parsedLine[i].find(">") + 1;
              int end1 = parsedLine[i].length();
              while (start1 < end1) {
                parentBody += parsedLine[i][start1];
                start1++;
              }
            }
          }
        }
      }
      input.close();

      // if the webpage node is not created then...
      if (!nodeMap.count(filename)) {
        // create a new node and assign the title and body, and keep the
        // vector empty
        WebpageNode *parentNode = new WebpageNode();

        // add new node to map
        nodeMap.insert(make_pair(filename, parentNode));
        nodeMap[filename]->setNode(parentTitle, parentBody);
      }

      // if it is already created...
      else {
        // add the title and body to the webpage node that already exist
        nodeMap[filename]->setNode(parentTitle, parentBody);
      }

      // for loop that treverses the links vectors and creates child nodes
      for (int i = 0; i < links.size(); i++) {
        string childFilename = links[i];
        ifstream input;
        input.open(links[i]);
        // check if the file exist in the folder
        if (!input.is_open()) {
          // if it doesnt exist print out saying the file doesnt exist
          cout << "File" << links[i] << "Not Found" << endl;
        } else if (!nodeMap.count(childFilename)) {
          string childTitle = links[i];
          // parse the .html out of the file name and save it to the title
          // string
          // if the file exist create a webpagenode of the link
          WebpageNode *childNode = new WebpageNode();

          // add the webpage node to the map
          nodeMap.insert(make_pair(childFilename, childNode));

          // add a pointer to the webpage node to the parent node vector
          int sizeOfMap = nodeMap.size();

          nodeMap[filename]->addLink().push_back(childNode);

        } else {
          nodeMap[filename]->addLink().push_back(nodeMap[childFilename]);
        }
      }
    }
  }
}

void WebpageNetwork::RemoveFiles(vector<string> inputFilenames) {
  for (int i = 0; i < inputFilenames.size(); i++) {
    string filename = inputFilenames[i];
    fstream input;
    input.open(filename);

    // check if the file exist in the folder
    if (!input.is_open()) {
      // if it doesnt exist print out saying the file doesnt exist
      cout << "File " << filename << " Not Found" << endl;
      cout << filename << " Cannot Be Deleted" << endl;
    }

    else {
      for (auto i = nodeMap.begin(); i != nodeMap.end(); i++) {
        for (int j = 0; j < i->second->getLinksSize(); j++) {
          if (i->second->getLinksAt(j) == nodeMap[filename]) {
            i->second->removeFromLinksAt(j);
          }
        }
      }
      delete nodeMap[filename];
      nodeMap[filename] = NULL;
      nodeMap.erase(filename);
    }
  }
}

// begins interative mode at a webpage
// Precondition: A valid starting node must be defined
// Postcondition: Interactive mode is started on the Node. Current Node is
// set to the starting node. An error is printed if start doesnt exist
void WebpageNetwork::InteractiveMode(string start) {
  cout << " " << endl;

  // check if the webpage exist inside the map
  if (!nodeMap.count(start)) {
    cout << start << " Does Not Exist" << endl;
    cout << "Iteractive Mode Cannot Run With " << start
         << " As The Starting Point" << endl;
  }

  else {
    // add the current node to a stack
    lastVisited.push(nodeMap[start]);
    curr = nodeMap[start];
    int program = 0;

    while (program == 0) {
      // Display the current webage which is the variable being passed in
      // "start"
      cout << " " << endl;
      cout << *lastVisited.top() << endl;

      // Display the options the user has and ask the user to choose a menu
      cout << "Select a Option:" << endl;
      cout << "1) Display HTML Body" << endl;
      cout << "2) List the links" << endl;
      cout << "3) Go Back to the previous page" << endl;
      cout << "4) Exit Interactive Mode" << endl;

      int option1;
      cin >> option1;
      cout << " " << endl;

      // create a switch statement
      switch (option1) {
        case 1:
          // Display the HTML body for the current webpage
          cout << curr->getBody() << endl;
          break;

        case 3:

          // Edge case of not having a webpage to move back to
          if (lastVisited.size() == 1) {
            cout << "You cannot go back to the previous page!" << endl;
            break;
          }
          // 3) Pop the stack
          lastVisited.pop();
          // update the current
          curr = lastVisited.top();
          cout << " " << endl;

          break;

        case 4:
          // exit the iterative mode
          cout << "Exiting Iteractive Mode!" << endl;
          cout << " " << endl;

          // setting the program equal to 1 allows us to exist the interactive
          // mode while loop
          program = 1;
          break;

        case 2:
          // Display the links that associate with the current webpage using
          cout << "Select a Webpage" << endl;
          for (int i = 0; i < curr->getLinksSize(); i++) {
            cout << i + 1 << ")"
                 << " " << curr->getLinksAt(i)->getTitle() << endl;
          }
          cout << "X) Return to Menu" << endl;

          // Take input from the user
          string linkSelection;
          cin >> linkSelection;

          if (linkSelection == "X") {
            cout << " " << endl;
            break;
          } else {
            // Update the current webpage depending on the users selection
            curr = curr->getLinksAt(stoi(linkSelection) - 1);
            lastVisited.push(curr);
            cout << " " << endl;
            break;
          }
      }
    }
  }
}