#include <iostream>
#include <regex>
#include "regular_expression_info.hpp"
#include "../helpers/strings.hpp"

using helpers::Strings;
using io_manager::ReadType;


namespace main_program {

    void RegularExpressionInfo::prepare(int argc, char **argv) {
        parser = std::make_unique<CLAParser>(argc, argv);
        reader = std::make_unique<FileReader>();
        what = ReturnState::PREPARED;
    }

    void RegularExpressionInfo::run() {
        const auto inputOption = *options.begin();
        const auto regexOption = *std::next(options.begin());
        bool isInputOptionExists = parser->isOptionExists(inputOption);
        bool isRegexOptionExists = parser->isOptionExists(regexOption);

        if (!isInputOptionExists || !isRegexOptionExists) {
            printHelp();
            return;
        }

        auto args = std::make_unique<InternalMainArgs3>();
        args->inputPath = parser->getOption(inputOption);
        args->regexPath = parser->getOption(regexOption);
        main(*args);
    }

    void RegularExpressionInfo::dispose() {
        what = ReturnState::DISPOSING;

        if (parser != nullptr) {
            parser.reset();
        }

        if (reader->isBind()) {
            reader->sever();
        }

        if (reader != nullptr) {
            reader.reset();
        }
    }

    void RegularExpressionInfo::main(InternalMainArgs3 &args) {
        readRegexFile(args);

        if (what != ReturnState::REGEX_FILE_OK) {
            return;
        }

        processInputFile(args);
    }

    void RegularExpressionInfo::printHelp() {
        std::cout << "USAGE:" << std::endl << "./LM --input input.txt --regex regex.txt" << std::endl;
    }

    void RegularExpressionInfo::readRegexFile(InternalMainArgs3 &args) {
        reader->setType(ReadType::WHOLE_FILE);
        reader->link(args.regexPath);

        if (!reader->isBind()) {
            what = ReturnState::REGEX_FILE_NOT_FOUND;
            std::cerr << "!reader->isBind()" << std::endl;
        }

        reader->readIntoBuffer();
        auto content = reader->getContentBuffer();
        args.regexContent = Strings::flatten(content);
        reader->sever();
        what = ReturnState::REGEX_FILE_OK;
    }

    void RegularExpressionInfo::processInputFile(InternalMainArgs3 &args) {
        reader->setType(ReadType::LINE_BY_LINE);
        reader->link(args.inputPath);

        if (!reader->isBind()) {
            what = ReturnState::INPUT_FILE_NOT_FOUND;
            std::cerr << "!reader->isBind()" << std::endl;
            return;
        }

        what = ReturnState::INPUT_FILE_PROCESSING;

        while (reader->hasNextLine()) {
            auto text = reader->getNextLine();
            args.currentInput = Strings::remove(text, '\n');
            printComplianceWithRegex(args);
        }

        reader->sever();
        what = ReturnState::INPUT_FILE_OK;
    }

    void RegularExpressionInfo::printComplianceWithRegex(const InternalMainArgs3 &args) {
        const auto &input = args.currentInput;
        const auto &regexStr = args.regexContent;

        auto text = std::string(input);
        std::smatch match;
        std::string matchStr;
        std::regex regExp(regexStr);

        while (std::regex_search(text, match, regExp)) {
            matchStr += *match.begin();
            text = match.suffix().str();
        }

        std::cout << matchStr << std::endl;
        std::cout << (matchStr == input ? "compliant" : "incompliant") << std::endl;
        std::cout << std::endl;
    }

}
