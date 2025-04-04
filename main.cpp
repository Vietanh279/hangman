#include "graphics.h"
#include "logic.h"
using namespace std;

int main(int argc, char *argv[]) {
    Graphics graphics;
    graphics.init();
    graphics.loadHangmanStages();

    Hangman game;
    game.init();

    SDL_Event event;
    bool quit = false;

    while (!quit && !game.isGameOver()) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }

            if (event.type == SDL_KEYDOWN) {
                char letter = event.key.keysym.sym;
                if (letter >= 'a' && letter <= 'z') letter -= 32;
                if (letter >= 'A' && letter <= 'Z') {
                    game.guessLetter(letter);
                }
            }
        }

        SDL_SetRenderDrawColor(graphics.renderer, 255, 255, 255, 255);
        SDL_RenderClear(graphics.renderer);


        graphics.renderHangman(game.wrongGuesses);


        SDL_Color textColor = {255, 0, 0};
        graphics.renderText("Word: " + game.guessedWord, 100, 100, textColor);
        graphics.renderText("Wrong guesses: " + to_string(game.wrongGuesses), 100, 150, textColor);

        string guessedLetters(game.guessedLetters.begin(), game.guessedLetters.end());
        graphics.renderText("Guessed letters: " + guessedLetters, 100, 200, textColor);


        if (game.isGameOver()) {
            if (game.guessedWord == game.secretWord) {
                graphics.renderText("You win!", 100, 250, textColor);
            } else {
                graphics.renderText("You lose! The word was: " + game.secretWord, 100, 250, textColor);
            }
            SDL_RenderPresent(graphics.renderer);
            SDL_Delay(3000);
            quit = true;
        }

        SDL_RenderPresent(graphics.renderer);
        SDL_Delay(10);
    }

    graphics.quit();
    return 0;
}
