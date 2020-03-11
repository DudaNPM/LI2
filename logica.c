//LOGICA DO PROGRAMA
#include <stdio.h>
#include "logica.h"
#include "dados.h"

int jogar(ESTADO *e, COORDENADA c)
{
    printf("jogar %d %d\n", c.coluna, c.linha);
    return 1;
}