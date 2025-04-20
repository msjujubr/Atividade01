#ifndef SIMULATOR_HPP
#define SIMULATOR_HPP

#include "config.hpp"

void inicializacao();

void animal_movim();
void animal_agua();
void schrodinger();
void escape();

int soma_pos(int x, int y);
bool atividade_fogo();
bool fog_prox(int x, int y);

#endif