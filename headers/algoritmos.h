#ifndef _ALGORITMOS_H_
#define _ALGORITMOS_H_

#include "../headers/grafo.h"

//Onde o algoritmo de Floyd-Warshal foi utilizado para calculara menor distância entre os pontos
//Também é aqui que o resultado do algoritmo Floyd-Warshal é utilizado para produzir a ordem de visita

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