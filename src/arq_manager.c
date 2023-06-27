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

lista* le_caminhos(){
    FILE* caminhos_file;
    caminhos_file = fopen("/home/arthur/Desktop/grafos/info/caminhos.csv", "r");
    if (caminhos_file == NULL) {
        perror("Erro em le_caminhos: falha em abrir o arquivo");
        return NULL;
    }
    lista* caminhos = lista_cria();
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), caminhos_file)) {
        if (buffer[0] == '#') {
            continue; 
        }

        char inicio[10];
        char fim[10];

        int result = sscanf(buffer, "%[^,],%[^,\n]", inicio, fim);
        if (result == 2) {
            caminho* caminho_lido = caminho_cria(inicio, fim);
            lista_insere(caminhos, no_cria((void*)caminho_lido), -1);
        }
    }
    fclose(caminhos_file);
    return caminhos;
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
    }
    return tabela;
}

int acha_na_tabela (char**tabela, char*nome){
    if(tabela == NULL){
        printf("Erro em acha_na_tabela: tabela nula");
        return 0;
    }
    if(nome == NULL){
        printf("Erro em acha_na_tabela: nome nulo");
        return 0;
    }

    for (int i=0; tabela[i]!= NULL; i++){
        if(strcmp(tabela[i], nome)==0){
            return i;
        }
    }
    printf("Erro em acha_na_tabela: nome não esta na tabela");
    return 0;
}
void test_le_caminhos() {
    lista* caminhos = le_caminhos();
    
    if (caminhos == NULL) {
        printf("Falha ao ler os caminhos do arquivo.\n");
        return;
    }
    
    printf("Caminhos lidos:\n");
    no* current = caminhos->primeiro;
    while (current != NULL) {
        caminho* caminho_atual = (caminho*)current->data;
        printf("%s -> %s\n", caminho_atual->inicio, caminho_atual->fim);
        current = current->prox;
    }
    
    lista_destroi(caminhos);
}




