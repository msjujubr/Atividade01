#ifndef CONFIG_HPP
#define CONFIG_HPP

#include "archives.hpp"
#include <algorithm> 
#include <sstream> 
#include <random>
#include <utility>

struct Config {
    int iteracoes = 1000;

    bool vntD = 0;
    bool vntE = 0;
    bool vntC = 0;
    bool vntB = 0;

    std::vector<std::vector<int>> floresta;
    std::vector<std::pair<int, int>> arvores_queimando;

    int n, m;
    int animPosX, animPosY, animMov, animCont, animMort;
    bool animVid;
};

extern Config config;

int defVento();
void configuracoes();
void inicio_animal();

void propagacao();
void prop(int x, int y, std::vector<std::pair<int,int>>& auxiliar);

void save_game();

#endif