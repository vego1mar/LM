#ifndef FSM_READER_HPP
#define FSM_READER_HPP

#include <memory>
#include "file_reader.hpp"
#include "../automatons/dfa.hpp"

using automatons::DFA;
using automatons::Alphabet;
using automatons::States;
using automatons::DFATransitionMap;

namespace io_manager {

    typedef std::vector<std::string> Tokens;


    class FSMReader {
    private:
        std::unique_ptr<FileReader> reader;

    public:
        FSMReader() = default;

        FSMReader(const FSMReader &rhs) = delete;

        FSMReader(FSMReader &&rvalue) noexcept = delete;

        FSMReader &operator=(const FSMReader &rhs) = delete;

        FSMReader &operator=(FSMReader &&rvalue) noexcept = delete;

        virtual ~FSMReader() = default;

        void parse(const std::string &path, DFA &outDfa);

    private:
        static void parseAlphabetLine(const Tokens &tokens, DFA &outDfa);

        static void parseStates(const Tokens &tokens, DFA &outDfa);

        static void parseStart(const Tokens &tokens, DFA &outDfa);

        static void parseFinals(const Tokens &tokens, DFA &outDfa);

        static void parseTransitions(const Tokens &tokens, DFA &outDfa);

        static void passThroughHeader(const Tokens &tokens, const Alphabet &alphabet, std::size_t &iter);

    };

}

#endif //FSM_READER_HPP
