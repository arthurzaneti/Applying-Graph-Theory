#include "../headers/caminho_ufsm.h"
#include <stdio.h>
#include <stdlib.h>

caminho_ufsm *caminho_ufsm_cria(char* inicio, char* fim){
    if (inicio == NULL|| fim ==NULL){
        printf("Erro na criação de caminho_ufsm: inicio ou fim nulos");
        return NULL;
    }
    caminho_ufsm* c = malloc(sizeof(caminho_ufsm));
    if (c==NULL){
        printf("Erro de alocação de caminho_ufsm: falha no malloc");
        return NULL;
    }
    c->inicio = inicio;
    c->fim = fim;
    return c;
}
void caminho_ufsm_destroi(caminho_ufsm* c){
    if (c==NULL){
        printf("Erro na destruição de caminho_ufsm: caminho nulo");
        return;
    }
    free(c);
    return;
}
void caminho_ufsm_testa() {
    
    char inicio[] = "r001";
    char fim[] = "cam6";

    caminho_ufsm* c = caminho_ufsm_cria(inicio, fim);
    if (c == NULL) {
        printf("Falha na criação do caminho_ufsm.\n");
        return;
    }

    printf("Inicio: %s\n", c->inicio);
    printf("Fim: %s\n", c->fim);

    caminho_ufsm_destroi(c);
    printf("caminho_ufsm destruído.\n");
}
