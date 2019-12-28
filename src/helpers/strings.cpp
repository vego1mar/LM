#include <sstream>
#include <algorithm>
#include <regex>
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

    std::string Strings::between(const std::string &source, const std::string &lhs, const std::string &rhs) {
        // lhs(.*)rhs
        std::string regexStr = lhs + "(.*)" + rhs;
        std::regex contentBetween(regexStr);
        std::smatch baseMatch;
        std::regex_search(source, baseMatch, contentBetween);

        if (baseMatch.empty()) {
            return std::string();
        }

        std::string matchStr = baseMatch[0].str();
        auto lowerBound = lhs.size();
        auto upperBound = matchStr.size() - rhs.size();
        auto result = matchStr.substr(0, upperBound).substr(lowerBound);
        return result;
    }

    std::string Strings::flatten(const std::vector<char> &buffer) {
        std::string flatten;

        for (const auto &symbol : buffer) {
            flatten += symbol;
        }

        return flatten;
    }

}
