#include "Dohoa.h"
#include "game.h"
using namespace std;

int main(int argc, char *argv[]) {
    DoHoa graphic;
    graphic.init();
    graphic.TaiHoatAnh();

    Hangman troChoi;
    troChoi.hangman();

    SDL_Event event;
    bool thoat = false;

    while (!thoat && !troChoi.isGameOver()) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                thoat = true;
            }

            if (event.type == SDL_KEYDOWN) {
                char ChuCai = event.key.keysym.sym;
                if (ChuCai >= 'a' && ChuCai <= 'z') ChuCai -= 32;
                if (ChuCai >= 'A' && ChuCai <= 'Z') {
                    troChoi.DoanChuCai(ChuCai);
                }
            }
        }

        SDL_SetRenderDrawColor(graphic.renderer, 255, 255, 255, 255);
        SDL_RenderClear(graphic.renderer);


        graphic.HienThiHoatAnh(troChoi.soLanDoanSai);


        SDL_Color b = {255, 0, 0};
        graphic.VeChuCai("Word: " + troChoi.tuDaDoan, 100, 100, b);
        graphic.VeChuCai("So Lan Doan Sai: " + to_string(troChoi.soLanDoanSai), 100, 150, b);

        string ChuCaiDaDoan(troChoi.ChuCaiDaDoan.begin(), troChoi.ChuCaiDaDoan.end());
        graphic.VeChuCai("Tu Da Doan: " + ChuCaiDaDoan, 100, 200, b);


        if (troChoi.isGameOver()) {
            if (troChoi.tuDaDoan == troChoi.Tucandoan) {
                graphic.VeChuCai("Ban Thang!", 100, 250, b);
            } else {
                graphic.VeChuCai("Ban Da Thua! Tu Chinh Xac La: " + troChoi.Tucandoan, 100, 250, b);
            }
            SDL_RenderPresent(graphic.renderer);
            SDL_Delay(3000);
            thoat = true;
        }

        SDL_RenderPresent(graphic.renderer);
        SDL_Delay(10);
    }

    graphic.quit();
    return 0;
}
