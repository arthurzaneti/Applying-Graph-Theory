#include "../headers/lista.h"
#include "../headers/grafo.h"
#include "../headers/arq_manager.h"
#include "../headers/calcula_distancia.h"
#include "../headers/caminho.h"
#include "../headers/ufsm.h"
#include "../headers/heap.h"
#include "../headers/floyd_warshal.h"

#include <assert.h>
#include <stdio.h>

int main(){
    Grafo ufsm = cria_grafo_ufsm();

    matrizes * resultado_floyd_warshal = algoritmo_floyd_warshal(ufsm);

    printa_matriz_adjacencias(resultado_floyd_warshal->matriz_de_adjacencias, resultado_floyd_warshal->n_valores);
    printa_matriz_caminho_mais_curto(resultado_floyd_warshal->matriz_caminho_mais_curto, resultado_floyd_warshal->n_valores);
    
    return 0;
}