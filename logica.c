//LOGICA DO PROGRAMA
#include <stdio.h>
#include <stdlib.h>
#include "logica.h"
#include "dados.h"
#include "interface.h"


int pertence_as_jogadas(ESTADO *e, COORDENADA coord, int i){
    int result = 0;
    int x;

    for (x = 0; x < i; x++){
        if ((e->jogadas[x].jogador1.coluna == coord.coluna && e->jogadas[x].jogador1.linha == coord.linha )
            ||
            (e->jogadas[x].jogador2.coluna == coord.coluna && e->jogadas[x].jogador2.linha == coord.linha ))
            result = 1;
    }

    return result;
}


int validar_vitoria(ESTADO *e, COORDENADA coord){
    int coluna_jogada = obter_coluna(coord);
    int linha_jogada = obter_linha(coord);
    int jogador_atual = obter_jogador_atual(e);
    int result = 0;

    if (coluna_jogada == 7 && linha_jogada == 7) result = 2; //Canto superior direito
    if (coluna_jogada == 0 && linha_jogada == 0) result = 1; //Canto inferior esquerdo

//Lado superior do tabuleiro
    if (linha_jogada == 7) {
        if (coluna_jogada == 0
            && casa_livre(e, (COORDENADA) {coluna_jogada + 1, linha_jogada}) != 1
            && casa_livre(e, (COORDENADA) {coluna_jogada + 1, linha_jogada - 1}) != 1
            && casa_livre(e, (COORDENADA) {coluna_jogada, linha_jogada - 1}) != 1)
            result = jogador_atual;
        else if (casa_livre(e, (COORDENADA) {coluna_jogada + 1, linha_jogada    }) != 1 &&
                 casa_livre(e, (COORDENADA) {coluna_jogada + 1, linha_jogada - 1}) != 1 &&
                 casa_livre(e, (COORDENADA) {coluna_jogada    , linha_jogada - 1}) != 1 &&
                 casa_livre(e, (COORDENADA) {coluna_jogada - 1, linha_jogada - 1}) != 1 &&
                 casa_livre(e, (COORDENADA) {coluna_jogada - 1, linha_jogada    }) != 1)
            result = jogador_atual;
    }

//Lado inferior do tabuleiro
    if (linha_jogada == 0) {
        if (coluna_jogada == 7 &&
            casa_livre(e, (COORDENADA) {coluna_jogada - 1, linha_jogada}) != 1 &&
            casa_livre(e, (COORDENADA) {coluna_jogada - 1, linha_jogada + 1}) != 1 &&
            casa_livre(e, (COORDENADA) {coluna_jogada, linha_jogada + 1}) != 1)
            result = jogador_atual;
        else if (casa_livre(e, (COORDENADA) {coluna_jogada + 1, linha_jogada    }) != 1 &&
                 casa_livre(e, (COORDENADA) {coluna_jogada + 1, linha_jogada + 1}) != 1 &&
                 casa_livre(e, (COORDENADA) {coluna_jogada    , linha_jogada + 1}) != 1 &&
                 casa_livre(e, (COORDENADA) {coluna_jogada - 1, linha_jogada + 1}) != 1 &&
                 casa_livre(e, (COORDENADA) {coluna_jogada - 1, linha_jogada    }) != 1)
            result = jogador_atual;
    }

//Lado esquerdo do tabuleiro
    if (coluna_jogada == 0 &&
        casa_livre(e, (COORDENADA) {coluna_jogada + 1, linha_jogada    }) != 1 &&
        casa_livre(e, (COORDENADA) {coluna_jogada + 1, linha_jogada + 1}) != 1 &&
        casa_livre(e, (COORDENADA) {coluna_jogada    , linha_jogada + 1}) != 1 &&
        casa_livre(e, (COORDENADA) {coluna_jogada + 1, linha_jogada - 1}) != 1 &&
        casa_livre(e, (COORDENADA) {coluna_jogada    , linha_jogada - 1}) != 1)
        result = jogador_atual;

//Lado direito do tabuleiro
    if (coluna_jogada == 7 &&
        casa_livre(e, (COORDENADA) {coluna_jogada - 1, linha_jogada    }) != 1 &&
        casa_livre(e, (COORDENADA) {coluna_jogada - 1, linha_jogada + 1}) != 1 &&
        casa_livre(e, (COORDENADA) {coluna_jogada    , linha_jogada + 1}) != 1 &&
        casa_livre(e, (COORDENADA) {coluna_jogada - 1, linha_jogada - 1}) != 1 &&
        casa_livre(e, (COORDENADA) {coluna_jogada    , linha_jogada - 1}) != 1)
        result = jogador_atual;

//Caso em que o jogador fica rodeado de pecas pretas no "meio" do tabuleiro
    if (casa_livre(e,(COORDENADA) {coluna_jogada    , linha_jogada + 1}) != 1 &&
        casa_livre(e,(COORDENADA) {coluna_jogada + 1, linha_jogada + 1}) != 1 &&
        casa_livre(e,(COORDENADA) {coluna_jogada + 1, linha_jogada    }) != 1 &&
        casa_livre(e,(COORDENADA) {coluna_jogada + 1, linha_jogada - 1}) != 1 &&
        casa_livre(e,(COORDENADA) {coluna_jogada    , linha_jogada - 1}) != 1 &&
        casa_livre(e,(COORDENADA) {coluna_jogada - 1, linha_jogada - 1}) != 1 &&
        casa_livre(e,(COORDENADA) {coluna_jogada - 1, linha_jogada    }) != 1 &&
        casa_livre(e,(COORDENADA) {coluna_jogada - 1, linha_jogada + 1}) != 1)
        result = jogador_atual;

    return result;
}


int validar_jogada(ESTADO *e, COORDENADA coord){
    int result = 0;
    int coluna_atual = obter_coluna(obter_ultima_jogada(e));
    int linha_atual = obter_linha(obter_ultima_jogada(e));
    int coluna_jogada = obter_coluna(coord);
    int linha_jogada = obter_linha(coord);
    int x, y, z;

    //Verifica se o jogador está a jogar para a vizinhaça da peça atual
    x = abs(coluna_atual - coluna_jogada) <= 1 && abs(linha_atual - linha_jogada) <= 1;

    //Verifica se a peça para a qual o jogador pretende jogar esta livre (VAZIO)
    y = casa_livre(e, coord);

    //Verifica se a coordenada jogada pelo jogador não coincide com a peça atual
    z = coluna_atual != coluna_jogada || linha_atual != linha_jogada;

    if (x && y && z) result = 1;
    return result;
}


int jogar(ESTADO *e, COORDENADA coord){
    int valida = validar_jogada(e,coord);
    int vitoria = validar_vitoria(e,coord);
    COORDENADA peca_branca = obter_ultima_jogada(e);

    if (valida == 1) {  atualiza_jogadas(e, coord); //Controlo da informacao sobre as jogadas
                        atualiza_jogador_atual(e); //Troca de jogador
                        atualiza_num_jogadas(e); //Controlo do numero de jogadas
                        atualiza_casa(e, peca_branca, PRETA); //A peca que antes era BRANCA passa a ser PRETA
                        atualiza_casa(e, coord, BRANCA); //A casa onde o jogador joga passa a ser BRANCA
                        atualiza_ultima_jogada(e, coord); //A ultima jogada passa a ser a jogada acabada de efetuar
                     }
    else mostrar_erro(JOGADA_INVALIDA);

    if (vitoria != 0 && valida == 1){
        mostrar_tabuleiro(e);
        mostrar_vitoria(vitoria);
        return 0;
    }

    return 1;
}