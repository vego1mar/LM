#!/bin/bash
#!/bin/rm
#!/bin/echo
#!/bin/mkdir
#!/usr/bin/g++
echo "REMOVE PREVIOUS BUILD"
rm -rf sonar-build

echo "BUILDING"
mkdir sonar-build
echo "./sonar-build"
g++ -Wall -fexceptions -std=c++14 -g  -c src/main.cpp -o sonar-build/main.o
echo "./sonar-build/helpers"
mkdir sonar-build/helpers
g++ -Wall -fexceptions -std=c++14 -g  -c src/helpers/helpers.cpp -o sonar-build/helpers/helpers.o
echo "./sonar-build/automatons"
mkdir sonar-build/automatons
g++ -Wall -fexceptions -std=c++14 -g  -c src/automatons/dfa.cpp -o sonar-build/automatons/dfa.o
g++ -Wall -fexceptions -std=c++14 -g  -c src/automatons/nfa.cpp -o sonar-build/automatons/nfa.o
g++ -Wall -fexceptions -std=c++14 -g  -c src/automatons/printers.cpp -o sonar-build/automatons/printers.o
RC=$?

if [ $RC -ne 0 ]; then
  echo "BUILD FAILURE"
else
  echo "BUILD SUCCESS"
fi
