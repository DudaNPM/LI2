//CAMADA DA INTERFACE
#include <stdio.h>
#include <string.h>
#include "dados.h"
#include "logica.h"
#include "interface.h"
#define BUF_SIZE 1024


int controlo_comando = 0;
int controlo_comando2 = 0;
int maior_num_jogadas = 0;


int jog2(ESTADO *e){

    //Escolhe a jogada para a casa mais próxima do objetivo
    COORDENADA nova = distancia_euclidiana(e);

    return jogar(e,nova);
}


int jog(ESTADO *e){

    //Escolhe uma jogada aleatória
    COORDENADA nova = escolha_aleatoria(e);

    return jogar(e,nova);
}


void pos(ESTADO *e, int jogada, int maior_jogada){
    int jog = obter_num_jogadas(e);

    if (jog >= maior_jogada) maior_num_jogadas = jog;

    if (jogada <= maior_num_jogadas && jogada <= jog) atualiza_estado2(e, jogada);
    else if (jogada <= maior_num_jogadas || jogada >= jog) atualiza_estado3(e, jogada);
    else {
        mostrar_erro(JOGADA_INVALIDA);
        controlo_comando2++;
    }
}


void movs(ESTADO *e) {
    int jogador = obter_jogador_atual(e); //Numero do jogador atual
    int jogadas = obter_num_jogadas(e); //Numero do jogadas efetuadas
    int i;

    for (i = 0; i < jogadas; i++) {

        if (i < 9) printf("0%d: ", i + 1);
        else printf("%d: ", i + 1);

        int coluna = obter_coluna(obter_coord(e, i, 1)) + 'a';
        int linha = obter_linha(obter_coord(e, i, 1)) + 1;
        printf("%c%d ", coluna, linha);

        int coluna2 = obter_coluna(obter_coord(e, i, 2)) + 'a';
        int linha2 = obter_linha(obter_coord(e, i, 2)) + 1;
        printf("%c%d", coluna2, linha2);

        putchar('\n');
    }

    if (jogador == 2) {
        if (jogadas < 9) printf("0%d: ", i + 1);
        else printf("%d: ", i + 1);

        int coluna = obter_coluna(obter_coord(e, i, 1)) + 'a';
        int linha = obter_linha(obter_coord(e, i, 1)) + 1;
        printf("%c%d ", coluna, linha);
        putchar('\n');
    }
}


void gravar_jogadas(ESTADO *e, FILE *fp){
    int jogador = obter_jogador_atual(e); //Numero do jogador atual
    int jogadas = obter_num_jogadas(e); //Numero do jogadas efetuadas
    int i;

    for (i = 0; i < jogadas; i++) {

        if (i < 9) fprintf(fp, "0%d: ", i + 1);
        else fprintf(fp, "%d: ", i + 1);

        int coluna = obter_coluna(obter_coord(e, i, 1)) + 'a';
        int linha = obter_linha(obter_coord(e, i, 1)) + 1;
        fprintf(fp, "%c%d", coluna, linha);

        int coluna2 = obter_coluna(obter_coord(e, i, 2)) + 'a';
        int linha2 = obter_linha(obter_coord(e, i, 2)) + 1;
        fprintf(fp, " %c%d", coluna2, linha2);

        fputc('\n', fp);
    }

    if (jogador == 2){
        if (jogadas < 9) fprintf(fp, "0%d: ", i + 1);
        else fprintf(fp, "%d: ", i + 1);

        int coluna = obter_coluna(obter_coord(e, i, 1)) + 'a';
        int linha = obter_linha(obter_coord(e, i, 1)) + 1;
        fprintf(fp, "%c%d", coluna, linha);

        fputc('\n', fp);
    }
}


void gravar_tabuleiro(ESTADO *e, FILE *fp){
    int linha, coluna, i;

    for (linha = i = 7; linha >= 0; linha--, i--){
        for (coluna = 0; coluna < 8; coluna++){
            if (coluna == 0 && linha == 0) fprintf(fp, "1");
            else if (coluna == 7 && linha == 7) fprintf(fp, "2");
            else if (obter_estado_casa(e, (COORDENADA) {coluna,linha}) == BRANCA) fprintf(fp, "*");
            else if (obter_estado_casa(e, (COORDENADA) {coluna,linha}) == PRETA) fprintf(fp, "#");
            else fprintf(fp, ".");
        }
        if (i != 0) fputc('\n', fp);
    }

    fputc('\n', fp);
}


void gravar(ESTADO *e, char ficheiro[]){
    FILE *fPointer = fopen(ficheiro, "w");
    gravar_tabuleiro(e, fPointer);
    fputc('\n', fPointer);
    gravar_jogadas(e, fPointer);
    fclose(fPointer);
}


