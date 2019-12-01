cmake_minimum_required(VERSION 3.15)
project(LM)

set(CMAKE_CXX_STANDARD 14)

add_executable(LM
        main.cpp
        src/dfa.hpp src/dfa.cpp
        src/helpers.hpp src/helpers.cpp)
add_subdirectory(Catch_tests)
