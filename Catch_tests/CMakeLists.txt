add_executable(Catch_tests_run
        dfa_test.cpp ../src/dfa.cpp
        ../src/helpers.cpp
        )
target_link_libraries(Catch_tests_run)
