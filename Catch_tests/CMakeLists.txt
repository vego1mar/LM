add_executable(Catch_tests_run
        automatons/dfa_test.cpp ../src/automatons/dfa.cpp
        automatons/nfa_test.cpp ../src/automatons/nfa.cpp
        ../src/helpers/helpers.cpp
        )
target_link_libraries(Catch_tests_run)
