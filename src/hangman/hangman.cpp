#include "hangman.h"
void validateWord(const string& testWord)
{
    unsigned char code;
    for (char letter : testWord) {
        code = (unsigned char)letter;
        if (code > 96 and code < 123) {
            continue;
        } else if (code > 47 and code < 58) {
            throw runtime_error("There are number in the word!");
        } else if (code > 64 and code < 91) {
            throw runtime_error("There are capital letter in the word!");
        } else if (
                (code > 32 and code < 48) or (code > 57 and code < 65)
                or (code > 90 and code < 97) or (code > 122 and code < 126)) {
            throw runtime_error("There are symbol in the word!");
        }
    }
}
string getRandomWord(const string& filename)
{
    vector<string> words;
    string line;
    ifstream in(filename);
    if (not in.is_open() or in.bad()) {
        throw runtime_error("Can not open file!");
    }
    while (in >> line) {
        validateWord(line);
        words.push_back(line);
    }
    in.close();
    random_device device;
    mt19937 generator(device());
    uniform_int_distribution<unsigned long> distribution(0, words.size() - 1);
    return words[distribution(generator)];
}

void displayHangman(const int& mistakes)
{
    if (mistakes == 0) {
        mvprintw(
                0,
                1,
                "________    \n"
                "|       |   \n"
                "|           \n"
                "|           \n"
                "|           \n"
                "|           \n"
                "|_____      \n"
                "|     |___  \n"
                "|_________| \n");
    }
    switch (mistakes) {
    case 6:
        mvprintw(4, 9, "\\");
    case 5:
        mvprintw(4, 7, "/");
    case 4:
        mvprintw(3, 9, "\\");
    case 3:
        mvprintw(3, 7, "/");
    case 2:
        mvprintw(3, 8, "|");
    case 1:
        mvprintw(2, 8, "o");
    }
    if (mistakes == 6) {
        winLoseMessage(false);
    }
}

void winLoseMessage(const bool& isWin)
{
    clear();
    if (isWin) {
        printw(" __ __   ___   __ __      __    __  ____  ____   __ \n"
               "|  |  | /   \\ |  |  |    |  |__|  ||    ||    \\ |  |\n"
               "|  |  ||     ||  |  |    |  |  |  | |  | |  _  ||  |\n"
               "|  ~  ||  O  ||  |  |    |  |  |  | |  | |  |  ||__|\n"
               "|___, ||     ||  :  |    |  `  '  | |  | |  |  | __ \n"
               "|     ||     ||     |     \\      /  |  | |  |  ||  |\n"
               "|____/  \\___/  \\__,_|      \\_/\\_/  |____||__|__||__|\n"
               "                                                    \n"
               "");
    } else {
        printw("__   _______ _   _  ______ _____ ___________ \n"
               "\\ \\ / /  _  | | | | |  _  \\_   _|  ___|  _  \\\n"
               " \\ V /| | | | | | | | | | | | | | |__ | | | |\n"
               "  \\ / | | | | | | | | | | | | | |  __|| | | |\n"
               "  | | \\ \\_/ / |_| | | |/ / _| |_| |___| |/ / \n"
               "  \\_/  \\___/ \\___/  |___/  \\___/\\____/|___/  \n"
               "                                             \n"
               "                                             \n");
    }
    getch();
    endwin();
    exit(0);
}

void displayCells(const int& n)
{
    string cells, top;
    for (int i = 0; i < n; i++) {
        top += " _";
        cells += "|_";
    }
    mvprintw(10, 2, "%s", top.c_str());
    mvprintw(11, 2, "%s|", cells.c_str());
}
void printWord(
        bool& letterGuessed,
        const int& wordLength,
        const int& key,
        const string& hiddenWord,
        string& guessedWord)
{
    for (int index = 0, CharacterPos = 3; index < wordLength;
         index++, CharacterPos += 2) {
        if ((char)key == hiddenWord[index]) {
            guessedWord[index] = hiddenWord[index];
            letterGuessed = true;
            mvprintw(11, CharacterPos, "%c", hiddenWord[index]);
            if (guessedWord == hiddenWord) {
                winLoseMessage(true);
            }
        }
    }
}
void displayMissingLetters(const string& missingLetters)
{
    mvprintw(12, 2, "Missing Letters: ");
    for (char letter : missingLetters) {
        printw("%c  ", letter);
    }
}
void doNotRecountMistake(string& missingLetters, const int& key, int& mistakes)
{
    if (missingLetters.find((char)key) == string::npos) {
        missingLetters[mistakes] = (char)key;
        mistakes++;
    }
}
void playGame()
{
    initscr();
    noecho();
    curs_set(0);
    string hiddenWord = getRandomWord("words.txt");
    string missingLetters(6, ' ');
    int wordLength = (int)hiddenWord.size();
    string guessedWord(wordLength, ' ');
    int key, mistakes = 0;
    displayCells(wordLength);
    displayHangman(mistakes);
    while ((key = getch()) != 27) {
        bool letterGuessed = false;
        printWord(letterGuessed, wordLength, key, hiddenWord, guessedWord);
        if (not letterGuessed) {
            doNotRecountMistake(missingLetters, key, mistakes);
        }
        displayMissingLetters(missingLetters);
        displayHangman(mistakes);
    }
    endwin();
}