#include "../catch.hpp"
#include "../../src/io_manager/file_reader.hpp"

using io_manager::FileReader;
using io_manager::ReadType;

TEST_CASE("file_reader.hpp", "[file_reader]") {
    const std::string &DFA_1_PATH = "../../files/dfa_1.txt";
    const long &DFA_1_SIZE = 1635;

    SECTION("read LINE_BY_LINE -> OK") {
        std::vector<std::string> lines;
        FileReader reader;
        reader.link(DFA_1_PATH);
        REQUIRE(reader.isBind());

        while (reader.hasNextLine()) {
            lines.push_back(reader.getNextLine());
        }

        REQUIRE(reader.getType() == ReadType::LINE_BY_LINE);
        REQUIRE_THAT(reader.getFileName(), Catch::Equals(DFA_1_PATH));
        REQUIRE(reader.getFileSize() == DFA_1_SIZE);
        reader.sever();
        REQUIRE(!reader.isBind());
        REQUIRE(reader.getFileSize() == -1);
        REQUIRE_THROWS_AS(reader.getContentBuffer(), std::bad_function_call);
    }

    SECTION("read WHOLE_FILE -> OK") {
        FileReader reader;
        reader.setType(ReadType::WHOLE_FILE);
        reader.link(DFA_1_PATH);
        assert(reader.isBind());

        reader.readIntoBuffer();

        REQUIRE(reader.getContentBuffer().size() == DFA_1_SIZE);
        reader.sever();
        REQUIRE_THROWS_AS(reader.hasNextLine(), std::bad_function_call);
    }

}
