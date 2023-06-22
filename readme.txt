Name: Rohan Patel 
Date: 1/19/23
Course: CSS343 B
Assignment: Assignment 1 - Review 

Overview: 

- In this assighment I recreated a webpage mapping, by implementaing a graph that stores webpage nodes. 
- To implement the graph I stored nodes consisting of a body, title, and links from a HMTL file into a unordered map. 
- I then created a method which deltes webpages from the graph. 
- Finally I implemented a interactive mode in which I used a switch statement to execute the users chocie of movement and output from the graph. 

Compiled With: 

g++ -g -O0 WebpageDriver.cpp WebpageNode.cpp WebpageNetwork.cpp -o web
valgrind --leak-check=yes ./web < inputs
cat inputs | ./web 
