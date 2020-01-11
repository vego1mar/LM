#define CATCH_CONFIG_MAIN

#include "../catch.hpp"
#include "../../src/automatons/dfa.hpp"
#include "../../src/automatons/definitions.hpp"
#include "../../src/io_manager/fsm_reader.hpp"
#include "../../src/tests/definitions.hpp"

using automatons::DFA;
using automatons::Alphabet;
using automatons::States;
using automatons::DFATransitionMap;
using automatons::DFATransitionStep;
using io_manager::FSMReader;
using tests::Constants;


TEST_CASE("dfa.hpp", "[dfa]") {
    const Constants CONST;

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
        std::string expectedToString = "{[a,b,c],[0,1,2],[2],<9>,0}";
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

    SECTION("DFA stepper -> OK") {
        DFA dfa;
        FSMReader reader;
        reader.parse(CONST.DFA_2_PATH, dfa);
        std::vector<DFATransitionStep> results;
        const std::vector<DFATransitionStep> expectedResults = {
                std::make_tuple<>(false, std::make_pair<>(0, '5'), 105),
                std::make_tuple<>(false, std::make_pair<>(105, '5'), 110),
                std::make_tuple<>(false, std::make_pair<>(110, 'b'), 210),
                std::make_tuple<>(true, std::make_pair<>(210, '5'), 215),
                std::make_tuple<>(true, std::make_pair<>(215, '5'), 220),
                std::make_tuple<>(false, std::make_pair<>(220, 'z'), 200),
                std::make_tuple<>(false, std::make_pair<>(200, '1'), 201),
                std::make_tuple<>(false, std::make_pair<>(201, '1'), 202),
                std::make_tuple<>(false, std::make_pair<>(202, '1'), 203),
                std::make_tuple<>(false, std::make_pair<>(203, '1'), 204),
                std::make_tuple<>(false, std::make_pair<>(204, '1'), 205),
                std::make_tuple<>(false, std::make_pair<>(205, '1'), 206),
                std::make_tuple<>(false, std::make_pair<>(206, '1'), 207),
                std::make_tuple<>(false, std::make_pair<>(207, '1'), 208),
                std::make_tuple<>(false, std::make_pair<>(208, 'a'), 108),
                std::make_tuple<>(false, std::make_pair<>(108, '2'), 110),
                std::make_tuple<>(false, std::make_pair<>(110, '1'), 111),
                std::make_tuple<>(true, std::make_pair<>(111, 'r'), 109),
        };
        const std::string &input = "55b55z11111111a21r";

        for (const auto &event : input) {
            const auto &step = dfa.getNextStep(event);
            results.emplace_back(step);
        }

        REQUIRE(results.size() == expectedResults.size());
        REQUIRE_THAT(results, Catch::UnorderedEquals(expectedResults));
    }

}
