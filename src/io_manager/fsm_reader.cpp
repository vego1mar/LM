#include "fsm_reader.hpp"
#include "../helpers/strings.hpp"

namespace io_manager {

    using automatons::Alphabet;
    using automatons::States;
    using automatons::DFATransitionMap;
    using automatons::StateEventPair;
    using helpers::Strings;

    DFA &FSMReader::parseAndGet(const std::string &path) {
        dfa = std::make_unique<DFA>();
        reader = std::make_unique<FileReader>();
        reader->setType(ReadType::WHOLE_FILE);
        reader->link(path);
        reader->readIntoBuffer();

        const auto &fileContent = reader->getContentBuffer();
        auto flattenedContent = std::make_unique<std::string>(Strings::flatten(fileContent));
        auto alphabetDef = Strings::between(*flattenedContent, "alphabet", "states");
        auto statesDef = Strings::between(*flattenedContent, "states", "start");
        auto startDef = Strings::between(*flattenedContent, "start", "finals");
        auto finalsDef = Strings::between(*flattenedContent, "finals", "transitions");
        auto transitionsDef = Strings::between(*flattenedContent, "transitions", "%%");
        flattenedContent.reset();

        parseAlphabetLine(Strings::split(alphabetDef));
        parseStates(Strings::split(statesDef));
        parseStart(Strings::split(startDef));
        parseFinals(Strings::split(finalsDef));
        parseTransitions(Strings::split(transitionsDef));

        reader->sever();
        return *dfa;
    }

    void FSMReader::parseAlphabetLine(const Tokens &tokens) {
        Alphabet alphabet;

        for (const auto &token : tokens) {
            for (const auto &symbol : token) {
                alphabet.insert(symbol);
            }
        }

        dfa->setAlphabet(alphabet);
    }

    void FSMReader::parseStates(const Tokens &tokens) {
        States states;

        for (const auto &state : tokens) {
            int parsedState = std::stoi(state);
            states.insert(parsedState);
        }

        dfa->setStates(states);
    }

    void FSMReader::parseStart(const Tokens &tokens) {
        if (tokens.empty()) {
            dfa->setStart(-1);
            return;
        }

        int parsedState = std::stoi(tokens[0]);
        dfa->setStart(parsedState);
    }

    void FSMReader::parseFinals(const Tokens &tokens) {
        States finals;

        for (const auto &state : tokens) {
            int parsedState = std::stoi(state);
            finals.insert(parsedState);
        }

        dfa->setFinals(finals);
    }

    void FSMReader::parseTransitions(const Tokens &tokens) {
        DFATransitionMap transitionMap;
        auto it = tokens.begin();

        // parse header

        while (it != tokens.end()) {
            while (*it != "\n" || it != tokens.end()) {
                // parse next line
                // build transition entry of (StateEventPair,int)
                it++;
            }

            it++;
        }

        dfa->setTransitions(transitionMap);
    }

}
