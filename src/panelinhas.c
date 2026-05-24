/*
 * Funcoes para encontrar panelinhas (grupos fechados) na rede social.
 */

#include <stdio.h>
#include <string.h>

#include "panelinhas.h"

/* escolhe o pivo: o vertice com mais vizinhos em P */
static int escolherPivo(Vertice G[], int ordem, int *P, int pSz, int *X, int xSz)
{
    int i, j, conn, maxConn, pivo;

    pivo    = P[0];
    maxConn = -1;

    for (i = 0; i < pSz; i++) {
        conn = 0;
        for (j = 0; j < pSz; j++)
            if (existeAresta(G, ordem, P[i], P[j])) conn++;
        if (conn > maxConn) { maxConn = conn; pivo = P[i]; }
    }
    for (i = 0; i < xSz; i++) {
        conn = 0;
        for (j = 0; j < pSz; j++)
            if (existeAresta(G, ordem, X[i], P[j])) conn++;
        if (conn > maxConn) { maxConn = conn; pivo = X[i]; }
    }
    return pivo;
}

/*
 * funcao recursiva do Bron-Kerbosch
 * R = grupo atual, P = candidatos, X = ja visitados
 * quando P e X ficam vazios, R e um clique maximal (panelinha se tamanho >= 3)
 */
static void bk(Vertice G[], int ordem,
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

    pivo = escolherPivo(G, ordem, P, pSz, X, xSz);

    nCand = 0;
    for (i = 0; i < pSz; i++)
        if (!existeAresta(G, ordem, pivo, P[i])) candidatos[nCand++] = P[i];

    curPSz = pSz; curXSz = xSz;
    for (i = 0; i < pSz; i++) curP[i] = P[i];
    for (i = 0; i < xSz; i++) curX[i] = X[i];

    for (i = 0; i < nCand; i++) {
        v = candidatos[i];

        for (j = 0; j < rSz; j++) newR[j] = R[j];
        newR[rSz] = v;
        newRSz = rSz + 1;

        newPSz = 0;
        for (j = 0; j < curPSz; j++)
            if (existeAresta(G, ordem, v, curP[j])) newP[newPSz++] = curP[j];

        newXSz = 0;
        for (j = 0; j < curXSz; j++)
            if (existeAresta(G, ordem, v, curX[j])) newX[newXSz++] = curX[j];

        bk(G, ordem, newR, newRSz, newP, newPSz, newX, newXSz, res);

        for (j = 0; j < curPSz; j++) {
            if (curP[j] == v) { curP[j] = curP[--curPSz]; break; }
        }
        curX[curXSz++] = v;
    }
}

void encontrarPanelinhas(Vertice G[], int ordem, ListaPanelinhas *res)
{
    int i;
    int P[MAX_VERTICES], X[MAX_VERTICES], R[MAX_VERTICES];

    if (!G || !res) return;

    res->qtd = 0;
    for (i = 0; i < ordem; i++) P[i] = i;
    bk(G, ordem, R, 0, P, ordem, X, 0, res);
}

void exibirPanelinhas(Vertice G[], ListaPanelinhas *lp)
{
    int i, j;

    if (!G || !lp) return;

    printf("\n=== Panelinhas (%d encontradas) ===\n\n", lp->qtd);
    for (i = 0; i < lp->qtd; i++) {
        printf("  Panelinha %2d (tamanho %d): { ", i + 1, lp->lista[i].tamanho);
        for (j = 0; j < lp->lista[i].tamanho; j++) {
            if (j) printf(", ");
            printf("%s", G[lp->lista[i].membros[j]].nome);
        }
        printf(" }\n");
    }
}

void consultarPorMembro(Vertice G[], ListaPanelinhas *lp, int vertice)
{
    int i, j, achou, count;

    if (!G || !lp) return;

    count = 0;
    printf("\n=== Panelinhas de \"%s\" ===\n\n", G[vertice].nome);

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
            printf("%s", G[lp->lista[i].membros[j]].nome);
        }
        printf(" }\n");
    }
    if (!count) printf("  (nenhuma panelinha encontrada)\n");
}

/* lista os influentes: participantes em 2+ panelinhas
   onde a intersecao das panelinhas so contem esse participante */
void consultarInfluentes(Vertice G[], int ordem, ListaPanelinhas *lp)
{
    int v, i, j, k, m, em_comum, encontrou;
    int cliquesDeV[MAX_PANELINHAS], nCliques;
    int algum;
    Panelinha *a, *b;

    if (!G || !lp) return;

    printf("\n=== Elementos Influentes ===\n\n");
    algum = 0;

    for (v = 0; v < ordem; v++) {
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
                if (em_comum == 1) {
                    encontrou = 1;
                    algum = 1;
                    printf("  - %s (panelinhas %d e %d)\n",
                           G[v].nome,
                           cliquesDeV[i] + 1,
                           cliquesDeV[j] + 1);
                }
            }
        }
    }
    if (!algum) printf("  (nenhum elemento influente encontrado)\n");
}

Panelinha *maiorPanelinha(ListaPanelinhas *lp)
{
    int i;
    Panelinha *maior = NULL;

    if (!lp) return NULL;

    for (i = 0; i < lp->qtd; i++) {
        if (!maior || lp->lista[i].tamanho > maior->tamanho)
            maior = &lp->lista[i];
    }
    return maior;
}
