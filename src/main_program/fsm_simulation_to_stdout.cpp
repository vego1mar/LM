#include <algorithm>
#include <memory>
#include <functional>
#include <iostream>
#include "fsm_simulation_to_stdout.hpp"
#include "../io_manager/fsm_reader.hpp"
#include "../helpers/strings.hpp"
#include "../helpers/to_string.hpp"

namespace main_program {

    using io_manager::FSMReader;
    using io_manager::ReadType;
    using helpers::Strings;


    void FSMSimulationToStdOut::joinCLI(int argc, char **argv) {
        parser = std::make_unique<CLAParser>(argc, argv);
    }

    bool FSMSimulationToStdOut::assembleCLI() {
        assemblies = std::make_unique<AssemblyData>();
        inputReader = std::make_unique<FileReader>();

        if (!parser->hasArguments()) {
            printHelp();
            return false;
        }

        if (hasDFAInteractiveModeBeenAcquired()) {
            simulateDFAInteractive();
            return false;
        }

        assembleFSMType();
        assembleFromDefinitionFile();
        assembleFromInputFile();
        return true;
    }

    void FSMSimulationToStdOut::runMain() {
        const auto &fsmType = assemblies->fsmType;
        auto it = assemblies->types.begin();
        const auto &dfaType = *it;
        it++;

        if (fsmType == dfaType) {
            simulateDFA();
            return;
        }

        const auto &nfaType = *it;
        it++;

        if (fsmType == nfaType) {
            simulateNFA();
            return;
        }

        const auto &tmType = *it;

        if (fsmType == tmType) {
            simulateTM();
        }
    }

    void FSMSimulationToStdOut::disposeHeap() {
        if (assemblies != nullptr) {
            assemblies.reset();
        }

        if (parser != nullptr) {
            parser.reset();
        }

        if (inputReader != nullptr && inputReader->isBind()) {
            inputReader->sever();
            inputReader.reset();
        }
    }

    void FSMSimulationToStdOut::printHelp() {
        std::cout << "SYNOPSIS:" << std::endl <<
                  "\tLM --fsm <FSM_OPTIONS> --def [DEF_FILE] --input [INPUT_FILE]" << std::endl <<
                  "LM --dfa-interactive --def [DEF_FILE]" << std::endl <<
                  std::endl <<
                  "OPTIONS:" << std::endl <<
                  "<FSM_OPTIONS> = [dfa | nfa | tm]" << std::endl <<
                  "[DEF_FILE] - file path to definition file" << std::endl <<
                  "[INPUT_FILE] - file path to input file" << std::endl <<
                  std::endl <<
                  "EXAMPLES:" << std::endl <<
                  "LM --fsm dfa --def ../../files/dfa1.txt --input ../../files/input1.txt" << std::endl <<
                  "LM --dfa-interactive --def dfa2.txt" << std::endl <<
                  "LM --fsm nfa --def nfa.txt --input input2.txt > output.txt" << std::endl <<
                  "LM --fsm tm --def tm.txt --input input4.txt | less" << std::endl;
    }

    void FSMSimulationToStdOut::assembleFSMType() {
        auto it = assemblies->options.begin();
        const auto &fsmOption = *it;

        if (!parser->isOptionExists(fsmOption)) {
            throw std::invalid_argument("!parser->isOptionExists(fsmOption) => " + fsmOption);
        }

        assemblies->fsmType = parser->getOption(fsmOption);
        const auto &types = assemblies->types;
        const auto &fsmType = assemblies->fsmType;
        bool isTypeAcceptable = std::find(types.begin(), types.end(), Strings::toLower(fsmType)) != types.end();

        if (!isTypeAcceptable) {
            throw std::invalid_argument("!isTypeAcceptable => " + fsmType);
        }
    }

