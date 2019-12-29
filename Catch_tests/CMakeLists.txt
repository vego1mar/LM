add_executable(
        Catch_tests_run

        automatons/dfa_test.cpp ../src/automatons/dfa.cpp
        automatons/nfa_test.cpp ../src/automatons/nfa.cpp
        automatons/turing_machine_test.cpp ../src/automatons/turing_machine.cpp
        ../src/automatons/printers.cpp

        command_line/cla_parser_test.cpp ../src/command_line/cla_parser.cpp

        helpers/strings_test.cpp ../src/helpers/strings.cpp
        ../src/helpers/to_string.cpp

        io_manager/file_reader_test.cpp ../src/io_manager/file_reader.cpp
        io_manager/fsm_reader_test.cpp ../src/io_manager/fsm_reader.cpp

        ../src/main_program/fsm_simulation_to_stdout.cpp

)
target_link_libraries(Catch_tests_run)
