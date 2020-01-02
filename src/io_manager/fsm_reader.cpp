#include <algorithm>
#include <numeric>
#include "fsm_reader.hpp"
#include "../helpers/strings.hpp"
#include "../helpers/collections.hpp"

namespace io_manager {

    using automatons::Alphabet;
    using automatons::States;
    using automatons::DFATransitionMap;
    using helpers::Strings;

    void FSMReader::parse(const std::string &path, DFA &outDfa) {
        reader = std::make_unique<FileReader>();
        reader->setType(ReadType::WHOLE_FILE);
        reader->link(path);
        reader->readIntoBuffer();

        const auto &fileContent = reader->getContentBuffer();
        auto flattenedContent = std::make_unique<std::string>(Strings::flatten(fileContent));
        auto content = Strings::betweenFirsts(*flattenedContent, "alphabet", "states");
        auto alphabet = getParsedAlphabetLine(Strings::split(Strings::replace(content, '\n', " ")));
        outDfa.setAlphabet(alphabet);
        content = Strings::betweenFirsts(*flattenedContent, "states", "start");
        auto states = getParsedStates(Strings::split(Strings::replace(content, '\n', " ")));
        outDfa.setStates(states);
        content = Strings::betweenFirsts(*flattenedContent, "start", "finals");
        parseStart(Strings::split(Strings::replace(content, '\n', " ")), outDfa);
        content = Strings::betweenFirsts(*flattenedContent, "finals", "transitions");
        auto finals = getParsedStates(Strings::split(Strings::replace(content, '\n', " ")));
        outDfa.setFinals(finals);
        content = Strings::betweenFirsts(*flattenedContent, "transitions", "%%");
        flattenedContent.reset();

        auto transitionsTokens = Strings::split(Strings::replace(content, '\n', "%"), '%');
        parseDFATransitions(transitionsTokens, outDfa);
        reader->sever();
    }

    void FSMReader::parse(const std::string &path, NFA &outNfa) {
        reader = std::make_unique<FileReader>();
        reader->setType(ReadType::WHOLE_FILE);
        reader->link(path);
        reader->readIntoBuffer();

        const auto &fileContent = reader->getContentBuffer();
        auto flattenedContent = std::make_unique<std::string>(Strings::flatten(fileContent));
        auto content = Strings::betweenFirsts(*flattenedContent, "alphabet", "states");
        auto alphabet = getParsedAlphabetLine(Strings::split(Strings::replace(content, '\n', " ")));
        outNfa.setAlphabet(alphabet);
        content = Strings::betweenFirsts(*flattenedContent, "states", "start");
        auto states = getParsedStates(Strings::split(Strings::replace(content, '\n', " ")));
        outNfa.setStates(states);
        content = Strings::betweenFirsts(*flattenedContent, "start", "finals");
        auto starts = getParsedStates(Strings::split(Strings::replace(content, '\n', " ")));
        outNfa.setStart(starts);
        content = Strings::betweenFirsts(*flattenedContent, "finals", "transitions");
        auto finals = getParsedStates(Strings::split(Strings::replace(content, '\n', " ")));
        outNfa.setFinals(finals);
        content = Strings::betweenFirsts(*flattenedContent, "transitions", "%%");
        flattenedContent.reset();

        auto transitionsTokens = Strings::split(Strings::replace(content, '\n', "%"), '%');
        parseNFATransitions(transitionsTokens, outNfa);
        reader->sever();
    }

    Alphabet FSMReader::getParsedAlphabetLine(const Tokens &tokens) {
        Alphabet alphabet;

        for (const auto &token : tokens) {
            for (const auto &symbol : token) {
                alphabet.insert(symbol);
            }
        }

        return alphabet;
    }

    States FSMReader::getParsedStates(const Tokens &tokens) {
        States states;

        for (const auto &state : tokens) {
            if (Strings::isNumber(state)) {
                int parsedState = std::stoi(state);
                states.insert(parsedState);
            }
        }

        return states;
    }

