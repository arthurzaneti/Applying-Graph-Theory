#include "../headers/grafo.h"
#include "../headers/lista.h"

#define TAMANHO_MAX_NOME 5
#define TAMANHO_MAX_LINHA 256
#define NUM_ELEMENTOS 35

typedef struct _local {
    char nome[TAMANHO_MAX_NOME];
    double latitude;
    double longitude;
    char descricao[TAMANHO_MAX_LINHA];
    int indice;
}local;

lista* le_locais();
char** tabela_conversao_cria(lista* l);