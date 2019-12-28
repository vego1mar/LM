cmake_minimum_required(VERSION 3.15)
project(LM)

set(CMAKE_CXX_STANDARD 14)

add_executable(LM
        src/main.cpp
        src/automatons/dfa.hpp src/automatons/dfa.cpp
        src/automatons/nfa.hpp src/automatons/nfa.cpp
        src/automatons/printers.hpp src/automatons/printers.cpp
        src/automatons/turing_machine.hpp src/automatons/turing_machine.cpp
        src/automatons/definitions.hpp
        src/automatons/interfaces.hpp
        src/helpers/to_string.hpp src/helpers/to_string.cpp
        src/helpers/strings.hpp src/helpers/strings.cpp
        src/io_manager/file_reader.hpp src/io_manager/file_reader.cpp
        src/io_manager/fsm_reader.hpp src/io_manager/fsm_reader.cpp
        )
add_subdirectory(Catch_tests)
