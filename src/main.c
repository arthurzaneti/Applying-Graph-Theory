#include "../headers/lista.h"
#include "../headers/grafo.h"
#include "../headers/arq_manager.h"
#include "../headers/calcula_distancia.h"
#include "../headers/caminho.h"
#include "../headers/ufsm.h"
#include "../headers/heap.h"
#include "../headers/algoritmos.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
    Grafo ufsm = cria_grafo_ufsm();

    lista* locais = le_locais();
    matrizes * resultado_floyd_warshal = algoritmo_floyd_warshal(ufsm);

    char **visitas = le_visita();

    char ** tabela = tabela_conversao_cria(locais);
    
    int *visitas_convertidas = converte_visitas(visitas, tabela);

    int*ordem = ordem_visita(resultado_floyd_warshal, visitas_convertidas);
    int i = 0;
    while(ordem[i] !=-1){
        printf("%d \n", ordem[i]);
        i++;
    }
    printa_matriz_caminho_mais_curto(resultado_floyd_warshal->matriz_caminho_mais_curto, resultado_floyd_warshal->n_valores);
    
    return 0;
}