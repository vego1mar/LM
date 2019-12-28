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

    class FSMReader {
    private:
        std::unique_ptr<FileReader> reader;
        std::unique_ptr<DFA> dfa;

    public:
        FSMReader() = default;

        FSMReader(const FSMReader &rhs) = delete;

        FSMReader(FSMReader &&rvalue) noexcept = delete;

        FSMReader &operator=(const FSMReader &rhs) = delete;

        FSMReader &operator=(FSMReader &&rvalue) noexcept = delete;

        virtual ~FSMReader() = default;

        DFA &parseAndGet(const std::string &path);

    private:

    };

}

#endif //FSM_READER_HPP
