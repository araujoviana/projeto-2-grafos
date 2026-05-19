/*
 * Teoria dos Grafos - 2026/1
 * Algoritmo de Bron-Kerbosch com pivotamento para enumerar cliques maximais.
 *
 * Referencia:
 *   Bron, C.; Kerbosch, J. (1973). "Algorithm 457: Finding all cliques of an
 *   undirected graph". Communications of the ACM. 16 (9): 575-577.
 */

#include <stdio.h>
#include <string.h>

#include "panelinhas.h"

/*
 * Escolhe o vertice pivô u em P U X que maximiza |N(u) ∩ P|.
 * Reduz o numero de chamadas recursivas ao excluir N(pivô) dos candidatos.
 */
static int escolherPivo(Grafo *g, int *P, int pSz, int *X, int xSz)
{
    int i, j, conn, maxConn, pivo;

    pivo    = P[0];
    maxConn = -1;

    for (i = 0; i < pSz; i++) {
        conn = 0;
        for (j = 0; j < pSz; j++)
            if (existeAresta(g, P[i], P[j])) conn++;
        if (conn > maxConn) { maxConn = conn; pivo = P[i]; }
    }
    for (i = 0; i < xSz; i++) {
        conn = 0;
        for (j = 0; j < pSz; j++)
            if (existeAresta(g, X[i], P[j])) conn++;
        if (conn > maxConn) { maxConn = conn; pivo = X[i]; }
    }
    return pivo;
}

/*
 * BronKerbosch(R, P, X):
 *   se P e X vazios -> relata R como clique maximal
 *   pivo u = argmax_{v in P U X} |N(v) ∩ P|
 *   para cada v em P \ N(u):
 *       BronKerbosch(R U {v}, P ∩ N(v), X ∩ N(v))
 *       P = P \ {v}
 *       X = X U {v}
 */
static void bk(Grafo *g,
               int *R, int rSz,
               int *P, int pSz,
               int *X, int xSz,
               ListaPanelinhas *res)
{
    int i, j, pivo, v;
    int candidatos[MAX_VERTICES], nCand;
    int curP[MAX_VERTICES], curX[MAX_VERTICES];
    int curPSz, curXSz;
    int newR[MAX_VERTICES], newP[MAX_VERTICES], newX[MAX_VERTICES];
    int newRSz, newPSz, newXSz;
    Panelinha *pan;

    if (pSz == 0 && xSz == 0) {
        if (rSz >= MIN_TAM_PANELINHA && res->qtd < MAX_PANELINHAS) {
            pan = &res->lista[res->qtd++];
            pan->tamanho = rSz;
            for (i = 0; i < rSz; i++) pan->membros[i] = R[i];
        }
        return;
    }
    if (pSz == 0) return;

    pivo = escolherPivo(g, P, pSz, X, xSz);

    /* Candidatos: P \ N(pivo) */
    nCand = 0;
    for (i = 0; i < pSz; i++)
        if (!existeAresta(g, pivo, P[i])) candidatos[nCand++] = P[i];

    /* Copias de trabalho de P e X (modificadas a cada iteracao) */
    curPSz = pSz; curXSz = xSz;
    for (i = 0; i < pSz; i++) curP[i] = P[i];
    for (i = 0; i < xSz; i++) curX[i] = X[i];

    for (i = 0; i < nCand; i++) {
        v = candidatos[i];

        /* newR = R U {v} */
        for (j = 0; j < rSz; j++) newR[j] = R[j];
        newR[rSz] = v;
        newRSz = rSz + 1;

        /* newP = curP ∩ N(v) */
        newPSz = 0;
        for (j = 0; j < curPSz; j++)
            if (existeAresta(g, v, curP[j])) newP[newPSz++] = curP[j];

        /* newX = curX ∩ N(v) */
        newXSz = 0;
        for (j = 0; j < curXSz; j++)
            if (existeAresta(g, v, curX[j])) newX[newXSz++] = curX[j];

        bk(g, newR, newRSz, newP, newPSz, newX, newXSz, res);

        /* Move v de curP para curX */
        for (j = 0; j < curPSz; j++) {
            if (curP[j] == v) { curP[j] = curP[--curPSz]; break; }
        }
        curX[curXSz++] = v;
    }
}

