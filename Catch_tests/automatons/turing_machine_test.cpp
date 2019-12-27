#include "../catch.hpp"
#include "../../src/automatons/turing_machine.hpp"

using automatons::TuringMachine;
using automatons::TMTransitionMap;
using automatons::ShiftDirection;
using automatons::Alphabet;
using automatons::States;

TEST_CASE("turing_machine.hpp", "[turing_machine]") {
    const auto BLANK = TuringMachine::BLANK_SYMBOL;
    const auto RIGHT = ShiftDirection::RIGHT;
    const auto NO_SHIFT = ShiftDirection::NO_SHIFT;
    const auto HALT = TuringMachine::HALT_STATE;

    SECTION("TM.toString -> OK") {
        States states = {0, 1, 2, 3};
        States finals = {3};
        Alphabet tapeAlphabet = {'a', 'b', 'c', 'd', 'e', 'f'};
        TMTransitionMap transitionMap = {
                {{0, 'c'},   {'d',   RIGHT,    1}},
                {{1, 'a'},   {'e',   RIGHT,    2}},
                {{2, 'b'},   {'f',   RIGHT,    3}},
                {{3, BLANK}, {BLANK, NO_SHIFT, HALT}},
        };
        TuringMachine tm;
        tm.setStates(states);
        tm.setAlphabet(tapeAlphabet);
        tm.setStart(0);
        tm.setFinals(finals);
        tm.setTransitions(transitionMap);
        std::string expectedToString = "{[-1,0,1,2,3],[-,a,b,c,d,e,f],0,[3]}";

        REQUIRE(tm.toString() == expectedToString);
    }

    SECTION("simulate: cab -> def") {
        States states = {0, 1, 2, 3};
        States finals = {3};
        int initialState = 0;
        Alphabet tapeAlphabet = {'a', 'b', 'c', 'd', 'e', 'f', BLANK};
        TMTransitionMap transitionMap = {
                {{0, 'c'},   {'d',   RIGHT,    1}},
                {{1, 'a'},   {'e',   RIGHT,    2}},
                {{2, 'b'},   {'f',   RIGHT,    3}},
                {{3, BLANK}, {BLANK, NO_SHIFT, HALT}},
        };
        TuringMachine tm;
        tm.setStates(states);
        tm.setAlphabet(tapeAlphabet);
        tm.setStart(initialState);
        tm.setFinals(finals);
        tm.setTransitions(transitionMap);
        std::string expectedToString = "{[-1,0,1,2,3],[-,a,b,c,d,e,f],0,[3]}";

        bool isAccepting = tm.simulate("cab", false);

        REQUIRE(tm.getAlphabet() == tapeAlphabet);
        REQUIRE(tm.getStates() == States{-1, 0, 1, 2, 3});
        REQUIRE(tm.getFinals() == finals);
        REQUIRE(tm.getStart() == initialState);
        REQUIRE(tm.getTransitions() == transitionMap);
        REQUIRE(tm.toString() == expectedToString);
        REQUIRE(isAccepting);
        REQUIRE_THAT(tm.getInputTape(), Catch::Equals("def"));
    }

    SECTION("nextStep() until hasNext(): cab -> def") {
        States states = {0, 1, 2, 3};
        States finals = {3};
        int initialState = 0;
        Alphabet tapeAlphabet = {'a', 'b', 'c', 'd', 'e', 'f', BLANK};
        TMTransitionMap transitionMap = {
                {{0, 'c'},   {'d',   RIGHT,    1}},
                {{1, 'a'},   {'e',   RIGHT,    2}},
                {{2, 'b'},   {'f',   RIGHT,    3}},
                {{3, BLANK}, {BLANK, NO_SHIFT, HALT}},
        };
        TuringMachine tm;
        tm.setStates(states);
        tm.setAlphabet(tapeAlphabet);
        tm.setStart(initialState);
        tm.setFinals(finals);
        tm.setTransitions(transitionMap);
        std::string expectedToString = "{[-1,0,1,2,3],[-,a,b,c,d,e,f],0,[3]}";
        std::vector<std::tuple<bool, std::string>> expectedResults = {
                {false, "dab"},
                {false, "deb"},
                {true,  "def"},
        };
        std::vector<std::tuple<bool, std::string>> results;
        tm.setInputTape("cab");

        while (tm.hasNextStep()) {
            results.emplace_back(tm.nextStep());
        }

        REQUIRE(tm.getAlphabet() == tapeAlphabet);
        REQUIRE(tm.getStates() == States{-1, 0, 1, 2, 3});
        REQUIRE(tm.getFinals() == finals);
        REQUIRE(tm.getStart() == initialState);
        REQUIRE(tm.getTransitions() == transitionMap);
        REQUIRE(tm.toString() == expectedToString);
        REQUIRE(results == expectedResults);
        REQUIRE_THROWS_AS(tm.nextStep(), std::out_of_range);
    }

}
