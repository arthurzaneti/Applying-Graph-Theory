#ifndef _CAMINHO_H_
#define _CAMINHO_H_

#include "lista.h"
#include "arq_manager.h"
#include "calcula_distancia.h"
#include "aresta.h"

typedef struct _caminho{
    char* inicio;
    char* fim;
}caminho;

caminho *caminho_cria(char* inicio, char* fim);
void caminho_destroi(caminho* c);
caminho* caminho_cria_vazio();
local* acha_local (lista* locais, char*nome);
lista* coloca_peso_caminhos (lista* caminhos, lista* locais, char** tabela);


#endif