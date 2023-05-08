#include "hangman.h"
using namespace std;

string getRandomWord(const string& filename)
{
    vector<string> words;
    string line;
    ifstream in(filename);
    while (in >> line) {
        words.push_back(line);
    }
    in.close();
    random_device device;
    mt19937 generator(device());
    uniform_int_distribution<unsigned long> distribution(0, words.size() - 1);
    return words[distribution(generator)];
}
void displayHangman()
{
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