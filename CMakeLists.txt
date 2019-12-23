cmake_minimum_required(VERSION 3.15)
project(LM)

set(CMAKE_CXX_STANDARD 14)

add_executable(LM
        src/main.cpp
        src/automatons/dfa.hpp src/automatons/dfa.cpp
        src/helpers/helpers.cpp src/automatons/definitions.hpp
        src/helpers/helpers.hpp
        src/automatons/interfaces.hpp)
add_subdirectory(Catch_tests)
