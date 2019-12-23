#include <iostream>
#include "dfa.hpp"
#include "../helpers/helpers.hpp"

namespace automatons {

    void DFA::setAlphabet(const Alphabet &outAlphabet) {
        alphabet.clear();
        alphabet = outAlphabet;
    }

    void DFA::setStates(const States &outStates) {
        states.clear();
        states = outStates;
    }

    void DFA::setFinals(const States &outFinals) {
        finals.clear();

        for (const auto &state : outFinals) {
            bool isInStates = outFinals.find(state) != outFinals.end();

            if (isInStates) {
                finals.insert(state);
            }
        }
    }

    void DFA::setTransitions(const DFATransitionMap &transitionMap) {
        transitions.clear();

        for (const auto &entry : transitionMap) {
            auto &state = std::get<0>(entry.first);
            auto &event = std::get<1>(entry.first);
            auto &nextState = entry.second;
            bool isStateInSet = states.find(state) != states.end();
            bool isInAlphabet = alphabet.find(event) != alphabet.end();
            bool isNextStateInSet = states.find(nextState) != states.end();

            if (isStateInSet && isInAlphabet && isNextStateInSet) {
                transitions.insert(entry);
            }
        }
    }

    void DFA::setStart(int startState) {
        start = startState;
    }

    const Alphabet &DFA::getAlphabet() const {
        return alphabet;
    }

    const States &DFA::getStates() const {
        return states;
    }

    const States &DFA::getFinals() const {
        return finals;
    }

    const DFATransitionMap &DFA::getTransitions() const {
        return transitions;
    }

    int DFA::getStart() const {
        return start;
    }

    bool DFA::simulate(const std::string &input, bool isVerbose) {
        int currentState = start;
        int nextState;
        StateEventPair pair;
        printStartState(currentState, isVerbose);

        for (const char &event : input) {
            pair = std::make_pair(currentState, event);
            nextState = doTransition(pair);
            currentState = nextState;
            printSimulationStep(pair, nextState, isVerbose);
        }

        bool isAccepted = isAcceptingState(currentState);
        printSimulationResult(isAccepted, isVerbose);
        return isAccepted;
    }

    std::string DFA::toString() const {
        return "{[" + helpers::toString(alphabet) + ',' + helpers::toString(states) + ',' +
               helpers::toString(finals) + ",<" + std::to_string(transitions.size()) + ">," +
               std::to_string(start) + '}';
    }

    int DFA::doTransition(const StateEventPair &currentPair) const {
        return transitions.at(currentPair);
    }

    bool DFA::isAcceptingState(const int &state) const {
        return finals.find(state) != finals.end();
    }

    void DFA::printStartState(const int &startState, bool isVerbose) const {
        if (!isVerbose) {
            return;
        }

        std::cout << std::to_string(startState) << std::endl;
    }

    void DFA::printSimulationStep(const StateEventPair &currentPair, const int &nextState, bool isVerbose) const {
        if (!isVerbose) {
            return;
        }

        const auto &state = std::get<0>(currentPair);
        const auto &event = std::get<1>(currentPair);
        std::string output = '[' + std::to_string(state) + ',' + event + "] -> " + std::to_string(nextState);
        std::cout << output << std::endl;
    }

    void DFA::printSimulationResult(bool isAcceptingState, bool isVerbose) const {
        if (!isVerbose) {
            return;
        }

        std::string output = (isAcceptingState) ? "ACCEPTED" : "REJECTED";
        std::cout << output << std::endl;
    }

}
