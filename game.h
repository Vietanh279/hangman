#ifndef _GAME_H
#define _GAME_H
using namespace std;
#include "Cauhinh.h"

struct Hangman {
    string Tucandoan;
    string tuDaDoan;
    int soLanDoanSai;
    vector<char> ChuCaiDaDoan;

    void hangman() {
        Tucandoan = CacTuTrongGame[rand() % CacTuTrongGame.size()];
        tuDaDoan = string(Tucandoan.length(), '_');
        soLanDoanSai = 0;
        ChuCaiDaDoan.clear();
    }

    bool DoanChuCai(char ChuCai) {
        ChuCaiDaDoan.push_back(ChuCai);
        bool correct = false;
        for (size_t i = 0; i < Tucandoan.length(); i++) {
            if (Tucandoan[i] == ChuCai) {
                tuDaDoan[i] = ChuCai;
                correct = true;
            }
        }
        if (!correct) soLanDoanSai++;
        return correct;
    }

    bool isGameOver() {
        return soLanDoanSai >= soLanDoanSaiToiDa || tuDaDoan == Tucandoan;
    }
};

#endif
