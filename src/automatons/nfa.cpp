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
        NFAPrinter stdOut;
        stdOut.setVerbosity(isVerbose);
        bool simulationResult = simulate(input, stdOut, 0, start);
        stdOut.printDerivationResult(simulationResult, true);
        return simulationResult;
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

    bool NFA::simulate(const std::string &slicedInput, const NFAPrinter &stdOut, int recursionLevel, const States &starts) const {
        States startingStates = starts;
        SimulationVariables args;
        args.wasTransitionDefined = true;

        if (recursionLevel > 0) {
            stdOut.printNewLine();
        }

        for (const auto &startState : startingStates) {
            int nextState = startState;
            args.slice = 0;

            for (const auto &event : slicedInput) {
                args.slicedInput = slicedInput;
                StateEventPair decisionPair = std::make_pair(nextState, event);
                handleTransition(args, stdOut, recursionLevel, decisionPair);
                bool isNextInputValid = true;

                if (args.nextStates.empty()) {
                    handleNoNextStates(args, stdOut);
                    isNextInputValid = false;
                }

                if (args.nextStates.size() > 1) {
                    handleMultipleNextStates(args, stdOut, recursionLevel);
                    isNextInputValid = false;
                }

                if (!isNextInputValid) {
                    break;
                }

                handleSingleNextState(args, stdOut, nextState);
            }

            if (isAcceptingState(nextState) && args.wasTransitionDefined) {
                args.results.push_back(true);
            }
        }

        bool isAnyStateAccepting = std::find(args.results.begin(), args.results.end(), true) != args.results.end();
        return isAnyStateAccepting;
    }

    bool NFA::isAnyStateAccepting(const States &nextStates) const {
        for (const auto &state : nextStates) {
            for (const auto &finalState : finals) {
                if (state == finalState) {
                    return true;
                }
            }
        }

        return false;
    }

    void NFA::handleMultipleNextStates(SimulationVariables &args, const NFAPrinter &stdOut, int level) const {
        auto newInput = args.slicedInput.substr(args.slice, args.slicedInput.size());

        if (newInput.empty()) {
            bool isAnyStateInFinals = isAnyStateAccepting(args.nextStates);
            args.results.push_back(isAnyStateInFinals);
            stdOut.printDerivationResult(isAnyStateInFinals, args.wasTransitionDefined);
            return;
        }

        bool branchResult = simulate(newInput, stdOut, level + 1, args.nextStates);
        args.results.push_back(branchResult);
    }

    void NFA::handleNoNextStates(SimulationVariables &args, const NFAPrinter &stdOut) const {
        args.results.push_back(false);
        args.wasTransitionDefined = false;
        stdOut.printDerivationResult(false, args.wasTransitionDefined);
    }

    void NFA::handleSingleNextState(const SimulationVariables &args, const NFAPrinter &stdOut, int &nextState) const {
        auto it = args.nextStates.begin();
        nextState = *it;

        if (args.slice == args.slicedInput.size()) {
            stdOut.printDerivationResult(isAcceptingState(nextState), true);
            return;
        }

        stdOut.printNewLine();
    }

    void NFA::handleTransition(SimulationVariables &args, const NFAPrinter &stdOut, int level, const StateEventPair &pair) const {
        args.slice++;
        args.wasTransitionDefined = true;
        args.nextStates = doTransition(pair);
        stdOut.printTransition(pair, args.nextStates, level);
    }

}
