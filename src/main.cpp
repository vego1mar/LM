#include "main_program/fsm_simulation_to_stdout.hpp"

int main(int argc, char *argv[]) {
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
