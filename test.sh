g++ -g -O0 WebpageDriver.cpp WebpageNode.cpp WebpageNetwork.cpp -o web
valgrind --leak-check=yes ./web < inputs
cat inputs | ./web 
