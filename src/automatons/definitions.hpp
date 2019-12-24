#ifndef DEFINITIONS_HPP
#define DEFINITIONS_HPP

#include <set>
#include <map>

namespace automatons {

    typedef std::set<char> Alphabet;
    typedef std::set<int> States;
    typedef std::pair<int, char> StateEventPair;
    typedef std::map<StateEventPair, int> DFATransitionMap;
    typedef std::map<StateEventPair, States> NFATransitionMap;

}

#endif //DEFINITIONS_HPP
