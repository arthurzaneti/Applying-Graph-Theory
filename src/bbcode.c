#include "../headers/bbcode.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static lista* cria_lista_ordem(int * ordem, lista* locais){
    if(ordem == NULL){
        printf("Erro em cria_lista_ordem: ordem nula");
    }
    if(locais == NULL){
        printf("Erro em cria_lista_ordem: ordem nula");
    }
    lista* lista_ordem = lista_cria();
    for(int i=0; ordem[i] !=-1; i++){
        no* novo_no = no_cria((local*)(lista_pega_elemento(locais, ordem[i])->data));
        lista_insere(lista_ordem, novo_no, -1);
    }
    return lista_ordem;
}


void cria_arq_bbcode(int* ordem, lista* locais){
    lista* ordem_locais = cria_lista_ordem(ordem, locais);
    FILE * bbcode;


    bbcode = fopen("bbcode.txt", "w");
    if (bbcode == NULL) {
    perror("Erro em cria_arq_bbcode: falha em criar o arquivo");
    return;
    }
    no* no_atual = ordem_locais->primeiro;
    fprintf(bbcode, "[map]");
    while(no_atual != NULL){
        local*l = (local*)no_atual->data;
        if(strlen(l->descricao) >0){
            fprintf(bbcode, "%.10f,%.10f(%s)\n", l->latitude, l->longitude, l->descricao );
        }
        else{
            fprintf(bbcode, "%f,%f", l->latitude, l->longitude);
        }
        no_atual = no_atual->prox;
    }
    fprintf(bbcode, "[/map]");
    fclose(bbcode);
}

