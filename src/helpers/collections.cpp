#include <algorithm>
#include "collections.hpp"

namespace helpers {

    unsigned long long Collections::sum(const std::vector<std::vector<std::size_t>> &superList) {
        unsigned long long sum = 0;

        for (const auto &subList : superList) {
            std::for_each(subList.begin(), subList.end(), [&sum](const std::size_t v) {
                sum += v;
            });
        }

        return sum;
    }

    void Collections::join(std::set<int> &base, const std::set<int> &source) {
        for (const auto &v : source) {
            base.insert(v);
        }
    }


}
