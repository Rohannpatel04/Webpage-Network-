#include <iostream>
#include <vector>

#include "WebpageNetwork.h"

using namespace std;

int main() {
  // setup the data we need
  WebpageNetwork web = WebpageNetwork();
  vector<string> files, toRemove;
  files.push_back("first.html");
  files.push_back("second.html");
  toRemove.push_back("second.html");
  files.push_back("third.html");
  files.push_back("fourth.html");
  toRemove.push_back("fourth.html");
  files.push_back("fifth.html");
  files.push_back("sixth.html");
  files.push_back("seventh.html");
  files.push_back(
      "eighth.html");  // eight doesn't exist, so these two should cause errors
  toRemove.push_back("eighth.html");

  // test adding functionality and Interactive Mode
  web.AddFiles(files);
  web.InteractiveMode("first.html");  // basic functionality test

  // test Remove functionality
  web.RemoveFiles(toRemove);
  web.InteractiveMode(
      "fourth.html");  // tests to see that the fourth page was really removed
  web.InteractiveMode(
      "sixth.html");  // tests the other disconnected part of the graph

  return 0;
}