    void FSMSimulationToStdOut::assembleFromDefinitionFile() {
        auto it = assemblies->options.begin();
        std::advance(it, 1);
        const std::string &defOption = *it;

        if (!parser->isOptionExists(defOption)) {
            throw std::invalid_argument("!parser->isOptionExists(defOption) => " + defOption);
        }

        auto filePath = parser->getOption(defOption);
        FSMReader reader;

        const auto &fsmType = assemblies->fsmType;
        it = assemblies->types.begin();
        const auto &dfaType = *it;
        it = std::next(assemblies->types.begin(), 1);
        const auto &nfaType = *it;
        it++;
        const auto &tmType = *it;

        if (fsmType == dfaType) {
            reader.parse(filePath, assemblies->dfa);
            return;
        }

        if (fsmType == nfaType) {
            reader.parse(filePath, assemblies->nfa);
            return;
        }

        if (fsmType == tmType) {
            reader.parse(filePath, assemblies->tm);
        }
    }

    void FSMSimulationToStdOut::assembleFromInputFile() {
        auto it = assemblies->options.begin();
        std::advance(it, 2);
        const std::string &inputOption = *it;

        if (!parser->isOptionExists(inputOption)) {
            throw std::invalid_argument("!parser->isOptionExists(inputOption) => " + inputOption);
        }

        auto filePath = parser->getOption(inputOption);
        inputReader->setType(ReadType::LINE_BY_LINE);
        inputReader->link(filePath);

        if (!inputReader->isBind()) {
            throw std::invalid_argument("!inputReader->isBind() => " + inputReader->getFileName());
        }
    }

    void FSMSimulationToStdOut::simulateDFA() {
        auto &dfa = assemblies->dfa;

        while (inputReader->hasNextLine()) {
            auto input = inputReader->getNextLine();
            auto validInput = Strings::remove(input, '\n');
            dfa.simulate(validInput, true);
        }
    }

    void FSMSimulationToStdOut::simulateNFA() {
        auto &nfa = assemblies->nfa;

        while (inputReader->hasNextLine()) {
            auto input = inputReader->getNextLine();
            auto validInput = Strings::remove(input, '\n');
            nfa.simulate(validInput, true);
        }
    }

    void FSMSimulationToStdOut::simulateTM() {
        auto &tm = assemblies->tm;

        while (inputReader->hasNextLine()) {
            auto input = inputReader->getNextLine();
            auto validInput = Strings::remove(input, '\n');
            tm.setInputTape(validInput);
            bool hasFirstBeenTouched = false;
            std::vector<EventActionTuple> transitions;
            bool isAccepting = false;

            while (tm.hasNextStep()) {
                const auto &step = tm.nextStep();
                const auto &tape = std::get<1>(step);
                const auto stepper = tm.getStepperData();
                isAccepting = std::get<0>(step);

                if (!hasFirstBeenTouched) {
                    hasFirstBeenTouched = true;
                    transitions.push_back(stepper.first);
                    const auto tapeStr = helpers::toString(stepper.headPosition - 1, tape);
                    const auto transitionStr = helpers::toString(stepper.first);
                    std::cout << transitionStr << std::endl << tapeStr << std::endl << std::endl;
                }

                transitions.push_back(stepper.previous);
                const auto tapeStr = helpers::toString(stepper.headPosition, tape);
                const auto transitionStr = helpers::toString(stepper.previous);
                std::cout << transitionStr << std::endl << tapeStr << std::endl;
                std::cout << std::endl;
            }

            __printInfoForExercise3(transitions);
            std::cout << ((isAccepting) ? "ACCEPTED" : "REJECTED") << std::endl;
        }
    }

    bool FSMSimulationToStdOut::hasDFAInteractiveModeBeenAcquired() {
        auto it = assemblies->singleOptions.begin();
        const auto &singleOption = *it;
        return parser->isOptionExists(singleOption);
    }

