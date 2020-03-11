//CAMADA DA INTERFACE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUF_SIZE 1024
#include "interface.h"
#include "dados.h"
#include "logica.h"

void mostrar_tabuleiro(ESTADO *e)
{
    int linha, coluna;
    for (linha = 0; linha < 8; linha++){
        for (coluna = 0; coluna < 8; coluna++){
            if (coluna == 0 && linha == 7) printf("1  ");
            else if (coluna == 7 && linha == 0) printf("2  ");
            else if (e->tab[coluna][linha] == BRANCA) printf("*  ");
            else if (e->tab[coluna][linha] == PRETA) printf("#  ");
            else printf(".  ");
        }
        putchar('\n');
    }
}


int interpretador(ESTADO *e) {
    char linha[BUF_SIZE];
    char col[2], lin[2];
    if(fgets(linha, BUF_SIZE, stdin) == NULL)
        return 0;
    if(strlen(linha) == 3 && sscanf(linha, "%[a-h]%[1-8]", col, lin) == 2) {
        COORDENADA coord = {*col - 'a', *lin - '1'};
        jogar(e, coord);
        mostrar_tabuleiro(e);
    }
    return 1;
}