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

echo "./sonar-build/automatons"
mkdir sonar-build/automatons
g++ -Wall -fexceptions -std=c++14 -g  -c src/automatons/dfa.cpp -o sonar-build/automatons/dfa.o
g++ -Wall -fexceptions -std=c++14 -g  -c src/automatons/nfa.cpp -o sonar-build/automatons/nfa.o
g++ -Wall -fexceptions -std=c++14 -g  -c src/automatons/printers.cpp -o sonar-build/automatons/printers.o
g++ -Wall -fexceptions -std=c++14 -g  -c src/automatons/turing_machine.cpp -o sonar-build/automatons/turing_machine.o

echo "./sonar-build/command_line"
mkdir sonar-build/command_line
g++ -Wall -fexceptions -std=c++14 -g  -c src/command_line/cla_parser.cpp -o sonar-build/command_line/cla_parser.o

echo "./sonar-build/grammatical"
mkdir sonar-build/grammatical
g++ -Wall -fexceptions -std=c++14 -g  -c src/grammatical/rpn.cpp -o sonar-build/grammatical/rpn.o

echo "./sonar-build/helpers"
mkdir sonar-build/helpers
g++ -Wall -fexceptions -std=c++14 -g  -c src/helpers/collections.cpp -o sonar-build/helpers/collections.o
g++ -Wall -fexceptions -std=c++14 -g  -c src/helpers/strings.cpp -o sonar-build/helpers/strings.o
g++ -Wall -fexceptions -std=c++14 -g  -c src/helpers/to_string.cpp -o sonar-build/helpers/to_string.o

echo "./sonar-build/io_manager"
mkdir sonar-build/io_manager
g++ -Wall -fexceptions -std=c++14 -g  -c src/io_manager/file_reader.cpp -o sonar-build/io_manager/file_reader.o
g++ -Wall -fexceptions -std=c++14 -g  -c src/io_manager/fsm_reader.cpp -o sonar-build/io_manager/fsm_reader.o

echo "./sonar-build/main_program"
mkdir sonar-build/main_program
g++ -Wall -fexceptions -std=c++14 -g  -c src/main_program/fsm_simulation_to_stdout.cpp -o sonar-build/main_program/fsm_simulation_to_stdout.o
g++ -Wall -fexceptions -std=c++14 -g  -c src/main_program/grammar_syntax_analyzer.cpp -o sonar-build/main_program/grammar_syntax_analyzer.o
g++ -Wall -fexceptions -std=c++14 -g  -c src/main_program/regular_expression_info.cpp -o sonar-build/main_program/regular_expression_info.o
g++ -Wall -fexceptions -std=c++14 -g  -c src/main_program/rpn_to_stdout.cpp -o sonar-build/main_program/rpn_to_stdout.o

RC=$?

if [ $RC -ne 0 ]; then
  echo "BUILD FAILURE"
else
  echo "BUILD SUCCESS"
fi
