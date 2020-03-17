//CAMADA DE DADOS
#include <stdlib.h>
#include "dados.h"




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


int obter_estado_casa(ESTADO *e, COORDENADA coord){
    return e->tab[coord.coluna][coord.linha];
}

int obter_jogador_atual(ESTADO *e){
    return e->jogador_atual;
}

int obter_num_jogadas(ESTADO *e){
    return e->num_jogadas;
}

//Verifica se uma casa é do tipo VAZIO
int casa_livre(ESTADO *e, COORDENADA coord){
    int result = 0;
    if (obter_estado_casa(e,coord) == VAZIO) result = 1;
    return result;
}

//Altera o estado da casa da ultima peca jogada para PRETA
void atualiza_ultima_peca(ESTADO *e){
    e->tab[e->ultima_jogada.coluna][e->ultima_jogada.linha] = PRETA;
}

//Altera o estado da casa para o qual o jogador pretende jogar para BRANCA
void atualiza_nova_peca(ESTADO *e, COORDENADA coord){
    e->tab[coord.coluna][coord.linha] = BRANCA;
}

//Altera o estado da ultima jogada
void atualiza_ultima_jogada(ESTADO *e, COORDENADA coord){
    e->ultima_jogada = coord;
}

//Atualiza o numero do jogador atual
void atualiza_jogador_atual(ESTADO *e){
    int player = obter_jogador_atual(e);
    if (player == 1) e->jogador_atual = 2;
    else e->jogador_atual = 1;;
}

//Atualiza o numero de jogadas
void atualiza_num_jogadas(ESTADO *e){
    int player = obter_jogador_atual(e);
    if (player == 1) e->num_jogadas++;
}











