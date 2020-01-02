#include <algorithm>
#include <memory>
#include "fsm_simulation_to_stdout.hpp"
#include "../io_manager/fsm_reader.hpp"
#include "../helpers/strings.hpp"

namespace main_program {

    using io_manager::FSMReader;
    using io_manager::ReadType;
    using helpers::Strings;


    void FSMSimulationToStdOut::joinCLI(int argc, char **argv) {
        parser = std::make_unique<CLAParser>(argc, argv);
    }

    void FSMSimulationToStdOut::assembleCLI() {
        assemblies = std::make_unique<AssemblyData>();
        inputReader = std::make_unique<FileReader>();
        assembleFSMType();
        assembleFromDefinitionFile();
        assembleFromInputFile();
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
            throw std::bad_function_call();
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
            throw std::bad_function_call();
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

}
