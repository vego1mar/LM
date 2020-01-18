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

    SECTION("convert1 -> OK") {
        RPN rpn;
        const std::string expectedResult2 = "2 5 1 + * 2 / 4 /";

        rpn.convert("((2*(5+1))/2)/4");

        REQUIRE_THAT(rpn.getPostfix(), Catch::Equals(expectedResult2));
    }

    SECTION("convert2 -> OK") {
        RPN rpn;
        const std::string expectedResult3 = "2 3 ^ 4 5 * + 1 1 2 + 3 4 5 * ^ - * -";

        rpn.convert("2^3+4*5-1*(1+2-3^(4*5))");

        REQUIRE_THAT(rpn.getPostfix(), Catch::Equals(expectedResult3));
    }

    SECTION("convert3 -> OK") {
        RPN rpn;
        const std::string expectedResult3 = "3 2 ^ 5 * 3 2 * 3 + / 5 1 / +";

        rpn.convert("(3^2*5)/(3*2+3)+5/1");

        REQUIRE_THAT(rpn.getPostfix(), Catch::Equals(expectedResult3));
    }

    SECTION("convert4 -> OK") {
        RPN rpn;
        const std::string expectedResult4 = "1 4 + 4 1 - * 2 3 ^ /";

        rpn.convert("((1+4)*(4-1))/(2^3)=");

        REQUIRE_THAT(rpn.getPostfix(), Catch::Equals(expectedResult4));
    }

}
