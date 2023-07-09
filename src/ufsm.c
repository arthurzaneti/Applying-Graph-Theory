#include "../headers/ufsm.h"
#include <stdio.h>
#include <stdlib.h>




Grafo cria_grafo_ufsm(){
    lista* locais = le_locais();
    
    lista* caminhos = le_caminhos();
    
    char** tabela =  tabela_conversao_cria(locais);
    lista* arestas = coloca_peso_caminhos(caminhos, locais, tabela);

    Grafo ufsm = g_cria(0,false);
    no* no_aresta_atual = arestas->primeiro;
    while(no_aresta_atual!=NULL){
        aresta* aresta_atual = (aresta*)no_aresta_atual->data;
        g_ins_aresta(ufsm, aresta_atual->inicio, aresta_atual->fim, aresta_atual->peso);
        no_aresta_atual = no_aresta_atual->prox;
    }
    return ufsm;
}