#ifndef DEFINITIONS_HPP
#define DEFINITIONS_HPP

#include <set>
#include <map>

namespace automatons {

    typedef std::set<char> Alphabet;
    typedef std::set<int> States;
    typedef std::pair<int, char> StateEventPair;
    typedef std::map<StateEventPair, int> DFATransitionMap;

}

#endif //DEFINITIONS_HPP
