#include "fsm_reader.hpp"
#include "../helpers/strings.hpp"

namespace io_manager {

    using automatons::Alphabet;
    using automatons::States;
    using automatons::DFATransitionMap;
    using automatons::StateEventPair;
    using helpers::Strings;

    void FSMReader::parse(const std::string &path, DFA &outDfa) {
        reader = std::make_unique<FileReader>();
        reader->setType(ReadType::WHOLE_FILE);
        reader->link(path);
        reader->readIntoBuffer();

        const auto &fileContent = reader->getContentBuffer();
        auto flattenedContent = std::make_unique<std::string>(Strings::flatten(fileContent));
        auto content = Strings::between(*flattenedContent, "alphabet", "states");
        parseAlphabetLine(Strings::split(Strings::replace(content, '\n', " ")), outDfa);
        content = Strings::between(*flattenedContent, "states", "start");
        parseStates(Strings::split(Strings::replace(content, '\n', " ")), outDfa);
        content = Strings::between(*flattenedContent, "start", "finals");
        parseStart(Strings::split(Strings::replace(content, '\n', " ")), outDfa);
        content = Strings::between(*flattenedContent, "finals", "transitions");
        parseFinals(Strings::split(Strings::replace(content, '\n', " ")), outDfa);
        content = Strings::between(*flattenedContent, "transitions", "%%");
        flattenedContent.reset();

        auto transitionsTokens = Strings::split(Strings::replace(content, '\n', "%"), '%');
        parseTransitions(transitionsTokens, outDfa);
        reader->sever();
    }

    void FSMReader::parseAlphabetLine(const Tokens &tokens, DFA &outDfa) {
        Alphabet alphabet;

        for (const auto &token : tokens) {
            for (const auto &symbol : token) {
                alphabet.insert(symbol);
            }
        }

        outDfa.setAlphabet(alphabet);
    }

    void FSMReader::parseStates(const Tokens &tokens, DFA &outDfa) {
        States states;

        for (const auto &state : tokens) {
            if (Strings::isNumber(state)) {
                int parsedState = std::stoi(state);
                states.insert(parsedState);
            }
        }

        outDfa.setStates(states);
    }

    void FSMReader::parseStart(const Tokens &tokens, DFA &outDfa) {
        if (tokens.empty() || !Strings::isNumber(tokens[0])) {
            outDfa.setStart(-1);
            return;
        }

        int parsedState = std::stoi(tokens[0]);
        outDfa.setStart(parsedState);
    }

    void FSMReader::parseFinals(const Tokens &tokens, DFA &outDfa) {
        States finals;

        for (const auto &final : tokens) {
            if (Strings::isNumber(final)) {
                int parsedState = std::stoi(final);
                finals.insert(parsedState);
            }
        }

        outDfa.setFinals(finals);
    }

    void FSMReader::parseTransitions(const Tokens &tokens, DFA &outDfa) {
        DFATransitionMap transitionMap;
        std::size_t i = 0;
        auto &alphabet = outDfa.getAlphabet();
        passThroughHeader(tokens, alphabet, i);

        for (std::size_t j = i; j < tokens.size(); j++) {
            const auto &line = tokens[j];
            auto tokenized = Strings::split(Strings::replace(line, '\t', " "));
            auto currentState = std::stoi(tokenized[0]);
            auto it = alphabet.begin();

            for (std::size_t k = 1; k < alphabet.size() + 1; k++) {
                auto subsequentState = std::stoi(tokenized[k]);
                StateEventPair currentPair = std::make_pair<>(currentState, *it);
                transitionMap[currentPair] = subsequentState;
                it++;
            }
        }

        outDfa.setTransitions(transitionMap);
    }

    void FSMReader::passThroughHeader(const Tokens &tokens, const Alphabet &alphabet, std::size_t &iter) {
        auto isHeaderLine = [&alphabet](const Tokens &tokenized) -> bool {
            for (const auto &token : tokenized) {
                bool isTokenCharacter = token.size() == 1;
                bool isTokenCharInAlphabet = alphabet.find(token[0]) != alphabet.end();

                if (!isTokenCharacter || !isTokenCharInAlphabet) {
                    return false;
                }
            }

            return true;
        };

        for (const auto &line : tokens) {
            auto tokenized = Strings::split(Strings::replace(line, '\t', " "));
            iter++;

            if (tokenized.size() < 2) {
                continue;
            }

            if (isHeaderLine(tokenized)) {
                break;
            }
        }
    }

}
