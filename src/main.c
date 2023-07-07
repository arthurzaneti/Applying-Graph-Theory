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
#include <stdlib.h>

int main(){
    Grafo ufsm = cria_grafo_ufsm();

    matrizes * resultado_floyd_warshal = algoritmo_floyd_warshal(ufsm);

    char **visitas = le_visita();

    char ** tabela = tabela_conversao_cria(le_locais());
    
    int **visitas_convertidas = converte_visitas(visitas, tabela);

    for(int i =0; i< conta_visitas(visitas); i++){
        printf("%d \n", *visitas_convertidas[i]);
    }
    
    return 0;
}