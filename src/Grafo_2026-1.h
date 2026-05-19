/*
 * Teoria dos Grafos - 2026/1
 * Implementacao base do TAD Grafo (nao-dirigido, matriz de adjacencia)
 */

#ifndef GRAFO_2026_1_H
#define GRAFO_2026_1_H

#define MAX_VERTICES 35
#define NOME_MAX     60
#define DETALHE_MAX  120

typedef struct {
    char nome[NOME_MAX];
    char detalhe[DETALHE_MAX];
} Participante;

typedef struct {
    int ordem;
    int adj[MAX_VERTICES][MAX_VERTICES];
    Participante participantes[MAX_VERTICES];
} Grafo;

Grafo *criarGrafo(int ordem);
void   destruirGrafo(Grafo *g);

void definirParticipante(Grafo *g, int v, const char *nome, const char *detalhe);
void adicionarAresta(Grafo *g, int u, int v);
void removerAresta(Grafo *g, int u, int v);
int  existeAresta(Grafo *g, int u, int v);
int  grauVertice(Grafo *g, int v);

void exibirGrafo(Grafo *g);

#endif
