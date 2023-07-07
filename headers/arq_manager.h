#ifndef _ARQ_MANAGER_H_
#define _ARQ_MANAGER_H_

#include "grafo.h"
#include "lista.h"


#define TAMANHO_MAX_NOME 5
#define TAMANHO_MAX_LINHA 256
#define NUM_ELEMENTOS 35

typedef struct _local {
    char nome[TAMANHO_MAX_NOME];
    double latitude;
    double longitude;
    char descricao[TAMANHO_MAX_LINHA];
}local;

#include "caminho.h"

lista* le_locais();
lista* le_caminhos();
char** tabela_conversao_cria(lista* locais);
int acha_na_tabela (char**tabela, char*nome);
void test_le_caminhos();

#endif