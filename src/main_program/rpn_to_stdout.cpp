#include "rpn_to_stdout.hpp"
#include "../helpers/strings.hpp"
#include "../grammatical/rpn.hpp"
#include <iostream>

using helpers::Strings;
using grammatical::RPN;


namespace main_program {

    void RPNToStdOut::prepare(int argc, char **argv) {
        parser = std::make_unique<CLAParser>(argc, argv);
        reader = std::make_unique<FileReader>();
    }

    void RPNToStdOut::dispose() {
        if (parser != nullptr) {
            parser.reset();
        }

        if (reader != nullptr) {
            reader.reset();
        }
    }

    void RPNToStdOut::run() {
        const auto fileOption = *options.begin();

        if (!parser->isOptionExists(fileOption)) {
            std::cerr << "--file option is missing." << std::endl;
            std::cout << "USAGE:" << std::endl << "LM --file input.txt" << std::endl;
            return;
        }

        const auto filePath = parser->getOption(fileOption);
        reader->setType(io_manager::ReadType::LINE_BY_LINE);
        reader->link(filePath);

        if (!reader->isBind()) {
            std::cerr << "File path is incorrect." << std::endl;
            return;
        }

        RPN converter;

        while (reader->hasNextLine()) {
            auto line = reader->getNextLine();
            line = Strings::remove(line, '\n');
            converter.convert(line);
            std::cout << converter.getPostfix() << std::endl;
        }

        reader->sever();
    }

}
