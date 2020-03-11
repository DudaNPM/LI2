//CAMADA DE DADOS
#ifndef PROJETO_RASTROS_DADOS_H
#define PROJETO_RASTROS_DADOS_H


typedef enum {VAZIO, BRANCA, PRETA} CASA;
/*
   Vazio = 0
   Branca = 1
   Preta = 2
*/


typedef struct {
    int coluna;
    int linha;
} COORDENADA;


typedef struct {
    COORDENADA jogador1;
    COORDENADA jogador2;
} JOGADA;


typedef JOGADA JOGADAS[32];


typedef struct {
    CASA tab[8][8]; //Array de 8 elementos, em que cada elemento contem um array de 8 elementos do tipo CASA (0,1,2)
    COORDENADA ultima_jogada;
    JOGADAS jogadas;
    int num_jogadas;
    int jogador_atual;
} ESTADO;


ESTADO *inicializar_estado();



















#endif //PROJETO_RASTROS_DADOS_H
