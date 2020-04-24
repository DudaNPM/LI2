/**
@file listas.h
Definição de listas
*/

#ifndef ___LISTAS_H___
#define ___LISTAS_H___

typedef struct nodo {
    void *valor;
    struct nodo *proximo;
} NODO, *LISTA;


/**
\brief Calcula o comprimento de uma lista
@param L A lista
@returns O comprimento
*/
int length(LISTA L);


/**
\brief Cria uma lista vazia
@returns Uma lista vazia
*/
LISTA criar_lista();


/**
\brief Insere um valor na cabeça da lista
@param L A lista
@param valor Apontador para o valor
@returns A lista L com o "valor" na cabeça da lista
*/
LISTA insere_cabeca(LISTA L, void *valor);


/**
\brief Devolve a cabeça da lista
@param L A lista
*/
void *devolve_cabeca(LISTA L);


/**
\brief Devolve a cauda da lista
@param L A lista
@return A lista L sem o primeiro elemento
*/
LISTA proximo(LISTA L);

/**
\brief Remove a cabeça da lista (libertando o espaço ocupado) e devolve a cauda
@param L A lista
@return A lista L sem o primeiro elemento
*/
LISTA remove_cabeca(LISTA L);

/**
\brief Verifica se uma lista está vazia
@param L A lista
@return Valor 1 se vazia, 0 caso contrário
*/
int lista_esta_vazia(LISTA L);


#endif //___LISTAS_H___