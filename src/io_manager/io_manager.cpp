#include <iostream>
#include <sys/stat.h>
#include <functional>
#include "io_manager.hpp"

namespace io_manager {

    const ReadType &FileReader::getType() const {
        return type;
    }

    void FileReader::setType(const ReadType &readType) {
        type = readType;
    }

    long FileReader::getFileSize() const {
        struct stat stat_buffer{};
        int rc = stat(fileName.c_str(), &stat_buffer);
        return rc == 0 ? stat_buffer.st_size : -1;
    }

    const std::string &FileReader::getFileName() const {
        return fileName;
    }

    bool FileReader::link(const std::string &path, std::_Ios_Openmode openModes) {
        if (isTied || path.empty()) {
            return false;
        }

        file = std::ifstream(path, openModes);

        if (file.fail()) {
            isTied = false;
            return false;
        }

        isTied = true;
        return true;
    }

    bool FileReader::sever() {
        if (!isTied) {
            return false;
        }

        file.close();
        isTied = false;
        return true;
    }

    bool FileReader::isBind() const {
        return isTied;
    }

    std::string FileReader::getNextLine() {
        if (type != ReadType::LINE_BY_LINE || !isTied) {
            throw std::bad_function_call();
        }

        if (!file.is_open()) {
            throw std::invalid_argument("!file.is_open()");
        }

        std::string line;
        std::getline(this->file, line);
        return line;
    }

    bool FileReader::hasNextLine() const {
        if (type != ReadType::LINE_BY_LINE || !isTied) {
            throw std::bad_function_call();
        }

        return file.eof();
    }

    std::vector<char> &FileReader::getContentBuffer() {
        if (type != ReadType::WHOLE_FILE || !isTied) {
            throw std::bad_function_call();
        }

        return contentBuffer;
    }

    void FileReader::readIntoBuffer() {
        if (type != ReadType::WHOLE_FILE || !isTied) {
            throw std::bad_function_call();
        }

        if (!file.is_open()) {
            throw std::invalid_argument("!file.is_open()");
        }

        auto first = (std::istreambuf_iterator<char>(file));
        auto last = (std::istreambuf_iterator<char>());
        contentBuffer = std::vector<char>(first, last);
    }

}
