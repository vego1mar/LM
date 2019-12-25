#include <iostream>
#include "printers.hpp"
#include "../helpers/helpers.hpp"

namespace automatons {

    void IAutomataPrinter::setVerbosity(bool verbose) {
        verbosity = verbose;
    }

    bool IAutomataPrinter::getVerbosity() const {
        return verbosity;
    }

    void NFAPrinter::printTransition(const StateEventPair &previous, const States &next, int level) const {
        if (!getVerbosity()) {
            return;
        }

        std::string strToPrint = '[' + std::to_string(level) + ']' +
                                 " (" + std::to_string(previous.first) + ',' + previous.second + ')' +
                                 " -> " + helpers::toString(next);
        std::cout << strToPrint;
    }

    void NFAPrinter::printDerivationResult(bool isAcceptingState, bool wasTransitionDefined) const {
        if (!getVerbosity()) {
            return;
        }

        if (!wasTransitionDefined) {
            std::cout << " => STOP" << std::endl;
            return;
        }

        std::string boolStr = (isAcceptingState) ? "ACCEPTED" : "REJECTED";
        std::cout << " => " << boolStr << std::endl;
    }

    void NFAPrinter::printNewLine() const {
        if (!getVerbosity()) {
            return;
        }

        std::cout << std::endl;
    }

    void DFAPrinter::printTransition(const StateEventPair &currentPair, const int &nextState) const {
        if (!getVerbosity()) {
            return;
        }

        const auto &state = std::get<0>(currentPair);
        const auto &event = std::get<1>(currentPair);
        std::string output = '[' + std::to_string(state) + ',' + event + "] -> " + std::to_string(nextState);
        std::cout << output << std::endl;
    }

    void DFAPrinter::printDerivationResult(bool isAcceptingState) const {
        if (!getVerbosity()) {
            return;
        }

        std::string output = (isAcceptingState) ? "ACCEPTED" : "REJECTED";
        std::cout << output << std::endl;
    }

}
