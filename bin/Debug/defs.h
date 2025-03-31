#ifndef _DEFS_H
#define _DEFS_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <vector>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const char* WINDOW_TITLE = "Hangman Game";

// Danh sách từ bí ẩn
const std::vector<std::string> WORDS = {"HANGMAN", "PROGRAMMING", "SDL2", "CODEBLOCKS", "GAME"};

// Số lần đoán sai tối đa
const int MAX_WRONG_GUESSES = 6;

#endif
