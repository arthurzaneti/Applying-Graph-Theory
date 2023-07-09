#ifndef _ARESTA_H_
#define _ARESTA_H_

//arestas do grafo

typedef struct _aresta{
    int inicio;
    int fim;
    double peso;
}aresta;



aresta *aresta_cria(int inicio, int fim, double peso);
void aresta_destroi(aresta* a);
void aresta_testa();

#endif