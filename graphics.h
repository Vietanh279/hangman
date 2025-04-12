#ifndef _DOHOA_H
#define _DOHOA_H
using namespace std;
#include "Cauhinh.h"
#include <SDL_image.h>

struct DoHoa {
    SDL_Window* window;
    SDL_Renderer* renderer;
    TTF_Font* font;
    SDL_Texture* HoatAnh[7];

    void init() {
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
            KiemtraLoi("SDL_Init", SDL_GetError());
        }
        window = SDL_CreateWindow("Hangman",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,  800, 600, SDL_WINDOW_SHOWN);
        if (window == nullptr) {
            KiemtraLoi("CreateWindow", SDL_GetError());
        }
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (renderer == nullptr) {
            KiemtraLoi("CreateRenderer", SDL_GetError());
        }
        if (TTF_Init() == -1) {
            KiemtraLoi("TTF_Init", TTF_GetError());
        }
        font = TTF_OpenFont("assets/arial.ttf", 24);
        if (font == nullptr) {
            KiemtraLoi("TTF_OpenFont", TTF_GetError());
        }


        if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
            KiemtraLoi("IMG_Init", IMG_GetError());
        }
    }

    void VeChuCai(const string& chu, int x, int y, SDL_Color mau) {
        SDL_Surface* surface = TTF_RenderText_Solid(font, chu.c_str(), mau);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_Rect vitri = {x, y, surface->w, surface->h};
        SDL_RenderCopy(renderer, texture, nullptr, &vitri);
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
    }

    void TaiHoatAnh() {
        for (int i = 0; i < 7; i++) {
            string path = "assets/hangman_" + to_string(i) + ".png";
            SDL_Surface* surface = IMG_Load(path.c_str());
            if (!surface) {
                KiemtraLoi("IMG_Load", IMG_GetError());
            }
            HoatAnh[i] = SDL_CreateTextureFromSurface(renderer, surface);
            SDL_FreeSurface(surface);
        }
    }

    void HienThiHoatAnh(int a) {
        if (a < 0 || a >= 7) return;
        SDL_Rect vitri = {100, 300, 600, 388};
        SDL_RenderCopy(renderer, HoatAnh[a], nullptr, &vitri);
    }

    void quit() {
        for (int i = 0; i < 7; i++) {
            if (HoatAnh[i]) {
                SDL_DestroyTexture(HoatAnh[i]);
            }
        }
        TTF_CloseFont(font);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        IMG_Quit();
        TTF_Quit();
        SDL_Quit();
    }

    void KiemtraLoi(const char* msg, const char* error) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "%s: %s", msg, error);
        SDL_Quit();
        exit(1);
    }
};

#endif
