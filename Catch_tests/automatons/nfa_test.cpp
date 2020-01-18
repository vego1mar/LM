#include "../catch.hpp"
#include "../../src/automatons/nfa.hpp"
#include "../../src/io_manager/fsm_reader.hpp"
#include "../../src/tests/definitions.hpp"

using automatons::NFA;
using automatons::Alphabet;
using automatons::States;
using automatons::NFATransitionMap;
using automatons::StateEventPair;
using io_manager::FSMReader;
using tests::Constants;


TEST_CASE("nfa_test.hpp", "[nfa]") {
    const Constants consts;
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
        REQUIRE(isAcceptingState5);
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

    SECTION("NFA2 -> OK") {
        NFA nfa;
        FSMReader reader;
        reader.parse(consts.NFA_2_PATH, nfa);

        const Alphabet expectedAlphabet = {'0', '1', '2', '3', '4', 'a', 'b', 'c', 'd', 'e'};
        const States expectedStates = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 100, 101, 102, 103, 104, 200, 201, 202, 203, 204};
        const States expectedStart = {0};
        const States expectedFinals = {100, 101, 102, 103, 104, 200, 201, 202, 203, 204};
        const NFATransitionMap expectedTransitions = {
                {StateEventPair(0, 'a'),   States{0}},
                {StateEventPair(0, 'b'),   States{0}},
                {StateEventPair(0, 'c'),   States{0}},
                {StateEventPair(0, 'd'),   States{0}},
                {StateEventPair(0, 'e'),   States{0}},
                {StateEventPair(0, '0'),   States{0}},
                {StateEventPair(0, '1'),   States{0}},
                {StateEventPair(0, '2'),   States{0}},
                {StateEventPair(0, '3'),   States{0}},
                {StateEventPair(0, '4'),   States{0}},
                {StateEventPair(0, EMPTY), States{1, 2}},
                {StateEventPair(1, '0'),   States{3}},
                {StateEventPair(1, '1'),   States{4}},
                {StateEventPair(1, '2'),   States{5}},
                {StateEventPair(1, '3'),   States{6}},
                {StateEventPair(1, '4'),   States{7}},
                {StateEventPair(2, 'a'),   States{8}},
                {StateEventPair(2, 'b'),   States{9}},
                {StateEventPair(2, 'c'),   States{10}},
                {StateEventPair(2, 'd'),   States{11}},
                {StateEventPair(2, 'e'),   States{12}},
                {StateEventPair(3, '0'),   States{100}},
                {StateEventPair(4, '1'),   States{101}},
                {StateEventPair(5, '2'),   States{102}},
                {StateEventPair(6, '3'),   States{103}},
                {StateEventPair(7, '4'),   States{104}},
                {StateEventPair(8, 'a'),   States{200}},
                {StateEventPair(9, 'b'),   States{201}},
                {StateEventPair(10, 'c'),  States{202}},
                {StateEventPair(11, 'd'),  States{203}},
                {StateEventPair(12, 'e'),  States{204}},
                {StateEventPair(100, '0'), States{100}},
                {StateEventPair(100, '1'), States{100}},
                {StateEventPair(100, '2'), States{100}},
                {StateEventPair(100, '3'), States{100}},
                {StateEventPair(100, '4'), States{100}},
                {StateEventPair(100, 'a'), States{100}},
                {StateEventPair(100, 'b'), States{100}},
                {StateEventPair(100, 'c'), States{100}},
                {StateEventPair(100, 'd'), States{100}},
                {StateEventPair(100, 'e'), States{100}},
                {StateEventPair(101, '0'), States{101}},
                {StateEventPair(101, '1'), States{101}},
                {StateEventPair(101, '2'), States{101}},
                {StateEventPair(101, '3'), States{101}},
                {StateEventPair(101, '4'), States{101}},
                {StateEventPair(101, 'a'), States{101}},
                {StateEventPair(101, 'b'), States{101}},
                {StateEventPair(101, 'c'), States{101}},
                {StateEventPair(101, 'd'), States{101}},
                {StateEventPair(101, 'e'), States{101}},
                {StateEventPair(102, '0'), States{102}},
                {StateEventPair(102, '1'), States{102}},
                {StateEventPair(102, '2'), States{102}},
                {StateEventPair(102, '3'), States{102}},
                {StateEventPair(102, '4'), States{102}},
                {StateEventPair(102, 'a'), States{102}},
                {StateEventPair(102, 'b'), States{102}},
                {StateEventPair(102, 'c'), States{102}},
                {StateEventPair(102, 'd'), States{102}},
                {StateEventPair(102, 'e'), States{102}},
                {StateEventPair(103, '0'), States{103}},
                {StateEventPair(103, '1'), States{103}},
                {StateEventPair(103, '2'), States{103}},
                {StateEventPair(103, '3'), States{103}},
                {StateEventPair(103, '4'), States{103}},
                {StateEventPair(103, 'a'), States{103}},
                {StateEventPair(103, 'b'), States{103}},
                {StateEventPair(103, 'c'), States{103}},
                {StateEventPair(103, 'd'), States{103}},
                {StateEventPair(103, 'e'), States{103}},
                {StateEventPair(104, '0'), States{104}},
                {StateEventPair(104, '1'), States{104}},
                {StateEventPair(104, '2'), States{104}},
                {StateEventPair(104, '3'), States{104}},
                {StateEventPair(104, '4'), States{104}},
                {StateEventPair(104, 'a'), States{104}},
                {StateEventPair(104, 'b'), States{104}},
                {StateEventPair(104, 'c'), States{104}},
                {StateEventPair(104, 'd'), States{104}},
                {StateEventPair(104, 'e'), States{104}},
                {StateEventPair(200, '0'), States{200}},
                {StateEventPair(200, '1'), States{200}},
                {StateEventPair(200, '2'), States{200}},
                {StateEventPair(200, '3'), States{200}},
                {StateEventPair(200, '4'), States{200}},
                {StateEventPair(200, 'a'), States{200}},
                {StateEventPair(200, 'b'), States{200}},
                {StateEventPair(200, 'c'), States{200}},
                {StateEventPair(200, 'd'), States{200}},
                {StateEventPair(200, 'e'), States{200}},
                {StateEventPair(201, '0'), States{201}},
                {StateEventPair(201, '1'), States{201}},
                {StateEventPair(201, '2'), States{201}},
                {StateEventPair(201, '3'), States{201}},
                {StateEventPair(201, '4'), States{201}},
                {StateEventPair(201, 'a'), States{201}},
                {StateEventPair(201, 'b'), States{201}},
                {StateEventPair(201, 'c'), States{201}},
                {StateEventPair(201, 'd'), States{201}},
                {StateEventPair(201, 'e'), States{201}},
                {StateEventPair(202, '0'), States{202}},
                {StateEventPair(202, '1'), States{202}},
                {StateEventPair(202, '2'), States{202}},
                {StateEventPair(202, '3'), States{202}},
                {StateEventPair(202, '4'), States{202}},
                {StateEventPair(202, 'a'), States{202}},
                {StateEventPair(202, 'b'), States{202}},
                {StateEventPair(202, 'c'), States{202}},
                {StateEventPair(202, 'd'), States{202}},
                {StateEventPair(202, 'e'), States{202}},
                {StateEventPair(203, '0'), States{203}},
                {StateEventPair(203, '1'), States{203}},
                {StateEventPair(203, '2'), States{203}},
                {StateEventPair(203, '3'), States{203}},
                {StateEventPair(203, '4'), States{203}},
                {StateEventPair(203, 'a'), States{203}},
                {StateEventPair(203, 'b'), States{203}},
                {StateEventPair(203, 'c'), States{203}},
                {StateEventPair(203, 'd'), States{203}},
                {StateEventPair(203, 'e'), States{203}},
                {StateEventPair(204, '0'), States{204}},
                {StateEventPair(204, '1'), States{204}},
                {StateEventPair(204, '2'), States{204}},
                {StateEventPair(204, '3'), States{204}},
                {StateEventPair(204, '4'), States{204}},
                {StateEventPair(204, 'a'), States{204}},
                {StateEventPair(204, 'b'), States{204}},
                {StateEventPair(204, 'c'), States{204}},
                {StateEventPair(204, 'd'), States{204}},
                {StateEventPair(204, 'e'), States{204}},
        };
        REQUIRE(nfa.getAlphabet() == expectedAlphabet);
        REQUIRE(nfa.getStates() == expectedStates);
        REQUIRE(nfa.getStart() == expectedStart);
        REQUIRE(nfa.getFinals() == expectedFinals);
        REQUIRE(nfa.getTransitions() == expectedTransitions);

        bool isAccepting = nfa.simulate("babaab", false);
        REQUIRE(isAccepting);
    }

}
