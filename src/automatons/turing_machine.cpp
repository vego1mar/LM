#include "turing_machine.hpp"
#include "../helpers/helpers.hpp"
#include "printers.hpp"

namespace automatons {

    const char TuringMachine::BLANK_SYMBOL = '-';
    const int TuringMachine::HALT_STATE = -1;


    void TuringMachine::setAlphabet(const Alphabet &outAlphabet) {
        tapeAlphabet = outAlphabet;
        tapeAlphabet.insert(TuringMachine::BLANK_SYMBOL);
    }

    void TuringMachine::setStates(const States &outStates) {
        states = outStates;
        states.insert(HALT_STATE);
    }

    void TuringMachine::setFinals(const States &outFinals) {
        finals = States();

        for (const auto &finalState : outFinals) {
            bool isFinalStateInStates = states.find(finalState) != states.end();

            if (isFinalStateInStates) {
                finals.insert(finalState);
            }
        }
    }

    void TuringMachine::setTransitions(const TMTransitionMap &transitionMap) {
        transitions = TMTransitionMap();

        for (const auto &entry : transitionMap) {
            const auto &eventPair = entry.first;
            const auto &state = std::get<0>(eventPair);
            const auto &event = std::get<1>(eventPair);

            const auto &actionTuple = entry.second;
            const auto &writeSymbol = std::get<0>(actionTuple);
            const auto &shiftHead = std::get<1>(actionTuple);
            const auto &nextState = std::get<2>(actionTuple);

            bool isStateInStates = states.find(state) != states.end();
            bool isEventInTapeAlphabet = tapeAlphabet.find(event) != tapeAlphabet.end();
            bool isWriteSymbolInTapeAlphabet = tapeAlphabet.find(writeSymbol) != tapeAlphabet.end();
            bool isNextStateInStates = states.find(nextState) != states.end();
            bool isEntryValid = isStateInStates && isEventInTapeAlphabet && isWriteSymbolInTapeAlphabet && isNextStateInStates;

            if (isEntryValid) {
                transitions.insert(entry);
            }
        }
    }

    void TuringMachine::setStart(int startState) {
        bool isStateInStates = states.find(startState) != states.end();

        if (isStateInStates) {
            initialState = startState;
            return;
        }

        initialState = TuringMachine::HALT_STATE;
    }

    void TuringMachine::setInputTape(const std::string &input) {
        if (input.empty()) {
            inputTape = std::string(1, BLANK_SYMBOL);
            return;
        }

        inputTape = input;
    }

    const Alphabet &TuringMachine::getAlphabet() const {
        return tapeAlphabet;
    }

    const States &TuringMachine::getStates() const {
        return states;
    }

    const States &TuringMachine::getFinals() const {
        return finals;
    }

    const TMTransitionMap &TuringMachine::getTransitions() const {
        return transitions;
    }

    int TuringMachine::getStart() const {
        return initialState;
    }

    const std::string &TuringMachine::getInputTape() const {
        return inputTape;
    }

    bool TuringMachine::simulate(const std::string &input, bool isVerbose) {
        std::string tape(input);
        std::size_t headPosition = 0;
        int currentState = initialState;
        TMPrinter stdOut;
        stdOut.setVerbosity(isVerbose);

        while (true) {
            bool shouldMachineBeHalted = (currentState == HALT_STATE);
            bool isHeadOutOfInput = (headPosition < 0 || headPosition >= tape.size());

            if (shouldMachineBeHalted || isHeadOutOfInput) {
                break;
            }

            char currentSymbol = getTapeHeadSymbol(tape, headPosition);
            StateEventPair event = {currentState, currentSymbol};
            auto action = getNextTransition(event);
            stdOut.printEventActionShift(event, action);
            writeIntoTape(tape, headPosition, action);
            shiftHeadPosition(headPosition, action);
            currentState = std::get<2>(action);
        }

        inputTape = tape;
        bool isCurrentStateInFinals = finals.find(currentState) != finals.end();
        return isCurrentStateInFinals;
    }

    std::tuple<bool, std::string> TuringMachine::simulateStep(bool isVerbose) {
        throw std::exception();
    }

    std::string TuringMachine::toString() const {
        return helpers::toString(*this);
    }

    TMActionTuple TuringMachine::getNextTransition(const StateEventPair &event) const {
        bool isEventDefined = transitions.find(event) != transitions.end();

        if (isEventDefined) {
            return transitions.at(event);
        }

        return {BLANK_SYMBOL, ShiftDirection::NO_SHIFT, HALT_STATE};
    }

    void TuringMachine::writeIntoTape(std::string &tape, std::size_t position, const TMActionTuple &action) {
        auto symbolToOverride = std::get<0>(action);
        tape[position] = symbolToOverride;
    }

    void TuringMachine::shiftHeadPosition(std::size_t &position, const TMActionTuple &action) {
        auto shiftType = std::get<1>(action);

        switch (shiftType) {
            case ShiftDirection::LEFT:
                position--;
                break;
            case ShiftDirection::RIGHT:
                position++;
                break;
            case ShiftDirection::NO_SHIFT:
            default:
                break;
        }
    }

    char TuringMachine::getTapeHeadSymbol(const std::string &tape, std::size_t &position) const {
        if (position < 0 || position >= tape.size()) {
            return TuringMachine::BLANK_SYMBOL;
        }

        return tape[position];
    }

}
