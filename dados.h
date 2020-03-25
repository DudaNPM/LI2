/**
@file dados.h
Definição do estado e das funções que o manipulam
*/

#ifndef ___DADOS_H___
#define ___DADOS_H___

#include <stdio.h>

/**
\brief Tipo de dados para a casa
*/
typedef enum {VAZIO,  // = 0
              BRANCA, // = 1
              PRETA   // = 2
} CASA;


/**
\brief Tipo de dados para as coordenadas
*/
typedef struct {
    int coluna;
    int linha;
} COORDENADA;


/**
\brief Tipo de dados para a jogada
*/
typedef struct {
    COORDENADA jogador1;
    COORDENADA jogador2;
} JOGADA;


/**
\brief Tipo de dados para as jogadas
*/
typedef JOGADA JOGADAS[32];


/**
\brief Tipo de dados para o estado
*/
typedef struct {
    /** O tabuleiro */
    CASA tab[8][8];
    /** As jogadas */
    JOGADAS jogadas;
    /** O número das jogadas, usado no prompt */
    int num_jogadas;
    /** O jogador atual */
    int jogador_atual;
    /** A coordenada da última jogada */
    COORDENADA ultima_jogada;
} ESTADO;


/**
\brief Tipo de dados para os erros
*/
typedef enum {OK,                  // = 0
              JOGADA_INVALIDA,     // = 1
              COORDENADA_INVALIDA, // = 2
              COMANDO_INVALIDO     // = 3
} ERROS;


/**
\brief Atualiza o estado do jogo guardado num ficheiro
@param fPointer Apontador para o ficheiro
*/
void atualiza_estado(FILE *fPointer, ESTADO *e);


/**
\brief Atualiza a lista de jogadas
@param e Apontador para o estado
@param coord Apontador para a última jogada
*/
void atualiza_jogadas(ESTADO *e, COORDENADA coord);


/**
\brief Atualiza o numero de jogadas
@param e Apontador para o estado
*/
void atualiza_num_jogadas(ESTADO *e);


/**
\brief Atualiza o numero do jogador atual
@param e Apontador para o estado
*/
void atualiza_jogador_atual(ESTADO *e);


/**
\brief Atualiza o estado da ultima jogada
@param e Apontador para o estado
@param coord A coordenada
*/
void atualiza_ultima_jogada(ESTADO *e, COORDENADA coord);


/**
\brief Muda o valor da casa de coordenadas coord para BRANCA
@param e Apontador para o estado
@param coord A coordenada
*/
void atualiza_nova_peca(ESTADO *e, COORDENADA coord);


/**
\brief Atualiza o estado da ultima peça jogada para PRETA
@param e Apontador para o estado
*/
void atualiza_ultima_peca(ESTADO *e);


/**
\brief Verifica se uma casa é do tipo VAZIO
@param e Apontador para o estado
@param c A coordenada
@returns O valor 1 se for VAZIO, 0 caso contrário
*/
int casa_livre(ESTADO *e, COORDENADA coord);


/**
\brief Devolve o num de jogadas efetuadas
@param e Apontador para o estado
@returns O num de jogadas
*/
int obter_num_jogadas(ESTADO *e);


/**
\brief Devolve o num do jogador que deve jogar
@param e Apontador para o estado
@param c A coordenada
@returns O valor da jogador
*/
int obter_jogador_atual(ESTADO *e);

/**
\brief Devolve o valor de uma casa
@param e Apontador para o estado
@param coord A coordenada
@returns O valor da casa
*/
int obter_estado_casa(ESTADO *e, COORDENADA coord);

/**
\brief Inicializa o valor do estado
@returns O novo estado
*/
ESTADO *inicializar_estado();

#endif
