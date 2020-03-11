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

    if (e->num_jogadas == 0)
    {
//8ª linha do tabuleiro
        for (coluna = 1; coluna <= 7; coluna++) putchar('.');
        putchar('2');
        putchar('\n');

//7ª e 6ª linha do tabuleiro
        for (linha=7; linha >= 6; linha--)
        {
            for (coluna = 1; coluna <= 8; coluna++) putchar('.');
            putchar('\n');
        }

//5ª linha do tabuleiro (com a peca branca na posicao 'e5')
        for (coluna = 1; coluna <= 4; coluna++) putchar('.');
        putchar('*');
        for (coluna = 6; coluna <= 8; coluna++) putchar('.');
        putchar('\n');

//4ª a 2ª linhas do tabuleiro
        for (linha = 4; linha >= 2; linha--)
        {
            for (coluna = 1; coluna <= 8; coluna++) putchar('.');
            putchar('\n');
        }

//1ª linha do tabuleiro
        putchar('1');
        for (coluna = 2; coluna <= 8; coluna++) putchar('.');
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