#include <functional>
#include "dfa.hpp"
#include "../helpers/to_string.hpp"
#include "printers.hpp"

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
        DFAPrinter stdOut;
        stdOut.setVerbosity(isVerbose);

        for (const char &event : input) {
            pair = std::make_pair(currentState, event);
            nextState = doTransition(pair);
            currentState = nextState;
            stdOut.printTransition(pair, nextState);
        }

        bool isAccepted = isAcceptingState(currentState);
        stdOut.printDerivationResult(isAccepted);
        return isAccepted;
    }

    std::string DFA::toString() const {
        return helpers::toString(*this);
    }

    int DFA::doTransition(const StateEventPair &currentPair) const {
        return transitions.at(currentPair);
    }

    bool DFA::isAcceptingState(const int &state) const {
        return finals.find(state) != finals.end();
    }

    DFATransitionStep DFA::getNextStep(const char &event) {
        if (!stepper->wasUsed) {
            stepper->wasUsed = true;
            stepper->currentState = getStart();
        }

        auto pair = StateEventPair(stepper->currentState, event);
        const auto nextState = doTransition(pair);

        bool isAccepted = isAcceptingState(nextState);
        const auto &currentPair = StateEventPair(stepper->currentState, event);
        stepper->currentState = nextState;
        return std::make_tuple<>(isAccepted, currentPair, nextState);
    }

}
