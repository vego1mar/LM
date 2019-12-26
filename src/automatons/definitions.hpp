#ifndef DEFINITIONS_HPP
#define DEFINITIONS_HPP

#include <set>
#include <map>
#include <vector>

namespace automatons {

    typedef std::set<char> Alphabet;
    typedef std::set<int> States;
    typedef std::pair<int, char> StateEventPair;
    typedef std::map<StateEventPair, int> DFATransitionMap;
    typedef std::map<StateEventPair, States> NFATransitionMap;

    struct SimulationVariables {
        States nextStates;
        std::vector<bool> results;
        std::size_t slice;
        bool wasTransitionDefined;
        std::string slicedInput;
    };

    enum class ShiftDirection {
        LEFT,
        RIGHT,
        NO_SHIFT
    };

    typedef std::tuple<char, ShiftDirection, int> TMActionTuple;
    typedef std::map<StateEventPair, TMActionTuple> TMTransitionMap;

}

#endif //DEFINITIONS_HPP
