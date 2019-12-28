#include <sstream>
#include <algorithm>
#include "strings.hpp"

namespace helpers {

    std::vector<std::string> Strings::split(const std::string &source, char delimiter) {
        std::stringstream stringify(source);
        std::string buffer;
        std::vector<std::string> words;

        while (std::getline(stringify, buffer, delimiter)) {
            if (!buffer.empty()) {
                words.push_back(buffer);
            }
        }

        return words;
    }

    std::string Strings::toLower(const std::string &source) {
        std::string target(source);
        std::transform(target.begin(), target.end(), target.begin(), [](unsigned char c) {
            return std::tolower(c);
        });
        return target;
    }

    bool Strings::startsWith(const std::string &source, const std::string &prefix) {
        return source.size() >= prefix.size() && source.compare(0, prefix.size(), prefix) == 0;
    }

}
