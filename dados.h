//CAMADA DE DADOS
#ifndef PROJETO_RASTROS_DADOS_H
#define PROJETO_RASTROS_DADOS_H


typedef enum {VAZIO,  // = 0
              BRANCA, // = 1
              PRETA   // = 2
} CASA;


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


typedef enum {OK,                 // = 0
              JOGADA_INVALIDA,    // = 1
              COORDENADA_INVALIDA // = 2
} ERROS;


ESTADO *inicializar_estado();

int obter_estado_casa(ESTADO *e, COORDENADA coord);

int obter_jogador_atual(ESTADO *e);

int obter_num_jogadas(ESTADO *e);

int casa_livre(ESTADO *e, COORDENADA coord);

void atualiza_ultima_peca(ESTADO *e);

void atualiza_nova_peca(ESTADO *e, COORDENADA coord);

void atualiza_ultima_jogada(ESTADO *e, COORDENADA coord);

void atualiza_jogador_atual(ESTADO *e);

void atualiza_num_jogadas(ESTADO *e);


















#endif //PROJETO_RASTROS_DADOS_H
