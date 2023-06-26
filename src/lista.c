#include "../headers/lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

lista* lista_cria(){
    lista* l = malloc(sizeof(lista));
    if (l==NULL){
        printf("Erro de alocação da lista: falha no malloc");
        return NULL;
    };
    l->primeiro = NULL;
    l->ultimo = NULL;
    l->num_elementos = 0;
    return (l);
}

no* no_cria(void*data){
    no* n = malloc(sizeof(no));
    if (n==NULL){
        printf("Erro de alocação do no: falha no malloc");
        return NULL;
    }
    n->data = data;
    n->prox = NULL;
    n->ant = NULL;
    return n;
}

void lista_insere_inicio_aux(lista* l, no* elem){
    if(l->primeiro ==NULL) lista_insere_vazia_aux(l, elem);
    else{
        elem->ant = NULL;
        elem->prox= l->primeiro;
        elem->prox->ant = elem;
        l->primeiro = elem;
    }
}

void lista_insere_fim_aux(lista*l, no* elem){
    if(l->primeiro ==NULL) lista_insere_vazia_aux(l, elem);
    else{

        elem->ant = l->ultimo;
        elem->prox= NULL;
        elem->ant->prox = elem;
        l->ultimo = elem;
    }
}

void lista_insere_vazia_aux(lista*l, no* elem){
    l->ultimo = elem;
    l->primeiro = elem;
    elem->prox = NULL;
    elem->ant =NULL;
}

void lista_insere(lista*l, no* elem, int pos){
    if (l==NULL){
        printf("Erro de inserção: Lista nula");
        return;
    }else if(elem==NULL){
        printf("Erro de inserção: Nó nulo");
        return;
    }
    if (pos<0)pos+= l->num_elementos+1;
    if (pos<0){
        printf("Erro de inserção: Posição muito pequena");
        return;
    }else if(pos > l->num_elementos){
        printf("Erro de inserção: Posição muito grande");
        return;
    }
    else{
        if (pos==0) {
            lista_insere_inicio_aux(l, elem);
        }
        else if (pos==l->num_elementos) {
            lista_insere_fim_aux(l, elem);
        }
        else{
            no *no_atual = l->primeiro;
            int contador = 0;
            while(contador < pos-1){
                no_atual = no_atual->prox;
                contador++;
            }
            assert(no_atual->prox !=NULL);
            elem->prox = no_atual->prox;
            elem->ant = no_atual;
            no_atual->prox = elem;
            elem->prox->ant = elem;
            
        }
    }
    l->num_elementos++;
}
static void* lista_remove_1_elem(lista* l){
    no* no_remover = l->primeiro;
    void* valor_do_no = no_remover->data;
    free(no_remover);
    l->num_elementos--;
    l->primeiro = NULL;
    l->ultimo = NULL;
    return (valor_do_no);
}
void* lista_remove_inicio_aux(lista*l){
    if (l->num_elementos ==1) return  lista_remove_1_elem(l);
    no* no_remover = l->primeiro;
    no_remover->prox->ant = NULL;
    l->primeiro = no_remover->prox;
    void* valor_do_no = no_remover->data;
    free(no_remover);
    l->num_elementos--;
    return (valor_do_no);
}

void* lista_remove_fim_aux(lista*l){
    if (l->num_elementos ==1) return lista_remove_1_elem(l);
    no* no_remover = l->ultimo;
    no_remover->ant->prox = NULL;
    l->ultimo = no_remover->ant;
    void* valor_do_no = no_remover->data;
    free(no_remover);
    l->num_elementos--;
    return (valor_do_no);
}

void* lista_remove(lista *l, int pos){
    if(!verifica_remoção_aux(l,pos)) return NULL;
    if (pos <0) pos += l->num_elementos;
    if (pos==0)return lista_remove_inicio_aux(l);
    if (pos==l->num_elementos -1) return lista_remove_fim_aux(l);
    int contador = 0;
    no* no_atual = l->primeiro;
    while (contador<pos){
        no_atual = no_atual->prox;
        contador++;
    } 
    no_atual->ant->prox = no_atual->prox;
    no_atual->prox->ant = no_atual->ant;
    void* valor_do_no = no_atual->data;
    free(no_atual);
    l->num_elementos--;   
    return (valor_do_no);
}

bool verifica_remoção_aux(lista*l, int pos){
    if(l==NULL){
        printf("Erro de remoção: Lista nula");
        return false;
    }
    if(l->primeiro ==NULL){
        printf("Erro de remoção: Lista sem nenhum elemento");
        return false;
    }
    if (pos <0) pos += l->num_elementos;
    if (pos <0){
        printf("Erro de remoção: Posição muito pequena");
        return false;
    }
    if(pos>l->num_elementos){
        printf("Erro de remoção: Posição muito grande");
        return false;
    }
    return true;
}

