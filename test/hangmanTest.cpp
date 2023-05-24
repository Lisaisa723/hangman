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

TEST_CASE("Number in the word", "[validateWord]")
{
    std::string errorMessage;
    try {
        validateWord("w8");
    } catch (const std::runtime_error& e) {
        errorMessage = e.what();
    }
    REQUIRE(errorMessage == "There are number in the word!");
}

TEST_CASE("Capital letter in the word", "[validateWord]")
{
    std::string errorMessage;
    try {
        validateWord("Word");
    } catch (const std::runtime_error& e) {
        errorMessage = e.what();
    }
    REQUIRE(errorMessage == "There are capital letter in the word!");
}

TEST_CASE("Symbol in the word", "[validateWord]")
{
    std::string errorMessage;
    try {
        validateWord("$nake");
    } catch (const std::runtime_error& e) {
        errorMessage = e.what();
    }
    REQUIRE(errorMessage == "There are symbol in the word!");
}

TEST_CASE("The error has not been committed yet", "[doNotRecountMistake]")
{
    std::string missingLetters = " ";
    int mistakes = 0;
    doNotRecountMistake(missingLetters, 'a', mistakes);
    REQUIRE(missingLetters.size() == 1);
    REQUIRE(missingLetters[0] == 'a');
    REQUIRE(mistakes == 1);
}

TEST_CASE("The error has been committed", "[doNotRecountMistake]")
{
    std::string missingLetters = "a";
    int mistakes = 1;
    doNotRecountMistake(missingLetters, 'a', mistakes);
    REQUIRE(missingLetters.size() == 1);
    REQUIRE(missingLetters[0] == 'a');
    REQUIRE(mistakes == 1);
}