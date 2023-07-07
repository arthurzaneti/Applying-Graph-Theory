#ifndef _FLOYD_WARSHAL_H_
#define _FLOYD_WARSHAL_H_

#include "../headers/grafo.h"
typedef struct matrizes {
    float** matriz_de_adjacencias;
    int** matriz_caminho_mais_curto;
    int n_valores;
} matrizes;

matrizes* algoritmo_floyd_warshal(grafo* g);

void printa_matriz_adjacencias(float ** matriz, int n);
void printa_matriz_caminho_mais_curto(int** matriz, int n);

void matrizes_destroi(matrizes* m);

void fw_testa();

#endif