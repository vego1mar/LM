#ifndef FSM_SIMULATION_TO_STDOUT_HPP
#define FSM_SIMULATION_TO_STDOUT_HPP

#include <string>
#include <memory>
#include <list>
#include "../command_line/cla_parser.hpp"
#include "../automatons/dfa.hpp"
#include "../io_manager/file_reader.hpp"
#include "../automatons/nfa.hpp"

using command_line::CLAParser;
using automatons::DFA;
using io_manager::FileReader;
using automatons::NFA;
using automatons::DFATransitionStep;
using automatons::StateEventPair;


namespace main_program {

    struct AssemblyData {
        const std::list<std::string> types = {"dfa", "nfa", "tm"};
        const std::list<std::string> options = {"--fsm", "--def", "--input"};
        const std::list<std::string> singleOptions = {"--dfa-interactive"};
        std::string fsmType;
        DFA dfa;
        NFA nfa;
    };


    class FSMSimulationToStdOut {
    private:
        std::unique_ptr<AssemblyData> assemblies;
        std::unique_ptr<FileReader> inputReader;
        std::unique_ptr<CLAParser> parser;

    public:
        FSMSimulationToStdOut() = default;

        FSMSimulationToStdOut(const FSMSimulationToStdOut &rhs) = delete;

        FSMSimulationToStdOut(FSMSimulationToStdOut &&rvalue) noexcept = delete;

        FSMSimulationToStdOut &operator=(const FSMSimulationToStdOut &rhs) = delete;

        FSMSimulationToStdOut &operator=(FSMSimulationToStdOut &&rvalue) noexcept = delete;

        virtual ~FSMSimulationToStdOut() = default;

        void joinCLI(int argc, char **argv);

        bool assembleCLI();

        void runMain();

        void disposeHeap();

        static void printHelp();

    private:

        void assembleFSMType();

        void assembleFromDefinitionFile();

        void assembleFromInputFile();

        void simulateDFA();

        void simulateNFA();

        bool hasDFAInteractiveModeBeenAcquired();

        void simulateDFAInteractive();

        static void __interpretNextStateForExercise1(const DFATransitionStep &step);

        static void __interpretEventForExercise1(const DFATransitionStep &step);

        static void __printTraversedPathForExercise1(const std::vector<StateEventPair> &steps);

        static void __printResultForExercise1(const DFATransitionStep &lastStep);

    };


}

#endif //FSM_SIMULATION_TO_STDOUT_HPP
