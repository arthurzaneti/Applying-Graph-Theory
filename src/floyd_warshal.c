#include "../headers/floyd_warshal.h"
#include <stdlib.h>
#include <stdio.h>

#define INFINITO 2147483647
#define NAO_EXISTE -2147483647



static matrizes *matrizes_cria(int n) {
    matrizes *m = malloc(sizeof(struct matrizes));
    m->n_valores = n;

    m->matriz_de_adjacencias = malloc(n * sizeof(float*));
    for (int i = 0; i < n; ++i) {
        m->matriz_de_adjacencias[i] = malloc(n * sizeof(int));
    }

    m->matriz_caminho_mais_curto = malloc(n * sizeof(int*));
    for (int i = 0; i < n; ++i) {
        m->matriz_caminho_mais_curto[i] = malloc(n * sizeof(int));
    }

    return m;
}

void matrizes_destroi(matrizes* m) {
    int n = m->n_valores;

    for (int i = 0; i < n; ++i) {
        free(m->matriz_de_adjacencias[i]);
    }
    free(m->matriz_de_adjacencias);

    for (int i = 0; i < n; ++i) {
        free(m->matriz_caminho_mais_curto[i]);
    }
    free(m->matriz_caminho_mais_curto);

    free(m);
}

void printa_matriz_adjacencias(float** matriz, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if(matriz[i][j] == INFINITO){
                printf("INFINITO ");
            }else{
                printf("%f ", matriz[i][j]);
            }
        }
        printf("\n");
    }
}
void printa_matriz_caminho_mais_curto(int** matriz, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if(matriz[i][j] == NAO_EXISTE){
                printf("NAO_EXISTE ");
            }else{
                printf("%d ", matriz[i][j]);
            }
        }
        printf("\n");
    }
}

static float** pega_matriz_adjacencia (grafo* g) {

    int num_vertices = g->lista_de_adjacencias->num_elementos;

    float** matriz_adjacencia = malloc(num_vertices * sizeof(float*));
    if(matriz_adjacencia == NULL){
        printf("Falha no malloc: Erro em pega matriz adjacencia");
        return NULL;
    }

    for (int i = 0; i < num_vertices; ++i) {
        matriz_adjacencia[i] = calloc(num_vertices, sizeof(float));
        if(matriz_adjacencia[i] == NULL){
            printf("Falha no calloc: Erro em pega matriz adjacencia");
        return NULL;
        }
    }
    for (int i =0; i<num_vertices; i++){
        for (int j =0; j<num_vertices; j++){
            matriz_adjacencia[i][j] = 0.0;
        }
    }

    g_arestas(g);

    int origem, destino;
    float peso;

    while(g_proxima_aresta(g, &origem, &destino, &peso)){
        matriz_adjacencia[origem][destino] = peso;
    }
    matriz_adjacencia[origem][destino] = peso;

    for (int i =0; i<num_vertices; i++){
        for (int j =0; j<num_vertices; j++){
            if (matriz_adjacencia[i][j] == 0.0 && i!=j){
                matriz_adjacencia[i][j] = INFINITO;
            }
        }
    }
    return matriz_adjacencia;
}

static int** pega_matriz_caminho_mais_curto(grafo* g){
    int num_vertices = g->lista_de_adjacencias->num_elementos;

    int** matriz_sp = malloc(num_vertices * sizeof(int*));

    if(matriz_sp == NULL){
        printf("Falha no malloc: Erro em pega_matriz_caminho_mais_curto");
        return NULL;
    }

    for (int i = 0; i < num_vertices; ++i) {
        matriz_sp[i] = calloc(num_vertices, sizeof(int));
        if(matriz_sp[i] == NULL){
            printf("Falha no calloc: Erro em pega_matriz_caminho_mais_curto");
        return NULL;
        }
    }

    for (int i =0; i<num_vertices; i++){
        for (int j =0; j<num_vertices; j++){
            matriz_sp[i][j] = NAO_EXISTE;
        }
    }

    g_arestas(g);

    int origem, destino;
    float peso;

    while(g_proxima_aresta(g, &origem, &destino, &peso)){
        matriz_sp[origem][destino] = origem;
    }
    matriz_sp[origem][destino] = origem;
    
    return(matriz_sp);
}

static matrizes* pega_matrizes(grafo * g){
    if(g == NULL){
        printf("Erro em pega matrizes: grafo nulo");
        return NULL;
    }

    matrizes* m = matrizes_cria(g->lista_de_adjacencias->num_elementos);
    m->matriz_de_adjacencias = pega_matriz_adjacencia(g);
    m->matriz_caminho_mais_curto = pega_matriz_caminho_mais_curto(g);
    return m;
}

matrizes* algoritmo_floyd_warshal(grafo* g) {
    matrizes* m = pega_matrizes(g);
    int n = m->n_valores;
    
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (m->matriz_de_adjacencias[i][k] + m->matriz_de_adjacencias[k][j] < m->matriz_de_adjacencias[i][j]) {
                    m->matriz_de_adjacencias[i][j] = m->matriz_de_adjacencias[i][k] + m->matriz_de_adjacencias[k][j];
                    m->matriz_caminho_mais_curto[i][j] = m->matriz_caminho_mais_curto[k][j];
                }
            }
        }
    }
    
    return m;
}

void fw_testa() {

    grafo* g = g_cria(0, false);
    g_ins_aresta(g, 1, 2, 1.5);
    g_ins_aresta(g, 0, 1, 2.0);
    g_ins_aresta(g, 0, 3, 6.9);
    g_ins_aresta(g, 1, 4, 0.2);
    g_ins_aresta(g, 3, 2, 0.3);
    g_ins_aresta(g, 4, 3, 10.0);
    g_ins_aresta(g, 0, 2, 11.0);

    matrizes* m = pega_matrizes(g);

    printa_matriz_adjacencias(m->matriz_de_adjacencias, m->n_valores);
    printa_matriz_caminho_mais_curto(m->matriz_caminho_mais_curto, m->n_valores);

    matrizes* fw_m = algoritmo_floyd_warshal(g);
    
    printa_matriz_adjacencias(fw_m->matriz_de_adjacencias, fw_m->n_valores);
    printa_matriz_caminho_mais_curto(fw_m->matriz_caminho_mais_curto, fw_m->n_valores);

    g_destroi(g);
}