void lista_destroi(lista*l){
    if(l->primeiro==NULL) {
        free(l);
        return;
    }
    no* no_atual = l->primeiro;
    while(no_atual!=NULL){
        no* prox_do_atual = no_atual->prox;
        free(no_atual);
        no_atual = prox_do_atual;
    }
    free(l);
}
no* lista_pega_elemento(lista* l, int pos){
    if(l==NULL){
        printf("Erro em pega_elemento: lista nula");
        return NULL;
    }
    if (pos < 0){
        pos += l->num_elementos;
    }
    if (pos <0 || pos >= l->num_elementos){
        printf("Erro em pega_elemento: indice fora de alcance");
        return NULL;
    }
    no* no_atual = l->primeiro;
    int contador = 0;
    while(no_atual != NULL){
        if(contador == pos){
            return no_atual;
            break;
        }
        contador++;
        no_atual=no_atual->prox;
    }
    printf("Erro inesperado em pega elemento");
    return NULL;
}

void lista_testa() {
    lista* l = lista_cria();

    int a = 10;
    void* ptra = &a;
    no* no_int = no_cria(ptra);
    lista_insere(l, no_int, 0);
    assert(l->num_elementos == 1);
    assert(l->primeiro == no_int);
    assert(l->ultimo == no_int);

    char b = 'b';
    void* ptrb = &b;
    no* no_char = no_cria(ptrb);
    lista_insere(l, no_char, l->num_elementos);
    assert(l->num_elementos == 2);
    assert(l->primeiro == no_int);
    assert(l->ultimo == no_char);

    float c = 3.14;
    void* ptrc = &c;
    no* no_float = no_cria(ptrc);
    lista_insere(l, no_float, 1);
    assert(l->num_elementos == 3);
    assert(l->primeiro == no_int);
    assert(l->ultimo == no_char);

    int d = 20;
    void* ptrd = &d;
    no* no_negative = no_cria(ptrd);
    lista_insere(l, no_negative, -1);
    assert(l->num_elementos == 4);
    assert(l->primeiro == no_int);
    assert(l->ultimo == no_negative);

    int e = 30;
    void* ptre = &e;
    no* no_beyond = no_cria(ptre);
    lista_insere(l, no_beyond, -1);
    assert(l->num_elementos == 5);
    assert(l->primeiro == no_int);
    assert(l->ultimo == no_beyond);

    no* retrieved_0 = lista_pega_elemento(l, 0);
    assert(retrieved_0 == no_int);
    assert(*(int*)(retrieved_0->data) == a);

    no* retrieved_1 = lista_pega_elemento(l, 1);
    assert(retrieved_1 == no_float);
    assert(*(float*)(retrieved_1->data) == c);

    no* retrieved_2 = lista_pega_elemento(l, 2);
    assert(retrieved_2 == no_char);
    assert(*(char*)(retrieved_2->data) == b);

    no* retrieved_3 = lista_pega_elemento(l, 3);
    assert(retrieved_3 == no_negative);
    assert(*(int*)(retrieved_3->data) == d);

    no* retrieved_4 = lista_pega_elemento(l, 4);
    assert(retrieved_4 == no_beyond);
    assert(*(int*)(retrieved_4->data) == e);

    no* retrieved_neg_1 = lista_pega_elemento(l, -1);
    assert(retrieved_neg_1 == no_beyond);
    assert(*(int*)(retrieved_neg_1->data) == e);

    no* retrieved_neg_2 = lista_pega_elemento(l, -2);
    assert(retrieved_neg_2 == no_negative);
    assert(*(int*)(retrieved_neg_2->data) == d);

    no* retrieved_neg_3 = lista_pega_elemento(l, -3);
    assert(retrieved_neg_3 == no_char);
    assert(*(char*)(retrieved_neg_3->data) == b);

    no* retrieved_neg_4 = lista_pega_elemento(l, -4);
    assert(retrieved_neg_4 == no_float);
    assert(*(float*)(retrieved_neg_4->data) == c);

    no* retrieved_neg_5 = lista_pega_elemento(l, -5);
    assert(retrieved_neg_5 == no_int);
    assert(*(int*)(retrieved_neg_5->data) == a);

    void* removed_data = lista_remove(l, 0);
    assert(removed_data == ptra);
    assert(l->num_elementos == 4);
    assert(l->primeiro == no_float);

    removed_data = lista_remove(l, 2);
    assert(removed_data == ptrd);
    assert(l->num_elementos == 3);
    assert(l->ultimo == no_beyond);

    removed_data = lista_remove(l, l->num_elementos -1);
    assert(removed_data == ptre);
    assert(l->num_elementos == 2);
    assert(l->ultimo == no_char);
    
    removed_data = lista_remove(l, -1);
    assert(removed_data == ptrb);
    assert(l->num_elementos == 1);
    assert(l->primeiro == no_float);
    
    removed_data = lista_remove(l, 0);
    assert(removed_data == ptrc);
    assert(l->num_elementos == 0);
    
    assert(l->ultimo == NULL);
    assert(l->primeiro == NULL);
    
    lista_destroi(l);

    printf("Sucesso nos testes!\n");
}