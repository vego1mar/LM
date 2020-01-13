#ifndef TESTS_DEFINITIONS_HPP
#define TESTS_DEFINITIONS_HPP

#include <string>

namespace tests {

    struct Constants {

        const std::string DFA_1_PATH = "../../files/dfa_1.txt";
        const std::string INPUT_1_PATH = "../../files/input_1.txt";
        const long DFA_1_SIZE = 1637;
        const long INPUT_1_SIZE = 19;

        const std::string DFA_2_PATH = "../../files/dfa_2.txt";

        const std::string NFA_1_PATH = "../../files/nfa_1.txt";
        const std::string INPUT_2_PATH = "../../files/input_2.txt";
        const long NFA_1_SIZE = 2113;
        const long INPUT_2_SIZE = 24;

        const std::string TM_1_PATH = "../../files/tm_1.txt";

    };

}

#endif //TESTS_DEFINITIONS_HPP
