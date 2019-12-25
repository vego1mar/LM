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

        bool isAcceptingState = nfa.simulate("!cca", false);

        REQUIRE(!isAcceptingState);
        REQUIRE(nfa.toString() == expectedToString);
    }

    SECTION("NFA no.2 cases -> OK") {
        Alphabet alphabet = {'a', 'b', 'c', 'd', 'e', 'f', 'g'};
        States states = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17};
        States finals = {5, 7, 8, 14, 17};
        NFATransitionMap transitions = {
                {{0,  'd'},   {9}},
                {{0,  EMPTY}, {1}},
                {{1,  EMPTY}, {2}},
                {{2,  'a'},   {3,  6, 8}},
                {{3,  'b'},   {4}},
                {{4,  'c'},   {5}},
                {{6,  'c'},   {7}},
                {{7,  'f'},   {4}},
                {{9,  'a'},   {10}},
                {{9,  'b'},   {11}},
                {{10, 'e'},   {16}},
                {{10, 'f'},   {17}},
                {{11, 'a'},   {12}},
                {{11, 'b'},   {13, 15}},
                {{13, 'd'},   {14}},
                {{17, 'g'},   {17, 6}},
        };
        States start = {0, 17};
        NFA nfa;
        nfa.setAlphabet(alphabet);
        nfa.setStates(states);
        nfa.setFinals(finals);
        nfa.setTransitions(transitions);
        nfa.setStart(start);

        bool isAcceptingState1 = nfa.simulate("!!a", false);
        bool isAcceptingState2 = nfa.simulate("!!ac", false);
        bool isAcceptingState3 = nfa.simulate("!!abc", false);
        bool isAcceptingState4 = nfa.simulate("!!aa", false);
        bool isAcceptingState5 = nfa.simulate("dba", false);
        bool isAcceptingState6 = nfa.simulate("dbb", false);
        bool isAcceptingState7 = nfa.simulate("dbbd", false);
        bool isAcceptingState8 = nfa.simulate("da", false);
        bool isAcceptingState9 = nfa.simulate("dae", false);
        bool isAcceptingState10 = nfa.simulate("daf", false);
        bool isAcceptingState11 = nfa.simulate("dafg", false);
        bool isAcceptingState12 = nfa.simulate("dafgg", false);
        bool isAcceptingState13 = nfa.simulate("dafggc", false);
        bool isAcceptingState14 = nfa.simulate("dafggcfc", false);

        REQUIRE(isAcceptingState1);
        REQUIRE(isAcceptingState2);
        REQUIRE(isAcceptingState3);
        REQUIRE(!isAcceptingState4);
        REQUIRE(!isAcceptingState5);
        REQUIRE(!isAcceptingState6);
        REQUIRE(isAcceptingState7);
        REQUIRE(!isAcceptingState8);
        REQUIRE(!isAcceptingState9);
        REQUIRE(isAcceptingState10);
        REQUIRE(isAcceptingState11);
        REQUIRE(isAcceptingState12);
        REQUIRE(isAcceptingState13);
        REQUIRE(isAcceptingState14);
    }

}
