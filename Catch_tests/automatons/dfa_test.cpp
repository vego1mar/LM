#define CATCH_CONFIG_MAIN

#include "../catch.hpp"
#include "../../src/automatons/dfa.hpp"

using automatons::DFA;
using automatons::Alphabet;
using automatons::States;
using automatons::DFATransitionMap;

TEST_CASE("dfa.hpp", "[dfa]") {
    SECTION("DFA.setters -> OK") {
        Alphabet alphabet = {'a', 'b', 'c'};
        States states = {0, 1, 2};
        States finals = {2};
        DFATransitionMap transitionMap = {
                {{0, 'a'}, 2},
                {{0, 'b'}, 1},
                {{0, 'c'}, 0},
                {{1, 'a'}, 0},
                {{1, 'b'}, 2},
                {{1, 'c'}, 1},
                {{2, 'a'}, 0},
                {{2, 'b'}, 1},
                {{2, 'c'}, 2},
        };
        int start = 0;

        DFA dfa;
        dfa.setAlphabet(alphabet);
        dfa.setStates(states);
        dfa.setFinals(finals);
        dfa.setTransitions(transitionMap);
        dfa.setStart(start);

        CHECK(dfa.getAlphabet() == alphabet);
        CHECK(dfa.getStates() == states);
        CHECK(dfa.getFinals() == finals);
        CHECK(dfa.getTransitions() == transitionMap);
        CHECK(dfa.getStart() == start);
    }

    SECTION("DFA.simulate() -> OK") {
        Alphabet alphabet = {'a', 'b', 'c'};
        States states = {0, 1, 2};
        States finals = {2};
        DFATransitionMap transitionMap = {
                {{0, 'a'}, 2},
                {{0, 'b'}, 1},
                {{0, 'c'}, 0},
                {{1, 'a'}, 0},
                {{1, 'b'}, 2},
                {{1, 'c'}, 1},
                {{2, 'a'}, 0},
                {{2, 'b'}, 1},
                {{2, 'c'}, 2},
        };
        int start = 0;
        std::string input = "bccaaccbaaabb";
        std::string expectedToString = "{[[a,b,c],[0,1,2],[2],<9>,0}";
        DFA dfa;
        dfa.setAlphabet(alphabet);
        dfa.setStates(states);
        dfa.setFinals(finals);
        dfa.setTransitions(transitionMap);
        dfa.setStart(start);

        auto toString = dfa.toString();
        bool hasAcceptedInput = dfa.simulate(input, false);

        REQUIRE(toString == expectedToString);
        REQUIRE(hasAcceptedInput);
    }
}
