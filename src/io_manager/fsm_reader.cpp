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

        //auto tokens = Strings::split(line);
        //std::find('alphabet', fileContent) = A; std::find('states', A + fileContent) = B; substr(A, B) => parse()

        // TODO:
        // read whole file
        // substring('alphabet','states') -> parseAlphabet(tokens) : Alphabet
        // substring('states','start') -> parseStates(tokens) : States
        // substring('start','finals') -> parseStart(tokens) : int
        // substring('finals','transitions') -> parseFinals(tokens) : States
        // substring('transitions',file.end()) -> parseTransitions(tokens) : DFATransitionMap

        reader->sever();
        return *dfa;
    }

}
