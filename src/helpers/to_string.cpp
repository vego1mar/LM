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

    std::string toString(const automatons::ITuringMachine &tm) {
        auto statesStr = toString(tm.getStates());
        auto tapeAlphabetStr = toString(tm.getAlphabet());
        auto initialStateStr = std::to_string(tm.getStart());
        auto finalsStr = toString(tm.getFinals());
        return '{' + statesStr + ',' + tapeAlphabetStr + ',' + initialStateStr + ',' + finalsStr + '}';
    }

    std::string toString(const automatons::ShiftDirection &shiftType) {
        switch (shiftType) {
            case automatons::ShiftDirection::LEFT:
                return "LEFT";
            case automatons::ShiftDirection::RIGHT:
                return "RIGHT";
            case automatons::ShiftDirection::NO_SHIFT:
                return "NO_SHIFT";
            default:
                break;
        }

        return "UNKNOWN";
    }

    std::string toString(const bool &boolean) {
        return (boolean) ? "true" : "false";
    }

    std::string toString(const automatons::DFATransitionStep &transitionStep) {
        const auto &isAcceptingState = std::get<0>(transitionStep);
        const auto &previousState = std::get<0>(std::get<1>(transitionStep));
        const auto &event = std::get<1>(std::get<1>(transitionStep));
        const auto &nextState = std::get<2>(transitionStep);
        std::string string = '(' + std::to_string(previousState) + ',' + event + ") -> " + std::to_string(nextState);
        const std::string &status = (isAcceptingState) ? "ACCEPTED" : "REJECTED";
        string += " <" + status + '>';
        return string;
    }

    std::string toString(const automatons::EventActionTuple &eventAction) {
        const auto &eventPair = std::get<0>(eventAction);
        const auto &state = std::get<0>(eventPair);
        const auto &event = std::get<1>(eventPair);
        std::string eventStr = '(' + std::to_string(state) + ',' + event + ')';

        const auto &actionTuple = std::get<1>(eventAction);
        const auto &writeSymbol = std::get<0>(actionTuple);
        const auto &moveDirection = std::get<1>(actionTuple);
        const auto &nextState = std::get<2>(actionTuple);
        std::string actionStr = "(";
        actionStr += writeSymbol;
        actionStr += ',' + toString(moveDirection);
        actionStr += ',' + std::to_string(nextState) + ')';

        std::string resultStr = eventStr + " -> " + actionStr;
        return resultStr;
    }

    std::string toString(const std::size_t &headPos, const std::string &tape) {
        auto tapeStr = tape.substr(0, headPos) + '[';
        tapeStr += tape[headPos];
        tapeStr += ']' + tape.substr(headPos + 1);
        return tapeStr;
    }

}
