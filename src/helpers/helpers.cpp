#include <string>
#include <set>
#include "../automatons/interfaces.hpp"

namespace helpers {

    std::string toString(const std::set<char> &set) {
        if (set.empty()) {
            return "[]";
        }

        std::string toString = "[";
        char delimiter = ',';

        for (const char &character : set) {
            toString += character;
            toString += delimiter;
        }

        toString = toString.substr(0, toString.size() - 1) + ']';
        return toString;
    }

    std::string toString(const std::set<int> &set) {
        if (set.empty()) {
            return "[]";
        }

        std::string toString = "[";
        char delimiter = ',';

        for (const int &integer : set) {
            toString += std::to_string(integer) + delimiter;
        }

        toString = toString.substr(0, toString.size() - 1) + ']';
        return toString;
    }

    std::string toString(const automatons::IDFA &dfa) {
        auto alphabetStr = toString(dfa.getAlphabet());
        auto statesStr = toString(dfa.getStates());
        auto finalsStr = toString(dfa.getFinals());
        auto transitionsStr = std::to_string(dfa.getTransitions().size());
        auto startStr = std::to_string(dfa.getStart());
        return '{' + alphabetStr + ',' + statesStr + ',' + finalsStr + ",<" + transitionsStr + ">," + startStr + '}';
    }

    std::string toString(const automatons::INFA &nfa) {
        auto alphabetStr = toString(nfa.getAlphabet());
        auto statesStr = toString(nfa.getStates());
        auto finalsStr = toString(nfa.getFinals());
        auto transitionsStr = std::to_string(nfa.getTransitions().size());
        auto startStr = toString(nfa.getStart());
        return '{' + alphabetStr + ',' + statesStr + ',' + finalsStr + ",<" + transitionsStr + ">," + startStr + '}';
    }

}