void encontrarPanelinhas(Grafo *g, ListaPanelinhas *res)
{
    int i;
    int P[MAX_VERTICES], X[MAX_VERTICES], R[MAX_VERTICES];

    res->qtd = 0;
    for (i = 0; i < g->ordem; i++) P[i] = i;
    bk(g, R, 0, P, g->ordem, X, 0, res);
}

void exibirPanelinhas(Grafo *g, ListaPanelinhas *lp)
{
    int i, j;

    printf("\n=== Panelinhas (%d encontradas) ===\n\n", lp->qtd);
    for (i = 0; i < lp->qtd; i++) {
        printf("  Panelinha %2d (tamanho %d): { ", i + 1, lp->lista[i].tamanho);
        for (j = 0; j < lp->lista[i].tamanho; j++) {
            if (j) printf(", ");
            printf("%s", g->participantes[lp->lista[i].membros[j]].nome);
        }
        printf(" }\n");
    }
}

void consultarPorMembro(Grafo *g, ListaPanelinhas *lp, int vertice)
{
    int i, j, achou, count;

    count = 0;
    printf("\n=== Panelinhas de \"%s\" ===\n\n", g->participantes[vertice].nome);

    for (i = 0; i < lp->qtd; i++) {
        achou = 0;
        for (j = 0; j < lp->lista[i].tamanho; j++) {
            if (lp->lista[i].membros[j] == vertice) { achou = 1; break; }
        }
        if (!achou) continue;
        count++;
        printf("  %d. { ", count);
        for (j = 0; j < lp->lista[i].tamanho; j++) {
            if (j) printf(", ");
            printf("%s", g->participantes[lp->lista[i].membros[j]].nome);
        }
        printf(" }\n");
    }
    if (!count) printf("  (nenhuma panelinha encontrada)\n");
}

/*
 * Um elemento v eh influente se existem panelinhas alpha e beta com
 * v em alpha, v em beta, e alpha intersec beta = {v}.
 */
void consultarInfluentes(Grafo *g, ListaPanelinhas *lp)
{
    int v, i, j, k, m, em_comum;
    int cliquesDeV[MAX_PANELINHAS], nCliques;
    int encontrou, algum;
    Panelinha *a, *b;

    printf("\n=== Elementos Influentes ===\n\n");
    algum = 0;

    for (v = 0; v < g->ordem; v++) {
        nCliques = 0;
        for (i = 0; i < lp->qtd; i++) {
            for (j = 0; j < lp->lista[i].tamanho; j++) {
                if (lp->lista[i].membros[j] == v) {
                    cliquesDeV[nCliques++] = i;
                    break;
                }
            }
        }
        if (nCliques < 2) continue;

        encontrou = 0;
        for (i = 0; i < nCliques && !encontrou; i++) {
            for (j = i + 1; j < nCliques && !encontrou; j++) {
                a = &lp->lista[cliquesDeV[i]];
                b = &lp->lista[cliquesDeV[j]];
                em_comum = 0;
                for (k = 0; k < a->tamanho; k++) {
                    for (m = 0; m < b->tamanho; m++) {
                        if (a->membros[k] == b->membros[m]) em_comum++;
                    }
                }
                /* intersecao = {v} apenas */
                if (em_comum == 1) encontrou = 1;
            }
        }
        if (encontrou) {
            printf("  - %s\n", g->participantes[v].nome);
            algum = 1;
        }
    }
    if (!algum) printf("  (nenhum elemento influente encontrado)\n");
}

Panelinha *maiorPanelinha(ListaPanelinhas *lp)
{
    int i;
    Panelinha *maior = NULL;

    for (i = 0; i < lp->qtd; i++) {
        if (!maior || lp->lista[i].tamanho > maior->tamanho)
            maior = &lp->lista[i];
    }
    return maior;
}
