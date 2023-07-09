#include "../headers/lista.h"
#include "../headers/grafo.h"
#include "../headers/arq_manager.h"
#include "../headers/calcula_distancia.h"
#include "../headers/caminho.h"
#include "../headers/ufsm.h"
#include "../headers/algoritmos.h"
#include "../headers/bbcode.h"

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

    int *ordem = ordem_visita(resultado_floyd_warshal, visitas_convertidas);

    cria_arq_bbcode(ordem, locais);

    lista_destroi(locais);
    g_destroi(ufsm);
    for(int i =0; i < NUM_ELEMENTOS; i++){
        free(tabela[i]);
    }
    for(int i =0; visitas[i] != NULL; i++){
        free(visitas[i]);
    }
    free(visitas);
    free(ordem);
    free(visitas_convertidas);
    matrizes_destroi(resultado_floyd_warshal);
    
    return 0;
}