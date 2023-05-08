#ifndef HANGMAN_H
#define HANGMAN_H

#include <fstream>
#include <iostream>
#include <ncurses.h>
#include <random>
#include <vector>

using namespace std;

void displayHangman();
void winLoseMessage(const bool& isWin);
string getRandomWord(const string& filename);
void displayCells(const int& n);

#endif
