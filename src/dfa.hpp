#ifndef DFA_HPP
#define DFA_HPP

#include <set>
#include <map>

namespace dfa {

    typedef std::set<char> Alphabet;
    typedef std::set<int> States;
    typedef std::pair<int, char> StateEventPair;
    typedef std::map<StateEventPair, int> TransitionMap;

    class DFA {

    private:
        Alphabet alphabet;
        States states;
        States finals;
        TransitionMap transitions;
        int start;

    public:
        DFA();

        DFA(const DFA &rhs) = delete;

        DFA(DFA &&rvalue) = delete;

        DFA &operator=(const DFA &rhs) = delete;

        DFA &operator=(DFA &&rvalue) noexcept = delete;

        virtual ~DFA() = default;

        void setAlphabet(const Alphabet &outAlphabet);

        void setStates(const States &outStates);

        void setFinals(const States &outFinals);

        void setTransitions(const TransitionMap &transitionMap);

        void setStart(int start);

        const Alphabet &getAlphabet() const;

        const States &getStates() const;

        const States &getFinals() const;

        const TransitionMap &getTransitions() const;

        int getStart() const;

        bool simulate(const std::string &input, bool isVerbose = true);

        std::string toString() const;

    private:
        int doTransition(StateEventPair &currentPair) const;

        bool isAcceptingState(int &state) const;

        void printStartState(int &startState, bool isVerbose) const;

        void printSimulationStep(StateEventPair &currentPair, int &nextState, bool isVerbose) const;

        void printSimulationResult(bool isAcceptingState, bool isVerbose) const;

    };

}

#endif //DFA_HPP
