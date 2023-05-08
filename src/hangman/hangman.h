#ifndef HANGMAN_H
#define HANGMAN_H

#include <fstream>
#include <iostream>
#include <ncurses.h>
#include <random>
#include <vector>

void displayHangman();
void winLoseMessage(const bool& isWin);

#endif