    void FSMReader::parseStart(const Tokens &tokens, DFA &outDfa) {
        if (tokens.empty() || !Strings::isNumber(tokens[0])) {
            outDfa.setStart(-1);
            return;
        }

        int parsedState = std::stoi(tokens[0]);
        outDfa.setStart(parsedState);
    }

    void FSMReader::parseDFATransitions(const Tokens &tokens, DFA &outDfa) {
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

    void FSMReader::parseNFATransitions(const Tokens &tokens, NFA &outNfa) {
        auto transitionMap = std::make_unique<NFATransitionMap>();
        std::size_t i = 0;

        auto pod = std::make_unique<NFATransitionEntryPOD>();
        pod->symbolsColumn = nullptr;
        pod->nextStatesColumn = nullptr;
        pod->currentState = nullptr;
        pod->containsBrackets = nullptr;
        pod->containsParentheses = nullptr;
        pod->pairs = std::make_unique<std::vector<StateEventPair>>();
        pod->nextStates = std::make_unique<std::vector<States>>();
        pod->repetitions = nullptr;
        pod->isDoubleBracketed = nullptr;
        pod->iterators = std::make_unique<Successors>();

        for (std::size_t j = i; j < tokens.size(); j++) {
            const auto &line = tokens[j];
            auto tokenized = Strings::split(Strings::replace(line, '\t', " "));

            if (tokenized.size() >= 3) {
                parseNFATransitionEntry(*transitionMap, tokenized, *pod);
            }
        }

        outNfa.setTransitions(*transitionMap);
    }

    void FSMReader::passThroughHeader(const Tokens &tokens, const Alphabet &alphabet, std::size_t &iter) {
        auto checkIfItsHeaderLine = [&alphabet](const Tokens &tokenized, bool &itWasHeaderLine) {
            for (const auto &token : tokenized) {
                bool isTokenCharacter = token.size() == 1;
                bool isTokenCharInAlphabet = alphabet.find(token[0]) != alphabet.end();

                if (!isTokenCharacter || !isTokenCharInAlphabet) {
                    itWasHeaderLine = false;
                    return;
                }
            }

            itWasHeaderLine = true;
        };

        for (const auto &line : tokens) {
            auto tokenized = Strings::split(Strings::replace(line, '\t', " "));
            iter++;

            if (tokenized.size() < 2) {
                continue;
            }

            bool itWasHeaderLine;
            checkIfItsHeaderLine(tokenized, itWasHeaderLine);

            if (itWasHeaderLine) {
                break;
            }
        }
    }

    void FSMReader::parseNFATransitionEntry(NFATransitionMap &transitionMap, const Tokens &tokenized, NFATransitionEntryPOD &pod) {
        int currentState = std::stoi(tokenized[0]);
        const auto &symbolsColumn = tokenized[1];
        const auto &nextStatesColumn = tokenized[2];

        auto throwExceptionIfPalesAreNotPaired = [](const std::string &column, NFATransitionEntryPOD &pod) {
            bool &containsBrackets = *pod.containsBrackets;
            bool &containsParentheses = *pod.containsParentheses;
            containsBrackets = Strings::contains(column, "[") && Strings::contains(column, "]");
            containsParentheses = Strings::contains(column, "(") && Strings::contains(column, ")");

            if (!containsBrackets && !containsParentheses) {
                throw std::out_of_range("!containsBrackets && !containsParentheses");
            }
        };

        pod.symbolsColumn = std::make_unique<std::string>(symbolsColumn);
        pod.nextStatesColumn = std::make_unique<std::string>(nextStatesColumn);
        pod.currentState = std::make_unique<int>(currentState);
        pod.containsBrackets = std::make_unique<bool>(false);
        pod.containsParentheses = std::make_unique<bool>(false);
        pod.pairs = std::make_unique<std::vector<StateEventPair>>();
        pod.nextStates = std::make_unique<std::vector<States>>();
        pod.repetitions = std::make_unique<std::vector<std::vector<std::size_t>>>();
        pod.isDoubleBracketed = std::make_unique<std::vector<bool>>();
        pod.iterators = std::make_unique<Successors>();

        auto &containsBrackets = *pod.containsBrackets;
        auto &containsParentheses = *pod.containsParentheses;
        auto &pairs = *pod.pairs;
        throwExceptionIfPalesAreNotPaired(symbolsColumn, pod);
        parseNFASymbolsColumn(pod);

        containsBrackets = Strings::contains(nextStatesColumn, "[") && Strings::contains(nextStatesColumn, "]");
        containsParentheses = Strings::contains(nextStatesColumn, "(") && Strings::contains(nextStatesColumn, ")");
        throwExceptionIfPalesAreNotPaired(nextStatesColumn, pod);
        parseNFANextStatesColumn(pod);

        const auto &repetitions = *pod.repetitions;
        auto sumOfEvents = helpers::Collections::sum(repetitions);

        if (sumOfEvents != (*pod.pairs).size() || (*pod.nextStates).size() > sumOfEvents) {
            throw std::length_error("sumOfEvents != stateEventVector.size() || sumOfEvents > nextStatesVector.size()");
        }

        auto &its = (*pod.iterators);
        typedef const NFATransitionEntryPOD &Param1;
        typedef const std::size_t &Param2;

        if (repetitions.size() != (*pod.isDoubleBracketed).size()) {
            throw std::length_error("repetitions.size() != (*pod.isDoubleBracketed).size()");
        }

        for (const auto &lineRepetition : repetitions) {
            for (const auto &repetitionsNo : lineRepetition) {
                makeNFATransitionEntries(transitionMap, pod, repetitionsNo);
            }
        }
    }

    void FSMReader::processNFAEntryPairsBrackets(const Tokens &symbolsTokens, NFATransitionEntryPOD &pod) {
        const int &currentState = *pod.currentState;
        auto &pairs = *pod.pairs;
        std::size_t repetitives = 0;

        for (const auto &symbol : symbolsTokens) {
            if (symbol.size() != 1) {
                throw std::length_error("symbol.size() != 1");
            }

            auto currentPair = StateEventPair(currentState, symbol[0]);
            pairs.emplace_back(currentPair);
            repetitives++;
        }

        (*pod.repetitions).emplace_back(std::vector<std::size_t>{repetitives});
    }

    void FSMReader::processNFAEntryPairParentheses(NFATransitionEntryPOD &pod) {
        const std::string &symbolsColumn = *pod.symbolsColumn;
        const int &currentState = *pod.currentState;
        auto &pairs = *pod.pairs;
        auto &repetitions = *pod.repetitions;
        std::size_t nextClosingParenthesis = 0;
        auto slice = symbolsColumn.substr(symbolsColumn.find('('));

        // There may be many pairs of parentheses.
        while (nextClosingParenthesis != std::string::npos) {
            auto subSymbols = slice.substr(nextClosingParenthesis);
            auto symbol = Strings::betweenFirsts(subSymbols, "(", ")");

            if (symbol.size() != 1) {
                throw std::length_error("symbol.size() != 1");
            }

            nextClosingParenthesis = slice.find(')', 3);
            auto pair = StateEventPair(currentState, symbol[0]);
            pairs.emplace_back(pair);
        }

        repetitions.emplace_back(std::vector<std::size_t>{1});
    }

    void FSMReader::processNFAEntryNextSingleBrackets(NFATransitionEntryPOD &pod) {
        const std::string &nextStatesColumn = *pod.nextStatesColumn;
        auto &nextStates = *pod.nextStates;
        auto setsStr = Strings::betweenFirsts(nextStatesColumn, "[", "]");
        auto sets = Strings::split(setsStr, ';');

        for (const auto &setStr : sets) {
            auto tokens = Strings::split(setStr, ',');
            States currentNext = States();

            std::for_each(tokens.begin(), tokens.end(), [&tokens, &currentNext](const std::string &setStates) {
                auto next = Strings::split(setStates, ',');

                for (const auto &stateStr : next) {
                    int nextState = std::stoi(stateStr);
                    currentNext.insert(nextState);
                }
            });

            nextStates.emplace_back(currentNext);
        }
    }

    void FSMReader::processNFAEntryNextDoubleBrackets(NFATransitionEntryPOD &pod) {
        const std::string &nextStatesColumn = *pod.nextStatesColumn;
        NFAEntryNext &nextStates = *pod.nextStates;
        auto stateStr = Strings::betweenFirsts(nextStatesColumn, "[[", "]]");
        int state = std::stoi(stateStr);
        auto next = States({state});
        nextStates.emplace_back(next);
    }

    void FSMReader::processNFAEntryNextParentheses(NFATransitionEntryPOD &pod) {
        const std::string &nextStatesColumn = *pod.nextStatesColumn;
        auto &nextStates = *pod.nextStates;
        auto statesStr = Strings::betweenFirsts(nextStatesColumn, "(", ")");
        auto tokens = Strings::split(statesStr, ',');
        States next;

        for (const auto &stateStr : tokens) {
            int parsedState = std::stoi(stateStr);
            next.insert(parsedState);
        }

        nextStates.emplace_back(next);
    }

    void FSMReader::parseNFASymbolsColumn(NFATransitionEntryPOD &pod) {
        auto &containsBrackets = *pod.containsBrackets;
        auto &containsParentheses = *pod.containsParentheses;

        if (containsBrackets) {
            auto symbolsStr = Strings::betweenFirsts(*pod.symbolsColumn, "[", "]");
            auto symbolsTokens = Strings::split(symbolsStr, ',');
            processNFAEntryPairsBrackets(symbolsTokens, pod);
        }

        if (containsParentheses) {
            processNFAEntryPairParentheses(pod);
        }
    }

    void FSMReader::parseNFANextStatesColumn(NFATransitionEntryPOD &pod) {
        const auto &nextStatesColumn = *pod.nextStatesColumn;
        auto &containsBrackets = *pod.containsBrackets;
        auto &containsParentheses = *pod.containsParentheses;

        if (containsBrackets) {
            bool containsSinglePair = Strings::contains(nextStatesColumn, "[") && Strings::contains(nextStatesColumn, "]");
            bool containsDoublePair = Strings::contains(nextStatesColumn, "[[") && Strings::contains(nextStatesColumn, "]]");

            if (!containsSinglePair && !containsDoublePair) {
                throw std::out_of_range("!containsSinglePair && !containsDoublePair");
            }

            // One pair expected: either single or double. Double prioritized.
            if (containsDoublePair) {
                processNFAEntryNextDoubleBrackets(pod);
                (*pod.isDoubleBracketed).push_back(true);
            } else {
                processNFAEntryNextSingleBrackets(pod);
                (*pod.isDoubleBracketed).push_back(false);
            }
        }

        if (containsParentheses) {
            processNFAEntryNextParentheses(pod);
            (*pod.isDoubleBracketed).push_back(false);
        }
    }

    void FSMReader::makeNFATransitionEntries(NFATransitionMap &map, NFATransitionEntryPOD &pod, const std::size_t &no) {
        const auto &repetitionsNo = no;
        auto &its = *pod.iterators;
        auto &transitionMap = map;
        its.itSuccinct = 0;

        if ((*pod.isDoubleBracketed)[its.itNext]) {
            while (its.itSuccinct < repetitionsNo) {
                const auto &first = (*pod.pairs)[its.itSymbols];
                const auto &second = (*pod.nextStates)[its.itNext];
                transitionMap[first] = second;
                its.itSymbols++;
                its.itSuccinct++;
            }

            its.itNext++;
            return;
        }

        while (its.itSuccinct < repetitionsNo) {
            const auto &event = (*pod.pairs)[its.itSymbols];
            const auto &next = (*pod.nextStates)[its.itNext];
            transitionMap[event] = next;
            its.itSuccinct++;
            its.itSymbols++;
            its.itNext++;
        }
    }

}