void ler(char ficheiro[], ESTADO *e){
    FILE *fPointer = fopen(ficheiro, "r");
    atualiza_estado(fPointer, e);
    fclose(fPointer);
}


void mostrar_erro(ERROS erro){
    char *possiveis_erros[] = { "OK",
                                "Jogada inválida, tenta outra vez.",
                                "Coordenada inválida, tenta outra vez.",
                                "Comando não reconhecido, tenta outra vez."
    };
    if (erro != OK) printf("%s\n\n\n", possiveis_erros[erro]);
}


void mostrar_vitoria(int jogador){
    printf("Parabéns Player%d, ganhou este jogo!!!\n", jogador);
}


void mostrar_prompt(ESTADO *e){

    int jog_atual = obter_jogador_atual(e);
    int num_jogadas = obter_num_jogadas(e);

    printf("#(Jogada_%d) Player_%d faça a sua jogada> ", num_jogadas, jog_atual);
}


void mostrar_tabuleiro(ESTADO *e)
{
    int linha, coluna, i;

    putchar('\n');
    printf("            a  b  c  d  e  f  g  h\n");
    printf("           __ __ __ __ __ __ __ __\n");

    for (linha = i = 7; linha >= 0; linha--, i--){
        printf("       %d  | ", i+1);
        for (coluna = 0; coluna < 8; coluna++){
            if (coluna == 0 && linha == 0) printf("1  ");
            else if (coluna == 7 && linha == 7) printf("2  ");
            else if (obter_estado_casa(e, (COORDENADA) {coluna,linha}) == BRANCA) printf("*  ");
            else if (obter_estado_casa(e, (COORDENADA) {coluna,linha}) == PRETA) printf("#  ");
            else printf(".  ");
        }
        putchar('\n');
    }

    putchar('\n');
}


int interpretador(ESTADO *e) {
    char linha[BUF_SIZE];
    char col[2], lin[2];
    int result = 1;
    char comando[BUF_SIZE];
    int aux_comando[BUF_SIZE];
    char ficheiro[BUF_SIZE];


    //O jogador introduziu um comando na jogada anterior, logo não faz sentido mostrar o tab novamente
    if (controlo_comando + 1 == controlo_comando2) {
        mostrar_prompt(e);
        controlo_comando++;
    }
    //O jogador nao introduziu um comando na jogada anterior
    else {
        mostrar_tabuleiro(e);
        mostrar_prompt(e);
    }


    if(fgets(linha, BUF_SIZE, stdin) == NULL)
        result = 0;


    //O jogador introduz um comando
    if(strlen(linha) == 2) {
        //Comando "Q" para sair do jogo
        if (sscanf(linha, "%[Q]", comando) == 1) {
            result = 0;
        }
        //Comando inválido de 1 letra
        else {
            mostrar_erro(COMANDO_INVALIDO);
            controlo_comando2++;
        }
    }


    //O jogador intoduz uma coordenada ou comando
    if (strlen(linha) == 3) {
        //Coordenada válida
        if (sscanf(linha, "%[a-h]%[1-8]", col, lin) == 2) {
            COORDENADA coord = {*col - 'a', *lin - '1'};
            result = jogar(e, coord);
            putchar('\n');
            putchar('\n');
        }
        //Coordenada inválida
        else if (sscanf(linha, "%[a-z]%[0-9]", col, lin) == 2) {
            mostrar_erro(COORDENADA_INVALIDA);
        }
        //Comando invalido de 2 letras
        else {
            mostrar_erro(COMANDO_INVALIDO);
            controlo_comando2++;
        }
    }


    //O jogador introduz um comando
    if (strlen(linha) > 3) {
        //Comando "gr"
        if (sscanf(linha, "gr %s", ficheiro) == 1) {
            gravar(e, ficheiro);
            controlo_comando2++;
        }
        //Comando "ler"
        else if (sscanf(linha, "ler %s", ficheiro) == 1) {
            ler(ficheiro, e);
            result = 1;
        }
        //Comando "movs"
        else if (strcmp(linha,"movs\n") == 0) {
            putchar('\n');
            movs(e);
            putchar('\n');
            controlo_comando2++;
        }
        //Comando "pos"
        else if (sscanf(linha, "pos %d", aux_comando) == 1) {
            pos(e, *aux_comando, maior_num_jogadas);
            result = 1;
        }
        //Comando "jog"
        else if (strcmp(linha,"jog\n") == 0) {
            result = jog(e);
        }
        //Comando "jog2"
        else if (strcmp(linha,"jog2\n") == 0) {
            result = jog2(e);
        }
        else {
            mostrar_erro(COMANDO_INVALIDO);
            controlo_comando2++;
        }
    }


    return result;
}