#include "../headers/caminho.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

caminho* caminho_cria(char* inicio, char* fim) {
    if (inicio == NULL || fim == NULL) {
        printf("Erro na criação de caminho: inicio ou fim nulos");
        return NULL;
    }

    caminho* c = malloc(sizeof(caminho));
    if (c == NULL) {
        printf("Erro de alocação de caminho: falha no malloc");
        return NULL;
    }

    c->inicio = malloc(strlen(inicio) + 1); 
    if (c->inicio == NULL) {
        printf("Erro de alocação de caminho: falha no malloc para inicio");
        free(c); 
        return NULL;
    }
    strcpy(c->inicio, inicio); 

    c->fim = malloc(strlen(fim) + 1); 
    if (c->fim == NULL) {
        printf("Erro de alocação de caminho: falha no malloc para fim");
        free(c->inicio); 
        free(c); 
        return NULL;
    }
    strcpy(c->fim, fim); 

    return c;
}

caminho *caminho_cria_vazio(){
    caminho* c = malloc(sizeof(caminho));
    if (c == NULL) {
        printf("Erro de alocação de caminho: falha no malloc\n");
        return NULL;
    }
    
    c->inicio = NULL;
    c->fim = NULL;

    return c;
}

void caminho_destroi(caminho* c){
    if (c==NULL){
        printf("Erro na destruição de caminho: caminho nulo");
        return;
    }
    free(c);
    return;
}

local* acha_local (lista* locais, char*nome){
    if(locais==NULL){
        return NULL;
    }
    no *no_atual = locais->primeiro; 
    while(no_atual !=NULL){
        if(strcmp(((local*)(no_atual->data))->nome, nome)==0){
            return ((local*)no_atual->data);
        }
        no_atual = no_atual->prox;
    }
    printf("Erro em acha_local: nome não achado na lista de locais");
    assert(1==2);
    return NULL;
}

lista* coloca_peso_caminhos (lista* caminhos, lista* locais, char** tabela){
    if(caminhos == NULL|| locais==NULL){
        printf("Erro na pesagem dos caminhos: caminhos ou locais nulos");
        return NULL;
    }
    lista* arestas = lista_cria();
    no* no_caminho_atual = caminhos->primeiro;
    
    while(no_caminho_atual!=NULL){

        caminho* caminho_atual = (caminho*)no_caminho_atual->data;
        local* local1 = acha_local(locais, caminho_atual->inicio);
        local* local2 = acha_local(locais, caminho_atual->fim);
        double distancia = calcula_distancia(local1->latitude, local1->longitude, local2->latitude, local2->longitude);
        
        aresta* caminho_pesado = aresta_cria(acha_na_tabela(tabela, local1->nome), acha_na_tabela(tabela, local2->nome), distancia);
        lista_insere(arestas, no_cria((void*)caminho_pesado), -1);
        no_caminho_atual = no_caminho_atual->prox;
    }
    return arestas;
}

void caminho_testa() {
}