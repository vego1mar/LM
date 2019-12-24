#include <iostream>
#include "printers.hpp"
#include "../helpers/helpers.hpp"

namespace automatons {

    void IAutomataPrinter::setVerbosity(bool verbose) {
        verbosity = verbose;
    }

    void NFAPrinter::printTransition(const StateEventPair &previous, const States &next, int level) const {
        if (!verbosity) {
            return;
        }

        std::string strToPrint = '[' + std::to_string(level) + ']' +
                                 " (" + std::to_string(previous.first) + ',' + previous.second + ')' +
                                 " -> " + helpers::toString(next);
        std::cout << strToPrint;
    }

    void NFAPrinter::printDerivationResult(bool isAcceptingState, bool wasTransitionDefined, int level) const {
        if (!verbosity) {
            return;
        }

        if (!wasTransitionDefined) {
            std::cout << " => STOP" << std::endl;
            return;
        }

        std::string boolStr = (isAcceptingState) ? "ACCEPTED" : "REJECTED";

        if (level == 0) {
            std::cout << boolStr << std::endl;
            return;
        }

        std::cout << " => " << boolStr << std::endl;
    }

    void NFAPrinter::printNewLine() const {
        if (!verbosity) {
            return;
        }

        std::cout << std::endl;
    }

}
