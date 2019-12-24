#ifndef HELPERS_HPP
#define HELPERS_HPP

#include "../automatons/interfaces.hpp"

namespace helpers {

    std::string toString(const std::set<char> &set);

    std::string toString(const std::set<int> &set);

    std::string toString(const automatons::IDFA &dfa);

    std::string toString(const automatons::INFA &nfa);

}

#endif //HELPERS_HPP
