/**
@file interface.h
Definição de funções que tratam da interção ecrã/jogador
*/

#ifndef ____INTERFACE_H___
#define ____INTERFACE_H___

#include "dados.h"
#include <stdio.h>


void movs(ESTADO *e);

/**
\brief Print do tabuleiro no ficheiro especifcado
@param e Apontador para o estado
@param fp Apontador para o ficheiro
*/
void gravar_tabuleiro(ESTADO *e, FILE *fp);


/**
\brief Print do tabuleiro, guardado em "ficheiro", no ecrã
@param ficheiro Apontador para o nome do ficherio
@return O estado que se encontrava no ficheiro
*/
ESTADO *ler(char ficheiro[]);


/**
\brief Guarda o estado  tabuleiro no ficheiro especifcado
@param e Apontador para o estado
@param ficheiro Apontador para o nome do ficheiro
*/
void gravar(ESTADO *e, char ficheiro[]);

/**
\brief Print do erro cometido pelo jogador
@param erro Apontador para o erro cometido
*/
void mostrar_erro(ERROS erro);


/**
\brief Print do jogador vencedor
@param jogador Apontador para o jogador vitorioso
*/
void mostrar_vitoria(int jogador);


/**
\brief Print de um promt personalizado
@param e Apontador para o estado
*/
void mostrar_prompt(ESTADO *e);


/**
\brief Print do tabuleiro
@param e Apontador para o estado
*/
void mostrar_tabuleiro(ESTADO *e);


/**
\brief Leitura de comandos ou jogadas
@param e Apontador para o estado
@returns O valor 1 se for para continuar o jogo, 0 caso contrário
*/
int interpretador(ESTADO *e);

#endif
