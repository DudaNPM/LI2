//LOGICA DO PROGRAMA
#include <stdio.h>
#include "logica.h"
#include "dados.h"

//Altera o estado da tabela de acordo com a coordenada 'coord' (jogada) para BRANCA
int jogar(ESTADO *e, COORDENADA coord)
{
    e->tab[coord.coluna][coord.linha] = BRANCA;
    return 1;
}