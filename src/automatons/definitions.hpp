#ifndef AUTOMATONS_DEFINITIONS_HPP
#define AUTOMATONS_DEFINITIONS_HPP

#include <set>
#include <map>
#include <vector>

namespace automatons {

    typedef std::set<char> Alphabet;
    typedef std::set<int> States;
    typedef std::pair<int, char> StateEventPair;
    typedef std::map<StateEventPair, int> DFATransitionMap;
    typedef std::map<StateEventPair, States> NFATransitionMap;

    struct SimulationVariables {
        States nextStates;
        std::vector<bool> results;
        std::size_t slice;
        bool wasTransitionDefined;
        std::string slicedInput;
    };

    enum class ShiftDirection {
        LEFT,
        RIGHT,
        NO_SHIFT
    };

    typedef std::tuple<char, ShiftDirection, int> ActionTuple;
    typedef std::map<StateEventPair, ActionTuple> TMTransitionMap;
    typedef std::tuple<StateEventPair, ActionTuple> EventActionTuple;

    struct TMStepper {
        std::size_t headPosition = 0;
        std::string workingTape;
        EventActionTuple previous;
        EventActionTuple next;
        bool hasNextStep = true;
        bool wasNotUsed = true;
        EventActionTuple first;
    };

    enum class StepperContinuation {
        PREVIOUS,
        NEXT
    };

    typedef std::tuple<bool, StateEventPair, int> DFATransitionStep;

    struct DFAStepper {
        int currentState = 0;
        bool wasUsed = false;
    };

}

#endif //AUTOMATONS_DEFINITIONS_HPP
