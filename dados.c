//CAMADA DE DADOS
#include <stdlib.h>
#include "dados.h"




ESTADO *inicializar_estado()
{
    int coluna, linha;
    ESTADO *e = (ESTADO *) malloc(sizeof(ESTADO));
    e->jogador_atual = 1;
    e->num_jogadas = 0;
    e->jogadas->jogador1.linha = 1;
    e->jogadas->jogador1.coluna = 1;
    e->jogadas->jogador2.linha = 8;
    e->jogadas->jogador2.coluna = 8;
//8ª linha do tabuleiro
    for (coluna = 0; coluna < 7; coluna++) e->tab[7][coluna] = VAZIO;
    e->tab[7][7] = '2';
//7ª e 6ª linha do tabuleiro
    for (linha = 6; linha >= 5; linha--)
    {
        for (coluna = 0; coluna < 8; coluna++) e->tab[linha][coluna] = VAZIO;
    }
//5ª linha do tabuleiro
    for (coluna = 0; coluna < 4; coluna++) e->tab[7][coluna] = VAZIO;
    e->tab[4][4] = BRANCA;
    for (coluna = 5; coluna < 8; coluna++) e->tab[7][coluna] = VAZIO;
//4ª a 2ª linha do tabuleiro
    for (linha = 3; linha >= 1; linha--)
    {
        for (coluna = 0; coluna < 8; coluna++) e->tab[linha][coluna] = VAZIO;
    }
//1ª linha do tabuleiro
    for (coluna = 1; coluna < 8; coluna++) e->tab[7][coluna] = VAZIO;
    e->tab[0][0] = '1';

    return e;
}
