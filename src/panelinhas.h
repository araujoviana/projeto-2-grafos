#ifndef PANELINHAS_H
#define PANELINHAS_H

#include "Grafo_2026-1.h"

#define MAX_PANELINHAS    200
#define MIN_TAM_PANELINHA 3

typedef struct {
    int membros[MAX_VERTICES];
    int tamanho;
} Panelinha;

typedef struct {
    Panelinha lista[MAX_PANELINHAS];
    int qtd;
} ListaPanelinhas;

void encontrarPanelinhas(Vertice G[], int ordem, ListaPanelinhas *res);
void exibirPanelinhas(Vertice G[], ListaPanelinhas *lp);
void consultarPorMembro(Vertice G[], ListaPanelinhas *lp, int vertice);
void consultarInfluentes(Vertice G[], int ordem, ListaPanelinhas *lp);
Panelinha *maiorPanelinha(ListaPanelinhas *lp);

#endif
