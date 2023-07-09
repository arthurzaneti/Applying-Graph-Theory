#ifndef _LISTA_H_
#define _LISTA_H_
#include "aresta.h"
#include <stdbool.h>

//implementação de lista duplamente encadeada generica, ou seja,  pointers para void*.
//alguns campos estão aqui porque foram usados para implementar grafos depois, mas podem ser removidos

typedef struct no no;
typedef struct lista{
    no* primeiro;
    no* ultimo;
    int num_elementos;
    int elemento_de_partida;
}lista;

typedef struct no{
    void* data;
    no* prox;
    no* ant;
}no;

lista* lista_cria();
no* no_cria(void*data);

void lista_insere(lista*l, no* elem, int pos);
void* lista_remove(lista *l, int pos);
no* lista_pega_elemento(lista* l, int pos);

void lista_destroi(lista *l);

#endif