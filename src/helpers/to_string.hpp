#ifndef TO_STRING_HPP
#define TO_STRING_HPP

#include "../automatons/interfaces.hpp"
#include "../automatons/definitions.hpp"
#include "../io_manager/fsm_reader.hpp"

namespace helpers {

    std::string toString(const std::set<char> &set);

    std::string toString(const std::set<int> &set);

    std::string toString(const automatons::IDFA &dfa);

    std::string toString(const automatons::INFA &nfa);

    std::string toString(const automatons::ITuringMachine &tm);

    std::string toString(const automatons::ShiftDirection &shiftType);

    std::string toString(const bool &boolean);

    std::string toString(const automatons::DFATransitionStep &transitionStep);

    std::string toString(const automatons::EventActionTuple &eventAction);

    std::string toString(const std::size_t &headPos, const std::string &tape);

}

#endif //TO_STRING_HPP
