/*
 * Teoria dos Grafos - 2026/1
 * Identificacao de panelinhas (cliques maximais) em uma rede social
 */

#ifndef PANELINHAS_H
#define PANELINHAS_H

#include "Grafo_2026-1.h"

#define MAX_PANELINHAS      200
#define MIN_TAM_PANELINHA   3

typedef struct {
    int membros[MAX_VERTICES];
    int tamanho;
} Panelinha;

typedef struct {
    Panelinha lista[MAX_PANELINHAS];
    int qtd;
} ListaPanelinhas;

/* Encontra todas as panelinhas (cliques maximais de tamanho >= 3) */
void encontrarPanelinhas(Grafo *g, ListaPanelinhas *res);

/* Exibe todas as panelinhas encontradas */
void exibirPanelinhas(Grafo *g, ListaPanelinhas *lp);

/* Lista todas as panelinhas das quais 'vertice' faz parte */
void consultarPorMembro(Grafo *g, ListaPanelinhas *lp, int vertice);

/*
 * Lista os elementos influentes: pertencem a duas ou mais panelinhas
 * alpha e beta tais que alpha intersec beta = { elemento }.
 */
void consultarInfluentes(Grafo *g, ListaPanelinhas *lp);

/* Retorna ponteiro para a panelinha de maior tamanho */
Panelinha *maiorPanelinha(ListaPanelinhas *lp);

#endif
