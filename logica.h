//LOGICA DO PROGRAMA
#ifndef PROJETO_RASTROS_LOGICA_H
#define PROJETO_RASTROS_LOGICA_H

#include "dados.h"

int jogar(ESTADO *e, COORDENADA c);
int validar_jogada(ESTADO *e, COORDENADA coord);
int validar_vitoria(ESTADO *e, COORDENADA coord);

#endif //PROJETO_RASTROS_LOGICA_H