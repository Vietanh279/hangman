#ifndef _GRAPHICS_H
#define _GRAPHICS_H

#include "defs.h"

struct Graphics {
    SDL_Window* window;
    SDL_Renderer* renderer;
    TTF_Font* font;

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
    }

    void renderText(const std::string& text, int x, int y, SDL_Color color) {
        SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_Rect dest = {x, y, surface->w, surface->h};
        SDL_RenderCopy(renderer, texture, nullptr, &dest);
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
    }

    void quit() {
        TTF_CloseFont(font);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
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
