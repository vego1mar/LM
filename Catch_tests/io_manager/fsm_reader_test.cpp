#include "../catch.hpp"
#include "../../src/io_manager/fsm_reader.hpp"
#include "../../src/io_manager/file_reader.hpp"
#include "../../src/helpers/strings.hpp"
#include "../../src/tests/definitions.hpp"

using io_manager::FSMReader;
using io_manager::FileReader;
using helpers::Strings;
using automatons::DFATransitionMap;
using automatons::Alphabet;
using automatons::States;
using automatons::NFATransitionMap;
using automatons::DFA;
using automatons::NFA;
using automatons::TuringMachine;
using automatons::TMTransitionMap;
using automatons::StateEventPair;
using automatons::ActionTuple;
using automatons::ShiftDirection;
using tests::Constants;


TEST_CASE("fsm_reader.hpp", "[fsm_reader]") {
    Constants consts;

    SECTION("parse(DFA_1) -> dfa object OK") {
        Alphabet expectedAlphabet = {'1', '2', '5', 'a', 'b', 'r', 'z'};
        States expectedStates = {0, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
                                 200, 201, 202, 203, 204, 205, 206, 207, 208, 209, 210, 211, 212, 213, 214, 215, 216,
                                 217, 218, 219, 220, 221, 222, 223, 224};
        int expectedStart = 0;
        States expectedFinals = {100, 109, 112, 200, 215, 220};
        DFATransitionMap expectedTransitionMap = {
                {{0,   '1'}, 101},
                {{0,   '2'}, 102},
                {{0,   '5'}, 105},
                {{0,   'a'}, 100},
                {{0,   'b'}, 200},
                {{0,   'r'}, 0},
                {{0,   'z'}, 0},
                {{100, '1'}, 101},
                {{100, '2'}, 102},
                {{100, '5'}, 105},
                {{100, 'a'}, 100},
                {{100, 'b'}, 200},
                {{100, 'r'}, 100},
                {{100, 'z'}, 100},
                {{101, '1'}, 102},
                {{101, '2'}, 103},
                {{101, '5'}, 106},
                {{101, 'a'}, 101},
                {{101, 'b'}, 201},
                {{101, 'r'}, 100},
                {{101, 'z'}, 100},
                {{102, '1'}, 103},
                {{102, '2'}, 104},
                {{102, '5'}, 107},
                {{102, 'a'}, 102},
                {{102, 'b'}, 202},
                {{102, 'r'}, 100},
                {{102, 'z'}, 100},
                {{103, '1'}, 104},
                {{103, '2'}, 105},
                {{103, '5'}, 108},
                {{103, 'a'}, 103},
                {{103, 'b'}, 203},
                {{103, 'r'}, 100},
                {{103, 'z'}, 100},
                {{104, '1'}, 105},
                {{104, '2'}, 106},
                {{104, '5'}, 109},
                {{104, 'a'}, 104},
                {{104, 'b'}, 204},
                {{104, 'r'}, 100},
                {{104, 'z'}, 100},
                {{105, '1'}, 106},
                {{105, '2'}, 107},
                {{105, '5'}, 110},
                {{105, 'a'}, 105},
                {{105, 'b'}, 205},
                {{105, 'r'}, 100},
                {{105, 'z'}, 100},
                {{106, '1'}, 107},
                {{106, '2'}, 108},
                {{106, '5'}, 111},
                {{106, 'a'}, 106},
                {{106, 'b'}, 206},
                {{106, 'r'}, 100},
                {{106, 'z'}, 100},
                {{107, '1'}, 108},
                {{107, '2'}, 109},
                {{107, '5'}, 112},
                {{107, 'a'}, 107},
                {{107, 'b'}, 207},
                {{107, 'r'}, 100},
                {{107, 'z'}, 100},
                {{108, '1'}, 109},
                {{108, '2'}, 110},
                {{108, '5'}, 113},
                {{108, 'a'}, 108},
                {{108, 'b'}, 208},
                {{108, 'r'}, 100},
                {{108, 'z'}, 100},
                {{109, '1'}, 110},
                {{109, '2'}, 111},
                {{109, '5'}, 114},
                {{109, 'a'}, 109},
                {{109, 'b'}, 209},
                {{109, 'r'}, 109},
                {{109, 'z'}, 100},
                {{110, '1'}, 111},
                {{110, '2'}, 112},
                {{110, '5'}, 115},
                {{110, 'a'}, 110},
                {{110, 'b'}, 210},
                {{110, 'r'}, 109},
                {{110, 'z'}, 100},
                {{111, '1'}, 112},
                {{111, '2'}, 113},
                {{111, '5'}, 116},
                {{111, 'a'}, 111},
                {{111, 'b'}, 211},
                {{111, 'r'}, 109},
                {{111, 'z'}, 100},
                {{112, '1'}, 112},
                {{112, '2'}, 112},
                {{112, '5'}, 112},
                {{112, 'a'}, 112},
                {{112, 'b'}, 212},
                {{112, 'r'}, 112},
                {{112, 'z'}, 100},
                {{113, '1'}, 113},
                {{113, '2'}, 113},
                {{113, '5'}, 113},
                {{113, 'a'}, 113},
                {{113, 'b'}, 213},
                {{113, 'r'}, 112},
                {{113, 'z'}, 100},
                {{114, '1'}, 114},
                {{114, '2'}, 114},
                {{114, '5'}, 114},
                {{114, 'a'}, 114},
                {{114, 'b'}, 214},
                {{114, 'r'}, 112},
                {{114, 'z'}, 100},
                {{115, '1'}, 115},
                {{115, '2'}, 115},
                {{115, '5'}, 115},
                {{115, 'a'}, 115},
                {{115, 'b'}, 215},
                {{115, 'r'}, 112},
                {{115, 'z'}, 100},
                {{116, '1'}, 116},
                {{116, '2'}, 116},
                {{116, '5'}, 116},
                {{116, 'a'}, 116},
                {{116, 'b'}, 216},
                {{116, 'r'}, 112},
                {{116, 'z'}, 100},
                {{200, '1'}, 201},
                {{200, '2'}, 202},
                {{200, '5'}, 205},
                {{200, 'a'}, 100},
                {{200, 'b'}, 200},
                {{200, 'r'}, 200},
                {{200, 'z'}, 200},
                {{201, '1'}, 202},
                {{201, '2'}, 203},
                {{201, '5'}, 206},
                {{201, 'a'}, 101},
                {{201, 'b'}, 201},
                {{201, 'r'}, 200},
                {{201, 'z'}, 200},
                {{202, '1'}, 203},
                {{202, '2'}, 204},
                {{202, '5'}, 207},
                {{202, 'a'}, 102},
                {{202, 'b'}, 202},
                {{202, 'r'}, 200},
                {{202, 'z'}, 200},
                {{203, '1'}, 204},
                {{203, '2'}, 205},
                {{203, '5'}, 208},
                {{203, 'a'}, 103},
                {{203, 'b'}, 203},
                {{203, 'r'}, 200},
                {{203, 'z'}, 200},
                {{204, '1'}, 205},
                {{204, '2'}, 206},
                {{204, '5'}, 209},
                {{204, 'a'}, 104},
                {{204, 'b'}, 204},
                {{204, 'r'}, 200},
                {{204, 'z'}, 200},
                {{205, '1'}, 206},
                {{205, '2'}, 207},
                {{205, '5'}, 210},
                {{205, 'a'}, 105},
                {{205, 'b'}, 205},
                {{205, 'r'}, 200},
                {{205, 'z'}, 200},
                {{206, '1'}, 207},
                {{206, '2'}, 208},
                {{206, '5'}, 211},
                {{206, 'a'}, 106},
                {{206, 'b'}, 206},
                {{206, 'r'}, 200},
                {{206, 'z'}, 200},
                {{207, '1'}, 208},
                {{207, '2'}, 209},
                {{207, '5'}, 212},
                {{207, 'a'}, 107},
                {{207, 'b'}, 207},
                {{207, 'r'}, 200},
                {{207, 'z'}, 200},
                {{208, '1'}, 209},
                {{208, '2'}, 210},
                {{208, '5'}, 213},
                {{208, 'a'}, 108},
                {{208, 'b'}, 208},
                {{208, 'r'}, 200},
                {{208, 'z'}, 200},
                {{209, '1'}, 210},
                {{209, '2'}, 211},
                {{209, '5'}, 214},
                {{209, 'a'}, 109},
                {{209, 'b'}, 209},
                {{209, 'r'}, 200},
                {{209, 'z'}, 200},
                {{210, '1'}, 211},
                {{210, '2'}, 212},
                {{210, '5'}, 215},
                {{210, 'a'}, 110},
                {{210, 'b'}, 210},
                {{210, 'r'}, 200},
                {{210, 'z'}, 200},
                {{211, '1'}, 212},
                {{211, '2'}, 213},
                {{211, '5'}, 216},
                {{211, 'a'}, 111},
                {{211, 'b'}, 211},
                {{211, 'r'}, 200},
                {{211, 'z'}, 200},
                {{212, '1'}, 213},
                {{212, '2'}, 214},
                {{212, '5'}, 217},
                {{212, 'a'}, 112},
                {{212, 'b'}, 212},
                {{212, 'r'}, 200},
                {{212, 'z'}, 200},
                {{213, '1'}, 214},
                {{213, '2'}, 215},
                {{213, '5'}, 218},
                {{213, 'a'}, 113},
                {{213, 'b'}, 213},
                {{213, 'r'}, 200},
                {{213, 'z'}, 200},
                {{214, '1'}, 215},
                {{214, '2'}, 216},
                {{214, '5'}, 219},
                {{214, 'a'}, 114},
                {{214, 'b'}, 214},
                {{214, 'r'}, 200},
                {{214, 'z'}, 200},
                {{215, '1'}, 216},
                {{215, '2'}, 217},
                {{215, '5'}, 220},
                {{215, 'a'}, 115},
                {{215, 'b'}, 215},
                {{215, 'r'}, 215},
                {{215, 'z'}, 200},
                {{216, '1'}, 217},
                {{216, '2'}, 218},
                {{216, '5'}, 221},
                {{216, 'a'}, 116},
                {{216, 'b'}, 216},
                {{216, 'r'}, 215},
                {{216, 'z'}, 200},
                {{217, '1'}, 218},
                {{217, '2'}, 219},
                {{217, '5'}, 222},
                {{217, 'a'}, 217},
                {{217, 'b'}, 217},
                {{217, 'r'}, 215},
                {{217, 'z'}, 200},
                {{218, '1'}, 219},
                {{218, '2'}, 220},
                {{218, '5'}, 223},
                {{218, 'a'}, 218},
                {{218, 'b'}, 218},
                {{218, 'r'}, 215},
                {{218, 'z'}, 200},
                {{219, '1'}, 220},
                {{219, '2'}, 221},
                {{219, '5'}, 224},
                {{219, 'a'}, 219},
                {{219, 'b'}, 219},
                {{219, 'r'}, 215},
                {{219, 'z'}, 200},
                {{220, '1'}, 220},
                {{220, '2'}, 220},
                {{220, '5'}, 220},
                {{220, 'a'}, 220},
                {{220, 'b'}, 220},
                {{220, 'r'}, 220},
                {{220, 'z'}, 200},
                {{221, '1'}, 221},
                {{221, '2'}, 221},
                {{221, '5'}, 221},
                {{221, 'a'}, 221},
                {{221, 'b'}, 221},
                {{221, 'r'}, 220},
                {{221, 'z'}, 200},
                {{222, '1'}, 222},
                {{222, '2'}, 222},
                {{222, '5'}, 222},
                {{222, 'a'}, 222},
                {{222, 'b'}, 222},
                {{222, 'r'}, 220},
                {{222, 'z'}, 200},
                {{223, '1'}, 223},
                {{223, '2'}, 223},
                {{223, '5'}, 223},
                {{223, 'a'}, 223},
                {{223, 'b'}, 223},
                {{223, 'r'}, 220},
                {{223, 'z'}, 200},
                {{224, '1'}, 224},
                {{224, '2'}, 224},
                {{224, '5'}, 224},
                {{224, 'a'}, 224},
                {{224, 'b'}, 224},
                {{224, 'r'}, 220},
                {{224, 'z'}, 200},
        };
        FSMReader reader;
        DFA dfa;

        reader.parse(consts.DFA_1_PATH, dfa);

        REQUIRE(dfa.getAlphabet() == expectedAlphabet);
        REQUIRE(dfa.getStates() == expectedStates);
        REQUIRE(dfa.getStart() == expectedStart);
        REQUIRE(dfa.getFinals() == expectedFinals);
        REQUIRE(dfa.getTransitions().size() == expectedTransitionMap.size());
        REQUIRE(dfa.getTransitions() == expectedTransitionMap);
    }

    SECTION("simulate(DFA_1; input) -> ACCEPT") {
        FSMReader reader;
        DFA dfa;

        reader.parse(consts.DFA_1_PATH, dfa);
        REQUIRE(dfa.getAlphabet().size() == 7);
        REQUIRE(dfa.getStates().size() == 43);
        REQUIRE(dfa.getFinals().size() == 6);
        REQUIRE(dfa.getTransitions().size() == 301);

        auto result = dfa.simulate("55b55z11111111a21r", false);

        REQUIRE(result);
    }

    SECTION("simulate(DFA_1; DFA_1_INPUT) -> ACCEPT") {
        FileReader fileReader;
        FSMReader fsmReader;
        DFA dfa;

        fileReader.link(consts.DFA_1_PATH);
        REQUIRE(fileReader.isBind());
        REQUIRE(fileReader.getFileSize() == consts.DFA_1_SIZE);
        fileReader.sever();

        fsmReader.parse(consts.DFA_1_PATH, dfa);
        REQUIRE(dfa.getAlphabet().size() == 7);
        REQUIRE(dfa.getStates().size() == 43);
        REQUIRE(dfa.getFinals().size() == 6);
        REQUIRE(dfa.getTransitions().size() == 301);

        fileReader.link(consts.INPUT_1_PATH);
        REQUIRE(fileReader.isBind());
        REQUIRE(fileReader.getFileSize() == consts.INPUT_1_SIZE);
        fileReader.setType(io_manager::ReadType::WHOLE_FILE);
        fileReader.readIntoBuffer();
        auto readInput = Strings::flatten(fileReader.getContentBuffer());
        auto validInput = Strings::remove(readInput, '\n');
        fileReader.sever();
        REQUIRE(!fileReader.isBind());

        auto result = dfa.simulate(validInput, false);

        REQUIRE(result);
    }

    SECTION("simulate(NFA_1; NFA_1_INPUT) -> [A,A,R,A]") {
        const auto &expectedAlphabet = Alphabet({'0', '1', '2', '3', '4', 'a', 'b', 'c', 'd', 'e'});
        const auto &expectedStates = States({1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 100, 101, 102, 103, 104,
                                             200, 201, 202, 203, 204});
        const auto &expectedFinals = States({100, 101, 102, 103, 104, 200, 201, 202, 203, 204});
        const auto &expectedStart = States({1, 2});
        const auto &expectedTransitions = NFATransitionMap({
                                                                   {{1,   '0'}, {3,  1}},
                                                                   {{1,   '1'}, {4,  1}},
                                                                   {{1,   '2'}, {5,  1}},
                                                                   {{1,   '3'}, {6,  1}},
                                                                   {{1,   '4'}, {7,  1}},
                                                                   {{1,   'a'}, {1}},
                                                                   {{1,   'b'}, {1}},
                                                                   {{1,   'c'}, {1}},
                                                                   {{1,   'd'}, {1}},
                                                                   {{1,   'e'}, {1}},
                                                                   {{2,   '0'}, {2}},
                                                                   {{2,   '1'}, {2}},
                                                                   {{2,   '2'}, {2}},
                                                                   {{2,   '3'}, {2}},
                                                                   {{2,   '4'}, {2}},
                                                                   {{2,   'a'}, {8,  2}},
                                                                   {{2,   'b'}, {9,  2}},
                                                                   {{2,   'c'}, {10, 2}},
                                                                   {{2,   'd'}, {11, 2}},
                                                                   {{2,   'e'}, {12, 2}},
                                                                   {{3,   '0'}, {100}},
                                                                   {{4,   '1'}, {101}},
                                                                   {{5,   '2'}, {102}},
                                                                   {{6,   '3'}, {103}},
                                                                   {{7,   '4'}, {104}},
                                                                   {{8,   'a'}, {200}},
                                                                   {{9,   'b'}, {201}},
                                                                   {{10,  'c'}, {202}},
                                                                   {{11,  'd'}, {203}},
                                                                   {{12,  'e'}, {204}},
                                                                   {{100, '0'}, {100}},
                                                                   {{100, '1'}, {100}},
                                                                   {{100, '2'}, {100}},
                                                                   {{100, '3'}, {100}},
                                                                   {{100, '4'}, {100}},
                                                                   {{100, 'a'}, {100}},
                                                                   {{100, 'b'}, {100}},
                                                                   {{100, 'c'}, {100}},
                                                                   {{100, 'd'}, {100}},
                                                                   {{100, 'e'}, {100}},
                                                                   {{101, '0'}, {101}},
                                                                   {{101, '1'}, {101}},
                                                                   {{101, '2'}, {101}},
                                                                   {{101, '3'}, {101}},
                                                                   {{101, '4'}, {101}},
                                                                   {{101, 'a'}, {101}},
                                                                   {{101, 'b'}, {101}},
                                                                   {{101, 'c'}, {101}},
                                                                   {{101, 'd'}, {101}},
                                                                   {{101, 'e'}, {101}},
                                                                   {{102, '0'}, {102}},
                                                                   {{102, '1'}, {102}},
                                                                   {{102, '2'}, {102}},
                                                                   {{102, '3'}, {102}},
                                                                   {{102, '4'}, {102}},
                                                                   {{102, 'a'}, {102}},
                                                                   {{102, 'b'}, {102}},
                                                                   {{102, 'c'}, {102}},
                                                                   {{102, 'd'}, {102}},
                                                                   {{102, 'e'}, {102}},
                                                                   {{103, '0'}, {103}},
                                                                   {{103, '1'}, {103}},
                                                                   {{103, '2'}, {103}},
                                                                   {{103, '3'}, {103}},
                                                                   {{103, '4'}, {103}},
                                                                   {{103, 'a'}, {103}},
                                                                   {{103, 'b'}, {103}},
                                                                   {{103, 'c'}, {103}},
                                                                   {{103, 'd'}, {103}},
                                                                   {{103, 'e'}, {103}},
                                                                   {{104, '0'}, {104}},
                                                                   {{104, '1'}, {104}},
                                                                   {{104, '2'}, {104}},
                                                                   {{104, '3'}, {104}},
                                                                   {{104, '4'}, {104}},
                                                                   {{104, 'a'}, {104}},
                                                                   {{104, 'b'}, {104}},
                                                                   {{104, 'c'}, {104}},
                                                                   {{104, 'd'}, {104}},
                                                                   {{104, 'e'}, {104}},
                                                                   {{200, '0'}, {200}},
                                                                   {{200, '1'}, {200}},
                                                                   {{200, '2'}, {200}},
                                                                   {{200, '3'}, {200}},
                                                                   {{200, '4'}, {200}},
                                                                   {{200, 'a'}, {200}},
                                                                   {{200, 'b'}, {200}},
                                                                   {{200, 'c'}, {200}},
                                                                   {{200, 'd'}, {200}},
                                                                   {{200, 'e'}, {200}},
                                                                   {{201, '0'}, {201}},
                                                                   {{201, '1'}, {201}},
                                                                   {{201, '2'}, {201}},
                                                                   {{201, '3'}, {201}},
                                                                   {{201, '4'}, {201}},
                                                                   {{201, 'a'}, {201}},
                                                                   {{201, 'b'}, {201}},
                                                                   {{201, 'c'}, {201}},
                                                                   {{201, 'd'}, {201}},
                                                                   {{201, 'e'}, {201}},
                                                                   {{202, '0'}, {202}},
                                                                   {{202, '1'}, {202}},
                                                                   {{202, '2'}, {202}},
                                                                   {{202, '3'}, {202}},
                                                                   {{202, '4'}, {202}},
                                                                   {{202, 'a'}, {202}},
                                                                   {{202, 'b'}, {202}},
                                                                   {{202, 'c'}, {202}},
                                                                   {{202, 'd'}, {202}},
                                                                   {{202, 'e'}, {202}},
                                                                   {{203, '0'}, {203}},
                                                                   {{203, '1'}, {203}},
                                                                   {{203, '2'}, {203}},
                                                                   {{203, '3'}, {203}},
                                                                   {{203, '4'}, {203}},
                                                                   {{203, 'a'}, {203}},
                                                                   {{203, 'b'}, {203}},
                                                                   {{203, 'c'}, {203}},
                                                                   {{203, 'd'}, {203}},
                                                                   {{203, 'e'}, {203}},
                                                                   {{204, '0'}, {204}},
                                                                   {{204, '1'}, {204}},
                                                                   {{204, '2'}, {204}},
                                                                   {{204, '3'}, {204}},
                                                                   {{204, '4'}, {204}},
                                                                   {{204, 'a'}, {204}},
                                                                   {{204, 'b'}, {204}},
                                                                   {{204, 'c'}, {204}},
                                                                   {{204, 'd'}, {204}},
                                                                   {{204, 'e'}, {204}},
                                                           });
        FileReader fileReader;
        FSMReader fsmReader;
        NFA nfa;

        fileReader.link(consts.NFA_1_PATH);
        REQUIRE(fileReader.isBind());
        REQUIRE(fileReader.getFileSize() == consts.NFA_1_SIZE);
        fileReader.sever();

        fsmReader.parse(consts.NFA_1_PATH, nfa);
        REQUIRE(nfa.getAlphabet().size() == 10);
        REQUIRE(nfa.getStates().size() == 22);
        REQUIRE(nfa.getFinals().size() == 10);
        REQUIRE(nfa.getStart().size() == 2);
        REQUIRE(nfa.getTransitions().size() == 130);
        REQUIRE(nfa.getAlphabet() == expectedAlphabet);
        REQUIRE(nfa.getStates() == expectedStates);
        REQUIRE(nfa.getFinals() == expectedFinals);
        REQUIRE(nfa.getStart() == expectedStart);
        REQUIRE(nfa.getTransitions() == expectedTransitions);

        fileReader.link(consts.INPUT_2_PATH);
        REQUIRE(fileReader.isBind());
        REQUIRE(fileReader.getFileSize() == consts.INPUT_2_SIZE);
        fileReader.setType(io_manager::ReadType::WHOLE_FILE);
        fileReader.readIntoBuffer();
        auto readInput = Strings::flatten(fileReader.getContentBuffer());
        auto validInputs = Strings::split(readInput, '\n');
        fileReader.sever();
        REQUIRE(!fileReader.isBind());

        std::vector<bool> results;
        std::vector<bool> expectedResults = {true, true, false, true};

        for (const auto &validInput : validInputs) {
            auto result = nfa.simulate(validInput, false);
            results.push_back(result);
        }

        REQUIRE_THAT(results, Catch::Equals(expectedResults));
    }

    SECTION("simulate(TM_1; TM_1_INPUT) -> OK") {
        const auto &EMPTY = automatons::TuringMachine::BLANK_SYMBOL;
        const auto &HALT = automatons::TuringMachine::HALT_STATE;

        Alphabet expectedAlphabet = {'a', 'b', EMPTY};
        States expectedStates = {0, 1, 2, 3, 4, HALT};
        int expectedStart = 0;
        States expectedFinals = {4};
        TMTransitionMap expectedTransitions = {
                {StateEventPair(0, 'a'),   ActionTuple('a', ShiftDirection::RIGHT, 1)},
                {StateEventPair(1, 'a'),   ActionTuple('a', ShiftDirection::RIGHT, 2)},
                {StateEventPair(2, 'a'),   ActionTuple('b', ShiftDirection::LEFT, 3)},
                {StateEventPair(3, 'a'),   ActionTuple('b', ShiftDirection::LEFT, 4)},
                {StateEventPair(4, 'a'),   ActionTuple('b', ShiftDirection::RIGHT, 0)},
                {StateEventPair(0, 'b'),   ActionTuple('b', ShiftDirection::RIGHT, 0)},
                {StateEventPair(1, 'b'),   ActionTuple('b', ShiftDirection::RIGHT, 0)},
                {StateEventPair(2, 'b'),   ActionTuple('b', ShiftDirection::RIGHT, 0)},
                {StateEventPair(3, 'b'),   ActionTuple('b', ShiftDirection::RIGHT, 0)},
                {StateEventPair(4, 'b'),   ActionTuple('b', ShiftDirection::RIGHT, 0)},
                {StateEventPair(0, EMPTY), ActionTuple(EMPTY, ShiftDirection::NO_SHIFT, HALT)},
                {StateEventPair(1, EMPTY), ActionTuple(EMPTY, ShiftDirection::NO_SHIFT, HALT)},
                {StateEventPair(2, EMPTY), ActionTuple(EMPTY, ShiftDirection::NO_SHIFT, HALT)},
                {StateEventPair(3, EMPTY), ActionTuple(EMPTY, ShiftDirection::NO_SHIFT, HALT)},
                {StateEventPair(4, EMPTY), ActionTuple(EMPTY, ShiftDirection::NO_SHIFT, HALT)},
        };
        FSMReader reader;
        TuringMachine tm;

        reader.parse(consts.TM_1_PATH, tm);
        REQUIRE(tm.getAlphabet() == expectedAlphabet);
        REQUIRE(tm.getStates() == expectedStates);
        REQUIRE(tm.getStart() == expectedStart);
        REQUIRE(tm.getFinals() == expectedFinals);
        REQUIRE(tm.getTransitions().size() == 15);
        REQUIRE(tm.getTransitions() == expectedTransitions);

        bool isAccepting = tm.simulate("bbaaabb", false);
        REQUIRE(!isAccepting);
    }

}
