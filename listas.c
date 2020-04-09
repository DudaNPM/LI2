#include "listas.h"
#include <stdlib.h>


LISTA criar_lista(){
    LISTA l = malloc(sizeof(NODO));
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
    LISTA l2;
    l2 = L->proximo;
    return l2;
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
    if (L->valor == NULL) return 1;
    else return 0;
}
















