/**
@file logica.h
Definição de funções que tratam da lógica do programa
*/

#ifndef ___LOGICA_H___
#define ___LOGICA_H___

#include "dados.h"
#include "listas.h"

/**
\brief Escolhe uma CASA livre na vizinhança da peça branca
@param e Apontador para o estado
@returns Coordenada aleatória
*/
COORDENADA escolha_aleatoria(ESTADO *e);


/**
\brief Verifica se as casas em volta da peça branca estão livres
@param e Apontador para o estado
@param coord Apontador para a coordenada
@returns Lista com as casas livres
*/
LISTA armaneza_pos_viz(ESTADO *e, COORDENADA coord);


/**
\brief Verifica se uma coordenada pertence ao arreio de jogadas
@param e Apontador para o estado
@param coord Apontador para a coordenada
@param i O índice do arreio
@returns Valor 1 se pertencer ao arreio, 0 caso contrário
*/
int pertence_as_jogadas(ESTADO *e, COORDENADA coord, int i);


/**
\brief Verifica se algum dos jogadores ganhou o jogo
@param e Apontador para o estado
@param coord Apontador para a coordenada
@returns Valor 1 ou 2 consoante o jogador vencedor
*/
int validar_vitoria(ESTADO *e, COORDENADA coord);

/**
\brief Verifica a jogada é válida ou não
@param e Apontador para o estado
@param coord Apontador para a coordenada
@returns Valor 1 se a jogada for válida, 0 caso contrário
*/
int validar_jogada(ESTADO *e, COORDENADA coord);

/**
\brief Dá continuidade ao jogo
@param e Apontador para o estado
@param coord Apontador para a coordenada
@returns Valor 0 se o jogo acabar, 1 caso contrário
*/
int jogar(ESTADO *e, COORDENADA c);

#endif