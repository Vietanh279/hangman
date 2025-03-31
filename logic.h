#ifndef _LOGIC_H
#define _LOGIC_H
using namespace std;
#include "defs.h"

struct Hangman {
    string secretWord;
    string guessedWord;
    int wrongGuesses;
    vector<char> guessedLetters;

    void init() {
        secretWord = WORDS[rand() % WORDS.size()];
        guessedWord = string(secretWord.length(), '_');
        wrongGuesses = 0;
        guessedLetters.clear();
    }

    bool guessLetter(char letter) {
        guessedLetters.push_back(letter);
        bool correct = false;
        for (size_t i = 0; i < secretWord.length(); i++) {
            if (secretWord[i] == letter) {
                guessedWord[i] = letter;
                correct = true;
            }
        }
        if (!correct) wrongGuesses++;
        return correct;
    }

    bool isGameOver() {
        return wrongGuesses >= MAX_WRONG_GUESSES || guessedWord == secretWord;
    }
};

#endif
