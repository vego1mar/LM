#ifndef STRINGS_HPP
#define STRINGS_HPP

#include <vector>
#include <string>

namespace helpers {

    class Strings {
    public:
        Strings() = delete;

        Strings(const Strings &rhs) = delete;

        Strings(Strings &&rvalue) noexcept = delete;

        Strings &operator=(const Strings &rhs) = delete;

        Strings &operator=(Strings &&rvalue) noexcept = delete;

        virtual ~Strings() = delete;

        static std::vector<std::string> split(const std::string &source, char delimiter = ' ');

        static std::string toLower(const std::string &source);

        static bool startsWith(const std::string &source, const std::string &prefix);

    };

}

#endif //STRINGS_HPP
