#include "../catch.hpp"
#include "../../src/helpers/strings.hpp"

using helpers::Strings;

TEST_CASE("strings.hpp", "[strings]") {
    SECTION("split('token1 2 three 4th', ' ') -> [token1,2,three,4th]") {
        std::string caseStr1 = "token1   2 three  4th ";
        std::string caseStr2 = "a,b,,c,d,efi,,,";
        std::vector<std::string> expectedResult1 = {"token1", "2", "three", "4th"};
        std::vector<std::string> expectedResult2 = {"a", "b", "c", "d", "efi"};

        auto result1 = Strings::split(caseStr1);
        auto result2 = Strings::split(caseStr2, ',');

        REQUIRE_THAT(result1, Catch::Equals(expectedResult1));
        REQUIRE_THAT(result2, Catch::Equals(expectedResult2));
    }

    SECTION("toLower('MAKE mE lOwEr') -> 'make me lower'") {
        std::string caseStr = "MAKE mE lOwEr";
        std::string expectedResult = "make me lower";

        auto result = Strings::toLower(caseStr);

        REQUIRE_THAT(result, Catch::Equals(expectedResult));
    }

    SECTION("startsWith('beta_012','beta') -> yes") {
        std::string caseStr1 = "beta_012";

        auto result1 = Strings::startsWith(caseStr1, "beta");
        auto result2 = Strings::startsWith(caseStr1, "eta");

        REQUIRE(result1);
        REQUIRE(!result2);
    }

}
