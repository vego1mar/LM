#include "grammar_syntax_analyzer.hpp"
#include "../helpers/strings.hpp"
#include <iostream>
#include <algorithm>

using helpers::Strings;


namespace main_program {

    const char GrammarSyntaxAnalyzer::EMPTY_SYMBOL = '\0';


    void GrammarSyntaxAnalyzer::prepare(int argc, char **argv) {
        parser = std::make_unique<CLAParser>(argc, argv);
        reader = std::make_unique<FileReader>();
    }

    void GrammarSyntaxAnalyzer::dispose() {
        if (parser != nullptr) {
            parser.reset();
        }

        if (reader != nullptr) {
            reader.reset();
        }

        if (reader != nullptr) {
            inputStr.reset();
        }

        if (currentPosition != nullptr) {
            currentPosition.reset();
        }

        if (catchedStr != nullptr) {
            catchedStr.reset();
        }
    }

    void GrammarSyntaxAnalyzer::run() {
        const auto inputOption = *options.begin();

        if (!parser->isOptionExists(inputOption)) {
            std::cout << "USAGE:" << std::endl << "LM --input input.txt" << std::endl;
            return;
        }

        const auto filePath = parser->getOption(inputOption);
        reader->setType(io_manager::ReadType::LINE_BY_LINE);
        reader->link(filePath);

        if (!reader->isBind()) {
            std::cerr << "File path is incorrect." << std::endl;
            return;
        }

        while (reader->hasNextLine()) {
            auto line = reader->getNextLine();
            line = Strings::remove(line, '\n');
            inputStr = std::make_unique<std::string>(line);
            catchedStr = std::make_unique<std::string>();
            currentPosition = std::make_unique<std::size_t>(0);
            analyze();
            const std::string isLineCompliant = (*catchedStr == *inputStr) ? "COMPLIANT" : "INCOMPLIANT";
            std::cout << "derived: '" << *catchedStr << '\'' << std::endl;
            std::cout << isLineCompliant << std::endl;
            std::cout << std::endl;
        }

        reader->sever();
    }

    void GrammarSyntaxAnalyzer::analyze(int level, char production) {
        const auto symbol = getCurrentSymbol();
        const auto expansions = getEnlisted(production);
        const auto selection = getSelectedAlternative(expansions, symbol);
        const auto symbolStr = (symbol == EMPTY_SYMBOL ? ' ' : symbol);
        std::string derivation = '[' + std::to_string(level) + "]{" + symbolStr + "}  " + production + " -> '" + selection + '\'';
        std::cout << derivation << std::endl;

        for (const auto &productionSymbol : selection) {
            bool isSymbolTerminal = !std::isupper(productionSymbol);

            if (!isSymbolTerminal) {
                analyze(level + 1, productionSymbol);
                continue;
            }

            *catchedStr += productionSymbol;
            (*currentPosition)++;
        }
    }

    char GrammarSyntaxAnalyzer::getCurrentSymbol() const {
        const auto &pos = *currentPosition;

        if (pos == std::string::npos || pos >= inputStr->size()) {
            return EMPTY_SYMBOL;
        }

        return (*inputStr)[pos];
    }

    Production GrammarSyntaxAnalyzer::getEnlisted(char production) {
        auto prod = Production({&EMPTY_SYMBOL});

        switch (production) {
            case 'S':
                return {"W;Z"};
            case 'Z':
                return {"W;Z", &EMPTY_SYMBOL};
            case 'W':
                return {"PV"};
            case 'V':
                return {"OW", &EMPTY_SYMBOL};
            case 'P':
                return {"R", "(W)"};
            case 'R':
                return {"LT"};
            case 'T':
                return {".L", &EMPTY_SYMBOL};
            case 'L':
                return {"CM"};
            case 'M':
                return {"L", &EMPTY_SYMBOL};
            case 'C':
                return {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
            case 'O':
                return {"*", ":", "+", "-", "^"};
            default:
                break;
        }

        return prod;
    }

    Firsts GrammarSyntaxAnalyzer::getFirstSymbols(char production) {
        Firsts firsts;

        switch (production) {
            case 'Z':
                return {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '(', EMPTY_SYMBOL};
            case 'W':
            case 'P':
            case 'S':
                return {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '('};
            case 'V':
                return {'*', ':', '+', '-', '^', EMPTY_SYMBOL};
            case 'O':
                return {'*', ':', '+', '-', '^'};
            case 'R':
            case 'L':
            case 'C':
                return {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
            case 'T':
                return {'.', EMPTY_SYMBOL};
            case 'M':
                return {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', EMPTY_SYMBOL};
            case ';':
            case EMPTY_SYMBOL:
            case '(':
            case ')':
            case '.':
            case '*':
            case ':':
            case '+':
            case '-':
            case '^':
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                return {production};
            default:
                break;
        }

        return firsts;
    }

    std::string GrammarSyntaxAnalyzer::getSelectedAlternative(const Production &production, const char &symbol) {
        for (const auto &alternative : production) {
            const auto &leftProduction = alternative[0];
            const auto firsts = getFirstSymbols(leftProduction);
            bool isSymbolInFirsts = std::find(firsts.begin(), firsts.end(), symbol) != firsts.end();

            if (isSymbolInFirsts) {
                return alternative;
            }
        }

        return "";
    }

}
