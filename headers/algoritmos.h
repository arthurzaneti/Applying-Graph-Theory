#ifndef _ALGORITMOS_H_
#define _ALGORITMOS_H_

#include "../headers/grafo.h"
typedef struct matrizes {
    double** matriz_de_adjacencias;
    int** matriz_caminho_mais_curto;
    int n_valores;
} matrizes;

matrizes* algoritmo_floyd_warshal(grafo* g);
int * ordem_visita(matrizes* m, int* visitas);

void printa_matriz_adjacencias(double ** matriz, int n);
void printa_matriz_caminho_mais_curto(int** matriz, int n);

void matrizes_destroi(matrizes* m);


#endif