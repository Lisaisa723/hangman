#include "hangman/hangman.h"
#include "catch.h"

TEST_CASE("Unable to open file", "[getRandomWord]")
{
    std::string errorMessage;
    try {
        getRandomWord("non-existent file");
    } catch (const std::runtime_error& e) {
        errorMessage = e.what();
    }
    REQUIRE(errorMessage == "Can not open file!");
}

TEST_CASE("File can be open", "[getRandomWord]")
{
    std::ofstream out("test_file.txt");
    out << "good" << std::endl;
    out.close();
    std::string errorMessage;
    try {
        getRandomWord("test_file.txt");
    } catch (const std::runtime_error& e) {
        errorMessage = e.what();
    }
    std::remove("test_file.txt");
    REQUIRE(errorMessage == "");
}