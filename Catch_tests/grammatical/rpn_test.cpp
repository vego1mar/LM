#include "../catch.hpp"
#include "../../src/grammatical/rpn.hpp"

using grammatical::RPN;


TEST_CASE("rpn.hpp", "[rpn]") {
    SECTION("(convert,getPostfix) -> OK") {
        RPN rpn;
        const std::string expectedResult1 = "2 5 * 1 + 2 /";

        rpn.convert("((2*5+1)/2)");

        REQUIRE_THAT(rpn.getPostfix(), Catch::Equals(expectedResult1));
    }
}
