add_executable(Catch_tests_run
        automatons/dfa_test.cpp ../src/automatons/dfa.cpp
        automatons/nfa_test.cpp ../src/automatons/nfa.cpp
        automatons/turing_machine_test.cpp ../src/automatons/turing_machine.cpp
        ../src/helpers/helpers.cpp
        ../src/automatons/printers.cpp
        )
target_link_libraries(Catch_tests_run)
