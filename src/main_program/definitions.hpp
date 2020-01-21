#ifndef MAIN_PROGRAM_DEFINITIONS_HPP
#define MAIN_PROGRAM_DEFINITIONS_HPP

#include <string>


namespace main_program {

    struct InternalMainArgs3 {
        std::string inputPath;
        std::string regexPath;
        std::string regexContent;
        std::string currentInput;
    };

    enum class ReturnState {
        OK,
        PREPARED,
        DISPOSING,
        REGEX_FILE_NOT_FOUND,
        REGEX_FILE_OK,
        INPUT_FILE_NOT_FOUND,
        INPUT_FILE_OK,
        INPUT_FILE_PROCESSING
    };

}

#endif //MAIN_PROGRAM_DEFINITIONS_HPP
