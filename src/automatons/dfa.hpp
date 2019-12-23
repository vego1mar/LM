#ifndef DFA_HPP
#define DFA_HPP

#include "definitions.hpp"
#include "interfaces.hpp"

namespace automatons {

    class DFA : public IDFA {

    private:
        Alphabet alphabet;
        States states;
        States finals;
        DFATransitionMap transitions;
        int start = 0;

    public:
        DFA() = default;

        DFA(const DFA &rhs) = delete;

        DFA(DFA &&rvalue) noexcept = delete;

        DFA &operator=(const DFA &rhs) = delete;

        DFA &operator=(DFA &&rvalue) noexcept = delete;

        ~DFA() override = default;

        void setAlphabet(const Alphabet &outAlphabet) override;

        void setStates(const States &outStates) override;

        void setFinals(const States &outFinals) override;

        void setTransitions(const DFATransitionMap &transitionMap) override;

        void setStart(int start) override;

        const Alphabet &getAlphabet() const override;

        const States &getStates() const override;

        const States &getFinals() const override;

        const DFATransitionMap &getTransitions() const override;

        int getStart() const override;

        bool simulate(const std::string &input, bool isVerbose) override;

        std::string toString() const override;

    private:
        int doTransition(const StateEventPair &currentPair) const;

        bool isAcceptingState(const int &state) const;

        void printStartState(const int &startState, bool isVerbose) const;

        void printSimulationStep(const StateEventPair &currentPair, const int &nextState, bool isVerbose) const;

        void printSimulationResult(bool isAcceptingState, bool isVerbose) const;

    };

}

#endif //DFA_HPP
