#ifndef HANGMAN_H
#define HANGMAN_H

#include <fstream>
#include <iostream>
#include <ncurses.h>
#include <random>
#include <string>
#include <vector>

using namespace std;

void displayHangman(const int& mistakes);
void winLoseMessage(const bool& isWin);
string getRandomWord(const string& filename);
void displayCells(const int& n);
void printWord(
        bool& letterGuessed,
        const int& wordLength,
        const int& key,
        const string& hiddenWord,
        string& guessedWord);
void displayMissingLetters(const string& missingLetters);
void playGame();

#endif
