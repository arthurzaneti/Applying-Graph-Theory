#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../headers/heap.h"
#include <assert.h>

heap* heap_cria(){
    heap* h = malloc(sizeof(heap));
    if(h==NULL){
        printf("Falha no malloc: Erro em heap_cria");
        return NULL;
    }
    h->num_elementos = 0;
    return h; 
}

static no_heap *pega_elem_pos(heap*h, int pos){

    if(h==NULL){
        printf("Erro em pega_elem_pos: heap nula");
        return NULL;
    }
    if(h->num_elementos == 0){
        printf("Erro em pega_elem_pos: heap vazia");
    }
    if (pos < 0){
        pos += h->num_elementos;
    }
    if (pos <0 || pos >= h->num_elementos){
        return NULL;
    }
    no_heap* no_atual = h->primeiro;
    int contador = 0;
    while(no_atual != NULL){
        if(contador == pos){
            return no_atual;
            break;
        }
        contador++;
        no_atual=no_atual->prox;
    }
    printf("Erro inesperado em pega elemento da fila heap");
    return NULL;

}

static void troca_prim_ult(heap* h, no_heap* n1, no_heap* n2) {
    if (n1->prox == n2) {
        n1->ant = n2;
        n1->prox = NULL;
        n2->prox = n1;
        n2->ant = NULL;

        h->primeiro = n2;
        h->ultimo = n1;

        n1->pos = 1;
        n2->pos = 0;
    } else {
        no_heap* segundo = n1->prox;
        no_heap* penultimo = n2->ant;

        penultimo->prox = n1;
        segundo->ant = n2;

        n1->ant = penultimo;
        n1->prox = NULL;
        n2->prox = segundo;
        n2->ant = NULL;


        h->primeiro = n2;
        h->ultimo = n1;

        n1->pos = n2->pos;
        n2->pos = 0;
    }
}


static void troca_prim (heap*h, no_heap* n1, no_heap* n2){
    if (n1->prox == n2){

        n2->prox->ant = n1;
        n2->ant = NULL;
        n1->ant = n2;
        n1->prox = n2->prox;
        n2->prox = n1;

        h->primeiro = n2;

        n2-> pos = 0;
        n1-> pos = 1;

    }else{
        no_heap * segundo = n1->prox;

        n2->prox->ant = n1;
        n2->ant->prox = n1;

        n1->prox = n2->prox;
        n1->ant = n2->ant;

        n2->ant = NULL;
        n2->prox = segundo;

        segundo->ant = n2;

        h->primeiro = n2;
        n1->pos = n2->pos;
        n2->pos = 0;
    }

}

static void troca_ult (heap*h, no_heap* n1, no_heap* n2){

    if(n2->ant == n1){
        n1->ant->prox = n2;
        n1->prox = NULL;
        n2->ant = n1->ant;
        n1->ant = n2;
        n2->prox = n1;

        h->ultimo = n1;

        n2->pos = h->num_elementos -2;
        n2->pos = h->num_elementos -1;

    }
    no_heap * penultimo = n2->ant;

    n1->prox->ant = n2;
    n1->ant->prox = n2;

    n2->prox = n1->prox;
    n2->ant = n1->ant;

    n1->prox = NULL;
    n1->ant = penultimo;

    penultimo->prox = n1;

    h->ultimo = n1;

    n2->pos = n1->pos;
    n1->pos = h->num_elementos - 1;

}

static void troca(heap*h, no_heap*n1, no_heap* n2){

    assert(n1 !=n2);

    if(h == NULL){
        printf("Erro em troca na heap: heap nula");
        return;
    }
    if(n1 == NULL || n2 == NULL){
        printf("Erro em troca na heap: nos nulos");
        return;
    }

    

    if(n1->ant == NULL){
        if(n2->prox == NULL){
            troca_prim_ult(h, n1, n2);

        }else{
            troca_prim(h, n1, n2);
        }
    }

    else if(n2->ant == NULL){
        if(n1->prox == NULL){
            troca_prim_ult(h, n2, n1);

        }else{
            troca_prim(h, n2, n1);
        }
    }
    else if(n2->prox == NULL){
        troca_ult(h, n1, n2);
    }
    else if(n1->prox == NULL){
        troca_ult(h, n2, n1);
    }

    else{
        no_heap* n1_ant = n1->ant;
        no_heap* n1_prox = n1->prox;

        n1->prox = n2->prox;
        n1->ant = n2->ant;

        n2->prox->ant = n1;
        n2->ant->prox = n1;

        n1_ant->prox = n2;
        n1_prox->ant = n2;
    
        n2->ant = n1_ant;
        n2->prox = n1_prox;

        int pos_aux = n2->pos;

        n2->pos = n1->pos;
        n1->pos = pos_aux;
    }
}

