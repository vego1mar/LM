#include "../catch.hpp"
#include "../../src/grammatical/rpn.hpp"

using grammatical::RPN;


TEST_CASE("rpn.hpp", "[rpn]") {
    SECTION("(convert,getPostfix) -> OK") {
        RPN rpn;
        const std::string expectedResult1 = "2 5 * 1 + 2 /";

        const auto result1 = rpn.convert("((2*5+1)/2)");

        REQUIRE(result1.length() > rpn.getPostfix().length());
        REQUIRE_THAT(rpn.getPostfix(), Catch::Equals(expectedResult1));
    }
}
