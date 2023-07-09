#include "../headers/algoritmos.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#define INFINITO 2147483647
#define NAO_EXISTE -2147483647
#define INFINITO_DOUBLE 999999999999.9


static matrizes *matrizes_cria(int n) {
    matrizes *m = malloc(sizeof(struct matrizes));
    m->n_valores = n;

    m->matriz_de_adjacencias = malloc(n * sizeof(double*));
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
    if(m == NULL){
        printf("Erro em matrizes destroi, matrizes nulas");
        return; 
    }
    if(m->matriz_de_adjacencias != NULL){
        for (int i = 0; i < m->n_valores; i++) {
            free(m->matriz_de_adjacencias[i]);
        }
        free(m->matriz_de_adjacencias);
    }

    if (m->matriz_caminho_mais_curto != NULL){
        for (int i = 0; i < m->n_valores; i++) {
            free(m->matriz_caminho_mais_curto[i]);
        }
        free(m->matriz_caminho_mais_curto);
    }

    free(m);
}

void printa_matriz_adjacencias(double** matriz, int n) {
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

static double** pega_matriz_adjacencia (grafo* g) {

    int num_vertices = g->lista_de_adjacencias->num_elementos;

    double** matriz_adjacencia = malloc(num_vertices * sizeof(double*));
    if(matriz_adjacencia == NULL){
        printf("Falha no malloc: Erro em pega matriz adjacencia");
        return NULL;
    }

    for (int i = 0; i < num_vertices; ++i) {
        matriz_adjacencia[i] = calloc(num_vertices, sizeof(double));
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
    double peso;

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
    double peso;

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
static int* array_bool(int n){
    int *array_bool = malloc(sizeof(int) * (n+1));
    array_bool[0] = 1;
    int i = 1;
    while(i < n){
        array_bool[i] = 0;
        i++;
    }
    array_bool[i+1] = -1;
    return array_bool;
}

static int * inverte_caminho(int * caminho){
    int contador = 0;
    while(caminho[contador]!=-1){
        contador++;
    }
    int* caminho_invertido = (int*)malloc(sizeof(int) * (contador+1));
    if(caminho_invertido == NULL){
        printf("Erro para inverter o vetor: malloc de caminho_invertido falhou");
        return NULL;
    }
    int i=0;
    while(i<contador) {
        caminho_invertido[i] = caminho[contador - 1 - i];
        i++;
    }

    caminho_invertido[i] = -1;
    free(caminho); 

    return caminho_invertido;

}
static int* pega_caminho(matrizes* m, int saida, int destino) {
    int* linha_caminho_mais_curto = m->matriz_caminho_mais_curto[saida];

    int* caminho = (int*)malloc((m->n_valores + 1) * sizeof(int));
    if (caminho == NULL) {
        printf("Erro em pega_caminho: falha em alocar memória\n");
        return NULL;
    }

    int i = 0;
    caminho[i] = destino;
    while (caminho[i] != saida) {
        caminho = (int*)realloc(caminho, (i + 2) * sizeof(int));
        if (caminho == NULL) {
            printf("Erro em pega_caminho: falha em realocar memória\n");
            return NULL;
        }
        caminho[i + 1] = linha_caminho_mais_curto[caminho[i]];
        i++;
    }
    caminho[i + 1] = -1;
    return inverte_caminho(caminho);
}

static int determina_proximo(matrizes* m, int* visitas, int* visitados, int atual){
    double* linha_pesos = m->matriz_de_adjacencias[atual];
    int melhor = -1;
    double melhor_peso = INFINITO_DOUBLE;

    for(int i = 0; visitas[i]!=-1; i++){
        if(visitados[i] == 1){
            continue;
        }
        else{
            if(linha_pesos[visitas[i]] < melhor_peso){
                melhor_peso = linha_pesos[visitas[i]];
                melhor = visitas[i];
            }
        }
    }

    return melhor;
}

static bool tem_nao_visitado(int * visitados){
    if(visitados == NULL){
        printf("Erro em tem_nao_visitados: array nulo");
        return false;
    }
    int i = 0;

    while(true){
        if(visitados[i] == -1) return false;
        if(visitados[i] == 0) return true;
        i++;
    }
    printf("Erro inesperado em tem nao visitados");
}

static void torna_visitado(int * visitas, int * visitados, int local){
    if(visitas==NULL){
        printf("Erro em torna_visitado: visitas nulo");
        return;
    }

    if(visitados==NULL){
        printf("Erro em torna_visitado: visitados nulo");
        return;
    }

    int i = 0;
    while(visitas[i] !=-1){
        if(visitas[i] == local){
            visitados[i] = 1;
            return;
        }
        i++;
    }

    
    return;
}
static int conta_visitas(int* visitas){
    if(visitas==NULL){
        printf("Erro em conta_visitas_convertidas: visitas nulo");
        return -1;
    }
    int i = 0;
    while(visitas[i] != -1){
        i++;
    }
    return i;
}

int * ordem_visita(matrizes* m, int* visitas){
    if(m==NULL){
        printf("Erro em ordem_visita: matrizes nulas");
        return NULL;
    }
    int tamanho_visitas = conta_visitas(visitas);

    int *ordem = (int*)malloc(sizeof(int)*100);
    if(ordem == NULL){
        printf("Erro em ordem_visita: falha no malloc");
        return NULL;
    }

    int *visitados = array_bool(tamanho_visitas);

    int elemento_de_partida = ordem[0] = visitas[0];
    int tam_ordem = 1;

    while(tem_nao_visitado(visitados) != 0){
        int proximo = determina_proximo(m, visitas, visitados, elemento_de_partida);
        int * proximo_caminho = pega_caminho(m, elemento_de_partida, proximo);

        int comeco_caminho = tam_ordem;
        for(int i =1; proximo_caminho[i]!=-1; i++){
            ordem[comeco_caminho+i-1] = proximo_caminho[i];
            tam_ordem++;
        }
        torna_visitado(visitas, visitados, proximo);
        elemento_de_partida = proximo;
    }

    ordem[tam_ordem] = -1;
    return ordem;
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

