#ifndef TURING_MACHINE_HPP
#define TURING_MACHINE_HPP

#include "interfaces.hpp"
#include "definitions.hpp"

namespace automatons {

    class TuringMachine : public ITuringMachine {
    public:
        static const char BLANK_SYMBOL;
        static const int HALT_STATE;

    private:
        States states;
        States finals = {HALT_STATE};
        Alphabet tapeAlphabet = {BLANK_SYMBOL};
        int initialState = 0;
        TMTransitionMap transitions;
        std::string inputTape;

    public:
        TuringMachine() = default;

        TuringMachine(const TuringMachine &rhs) = delete;

        TuringMachine(TuringMachine &&rvalue) noexcept = delete;

        TuringMachine &operator=(const TuringMachine &rhs) = delete;

        TuringMachine &operator=(TuringMachine &&rvalue) noexcept = delete;

        ~TuringMachine() override = default;

        void setAlphabet(const Alphabet &outAlphabet) override;

        void setStates(const States &outStates) override;

        void setFinals(const States &outFinals) override;

        void setTransitions(const TMTransitionMap &transitionMap) override;

        void setStart(int startState) override;

        void setInputTape(const std::string &input) override;

        const Alphabet &getAlphabet() const override;

        const States &getStates() const override;

        const States &getFinals() const override;

        const TMTransitionMap &getTransitions() const override;

        int getStart() const override;

        const std::string &getInputTape() const override;

        bool simulate(const std::string &input, bool isVerbose) override;

        std::tuple<bool, std::string> simulateStep(bool isVerbose);

        std::string toString() const override;

    private:
        TMActionTuple getNextTransition(const StateEventPair &event) const;

        static void writeIntoTape(std::string &tape, std::size_t position, const TMActionTuple &action);

        static void shiftHeadPosition(std::size_t &position, const TMActionTuple &action);

        char getTapeHeadSymbol(const std::string &tape, std::size_t &position) const;

    };

}

#endif //TURING_MACHINE_HPP
