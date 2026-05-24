/*
 * Grupo:
 *   - Matheus Gabriel Viana Araujo - 10420444
 *   - [NOME COMPLETO 2] - [RA]
 *   - [NOME COMPLETO 3] - [RA]
 *   - [NOME COMPLETO 4] - [RA]
 *   - [NOME COMPLETO 5] - [RA]
 */

#include <stdio.h>
#include "Grafo_2026-1.h"
#include "panelinhas.h"

/* monta a rede com 30 participantes e suas amizades */
static void inicializarRede(Vertice **G, int *ordem)
{
    *ordem = 30;
    criaGrafo(G, *ordem);

    /* participantes */
    definirParticipante(*G,  0, "Ana Clara",       "Computacao, 20 anos");
    definirParticipante(*G,  1, "Bruno Henrique",   "Engenharia Eletrica, 21 anos");
    definirParticipante(*G,  2, "Carlos Eduardo",   "Computacao, 22 anos");
    definirParticipante(*G,  3, "Daniela Ferreira", "Matematica, 20 anos");
    definirParticipante(*G,  4, "Eduardo Santos",   "Fisica, 23 anos");
    definirParticipante(*G,  5, "Fernanda Lima",    "Quimica, 21 anos");
    definirParticipante(*G,  6, "Gabriel Oliveira", "Administracao, 22 anos");
    definirParticipante(*G,  7, "Helena Costa",     "Medicina, 24 anos");
    definirParticipante(*G,  8, "Igor Matos",       "Direito, 21 anos");
    definirParticipante(*G,  9, "Julia Carvalho",   "Letras, 20 anos");
    definirParticipante(*G, 10, "Kevin Alves",      "Arquitetura, 23 anos");
    definirParticipante(*G, 11, "Laura Rodrigues",  "Psicologia, 22 anos");
    definirParticipante(*G, 12, "Marcos Pereira",   "Economia, 24 anos");
    definirParticipante(*G, 13, "Natalia Souza",    "Publicidade, 21 anos");
    definirParticipante(*G, 14, "Otavio Mendes",    "Jornalismo, 22 anos");
    definirParticipante(*G, 15, "Patricia Gomes",   "Pedagogia, 23 anos");
    definirParticipante(*G, 16, "Rafael Barbosa",   "Historia, 20 anos");
    definirParticipante(*G, 17, "Sabrina Castro",   "Filosofia, 21 anos");
    definirParticipante(*G, 18, "Thiago Ribeiro",   "Sociologia, 22 anos");
    definirParticipante(*G, 19, "Ursula Freitas",   "Biologia, 23 anos");
    definirParticipante(*G, 20, "Victor Moreira",   "Educacao Fisica, 20 anos");
    definirParticipante(*G, 21, "Wanessa Dias",     "Nutricao, 21 anos");
    definirParticipante(*G, 22, "Xavier Nunes",     "Design, 22 anos");
    definirParticipante(*G, 23, "Yara Cavalcanti",  "Moda, 24 anos");
    definirParticipante(*G, 24, "Zeca Pinto",       "Musica, 21 anos");
    definirParticipante(*G, 25, "Alice Monteiro",   "Cinema, 22 anos");
    definirParticipante(*G, 26, "Bernardo Farias",  "Teatro, 23 anos");
    definirParticipante(*G, 27, "Carla Teixeira",   "Danca, 20 anos");
    definirParticipante(*G, 28, "Diego Correia",    "Artes Visuais, 21 anos");
    definirParticipante(*G, 29, "Elisa Vieira",     "Fotografia, 22 anos");

    /* panelinha 1: Ana, Bruno, Carlos, Daniela */
    acrescentaAresta(*G, *ordem, 0, 1); acrescentaAresta(*G, *ordem, 0, 2); acrescentaAresta(*G, *ordem, 0, 3);
    acrescentaAresta(*G, *ordem, 1, 2); acrescentaAresta(*G, *ordem, 1, 3); acrescentaAresta(*G, *ordem, 2, 3);

    /* panelinha 2: Ana, Eduardo, Fernanda */
    acrescentaAresta(*G, *ordem, 0, 4); acrescentaAresta(*G, *ordem, 0, 5); acrescentaAresta(*G, *ordem, 4, 5);

    /* panelinha 3: Gabriel, Helena, Igor, Julia */
    acrescentaAresta(*G, *ordem, 6, 7); acrescentaAresta(*G, *ordem, 6, 8); acrescentaAresta(*G, *ordem, 6, 9);
    acrescentaAresta(*G, *ordem, 7, 8); acrescentaAresta(*G, *ordem, 7, 9); acrescentaAresta(*G, *ordem, 8, 9);

    /* panelinha 4: Gabriel, Kevin, Laura */
    acrescentaAresta(*G, *ordem, 6, 10); acrescentaAresta(*G, *ordem, 6, 11); acrescentaAresta(*G, *ordem, 10, 11);

    /* panelinha 5: Marcos, Natalia, Otavio */
    acrescentaAresta(*G, *ordem, 12, 13); acrescentaAresta(*G, *ordem, 12, 14); acrescentaAresta(*G, *ordem, 13, 14);

    /* panelinha 6: Patricia, Rafael, Sabrina */
    acrescentaAresta(*G, *ordem, 15, 16); acrescentaAresta(*G, *ordem, 15, 17); acrescentaAresta(*G, *ordem, 16, 17);

    /* panelinha 7: Natalia, Patricia, Thiago */
    acrescentaAresta(*G, *ordem, 13, 15); acrescentaAresta(*G, *ordem, 13, 18); acrescentaAresta(*G, *ordem, 15, 18);

    /* panelinha 8: Ursula, Victor, Wanessa */
    acrescentaAresta(*G, *ordem, 19, 20); acrescentaAresta(*G, *ordem, 19, 21); acrescentaAresta(*G, *ordem, 20, 21);

    /* panelinha 9: Xavier, Yara, Zeca */
    acrescentaAresta(*G, *ordem, 22, 23); acrescentaAresta(*G, *ordem, 22, 24); acrescentaAresta(*G, *ordem, 23, 24);

    /* panelinha 10: Ursula, Xavier, Alice */
    acrescentaAresta(*G, *ordem, 19, 22); acrescentaAresta(*G, *ordem, 19, 25); acrescentaAresta(*G, *ordem, 22, 25);

    /* panelinha 11: Alice, Bernardo, Carla */
    acrescentaAresta(*G, *ordem, 25, 26); acrescentaAresta(*G, *ordem, 25, 27); acrescentaAresta(*G, *ordem, 26, 27);

    /* panelinha 12: Carla, Diego, Elisa */
    acrescentaAresta(*G, *ordem, 27, 28); acrescentaAresta(*G, *ordem, 27, 29); acrescentaAresta(*G, *ordem, 28, 29);

    /* amizades extras que nao formam novas panelinhas */
    acrescentaAresta(*G, *ordem,  2, 22);
    acrescentaAresta(*G, *ordem,  3, 19);
    acrescentaAresta(*G, *ordem,  4, 20);
    acrescentaAresta(*G, *ordem,  5, 23);
    acrescentaAresta(*G, *ordem,  7, 14);
    acrescentaAresta(*G, *ordem,  8, 16);
    acrescentaAresta(*G, *ordem,  9, 18);
    acrescentaAresta(*G, *ordem, 10, 26);
    acrescentaAresta(*G, *ordem, 11, 28);
    acrescentaAresta(*G, *ordem, 12, 24);
    acrescentaAresta(*G, *ordem, 16, 21);
    acrescentaAresta(*G, *ordem, 17, 29);
}

int main(void)
{
    Vertice *G;
    int ordem;
    ListaPanelinhas panelinhas;
    Panelinha *maior;
    int i;

    inicializarRede(&G, &ordem);

    imprimeGrafo(G, ordem);

    encontrarPanelinhas(G, ordem, &panelinhas);
    exibirPanelinhas(G, &panelinhas);

    /* consulta panelinhas de alguns membros */
    consultarPorMembro(G, &panelinhas,  0); /* Ana Clara      */
    consultarPorMembro(G, &panelinhas,  6); /* Gabriel        */
    consultarPorMembro(G, &panelinhas, 13); /* Natalia Souza  */
    consultarPorMembro(G, &panelinhas, 27); /* Carla Teixeira */

    consultarInfluentes(G, ordem, &panelinhas);

    maior = maiorPanelinha(&panelinhas);
    if (maior) {
        printf("\n=== Maior Panelinha (tamanho %d) ===\n\n  { ", maior->tamanho);
        for (i = 0; i < maior->tamanho; i++) {
            if (i) printf(", ");
            printf("%s", G[maior->membros[i]].nome);
        }
        printf(" }\n");
    }

    destroiGrafo(&G, ordem);
    return 0;
}
