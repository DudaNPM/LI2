#include <stdlib.h>
#include <stdio.h>
#include "dados.h"
#define BUF_SIZE 1024

void atualiza_estado(FILE *fPointer, ESTADO *e){
    int coluna, linha;
    char line[BUF_SIZE];

    for (linha = 7; linha >= 0; linha--){
        fgets(line, BUF_SIZE, fPointer);
        for (coluna = 0; coluna < 8; coluna++) {
            if (line[coluna] == '*'){
                atualiza_casa(e, (COORDENADA) {coluna, linha}, BRANCA);
                atualiza_ultima_jogada(e, (COORDENADA) {coluna, linha});
            }
            else if (line[coluna] == '#') atualiza_casa(e, (COORDENADA) {coluna, linha}, PRETA);
            else atualiza_casa(e, (COORDENADA) {coluna, linha}, VAZIO);
        }
    }

    int counter = 0;
    while (fgetc(fPointer)!= EOF) counter++;
    if (counter%2 == 0) e->jogador_atual = 2;
    else e->jogador_atual = 1;

    e->num_jogadas = (counter-1) / 10;

}


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


void atualiza_casa(ESTADO *e, COORDENADA coord, CASA c){
    e->tab[coord.coluna][coord.linha] = c;
}


int casa_livre(ESTADO *e, COORDENADA coord){
    int result = 0;
    if (obter_estado_casa(e,coord) == VAZIO) result = 1;
    return result;
}


int obter_linha(COORDENADA coord){
    return coord.linha;
}


int obter_coluna(COORDENADA coord){
    return coord.coluna;
}


COORDENADA obter_coord(ESTADO *e, int i, int j){
    if (j == 1) return e->jogadas[i].jogador1;
    else return e->jogadas[i].jogador2;
}


COORDENADA obter_ultima_jogada(ESTADO *e){
    return e->ultima_jogada;
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











