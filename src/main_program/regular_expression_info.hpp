#ifndef REGULAR_EXPRESSION_INFO_HPP
#define REGULAR_EXPRESSION_INFO_HPP

#include "../io_manager/file_reader.hpp"
#include "../command_line/cla_parser.hpp"
#include "definitions.hpp"
#include <memory>
#include <list>

using io_manager::FileReader;
using command_line::CLAParser;


namespace main_program {

    class RegularExpressionInfo {
    private:
        const std::list<std::string> options = {"--input", "--regex"};
        ReturnState what = ReturnState::OK;
        std::unique_ptr<CLAParser> parser;
        std::unique_ptr<FileReader> reader;

    public:
        RegularExpressionInfo() = default;

        RegularExpressionInfo(const RegularExpressionInfo &rhs) = delete;

        RegularExpressionInfo(RegularExpressionInfo &&rvalue) noexcept = delete;

        RegularExpressionInfo &operator=(const RegularExpressionInfo &rhs) = delete;

        RegularExpressionInfo &operator=(RegularExpressionInfo &&rvalue) noexcept = delete;

        virtual ~RegularExpressionInfo() = default;

        void prepare(int argc, char **argv);

        void run();

        void dispose();

    private:
        void main(InternalMainArgs3 &args);

        static void printHelp();

        void readRegexFile(InternalMainArgs3 &args);

        void processInputFile(InternalMainArgs3 &args);

        static void printComplianceWithRegex(const InternalMainArgs3 &args);

    };

}

#endif //REGULAR_EXPRESSION_INFO_HPP
