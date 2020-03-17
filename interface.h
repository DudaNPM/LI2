//CAMADA DA INTERFACE
#ifndef PROJETO_RASTROS_INTERFACE_H
#define PROJETO_RASTROS_INTERFACE_H

#include "dados.h"


void mostrar_tabuleiro(ESTADO *e);
void mostrar_prompt(ESTADO *e);
int interpretador(ESTADO *e);
void mostrar_erro(ERROS erro);
void mostrar_vitoria(int jogador);

#endif //PROJETO_RASTROS_INTERFACE_H
