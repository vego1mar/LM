#include "../catch.hpp"
#include "../../src/automatons/nfa.hpp"

using automatons::NFA;
using automatons::Alphabet;
using automatons::States;
using automatons::NFATransitionMap;

TEST_CASE("nfa_test.hpp", "[nfa]") {
    const char EMPTY = automatons::NFA::EMPTY_SYMBOL;

    SECTION("NFA.simulate -> OK") {
        Alphabet alphabet = {'c', 'l'};
        States states = {0, 1, 2, 3, 4, 5, 6};
        States finals = {3, 6};
        NFATransitionMap transitions = {
                {{0, 'c'},   {0}},
                {{0, 'l'},   {0}},
                {{0, EMPTY}, {1, 4}},
                {{1, 'c'},   {2}},
                {{2, 'c'},   {3}},
                {{3, 'c'},   {3}},
                {{3, 'l'},   {3}},
                {{4, 'l'},   {5}},
                {{5, 'l'},   {6}},
                {{6, 'c'},   {6}},
                {{6, 'l'},   {6}},
        };
        States start = {0};
        NFA nfa;
        nfa.setAlphabet(alphabet);
        nfa.setStates(states);
        nfa.setFinals(finals);
        nfa.setTransitions(transitions);
        nfa.setStart(start);
        std::string expectedToString = "{[c,l],[0,1,2,3,4,5,6],[3,6],<11>,[0]}";

        bool isAcceptingState = nfa.simulate("!cca", true);

        REQUIRE(!isAcceptingState);
        REQUIRE(nfa.toString() == expectedToString);
    }

}
