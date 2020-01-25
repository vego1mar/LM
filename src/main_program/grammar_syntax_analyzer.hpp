#ifndef GRAMMAR_SYNTAX_ANALYZER_HPP
#define GRAMMAR_SYNTAX_ANALYZER_HPP

#include <memory>
#include <list>
#include "../io_manager/file_reader.hpp"
#include "../command_line/cla_parser.hpp"
#include "definitions.hpp"

using io_manager::FileReader;
using command_line::CLAParser;


namespace main_program {

    /* LL(1) grammar:
     * S::=W;Z
     * Z::=W;Z|ε
     * W::=PV
     * V::=OW|ε
     * P::=R|(W)
     * R::=LT
     * T::=.L|ε
     * L::=CM
     * M::=L|ε
     * C::=0|1|2|3|4|5|6|7|8|9
     * O::=*|:|+|-|^
     */
    class GrammarSyntaxAnalyzer {
    private:
        const std::list<std::string> options = {"--input"};
        static const char EMPTY_SYMBOL;
        std::unique_ptr<FileReader> reader;
        std::unique_ptr<CLAParser> parser;
        std::unique_ptr<std::string> inputStr;
        std::unique_ptr<std::string> catchedStr;
        std::unique_ptr<std::size_t> currentPosition;

    public:
        GrammarSyntaxAnalyzer() = default;

        GrammarSyntaxAnalyzer(const GrammarSyntaxAnalyzer &rhs) = delete;

        GrammarSyntaxAnalyzer(GrammarSyntaxAnalyzer &&rvalue) noexcept = delete;

        GrammarSyntaxAnalyzer &operator=(const GrammarSyntaxAnalyzer &rhs) = delete;

        GrammarSyntaxAnalyzer &operator=(GrammarSyntaxAnalyzer &&rvalue) noexcept = delete;

        virtual ~GrammarSyntaxAnalyzer() = default;

        void prepare(int argc, char **argv);

        void dispose();

        void run();

    private:

        void analyze(int level = 0, char production = 'S');

        char getCurrentSymbol() const;

        static Production getEnlisted(char production);

        static Firsts getFirstSymbols(char production);

        static std::string getSelectedAlternative(const Production &production, const char &symbol);

    };

}

#endif //GRAMMAR_SYNTAX_ANALYZER_HPP
