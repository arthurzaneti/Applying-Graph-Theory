#ifndef HEAP_H
#define HEAP_H

#include "lista.h"

typedef struct no_heap {
    aresta* aresta_heap;
    struct no_heap* prox;
} no_heap;

typedef struct {
    no_heap* primeiro;
    int tamanho;
} heap;

heap* heap_cria();
void heap_insere(heap* h, aresta* a);
double remover_minimo(heap* h);
void heap_testa();

#endif 
