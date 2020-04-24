//LOGICA DO PROGRAMA
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "dados.h"
#include "interface.h"
#include "listas.h"
#include "logica.h"


COORDENADA distancia_euclidiana(ESTADO *e){
    //Posição da peça branca
    COORDENADA pos_atual = obter_ultima_jogada(e);

    //Lista com as posições vizinhas da peça branca livres
    LISTA pos_vizinhas = armaneza_pos_viz(e, pos_atual);

    //Jogador atual
    int jog_atual = obter_jogador_atual(e);

    COORDENADA coordenada_mais_proxima = get_coord_mais_prox(pos_vizinhas, jog_atual);

    return coordenada_mais_proxima;
}


COORDENADA get_coord_mais_prox(LISTA casas_livres, int jogador_atual){
    double menor_dist = 100;
    COORDENADA coord_mais_proxima;

    while (!lista_esta_vazia(casas_livres)) {
        //Casa livre
        COORDENADA *c = (COORDENADA *) devolve_cabeca(casas_livres);

        //Distancia entre a casa em questao e a casa vencedora do jogador atual
        double dist = calcula_distancia(*c, jogador_atual);

        //Update da lista de casas livres
        casas_livres = proximo(casas_livres);

        //Update da coordenada mais proxima
        if (dist < menor_dist){
            menor_dist = dist;
            coord_mais_proxima = *c;
        }
    }

    return coord_mais_proxima;
}


double calcula_distancia(COORDENADA c, int jogador_atual){
    double dist;
    int coluna = obter_coluna(c);
    int linha = obter_linha(c);

    if(jogador_atual == 1)
        dist = sqrt(pow(coluna, 2) + pow(linha, 2));
    else
        dist = sqrt(pow(7 - coluna, 2) + pow(7 - linha, 2));

    return dist;
}


COORDENADA escolha_aleatoria(ESTADO *e){

    //Posição da peça branca
    COORDENADA pos_atual = obter_ultima_jogada(e);

    //Lista com as posições vizinhas da peça branca livres
    LISTA pos_vizinhas = armaneza_pos_viz(e, pos_atual);
    int comp = length(pos_vizinhas);

    //Indice aleatorio para a escolha da coordenada
    srandom(time(NULL));
    int i = (rand() % comp);

    //Avança na lista ate ao indice criado
    while (i > 0){
        pos_vizinhas = proximo(pos_vizinhas);
        i--;
    }

    COORDENADA *c = (COORDENADA *) devolve_cabeca(pos_vizinhas);

    return *c;
}


LISTA armaneza_pos_viz(ESTADO *e, COORDENADA coord){
    LISTA pos_vizinhas = criar_lista();
    int coluna = obter_coluna(coord);
    int linha = obter_linha(coord);
    int c = coluna, l = linha;

    // 3 casas de cima da peça branca
    COORDENADA *c1 = duplica_coordenada((COORDENADA) {c-1,l+1});
    COORDENADA *c2 = duplica_coordenada((COORDENADA) {c,l+1});
    COORDENADA *c3 = duplica_coordenada((COORDENADA) {c+1,l+1});
    if (casa_livre(e, *c1)) pos_vizinhas = insere_cabeca(pos_vizinhas, c1);
    if (casa_livre(e, *c2)) pos_vizinhas = insere_cabeca(pos_vizinhas, c2);
    if (casa_livre(e, *c3)) pos_vizinhas = insere_cabeca(pos_vizinhas, c3);

    // Casa do lado direito da peça branca
    COORDENADA *c4 = duplica_coordenada((COORDENADA) {c+1,l});
    if (casa_livre(e, *c4)) pos_vizinhas = insere_cabeca(pos_vizinhas, c4);

    // 3 casas de baixo da peça branca
    COORDENADA *c5 = duplica_coordenada((COORDENADA) {c+1,l-1});
    COORDENADA *c6 = duplica_coordenada((COORDENADA) {c,l-1});
    COORDENADA *c7 = duplica_coordenada((COORDENADA) {c-1,l-1});
    if (casa_livre(e, *c5)) pos_vizinhas = insere_cabeca(pos_vizinhas, c5);
    if (casa_livre(e, *c6)) pos_vizinhas = insere_cabeca(pos_vizinhas, c6);
    if (casa_livre(e, *c7)) pos_vizinhas = insere_cabeca(pos_vizinhas, c7);

    // Casa do lado esquerdo da peça branca
    COORDENADA *c8 = duplica_coordenada((COORDENADA) {c-1,l});
    if (casa_livre(e, *c8)) pos_vizinhas = insere_cabeca(pos_vizinhas, c8);

    return pos_vizinhas;
}


COORDENADA* duplica_coordenada(COORDENADA c){
    COORDENADA *c_clone = malloc(sizeof(COORDENADA));
    int coluna_c = obter_coluna(c);
    int linha_c = obter_linha(c);

    set_coluna(c_clone, coluna_c);
    set_linha(c_clone, linha_c);

    return c_clone;
}


int pertence_as_jogadas(ESTADO *e, COORDENADA coord, int i){
    int result = 0;
    int x; //Variavel para o controlo do indice da lista de jogadas

    //Percorre a lista de jogadas ate ao indice x
    for (x = 0; x < i; x++){
        COORDENADA casa_jogador1 = obter_coord(e, x, 1);
        COORDENADA casa_jogador2 = obter_coord(e, x, 2);
        //Se a coordenada pertencer a lista a variavel result é alterada para 1
        if (compara_coordenadas(coord, casa_jogador1) ||
            compara_coordenadas(coord, casa_jogador2))
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