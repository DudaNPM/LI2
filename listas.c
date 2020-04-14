#include "listas.h"
#include <stdlib.h>


LISTA criar_lista(){
    LISTA l = malloc(sizeof(NODO));
    l->valor = NULL;
    return l;
}


LISTA insere_cabeca(LISTA L, void *valor){
    LISTA l2 = malloc(sizeof(NODO));
    l2->valor = valor;
    l2->proximo = L;
    return l2;
}


void *devolve_cabeca(LISTA L){
    return L->valor;
}


LISTA proximo(LISTA L){
    return L->proximo;
}


LISTA remove_cabeca(LISTA L){
    LISTA l2 = NULL;
    if (L){
        l2 = L->proximo;
        free(L);
    }
    return l2;
}


int lista_esta_vazia(LISTA L){
    if (devolve_cabeca(L) == NULL) return 1;
    else return 0;
}


int length(LISTA L){
    int counter = 0;
    while (!lista_esta_vazia(L)){
        counter++;
        L = proximo(L);
    }
    return counter;
}













