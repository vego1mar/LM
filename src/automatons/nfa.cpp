#include <vector>
#include <algorithm>
#include "nfa.hpp"
#include "printers.hpp"
#include "../helpers/helpers.hpp"

namespace automatons {

    void automatons::NFA::setAlphabet(const Alphabet &outAlphabet) {
        alphabet.clear();
        alphabet = outAlphabet;
    }

    void NFA::setStates(const States &outStates) {
        states.clear();
        states = outStates;
    }

    void NFA::setFinals(const States &outFinals) {
        finals.clear();
        finals = outFinals;
    }

    void NFA::setTransitions(const NFATransitionMap &transitionMap) {
        transitions.clear();
        transitions = transitionMap;
    }

    void NFA::setStart(const States &startState) {
        start = startState;
    }

    const Alphabet &NFA::getAlphabet() const {
        return alphabet;
    }

    const States &NFA::getStates() const {
        return states;
    }

    const States &NFA::getFinals() const {
        return finals;
    }

    const NFATransitionMap &NFA::getTransitions() const {
        return transitions;
    }

    const States &NFA::getStart() const {
        return start;
    }

    bool NFA::simulate(const std::string &input, bool isVerbose) {
        return simulate(input, isVerbose, 0, start);
    }

    std::string NFA::toString() const {
        return helpers::toString(*this);
    }

    States NFA::doTransition(const StateEventPair &currentPair) const {
        bool isTransitionDefined = transitions.find(currentPair) != transitions.end();

        if (!isTransitionDefined) {
            return States();
        }

        return transitions.at(currentPair);
    }

    bool NFA::isAcceptingState(const int &state) const {
        return finals.find(state) != finals.end();
    }

    bool NFA::simulate(const std::string &slicedInput, bool isVerbose, int recursionLevel, const States &starts) const {
        States startingStates = starts;
        States nextStates;
        std::vector<bool> results;
        std::size_t slice;
        bool wasTransitionDefined = true;
        NFAPrinter stdOut;
        stdOut.setVerbosity(isVerbose);

        if (recursionLevel > 0) {
            stdOut.printNewLine();
        }

        for (const auto &startState : startingStates) {
            int nextState = startState;
            slice = 0;

            for (const auto &event : slicedInput) {
                slice++;
                wasTransitionDefined = true;
                StateEventPair pair = std::make_pair(nextState, event);
                nextStates = doTransition(pair);
                stdOut.printTransition(pair, nextStates, recursionLevel);

                if (nextStates.empty()) {
                    results.push_back(false);
                    wasTransitionDefined = false;
                    stdOut.printDerivationResult(false, wasTransitionDefined, recursionLevel);
                    break;
                }

                if (nextStates.size() > 1) {
                    auto newInput = slicedInput.substr(slice, slicedInput.size());
                    bool branchResult = simulate(newInput, isVerbose, recursionLevel + 1, nextStates);
                    results.push_back(branchResult);
                    break;
                }

                auto it = nextStates.begin();
                nextState = *it;
                stdOut.printNewLine();
            }

            if (isAcceptingState(nextState) && wasTransitionDefined) {
                results.push_back(true);
            }
        }

        bool isAnyStateAccepting = std::find(results.begin(), results.end(), true) != results.end();

        if (recursionLevel == 0) {
            stdOut.printDerivationResult(isAnyStateAccepting, wasTransitionDefined, recursionLevel);
        }

        return isAnyStateAccepting;
    }

}
