add_executable(Catch_tests_run
        automatons/dfa_test.cpp ../src/automatons/dfa.cpp
        automatons/nfa_test.cpp ../src/automatons/nfa.cpp
        automatons/turing_machine_test.cpp ../src/automatons/turing_machine.cpp
        helpers/to_string.cpp
        ../src/automatons/printers.cpp
        io_manager/file_reader_test.cpp ../src/io_manager/file_reader.cpp
        ../src/io_manager/fsm_reader.cpp
        helpers/strings_test.cpp ../src/helpers/strings.cpp
        )
target_link_libraries(Catch_tests_run)
