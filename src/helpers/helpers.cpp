#include <string>
#include <set>
#include "helpers.hpp"

namespace helpers {

    std::string toString(const std::set<char> &set) {
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
        std::string toString = "[";
        char delimiter = ',';

        for (const int &integer : set) {
            toString += std::to_string(integer) + delimiter;
        }

        toString = toString.substr(0, toString.size() - 1) + ']';
        return toString;
    }

}
