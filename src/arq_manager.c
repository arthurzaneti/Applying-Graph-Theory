#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "../headers/arq_manager.h"

static local* local_cria(){
    local* l = malloc(sizeof(local));
    if (l==NULL){
        printf("Erro na criação de local: local nulo");
        return NULL;
    }
    return l;
}

lista* le_locais() {
    FILE *locais_file;

    locais_file = fopen("/home/arthur/Desktop/grafos/info/locais.csv", "r");
    if (locais_file == NULL) {
        perror("Erro em le_locais: falha em abrir o arquivo");
        return NULL;
    }

    char buffer[TAMANHO_MAX_LINHA]; 
    lista* locais = lista_cria();

    bool primeira_iteracao = true;
    while (fgets(buffer, sizeof(buffer), locais_file)) {

        if(primeira_iteracao){
            primeira_iteracao = false;
            continue;
        }
        local* novo_local = local_cria();
        sscanf(buffer, "%[^,],%lf,%lf,%[^,\n]", novo_local->nome, &novo_local->latitude, &novo_local->longitude, novo_local->descricao);
        lista_insere(locais, no_cria((void*)novo_local), -1);
    }
    fclose(locais_file);
    return locais;
}
char** tabela_conversao_cria(lista* locais){
    char** tabela = malloc(sizeof(char*)* NUM_ELEMENTOS);
    if(tabela == NULL){
        printf("Erro na crianção da tabela de conversão: tabela nula");
        return NULL;
    }
    for (int i=0; i < NUM_ELEMENTOS; i++){
        local* local_atual = (local*)(lista_pega_elemento(locais, i)->data);
        tabela[i] = malloc(strlen(local_atual->nome +1));
        if (tabela[i] == NULL){
            printf("Erro na criação da tabela: falha no malloc");
            for(int j=0; j<i; i++){
                free(tabela[j]);
            }
            free(tabela);
            return NULL;
        }
        strcpy(tabela[i], local_atual->nome);
        printf("%s\n", tabela[i]);
    }
    return tabela;
}