    void FSMSimulationToStdOut::simulateDFAInteractive() {
        auto it = assemblies->options.begin();
        std::advance(it, 1);
        const std::string &defOption = *it;

        if (!parser->isOptionExists(defOption)) {
            throw std::invalid_argument("!parser->isOptionExists(defOption) => " + defOption);
        }

        auto filePath = parser->getOption(defOption);
        FSMReader reader;
        reader.parse(filePath, assemblies->dfa);
        const auto &alphabet = assemblies->dfa.getAlphabet();
        char event = '\0';
        std::vector<StateEventPair> steps;
        DFATransitionStep step;

        std::cout << "<interactive> = " << helpers::toString(assemblies->dfa.getAlphabet()) << std::endl;
        std::cout << "<exit> = [q]" << std::endl;
        std::cout << std::endl;

        while (event != 'q') {
            std::cin >> event;
            bool isInAlphabet = alphabet.find(event) != alphabet.end();

            if (!isInAlphabet) {
                std::cout << "Input ignored." << std::endl;
                std::cout << std::endl;
                continue;
            }

            step = assemblies->dfa.getNextStep(event);
            std::cout << helpers::toString(step) << std::endl;
            steps.push_back(std::get<1>(step));
            __interpretEventForExercise1(step);
            __interpretNextStateForExercise1(step);
            std::cout << std::endl;
        }

        __printTraversedPathForExercise1(steps);
        __printResultForExercise1(step);
    }

    void FSMSimulationToStdOut::__interpretNextStateForExercise1(const DFATransitionStep &step) {
        const auto &nextState = std::get<2>(step);
        std::string coinsStr = "0";

        if (nextState > 100 && nextState != 200) {
            const auto &nextStateStr = std::to_string(nextState);
            coinsStr = nextStateStr.substr(1);

            if (coinsStr[0] == '0') {
                coinsStr = coinsStr.substr(1);
            }
        }

        std::cout << "Worth: " << coinsStr << " zl." << std::endl;
    }

    void FSMSimulationToStdOut::__interpretEventForExercise1(const DFATransitionStep &step) {
        const auto &event = std::get<1>(std::get<1>(step));

        switch (event) {
            case '1':
                std::cout << "Thrown 1 zl." << std::endl;
                break;
            case '2':
                std::cout << "Thrown 2 zl." << std::endl;
                break;
            case '5':
                std::cout << "Thrown 5 zl." << std::endl;
                break;
            case 'a':
                std::cout << "Selected route: pool/pool+sauna (regular)." << std::endl;
                break;
            case 'b':
                std::cout << "Selected route: pool/pool+sauna (discounted, valid for 2h)." << std::endl;
                break;
            case 'r':
                std::cout << "Ticket acquired. Residue returned." << std::endl;
                break;
            case 'z':
                std::cout << "Requested refund." << std::endl;
                break;
            default:
                break;
        }
    }

    void FSMSimulationToStdOut::__printTraversedPathForExercise1(const std::vector<StateEventPair> &steps) {
        for (const auto &stepPair : steps) {
            const auto &state = std::get<0>(stepPair);
            const auto &event = std::get<1>(stepPair);
            const std::string &traversedPath = '(' + std::to_string(state) + ',' + event + ") -> ";
            std::cout << traversedPath;
        }
    }

    void FSMSimulationToStdOut::__printResultForExercise1(const DFATransitionStep &lastStep) {
        const auto &lastState = std::get<2>(lastStep);
        std::cout << std::to_string(lastState) << std::endl;
    }

    void FSMSimulationToStdOut::__printInfoForExercise3(const std::vector<EventActionTuple> &transitions) {
        const auto &firstState = std::get<0>(std::get<0>(transitions[0]));
        std::cout << '[' << std::to_string(firstState) << ',';

        for (const auto &eventAction : transitions) {
            const auto &currentState = std::get<2>(std::get<1>(eventAction));
            std::cout << std::to_string(currentState) + ',';
        }

        std::cout << ']' << std::endl;
    }

}
