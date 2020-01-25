#include "main_program/fsm_simulation_to_stdout.hpp"
#include "main_program/grammar_syntax_analyzer.hpp"
#include "main_program/regular_expression_info.hpp"
#include "main_program/rpn_to_stdout.hpp"


namespace programs {

    using main_program::FSMSimulationToStdOut;
    using main_program::GrammarSyntaxAnalyzer;
    using main_program::RPNToStdOut;
    using main_program::RegularExpressionInfo;


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

    void runProgram3(int argc, char *argv[]) {
        RegularExpressionInfo program;
        program.prepare(argc, argv);
        program.run();
        program.dispose();
    }

    void runProgram4(int argc, char *argv[]) {
        GrammarSyntaxAnalyzer program;
        program.prepare(argc, argv);
        program.run();
        program.dispose();
    }

}


int main(int argc, char *argv[]) {
    //programs::runProgram1(argc, argv);
    //programs::runProgram2(argc, argv);
    //programs::runProgram3(argc, argv);
    programs::runProgram4(argc, argv);
    return 0;
}
