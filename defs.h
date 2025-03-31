#ifndef _DEFS_H
#define _DEFS_H
using namespace std;
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <vector>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const char* WINDOW_TITLE = "Hangman Game";

const vector<string> WORDS = {"HANGMAN", "PROGRAMMING", "SDL2", "CODEBLOCKS", "GAME"};

const int MAX_WRONG_GUESSES = 6;

#endif
