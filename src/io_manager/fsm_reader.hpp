#ifndef FSM_READER_HPP
#define FSM_READER_HPP

#include <memory>
#include "file_reader.hpp"
#include "definitions.hpp"
#include "../automatons/dfa.hpp"
#include "../automatons/nfa.hpp"
#include "../automatons/definitions.hpp"

using io_manager::Tokens;
using automatons::DFA;
using automatons::NFA;
using automatons::Alphabet;
using automatons::States;
using automatons::NFATransitionMap;
using automatons::StateEventPair;

namespace io_manager {

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

        void parse(const std::string &path, NFA &outNfa);

    private:
        static Alphabet getParsedAlphabetLine(const Tokens &tokens);

        static States getParsedStates(const Tokens &tokens);

        static void parseStart(const Tokens &tokens, DFA &outDfa);

        static void parseDFATransitions(const Tokens &tokens, DFA &outDfa);

        static void parseNFATransitions(const Tokens &tokens, NFA &outNfa);

        static void passThroughHeader(const Tokens &tokens, const Alphabet &alphabet, std::size_t &iter);

        static void parseNFATransitionEntry(NFATransitionMap &transitionMap, const Tokens &tokenized, NFATransitionEntryPOD &pod);

        static void processNFAEntryPairsBrackets(const Tokens &symbolsTokens, const NFATransitionEntryPOD &pod);

        static void processNFAEntryPairParentheses(const NFATransitionEntryPOD &pod);

        static void processNFAEntryNextSingleBrackets(const NFATransitionEntryPOD &pod);

        static void processNFAEntryNextDoubleBrackets(const NFATransitionEntryPOD &pod);

        static void processNFAEntryNextParentheses(const NFATransitionEntryPOD &pod);

        static void parseNFASymbolsColumn(const NFATransitionEntryPOD &pod);

        static void parseNFANextStatesColumn(const NFATransitionEntryPOD &pod);

        static void makeNFATransitionEntries(NFATransitionMap &map, const NFATransitionEntryPOD &pod, const std::size_t &no);

    };

}

#endif //FSM_READER_HPP
