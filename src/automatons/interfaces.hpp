#ifndef INTERFACES_HPP
#define INTERFACES_HPP

#include <string>
#include "definitions.hpp"

namespace automatons {

    class IAutomata {
    public:
        virtual void setAlphabet(const Alphabet &outAlphabet) = 0;

        virtual void setStates(const States &outStates) = 0;

        virtual void setFinals(const States &outFinals) = 0;

        virtual const Alphabet &getAlphabet() const = 0;

        virtual const States &getStates() const = 0;

        virtual const States &getFinals() const = 0;

        virtual bool simulate(const std::string &input, bool isVerbose) = 0;

        virtual std::string toString() const = 0;

        virtual ~IAutomata() = default;
    };

    class IDFA : public IAutomata {
    public:
        virtual void setStart(int start) = 0;

        virtual int getStart() const = 0;

        virtual void setTransitions(const DFATransitionMap &transitionMap) = 0;

        virtual const DFATransitionMap &getTransitions() const = 0;

        ~IDFA() override = default;
    };

    class INFA : public IAutomata {
    public:
        virtual void setStart(const States &start) = 0;

        virtual const States &getStart() const = 0;

        virtual void setTransitions(const NFATransitionMap &transitionMap) = 0;

        virtual const NFATransitionMap &getTransitions() const = 0;

        ~INFA() override = default;
    };

    class ITuringMachine : public IAutomata {
    public:
        virtual void setStart(int startState) = 0;

        virtual int getStart() const = 0;

        virtual void setTransitions(const TMTransitionMap &transitionMap) = 0;

        virtual const TMTransitionMap &getTransitions() const = 0;

        virtual void setInputTape(const std::string &input) = 0;

        virtual const std::string &getInputTape() const = 0;

        ~ITuringMachine() override = default;
    };

}

#endif //INTERFACES_HPP
