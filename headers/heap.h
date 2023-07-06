#ifndef HEAP_H
#define HEAP_H

#include "lista.h"
#include "aresta.h"

typedef struct _no_heap no_heap;

typedef struct _heap {
    no_heap * primeiro;
    no_heap * ultimo;
    int num_elementos;
}heap;

typedef struct _no_heap{
    aresta* Aresta;
    int pos;
    no_heap * prox;
    no_heap * ant;
} no_heap;

heap* heap_cria();
void heap_insere(heap* h, aresta* a);
aresta* heap_remove(heap* h);
void heap_testa();

#endif 
