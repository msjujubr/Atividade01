#ifndef SIMULATOR_HPP
#define SIMULATOR_HPP

#include "config.hpp"

bool atividade_fogo();
bool fog_prox(int x, int y);

int soma_pos(int x, int y);

void inicializacao();

void schrodinger();
void animal();
void movimentacao_animal();
void animal_agua();

#endif