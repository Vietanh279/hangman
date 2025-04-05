#ifndef _GRAPHICS_H
#define _GRAPHICS_H
using namespace std;
#include "defs.h"
#include <SDL_image.h>

struct Graphics {
    SDL_Window* window;
    SDL_Renderer* renderer;
    TTF_Font* font;
    SDL_Texture* hangmanStages[7];

    void init() {
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
            logErrorAndExit("SDL_Init", SDL_GetError());
        }
        window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == nullptr) {
            logErrorAndExit("CreateWindow", SDL_GetError());
        }
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (renderer == nullptr) {
            logErrorAndExit("CreateRenderer", SDL_GetError());
        }
        if (TTF_Init() == -1) {
            logErrorAndExit("TTF_Init", TTF_GetError());
        }
        font = TTF_OpenFont("assets/arial.ttf", 24);
        if (font == nullptr) {
            logErrorAndExit("TTF_OpenFont", TTF_GetError());
        }


        if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
            logErrorAndExit("IMG_Init", IMG_GetError());
        }
    }

    void renderText(const string& text, int x, int y, SDL_Color color) {
        SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_Rect dest = {x, y, surface->w, surface->h};
        SDL_RenderCopy(renderer, texture, nullptr, &dest);
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
    }

    void loadHangmanStages() {
        for (int i = 0; i < 7; i++) {
            string path = "assets/hangman_" + to_string(i) + ".png";
            SDL_Surface* surface = IMG_Load(path.c_str());
            if (!surface) {
                logErrorAndExit("IMG_Load", IMG_GetError());
            }
            hangmanStages[i] = SDL_CreateTextureFromSurface(renderer, surface);
            SDL_FreeSurface(surface);
        }
    }

    void renderHangman(int stage) {
        if (stage < 0 || stage >= 7) return;
        SDL_Rect dest = {100, 300, 600, 388};
        SDL_RenderCopy(renderer, hangmanStages[stage], nullptr, &dest);
    }

    void quit() {
        for (int i = 0; i < 7; i++) {
            if (hangmanStages[i]) {
                SDL_DestroyTexture(hangmanStages[i]);
            }
        }
        TTF_CloseFont(font);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        IMG_Quit();
        TTF_Quit();
        SDL_Quit();
    }

    void logErrorAndExit(const char* msg, const char* error) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "%s: %s", msg, error);
        SDL_Quit();
        exit(1);
    }
};

#endif
