//CAMADA DE DADOS
#include <stdlib.h>
#include "dados.h"




ESTADO *inicializar_estado(){

    int coluna, linha;
    ESTADO *e = (ESTADO *) malloc(sizeof(ESTADO));
    e->jogador_atual = 1;
    e->num_jogadas = 0;
    e->ultima_jogada = (COORDENADA) {4,4};
    //e->jogadas = (JOGADAS){};

    for (linha = 0; linha < 8; linha++){
        for (coluna = 0; coluna < 8; coluna++){
            if (coluna == 4 && linha == 3) e->tab[coluna][linha] = BRANCA;
            else e->tab[coluna][linha] = VAZIO;
        }
    }

    return e;
}