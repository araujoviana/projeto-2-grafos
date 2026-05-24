#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<memory.h>

#include "Grafo_2026-1.h"

/*
 * Criacao de um grafo com ordem predefinida,
 * inicialmente sem nenhuma aresta
 */
void criaGrafo(Vertice **G, int ordem) {
    int i;
    *G = (Vertice*) malloc(sizeof(Vertice) * ordem);

    for (i = 0; i < ordem; i++) {
        (*G)[i].indice     = i;
        (*G)[i].nome[0]    = '\0';
        (*G)[i].detalhe[0] = '\0';
        (*G)[i].prim       = NULL;
    }
}

/*
 * Desaloca a memoria usada pelo grafo
 */
void destroiGrafo(Vertice **G, int ordem) {
    int i;
    Aresta *a, *n;

    for (i = 0; i < ordem; i++) {
        a = (*G)[i].prim;
        while (a != NULL) {
            n = a->prox;
            free(a);
            a = n;
        }
    }
    free(*G);
}

/*
 * Acrescenta aresta entre v1 e v2 (grafo nao-orientado)
 */
int acrescentaAresta(Vertice G[], int ordem, int v1, int v2) {
    Aresta *A1, *A2;

    if (v1 < 0 || v1 >= ordem)
        return 0;
    if (v2 < 0 || v2 >= ordem)
        return 0;

    A1 = (Aresta *) malloc(sizeof(Aresta));
    A1->vizinho = v2;
    A1->prox = G[v1].prim;
    G[v1].prim = A1;

    if (v1 == v2) return 1; /* laco */

    A2 = (Aresta *) malloc(sizeof(Aresta));
    A2->vizinho = v1;
    A2->prox = G[v2].prim;
    G[v2].prim = A2;

    return 1;
}

/* atribui nome e detalhes ao participante v */
void definirParticipante(Vertice G[], int v, const char *nome, const char *det) {
    strcpy(G[v].nome, nome);
    strcpy(G[v].detalhe, det);
}

/* retorna 1 se existe aresta entre v1 e v2, 0 caso contrario */
int existeAresta(Vertice G[], int ordem, int v1, int v2) {
    Aresta *aux;
    if (v1 < 0 || v1 >= ordem || v2 < 0 || v2 >= ordem)
        return 0;
    aux = G[v1].prim;
    while (aux != NULL) {
        if (aux->vizinho == v2)
            return 1;
        aux = aux->prox;
    }
    return 0;
}

/*
 * Imprime todos os participantes e suas amizades
 */
void imprimeGrafo(Vertice G[], int ordem) {
    int i;
    Aresta *aux;

    printf("=============================================================\n");
    printf("                      REDE SOCIAL\n");
    printf("=============================================================\n");
    printf("Participantes (%d):\n\n", ordem);

    for (i = 0; i < ordem; i++)
        printf("  [%2d] %-22s | %s\n", i, G[i].nome, G[i].detalhe);

    printf("\nAmizades:\n\n");
    for (i = 0; i < ordem; i++) {
        printf("  %-22s ->", G[i].nome);
        aux = G[i].prim;
        while (aux != NULL) {
            printf(" %s", G[aux->vizinho].nome);
            if (aux->prox != NULL) printf(",");
            aux = aux->prox;
        }
        printf("\n");
    }
    printf("=============================================================\n");
}
