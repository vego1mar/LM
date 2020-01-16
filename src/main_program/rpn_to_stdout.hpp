#ifndef RPNTOSTDOUT_HPP
#define RPNTOSTDOUT_HPP

#include "../io_manager/file_reader.hpp"
#include "../command_line/cla_parser.hpp"
#include <memory>
#include <list>

using io_manager::FileReader;
using command_line::CLAParser;


namespace main_program {

    class RPNToStdOut {
    private:
        const std::list<std::string> options = {"--file"};
        std::unique_ptr<FileReader> reader;
        std::unique_ptr<CLAParser> parser;


    public:
        RPNToStdOut() = default;

        RPNToStdOut(const RPNToStdOut &rhs) = delete;

        RPNToStdOut(RPNToStdOut &&rvalue) noexcept = delete;

        RPNToStdOut &operator=(const RPNToStdOut &rhs) = delete;

        RPNToStdOut &operator=(RPNToStdOut &&rvalue) noexcept = delete;

        virtual ~RPNToStdOut() = default;

        void prepare(int argc, char **argv);

        void dispose();

        void run();

    };

}

#endif //RPNTOSTDOUT_HPP
