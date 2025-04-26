#ifndef CONFIG_HPP
#define CONFIG_HPP

#include "archives.hpp"
#include <algorithm> 
#include <sstream> 
#include <random>
#include <utility>

struct Config {
    // Variáveis Personalizáveis
    int iteracoes = 100;
    bool vntD = 0, vntE = 0, vntC = 0, vntB = 0;

    // Variáveis Globais
    std::vector<std::vector<int>> floresta;
    std::vector<std::pair<int, int>> arv_1_2, arv_2_3;
    int n, m, animX, animY, animMov, animCnt, animMrt;
    bool animVid;
};

extern Config cnfg;

int defVento();

void configuracoes();
void propagacao();
void salvar();
void relatorio();

bool atividade_fogo();
void inicio_animal();
void prop(int x, int y, std::vector<std::pair<int,int>>& auxiliar);
void queimadas();

#endif