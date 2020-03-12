//LOGICA DO PROGRAMA
#include <stdio.h>
#include "logica.h"
#include "dados.h"

int jogar(ESTADO *e, COORDENADA c)
{
//Altera o estado da tabela de acordo com a coordenada 'c' (jogada) para BRANCA
    e->tab[c.coluna][c.linha] = BRANCA;
    return 1;
}