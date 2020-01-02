#include "../catch.hpp"
#include "../../src/helpers/collections.hpp"

using helpers::Collections;

TEST_CASE("collections.hpp", "[collections]") {
    SECTION("sum([N][M]) -> OK") {
        std::vector<std::vector<std::size_t>> list1 = {
                {0},
                {1, 2},
                {3, 4, 5},
                {6, 7, 8, 9}
        };
        std::vector<std::vector<std::size_t>> list2 = {
                {},
                {1, 2},
                {3},
        };

        auto result1 = Collections::sum(list1);
        auto result2 = Collections::sum(list2);

        REQUIRE(result1 == 45);
        REQUIRE(result2 == 6);
    }
}
