//CAMADA DA INTERFACE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUF_SIZE 1024
#include "dados.h"
#include "logica.h"


int controlo_comando = 0;
int controlo_comando2 = 0;


void gravar_tabuleiro(ESTADO *e, FILE *fp){
    int linha, coluna, i;

    fputc('\n', fp);
    fprintf(fp, "            a  b  c  d  e  f  g  h\n");
    fprintf(fp, "           __ __ __ __ __ __ __ __\n");

    for (linha = i = 7; linha >= 0; linha--, i--){
        fprintf(fp, "       %d  | ", i+1);
        for (coluna = 0; coluna < 8; coluna++){
            if (coluna == 0 && linha == 0) fprintf(fp, "1  ");
            else if (coluna == 7 && linha == 7) fprintf(fp, "2  ");
            else if (obter_estado_casa(e, (COORDENADA) {coluna,linha}) == BRANCA) fprintf(fp, "*  ");
            else if (obter_estado_casa(e, (COORDENADA) {coluna,linha}) == PRETA) fprintf(fp, "#  ");
            else fprintf(fp, ".  ");
        }
        fputc('\n', fp);
    }

    fputc('\n', fp);
}


void gravar(ESTADO *e, char ficheiro[]){
    FILE *fPointer = fopen(ficheiro, "w");
    gravar_tabuleiro(e, fPointer);
    fclose(fPointer);
}


void ler(char ficheiro[]){
    FILE *fPointer = fopen(ficheiro, "r");
    char single_line[50];

    while (!feof(fPointer)){
        fgets(single_line, 50, fPointer);
        puts(single_line);
    }

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
    char quit[1];
    char ficheiro[20];


    //O jogador escreveu um comando na jogada anterior, logo não faz sentido mostrar o tab novamente
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
        //O jogador usa o comando "Q" para sair do jogo
        if (sscanf(linha, "%[Q]", quit) == 1) {
            result = 0;
        }
        //O jogador usa um comando inválido de 1 letra apenas
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
        //O jogador introduz o comandos "gr"
        if (sscanf(linha, "gr %s", ficheiro) == 1) {
            gravar(e, ficheiro);
            controlo_comando2++;
        }
        //O jogador introduz o comandos "ler"
        else if (sscanf(linha, "ler %s", ficheiro) == 1) {
            ler(ficheiro);
            controlo_comando2++;
        }
        else {
            mostrar_erro(COMANDO_INVALIDO);
            controlo_comando2++;
        }
    }


    return result;
}