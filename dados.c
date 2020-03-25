#include <stdlib.h>
#include "dados.h"

void atualiza_jogadas(ESTADO *e, COORDENADA coord){
    int i = e->jogador_atual;

    if (i == 1){
        e->jogadas[e->num_jogadas].jogador1.coluna = coord.coluna;
        e->jogadas[e->num_jogadas].jogador1.linha = coord.linha;
    }
    else {
        e->jogadas[e->num_jogadas].jogador2.coluna = coord.coluna;
        e->jogadas[e->num_jogadas].jogador2.linha = coord.linha;
    }
}


void atualiza_num_jogadas(ESTADO *e){
    int player = obter_jogador_atual(e);
    if (player == 1) e->num_jogadas++;
}


void atualiza_jogador_atual(ESTADO *e){
    int player = obter_jogador_atual(e);
    if (player == 1) e->jogador_atual = 2;
    else e->jogador_atual = 1;;
}


void atualiza_ultima_jogada(ESTADO *e, COORDENADA coord){
    e->ultima_jogada = coord;
}


void atualiza_nova_peca(ESTADO *e, COORDENADA coord){
    e->tab[coord.coluna][coord.linha] = BRANCA;
}


void atualiza_ultima_peca(ESTADO *e){
    e->tab[e->ultima_jogada.coluna][e->ultima_jogada.linha] = PRETA;
}


int casa_livre(ESTADO *e, COORDENADA coord){
    int result = 0;
    if (obter_estado_casa(e,coord) == VAZIO) result = 1;
    return result;
}


int obter_num_jogadas(ESTADO *e){
    return e->num_jogadas;
}


int obter_jogador_atual(ESTADO *e){
    return e->jogador_atual;
}


int obter_estado_casa(ESTADO *e, COORDENADA coord){
    return e->tab[coord.coluna][coord.linha];
}


ESTADO *inicializar_estado(){

    int coluna, linha;
    ESTADO *e = (ESTADO *) malloc(sizeof(ESTADO));
    e->jogador_atual = 1;
    e->num_jogadas = 0;
    e->ultima_jogada = (COORDENADA) {4,4};

    for (linha = 0; linha < 8; linha++){
        for (coluna = 0; coluna < 8; coluna++)
            e->tab[coluna][linha] = VAZIO;
    }
    e->tab[4][4] = BRANCA;

    return e;
}











