#include "main_program/fsm_simulation_to_stdout.hpp"
#include "main_program/rpn_to_stdout.hpp"


namespace programs {

    void runProgram1(int argc, char *argv[]);

    void runProgram2(int argc, char *argv[]);

}


int main(int argc, char *argv[]) {
    //programs::runProgram1(argc, argv);
    programs::runProgram2(argc, argv);
    return 0;
}


namespace programs {

    using main_program::FSMSimulationToStdOut;
    using main_program::RPNToStdOut;


    void runProgram1(int argc, char *argv[]) {
        FSMSimulationToStdOut program;
        program.joinCLI(argc, argv);
        const auto &shouldBeNonInteractive = program.assembleCLI();

        if (shouldBeNonInteractive) {
            program.runMain();
        }

        program.disposeHeap();
    }

    void runProgram2(int argc, char *argv[]) {
        RPNToStdOut program;
        program.prepare(argc, argv);
        program.run();
        program.dispose();
    }

}