static void corrige_subindo(heap*h, no_heap* n){

    no_heap* pai = pega_elem_pos(h, (n->pos-1)/2);
    if(n->pos == 0) return;
    if(pai->Aresta->peso > n->Aresta->peso){
        troca(h, pai, n);
        corrige_subindo(h, n);
    }
}

static void heap_insere_vazia(heap*h, no_heap*n){
    h->primeiro = h->ultimo = n;
    n->pos = 0;
    n->ant = n->prox = NULL;
    h->num_elementos++;
}

void heap_insere(heap* h, aresta* Aresta){

    if(h == NULL){
        printf("Erro na inserção na heap: heap nulo");
    }
    if(Aresta == NULL){
        printf("Erro na inserção na heap: aresta nula");

    }
    no_heap* novo_no = malloc(sizeof(no_heap));
    if(novo_no ==NULL){
        printf("Falha no malloc: erro na alocação do no_heap");
    }
    novo_no->Aresta = Aresta;
    
    if(h->num_elementos == 0){
        heap_insere_vazia(h, novo_no);

    }else{

        h->num_elementos++;
        h->ultimo->prox = novo_no;
        novo_no->ant = h->ultimo;
        h->ultimo = novo_no;
        novo_no->pos = h->num_elementos-1;
        corrige_subindo(h, novo_no);
    }
    
}

static void heap_remove_ultimo(heap* h){
    no_heap* n = h->primeiro;
    h->primeiro = h->ultimo = NULL;
    free(n);
    h->num_elementos = 0;
}

static void corrige_descendo(heap* h, no_heap* n){
    no_heap * filho_esq = pega_elem_pos(h, n->pos * 2 + 1);
    no_heap * filho_dir = pega_elem_pos(h, n->pos * 2 + 2);
    
    if(filho_esq == NULL){
        return;
    }
    else if(filho_dir == NULL){
        if(filho_esq->Aresta->peso < n->Aresta->peso){
        troca(h, n, filho_esq);
        corrige_descendo(h, n);
        }
    }
    else{
        if(filho_esq->Aresta->peso < filho_dir->Aresta->peso){
            if(filho_esq->Aresta->peso < n->Aresta->peso){
                troca(h, n, filho_esq);
                corrige_descendo(h, n);
            }
        }
        else{
            if(filho_dir->Aresta->peso < n->Aresta->peso){
                troca(h, n, filho_dir);
                corrige_descendo(h, n);
            }
        }
    }
    return;
}

static void deleta_no(heap* h){
    no_heap* n = h->ultimo;
    
    h->ultimo = n->ant;
    n->ant->prox = NULL;

    h->num_elementos--;
    free(n);
}

