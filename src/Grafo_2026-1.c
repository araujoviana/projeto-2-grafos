/*
 * Teoria dos Grafos - 2026/1
 * Implementacao base do TAD Grafo
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Grafo_2026-1.h"

Grafo *criarGrafo(int ordem)
{
    int i, j;
    Grafo *g;

    if (ordem < 1 || ordem > MAX_VERTICES) return NULL;

    g = (Grafo *)malloc(sizeof(Grafo));
    if (!g) return NULL;

    g->ordem = ordem;
    for (i = 0; i < ordem; i++) {
        for (j = 0; j < ordem; j++)
            g->adj[i][j] = 0;
        g->participantes[i].nome[0]    = '\0';
        g->participantes[i].detalhe[0] = '\0';
    }
    return g;
}

void destruirGrafo(Grafo *g)
{
    if (g) free(g);
}

void definirParticipante(Grafo *g, int v, const char *nome, const char *detalhe)
{
    if (!g || v < 0 || v >= g->ordem) return;
    strncpy(g->participantes[v].nome,    nome,    NOME_MAX    - 1);
    strncpy(g->participantes[v].detalhe, detalhe, DETALHE_MAX - 1);
    g->participantes[v].nome[NOME_MAX       - 1] = '\0';
    g->participantes[v].detalhe[DETALHE_MAX - 1] = '\0';
}

void adicionarAresta(Grafo *g, int u, int v)
{
    if (!g || u < 0 || u >= g->ordem || v < 0 || v >= g->ordem || u == v) return;
    g->adj[u][v] = 1;
    g->adj[v][u] = 1;
}

void removerAresta(Grafo *g, int u, int v)
{
    if (!g || u < 0 || u >= g->ordem || v < 0 || v >= g->ordem) return;
    g->adj[u][v] = 0;
    g->adj[v][u] = 0;
}

int existeAresta(Grafo *g, int u, int v)
{
    if (!g || u < 0 || u >= g->ordem || v < 0 || v >= g->ordem) return 0;
    return g->adj[u][v];
}

int grauVertice(Grafo *g, int v)
{
    int i, grau = 0;
    if (!g || v < 0 || v >= g->ordem) return -1;
    for (i = 0; i < g->ordem; i++)
        grau += g->adj[v][i];
    return grau;
}

void exibirGrafo(Grafo *g)
{
    int i, j, primeiro;

    if (!g) return;

    printf("=============================================================\n");
    printf("                      REDE SOCIAL\n");
    printf("=============================================================\n");
    printf("Participantes (%d):\n\n", g->ordem);

    for (i = 0; i < g->ordem; i++) {
        printf("  [%2d] %-22s | %s\n",
               i,
               g->participantes[i].nome,
               g->participantes[i].detalhe);
    }

    printf("\nAmizades (grau):\n\n");
    for (i = 0; i < g->ordem; i++) {
        printf("  %-22s (grau %2d) ->", g->participantes[i].nome, grauVertice(g, i));
        primeiro = 1;
        for (j = 0; j < g->ordem; j++) {
            if (g->adj[i][j]) {
                printf("%s %s", primeiro ? "" : ",", g->participantes[j].nome);
                primeiro = 0;
            }
        }
        printf("\n");
    }
    printf("=============================================================\n");
}
