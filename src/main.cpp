#include "main_program/fsm_simulation_to_stdout.hpp"

int main(int argc, char *argv[]) {
    /*
     * Example of minimal command-line arguments:
     * programExecutable --fsm dfa --def ../../files/dfa_1.txt --input ../../files/input_1.txt
     * programExecutable --fsm nfa --def ../../files/nfa_1.txt --input ../../files/input_2.txt
     *
     * Expected example of usage:
     * programExecutable > simulation_result.txt
     */
    using main_program::FSMSimulationToStdOut;

    FSMSimulationToStdOut program;
    program.joinCLI(argc, argv);
    const auto &shouldBeNonInteractive = program.assembleCLI();

    if (shouldBeNonInteractive) {
        program.runMain();
    }

    program.disposeHeap();
    return 0;
}