aresta* heap_remove(heap*h){
    if(h == NULL){
        printf("Erro na remoção na heap: heap nulo");
        return NULL;
    }
    if(h->num_elementos == 0){
        printf("Erro na remoção na heap: heap vazia");
        return NULL;
    }
    aresta* aresta_retorna = h->primeiro->Aresta;

    if(pega_elem_pos(h, 1)==NULL && pega_elem_pos(h, 2)==NULL){
        heap_remove_ultimo(h);
    }
    else {
        troca(h, h->primeiro, h->ultimo);
        deleta_no(h);
        corrige_descendo(h, h->primeiro);
    }
    return aresta_retorna;
}
void heap_testa() {
    heap* h = heap_cria();
    assert(h != NULL);

    // Test inserting elements
    aresta* a1 = malloc(sizeof(aresta));
    a1->peso = 5;
    heap_insere(h, a1);

    assert(h->num_elementos == 1);
    assert(h->primeiro->Aresta == a1);
    assert(h->ultimo->Aresta == a1);

    aresta* a2 = malloc(sizeof(aresta));
    a2->peso = 3;

    heap_insere(h, a2);

    assert(h->num_elementos == 2);
    assert(h->primeiro->Aresta == a2);
    assert(h->ultimo->Aresta == a1);

    aresta* a3 = malloc(sizeof(aresta));
    a3->peso = 7;
    heap_insere(h, a3);

    assert(h->num_elementos == 3);
    assert(h->primeiro->Aresta == a2);
    assert(h->ultimo->Aresta == a3);

    aresta* a4 = malloc(sizeof(aresta));
    a4->peso = 2;
    heap_insere(h, a4);

    assert(h->num_elementos == 4);
    assert(h->primeiro->Aresta == a4);
    assert(h->ultimo->Aresta == a1);

    aresta* a5 = malloc(sizeof(aresta));
    a5->peso = 6;
    heap_insere(h, a5);

    assert(h->num_elementos == 5);
    assert(h->primeiro->Aresta == a4);
    assert(h->ultimo->Aresta == a5);

    // Test removing elements
    aresta* removed1 = heap_remove(h);
    assert(removed1 == a4);
    assert(h->num_elementos == 4);
    assert(h->primeiro->Aresta == a2);
    assert(h->ultimo->Aresta == a5);

    aresta* removed2 = heap_remove(h);
    assert(removed2 == a2);
    assert(h->num_elementos == 3);
    assert(h->primeiro->Aresta == a1);
    assert(h->ultimo->Aresta == a3);

    aresta* removed3 = heap_remove(h);
    assert(removed3 == a1);
    assert(h->num_elementos == 2);
    assert(h->primeiro->Aresta == a5);
    assert(h->ultimo->Aresta == a3);

    aresta* removed4 = heap_remove(h);
    assert(removed4 == a5);
    assert(h->num_elementos == 1);
    assert(h->primeiro->Aresta == a3);
    assert(h->ultimo->Aresta == a3);

    aresta* removed5 = heap_remove(h);
    assert(removed5 == a3);
    assert(h->num_elementos == 0);
    assert(h->primeiro == NULL);
    assert(h->ultimo == NULL);

    // Test inserting after removing all elements
    aresta* a6 = malloc(sizeof(aresta));
    a6->peso = 4;
    heap_insere(h, a6);

    assert(h->num_elementos == 1);
    assert(h->primeiro->Aresta == a6);
    assert(h->ultimo->Aresta == a6);

    // Continued:

    // Test inserting duplicate elements
    aresta* a7 = malloc(sizeof(aresta));
    a7->peso = 4;
    heap_insere(h, a7);

    assert(h->num_elementos == 2);
    assert(h->primeiro->Aresta == a6);
    assert(h->ultimo->Aresta == a7);

    // Test removing elements with duplicate weights
    aresta* removed6 = heap_remove(h);
    assert(removed6 == a6);
    assert(h->num_elementos == 1);
    assert(h->primeiro->Aresta == a7);
    assert(h->ultimo->Aresta == a7);

    aresta* removed7 = heap_remove(h);
    assert(removed7 == a7);
    assert(h->num_elementos == 0);
    assert(h->primeiro == NULL);
    assert(h->ultimo == NULL);

    // Test inserting and removing a large number of elements
    const int NUM_ELEMENTS = 100;
    for (int i = 0; i < NUM_ELEMENTS; i++) {
        aresta* a = malloc(sizeof(aresta));
        a->peso = i;
        heap_insere(h, a);
    }

    assert(h->num_elementos == NUM_ELEMENTS);

    for (int i = 0; i < NUM_ELEMENTS; i++) {
        aresta* removed = heap_remove(h);
        assert(1==1);
        assert(removed->peso == i);
        free(removed);
    }

    assert(h->num_elementos == 0);
    assert(h->primeiro == NULL);
    assert(h->ultimo == NULL);
    printf("Sucesso nos testes!\n");
    // Cleanup
    free(h);

}


