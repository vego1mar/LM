#ifndef IO_MANAGER_DEFINITIONS_HPP
#define IO_MANAGER_DEFINITIONS_HPP

#include <vector>
#include <string>
#include <memory>
#include "../automatons/definitions.hpp"

namespace io_manager {

    using automatons::StateEventPair;
    using automatons::States;


    typedef std::vector<std::string> Tokens;
    typedef std::vector<StateEventPair> NFAEntryPairs;
    typedef std::vector<States> NFAEntryNext;


    struct Successors {
        std::size_t itSymbols = 0;
        std::size_t itNext = 0;
        std::size_t itSuccinct = 0;
    };

    struct NFATransitionEntryPOD {
        std::unique_ptr<std::string> symbolsColumn;
        std::unique_ptr<std::string> nextStatesColumn;
        std::unique_ptr<int> currentState;
        std::unique_ptr<bool> containsBrackets;
        std::unique_ptr<bool> containsParentheses;
        std::unique_ptr<NFAEntryPairs> pairs;
        std::unique_ptr<std::vector<States>> nextStates;
        std::unique_ptr<std::vector<std::vector<std::size_t>>> repetitions;
        std::unique_ptr<std::vector<bool>> isDoubleBracketed;
        std::unique_ptr<Successors> iterators;
    };

}

#endif //IO_MANAGER_DEFINITIONS_HPP
