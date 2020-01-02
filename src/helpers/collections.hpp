#ifndef COLLECTIONS_HPP
#define COLLECTIONS_HPP

#include <vector>

namespace helpers {

    class Collections {
    public:
        Collections() = delete;

        Collections(const Collections &rhs) = delete;

        Collections(Collections &&rvalue) noexcept = delete;

        Collections &operator=(const Collections &rhs) = delete;

        Collections &operator=(Collections &&rvalue) noexcept = delete;

        virtual ~Collections() = delete;

        static unsigned long long sum(const std::vector<std::vector<std::size_t>> &superList);

    };

}

#endif //COLLECTIONS_HPP
