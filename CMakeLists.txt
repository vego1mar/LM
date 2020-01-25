cmake_minimum_required(VERSION 3.15)
project(LM)

set(CMAKE_CXX_STANDARD 14)

add_executable(
        LM
        src/main.cpp

        src/automatons/definitions.hpp
        src/automatons/interfaces.hpp
        src/automatons/dfa.hpp src/automatons/dfa.cpp
        src/automatons/nfa.hpp src/automatons/nfa.cpp
        src/automatons/printers.hpp src/automatons/printers.cpp
        src/automatons/turing_machine.hpp src/automatons/turing_machine.cpp

        src/command_line/cla_parser.hpp src/command_line/cla_parser.cpp

        src/grammatical/rpn.hpp src/grammatical/rpn.cpp

        src/helpers/collections.hpp src/helpers/collections.cpp
        src/helpers/strings.hpp src/helpers/strings.cpp
        src/helpers/to_string.hpp src/helpers/to_string.cpp

        src/io_manager/definitions.hpp
        src/io_manager/file_reader.hpp src/io_manager/file_reader.cpp
        src/io_manager/fsm_reader.hpp src/io_manager/fsm_reader.cpp

        src/main_program/definitions.hpp
        src/main_program/fsm_simulation_to_stdout.hpp src/main_program/fsm_simulation_to_stdout.cpp
        src/main_program/grammar_syntax_analyzer.hpp src/main_program/grammar_syntax_analyzer.cpp
        src/main_program/regular_expression_info.hpp src/main_program/regular_expression_info.cpp
        src/main_program/rpn_to_stdout.hpp src/main_program/rpn_to_stdout.cpp

        src/tests/definitions.hpp
)

add_subdirectory(Catch_tests)
