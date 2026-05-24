#ifndef GRAFO_2026_1_H
#define GRAFO_2026_1_H

#define MAX_VERTICES  35
#define NOME_MAX      60
#define DETALHE_MAX   120

/* celula de uma lista de arestas */
typedef struct a {
    int    vizinho;
    struct a *prox;
} Aresta;

/* cada vertice guarda nome e detalhes do participante */
typedef struct v {
    int  indice;
    char nome[NOME_MAX];
    char detalhe[DETALHE_MAX];
    Aresta *prim;
} Vertice;

void criaGrafo(Vertice **G, int ordem);
void destroiGrafo(Vertice **G, int ordem);
int  acrescentaAresta(Vertice G[], int ordem, int v1, int v2);
void definirParticipante(Vertice G[], int v, const char *nome, const char *det);
int  existeAresta(Vertice G[], int ordem, int v1, int v2);
void imprimeGrafo(Vertice G[], int ordem);

#endif
