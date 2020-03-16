//LOGICA DO PROGRAMA
#include <stdio.h>
#include <stdlib.h>
#include "logica.h"
#include "dados.h"
#include "interface.h"


int validar_jogada(ESTADO *e, COORDENADA coord){
    int result = 0;
    int coluna_atual = e->ultima_jogada.coluna;
    int linha_atual = e->ultima_jogada.linha;
    int coluna_jogada = coord.coluna;
    int linha_jogada = coord.linha;
    int x, y;

    x = abs(coluna_atual - coluna_jogada) <= 1 && abs(linha_atual - linha_jogada) <= 1;
    y = obter_estado_casa(e, coord) == VAZIO;

    if (x && y) result = 1;
    return result;
}


int validar_vitoria(ESTADO *e, COORDENADA coord){
    int coluna_jogada = coord.coluna;
    int linha_jogada = coord.linha;
    int jogador_atual = e->jogador_atual;
    int result = 0;

    if (coluna_jogada == 7 && linha_jogada == 7) result = 2; //Canto superior direito
    if (coluna_jogada == 0 && linha_jogada == 0) result = 1; //Canto inferior esquerdo

//Lado superior do tabuleiro
    if (linha_jogada == 7) {
        if (coluna_jogada == 0
            && obter_estado_casa(e, (COORDENADA) {coluna_jogada + 1, linha_jogada}) != 0
            && obter_estado_casa(e, (COORDENADA) {coluna_jogada + 1, linha_jogada - 1}) != 0
            && obter_estado_casa(e, (COORDENADA) {coluna_jogada, linha_jogada - 1}) != 0)
            result = jogador_atual;
        else if (obter_estado_casa(e, (COORDENADA) {coluna_jogada + 1, linha_jogada    }) == PRETA &&
                 obter_estado_casa(e, (COORDENADA) {coluna_jogada + 1, linha_jogada - 1}) == PRETA &&
                 obter_estado_casa(e, (COORDENADA) {coluna_jogada    , linha_jogada - 1}) == PRETA &&
                 obter_estado_casa(e, (COORDENADA) {coluna_jogada - 1, linha_jogada - 1}) == PRETA &&
                 obter_estado_casa(e, (COORDENADA) {coluna_jogada - 1, linha_jogada    }) == PRETA)
            result = jogador_atual;
    }

//Lado inferior do tabuleiro
    if (linha_jogada == 0) {
        if (coluna_jogada == 7
            && obter_estado_casa(e, (COORDENADA) {coluna_jogada - 1, linha_jogada}) != 0
            && obter_estado_casa(e, (COORDENADA) {coluna_jogada - 1, linha_jogada + 1}) != 0
            && obter_estado_casa(e, (COORDENADA) {coluna_jogada, linha_jogada + 1}) != 0)
            result = jogador_atual;
        else if (obter_estado_casa(e, (COORDENADA) {coluna_jogada + 1, linha_jogada    }) != 0 &&
                 obter_estado_casa(e, (COORDENADA) {coluna_jogada + 1, linha_jogada + 1}) != 0 &&
                 obter_estado_casa(e, (COORDENADA) {coluna_jogada    , linha_jogada + 1}) != 0 &&
                 obter_estado_casa(e, (COORDENADA) {coluna_jogada - 1, linha_jogada + 1}) != 0 &&
                 obter_estado_casa(e, (COORDENADA) {coluna_jogada - 1, linha_jogada    }) != 0)
            result = jogador_atual;
    }

//Lado esquerdo do tabuleiro
    if (coluna_jogada == 0 &&
        obter_estado_casa(e, (COORDENADA) {coluna_jogada + 1, linha_jogada    }) != 0 &&
        obter_estado_casa(e, (COORDENADA) {coluna_jogada + 1, linha_jogada + 1}) != 0 &&
        obter_estado_casa(e, (COORDENADA) {coluna_jogada    , linha_jogada + 1}) != 0 &&
        obter_estado_casa(e, (COORDENADA) {coluna_jogada + 1, linha_jogada - 1}) != 0 &&
        obter_estado_casa(e, (COORDENADA) {coluna_jogada    , linha_jogada - 1}) != 0)
        result = jogador_atual;

//Lado direito do tabuleiro
    if (coluna_jogada == 7 &&
        obter_estado_casa(e, (COORDENADA) {coluna_jogada - 1, linha_jogada    }) != 0 &&
        obter_estado_casa(e, (COORDENADA) {coluna_jogada - 1, linha_jogada + 1}) != 0 &&
        obter_estado_casa(e, (COORDENADA) {coluna_jogada    , linha_jogada + 1}) != 0 &&
        obter_estado_casa(e, (COORDENADA) {coluna_jogada - 1, linha_jogada - 1}) != 0 &&
        obter_estado_casa(e, (COORDENADA) {coluna_jogada    , linha_jogada - 1}) != 0)
        result = jogador_atual;

//Caso em que o jogador fica rodeado de pecas pretas no "meio" do tabuleiro
    if (obter_estado_casa(e,(COORDENADA) {coluna_jogada    , linha_jogada + 1}) != 0 &&
        obter_estado_casa(e,(COORDENADA) {coluna_jogada + 1, linha_jogada + 1}) != 0 &&
        obter_estado_casa(e,(COORDENADA) {coluna_jogada + 1, linha_jogada    }) != 0 &&
        obter_estado_casa(e,(COORDENADA) {coluna_jogada + 1, linha_jogada - 1}) != 0 &&
        obter_estado_casa(e,(COORDENADA) {coluna_jogada    , linha_jogada - 1}) != 0 &&
        obter_estado_casa(e,(COORDENADA) {coluna_jogada - 1, linha_jogada - 1}) != 0 &&
        obter_estado_casa(e,(COORDENADA) {coluna_jogada - 1, linha_jogada    }) != 0 &&
        obter_estado_casa(e,(COORDENADA) {coluna_jogada - 1, linha_jogada + 1}) != 0)
        result = jogador_atual;

    return result;
}



int jogar(ESTADO *e, COORDENADA coord)
{
    int player = obter_jogador_atual(e);
    COORDENADA ultima_jogada = e->ultima_jogada;
    int valida = validar_jogada(e,coord);
    int vitoria = validar_vitoria(e,coord);

    if (vitoria != 0){
//Altera o estado da casa da ultima peca jogada
        e->tab[ultima_jogada.coluna][ultima_jogada.linha] = PRETA;
//Altera o estado da casa para o qual o jogador pretende jogar
        e->tab[coord.coluna][coord.linha] = BRANCA;
        mostrar_tabuleiro(e);
        printf("#Parabéns Player%d, ganhou este jogo!!!\n", vitoria);
        return 0;
    }

    if (valida == 1){
//Troca de jogador & controlo do numero de jogadas
        if (player == 1) {
            e->jogador_atual = 2;
            e->num_jogadas++;
        } else e->jogador_atual = 1;

//Altera o estado da casa da ultima peca jogada
        e->tab[ultima_jogada.coluna][ultima_jogada.linha] = PRETA;

//Altera o estado da casa para o qual o jogador pretende jogar
        e->tab[coord.coluna][coord.linha] = BRANCA;

//Altera o estado da ultima jogada
        e->ultima_jogada = coord;
    }

    else printf("#Este valor não é uma jogada válida, tenta outra vez.\n\n\n");

    return 1;
}