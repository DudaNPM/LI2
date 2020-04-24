#include <stdlib.h>
#include <stdio.h>
#include "dados.h"
#include "logica.h"
#define BUF_SIZE 1024


void atualiza_estado3(ESTADO *e, int jogada) {

    COORDENADA c1 = obter_coord(e, jogada-1, 1);
    COORDENADA c2 = obter_coord(e, jogada-1, 2);


    if (c2.linha == 0 && c2.coluna == 0){
        set_jogador_atual(e, 2);
        set_ultima_jogada(e, c1);
        set_num_jogadas(e, jogada - 1);
        atualiza_casa(e, c1, BRANCA);
    }
    else{
        set_jogador_atual(e, 1);
        set_ultima_jogada(e, c2);
        set_num_jogadas(e, jogada);
        atualiza_casa(e, c1, PRETA);
        atualiza_casa(e, c2, BRANCA);

    }

    int coluna, linha;
    for (linha = 7; linha >= 0; linha--) {
        for (coluna = 0; coluna <= 7; coluna++) {
            if (pertence_as_jogadas(e, (COORDENADA) {coluna, linha}, jogada - 1))
                atualiza_casa(e, (COORDENADA) {coluna, linha}, PRETA);
        }
    }

    atualiza_casa(e, (COORDENADA) {4, 4}, PRETA);
}


void atualiza_estado2(ESTADO *e, int jogada) {

    set_jogador_atual(e, 1);

    if (jogada != 0) {
        COORDENADA coord = obter_coord(e, jogada - 1, 2);
        set_ultima_jogada(e, coord);
        set_num_jogadas(e, jogada);
        atualiza_casa(e, coord, BRANCA);

        int coluna, linha;
        for (linha = 7; linha >= 0; linha--) {
            for (coluna = 0; coluna <= 7; coluna++) {
                if (!pertence_as_jogadas(e, (COORDENADA) {coluna, linha}, jogada))
                    atualiza_casa(e, (COORDENADA) {coluna, linha}, VAZIO);
            }
        }
        atualiza_casa(e, (COORDENADA) {4, 4}, PRETA);
    }
    else{
        set_num_jogadas(e, jogada);
        set_ultima_jogada(e, (COORDENADA) {4,4});

        int coluna, linha;
        for (linha = 7; linha >= 0; linha--) {
            for (coluna = 0; coluna <= 7; coluna++) {
                    atualiza_casa(e, (COORDENADA) {coluna, linha}, VAZIO);
            }
        }
        atualiza_casa(e, (COORDENADA) {4, 4}, BRANCA);
    }
}


void atualiza_estado(FILE *fPointer, ESTADO *e){
    int coluna, linha;
    char line[BUF_SIZE];


    //Lê o tabuleiro
    for (linha = 7; linha >= 0; linha--){
        fgets(line, BUF_SIZE, fPointer);
        for (coluna = 0; coluna <= 7; coluna++) {
            if (line[coluna] == '*'){
                atualiza_casa(e, (COORDENADA) {coluna, linha}, BRANCA);
                atualiza_ultima_jogada(e, (COORDENADA) {coluna, linha});
            }
            else if (line[coluna] == '#') atualiza_casa(e, (COORDENADA) {coluna, linha}, PRETA);
            else atualiza_casa(e, (COORDENADA) {coluna, linha}, VAZIO);
        }
    }


    //Lê as informações relativas às jogadas, o num_jogadas e o jog_atual
    char line2[BUF_SIZE];
    int i = -1;
    while (fgets(line2, BUF_SIZE, fPointer) != NULL) {
        int num_jog;
        char c1, c2;
        int l1, l2;
        int num_tokens = sscanf(line2, "%d: %c%d %c%d", &num_jog, &c1, &l1, &c2, &l2);

        if(num_tokens == 5) {
            set_num_jogadas(e, num_jog);
            set_jogador_atual(e, 1);

            COORDENADA coord1 = form_coord(c1, l1);
            COORDENADA coord2 = form_coord(c2, l2);

            set_jogadas(e, coord1, coord2, i);
            i++;
        }
        else {
            set_num_jogadas(e, num_jog - 1);
            set_jogador_atual(e, 2);

            COORDENADA coord1 = form_coord(c1, l1);
            COORDENADA coord2 = {-1, -1};

            set_jogadas(e, coord1, coord2, i);
            i++;
        }
    }
}


COORDENADA form_coord(char coluna, int linha){
    COORDENADA c;
    c.coluna = coluna - 'a';
    c.linha = linha - 1;
    return c;
}


void set_ultima_jogada(ESTADO *e, COORDENADA coord){
    e->ultima_jogada = coord;
}


void set_jogadas(ESTADO *e, COORDENADA coord1, COORDENADA coord2, int i){
    e->jogadas[i].jogador1.coluna = coord1.coluna;
    e->jogadas[i].jogador1.linha = coord1.linha;
    e->jogadas[i].jogador2.coluna = coord2.coluna;
    e->jogadas[i].jogador2.linha = coord2.linha;
}


void set_num_jogadas(ESTADO *e, int n){
    e->num_jogadas = n;
}


void set_jogador_atual(ESTADO *e, int n){
    e->jogador_atual = n;
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
    if (coord.coluna >= 0 && coord.coluna <= 7 &&
        coord.linha  >= 0 && coord.linha  <= 7 &&
        obter_estado_casa(e,coord) == VAZIO      )
        result = 1;
    return result;
}


int compara_coordenadas(COORDENADA coord1, COORDENADA coord2){
    int result = 0;

    if (coord1.coluna == coord2.coluna &&
        coord1.linha  == coord2.linha)
        result = 1;

    return result;
}


void set_linha(COORDENADA* coord, int linha){
    coord->linha = linha;
}


void set_coluna(COORDENADA* coord, int coluna){
    coord->coluna = coluna;
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











