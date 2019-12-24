#ifndef NFA_HPP
#define NFA_HPP

#include "definitions.hpp"
#include "interfaces.hpp"

namespace automatons {

    /// Non-deterministic Finite Automata with empty moves
    class NFA : public INFA {
    public:
        static const char EMPTY_SYMBOL = '!';

    private:
        Alphabet alphabet;
        States states;
        States finals;
        NFATransitionMap transitions;
        States start = {0};

    public:
        NFA() = default;

        NFA(const NFA &rhs) = default;

        NFA(NFA &&rvalue) noexcept = delete;

        NFA &operator=(const NFA &rhs) = delete;

        NFA &operator=(NFA &&rvalue) noexcept = delete;

        ~NFA() override = default;

        void setAlphabet(const Alphabet &outAlphabet) override;

        void setStates(const States &outStates) override;

        void setFinals(const States &outFinals) override;

        void setTransitions(const NFATransitionMap &transitionMap) override;

        void setStart(const States &startState) override;

        const Alphabet &getAlphabet() const override;

        const States &getStates() const override;

        const States &getFinals() const override;

        const NFATransitionMap &getTransitions() const override;

        const States &getStart() const override;

        bool simulate(const std::string &input, bool isVerbose) override;

        std::string toString() const override;

    private:
        States doTransition(const StateEventPair &currentPair) const;

        bool isAcceptingState(const int &state) const;

        bool simulate(const std::string &slicedInput, bool isVerbose, int recursionLevel, const States &starts) const;

    };

}

#endif //NFA_HPP
