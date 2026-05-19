/*
 * Teoria dos Grafos - 2026/1  |  Universidade Presbiteriana Mackenzie
 * Projeto 2: Panelinhas em um Grupo Social
 *
 * Grupo:
 *   -
 *   -
 *   -
 *   -
 *   -
 *
 * Descricao:
 *   Modela uma rede social como um grafo nao-dirigido (vertices = participantes,
 *   arestas = amizades) e identifica panelinhas (cliques maximais com >= 3
 *   membros) usando o algoritmo de Bron-Kerbosch com pivotamento.
 *   Tambem detecta elementos influentes: participantes presentes em duas ou
 *   mais panelinhas alpha e beta tais que alpha intersec beta = {participante}.
 */

#include <stdio.h>
#include "Grafo_2026-1.h"
#include "panelinhas.h"

/*
 * Rede social com 30 participantes.
 *
 * Panelinhas esperadas (12 no total):
 *   1. { Ana Clara, Bruno Henrique, Carlos Eduardo, Daniela Ferreira }
 *   2. { Ana Clara, Eduardo Santos, Fernanda Lima }
 *   3. { Gabriel Oliveira, Helena Costa, Igor Matos, Julia Carvalho }
 *   4. { Gabriel Oliveira, Kevin Alves, Laura Rodrigues }
 *   5. { Marcos Pereira, Natalia Souza, Otavio Mendes }
 *   6. { Patricia Gomes, Rafael Barbosa, Sabrina Castro }
 *   7. { Natalia Souza, Patricia Gomes, Thiago Ribeiro }
 *   8. { Ursula Freitas, Victor Moreira, Wanessa Dias }
 *   9. { Xavier Nunes, Yara Cavalcanti, Zeca Pinto }
 *  10. { Ursula Freitas, Xavier Nunes, Alice Monteiro }
 *  11. { Alice Monteiro, Bernardo Farias, Carla Teixeira }
 *  12. { Carla Teixeira, Diego Correia, Elisa Vieira }
 *
 * Influentes esperados (8):
 *   Ana Clara, Gabriel Oliveira, Natalia Souza, Patricia Gomes,
 *   Ursula Freitas, Xavier Nunes, Alice Monteiro, Carla Teixeira
 */
static Grafo *inicializarRedeSocial(void)
{
    Grafo *g = criarGrafo(30);
    if (!g) return NULL;

    /* --- participantes --- */
    definirParticipante(g,  0, "Ana Clara",       "Computacao, 20 anos");
    definirParticipante(g,  1, "Bruno Henrique",   "Engenharia Eletrica, 21 anos");
    definirParticipante(g,  2, "Carlos Eduardo",   "Computacao, 22 anos");
    definirParticipante(g,  3, "Daniela Ferreira", "Matematica, 20 anos");
    definirParticipante(g,  4, "Eduardo Santos",   "Fisica, 23 anos");
    definirParticipante(g,  5, "Fernanda Lima",    "Quimica, 21 anos");
    definirParticipante(g,  6, "Gabriel Oliveira", "Administracao, 22 anos");
    definirParticipante(g,  7, "Helena Costa",     "Medicina, 24 anos");
    definirParticipante(g,  8, "Igor Matos",       "Direito, 21 anos");
    definirParticipante(g,  9, "Julia Carvalho",   "Letras, 20 anos");
    definirParticipante(g, 10, "Kevin Alves",      "Arquitetura, 23 anos");
    definirParticipante(g, 11, "Laura Rodrigues",  "Psicologia, 22 anos");
    definirParticipante(g, 12, "Marcos Pereira",   "Economia, 24 anos");
    definirParticipante(g, 13, "Natalia Souza",    "Publicidade, 21 anos");
    definirParticipante(g, 14, "Otavio Mendes",    "Jornalismo, 22 anos");
    definirParticipante(g, 15, "Patricia Gomes",   "Pedagogia, 23 anos");
    definirParticipante(g, 16, "Rafael Barbosa",   "Historia, 20 anos");
    definirParticipante(g, 17, "Sabrina Castro",   "Filosofia, 21 anos");
    definirParticipante(g, 18, "Thiago Ribeiro",   "Sociologia, 22 anos");
    definirParticipante(g, 19, "Ursula Freitas",   "Biologia, 23 anos");
    definirParticipante(g, 20, "Victor Moreira",   "Educacao Fisica, 20 anos");
    definirParticipante(g, 21, "Wanessa Dias",     "Nutricao, 21 anos");
    definirParticipante(g, 22, "Xavier Nunes",     "Design, 22 anos");
    definirParticipante(g, 23, "Yara Cavalcanti",  "Moda, 24 anos");
    definirParticipante(g, 24, "Zeca Pinto",       "Musica, 21 anos");
    definirParticipante(g, 25, "Alice Monteiro",   "Cinema, 22 anos");
    definirParticipante(g, 26, "Bernardo Farias",  "Teatro, 23 anos");
    definirParticipante(g, 27, "Carla Teixeira",   "Danca, 20 anos");
    definirParticipante(g, 28, "Diego Correia",    "Artes Visuais, 21 anos");
    definirParticipante(g, 29, "Elisa Vieira",     "Fotografia, 22 anos");

    /* --- panelinha 1: Ana, Bruno, Carlos, Daniela {0,1,2,3} --- */
    adicionarAresta(g, 0, 1); adicionarAresta(g, 0, 2); adicionarAresta(g, 0, 3);
    adicionarAresta(g, 1, 2); adicionarAresta(g, 1, 3); adicionarAresta(g, 2, 3);

    /* --- panelinha 2: Ana, Eduardo, Fernanda {0,4,5} --- */
    adicionarAresta(g, 0, 4); adicionarAresta(g, 0, 5); adicionarAresta(g, 4, 5);

    /* --- panelinha 3: Gabriel, Helena, Igor, Julia {6,7,8,9} --- */
    adicionarAresta(g, 6, 7); adicionarAresta(g, 6, 8); adicionarAresta(g, 6, 9);
    adicionarAresta(g, 7, 8); adicionarAresta(g, 7, 9); adicionarAresta(g, 8, 9);

    /* --- panelinha 4: Gabriel, Kevin, Laura {6,10,11} --- */
    adicionarAresta(g, 6, 10); adicionarAresta(g, 6, 11); adicionarAresta(g, 10, 11);

    /* --- panelinha 5: Marcos, Natalia, Otavio {12,13,14} --- */
    adicionarAresta(g, 12, 13); adicionarAresta(g, 12, 14); adicionarAresta(g, 13, 14);

    /* --- panelinha 6: Patricia, Rafael, Sabrina {15,16,17} --- */
    adicionarAresta(g, 15, 16); adicionarAresta(g, 15, 17); adicionarAresta(g, 16, 17);

    /* --- panelinha 7: Natalia, Patricia, Thiago {13,15,18} --- */
    adicionarAresta(g, 13, 15); adicionarAresta(g, 13, 18); adicionarAresta(g, 15, 18);

    /* --- panelinha 8: Ursula, Victor, Wanessa {19,20,21} --- */
    adicionarAresta(g, 19, 20); adicionarAresta(g, 19, 21); adicionarAresta(g, 20, 21);

    /* --- panelinha 9: Xavier, Yara, Zeca {22,23,24} --- */
    adicionarAresta(g, 22, 23); adicionarAresta(g, 22, 24); adicionarAresta(g, 23, 24);

    /* --- panelinha 10: Ursula, Xavier, Alice {19,22,25} --- */
    adicionarAresta(g, 19, 22); adicionarAresta(g, 19, 25); adicionarAresta(g, 22, 25);

    /* --- panelinha 11: Alice, Bernardo, Carla {25,26,27} --- */
    adicionarAresta(g, 25, 26); adicionarAresta(g, 25, 27); adicionarAresta(g, 26, 27);

    /* --- panelinha 12: Carla, Diego, Elisa {27,28,29} --- */
    adicionarAresta(g, 27, 28); adicionarAresta(g, 27, 29); adicionarAresta(g, 28, 29);

    /* --- amizades extras (nao formam novas panelinhas) --- */
    adicionarAresta(g,  2, 22); /* Carlos   - Xavier   */
    adicionarAresta(g,  3, 19); /* Daniela  - Ursula   */
    adicionarAresta(g,  4, 20); /* Eduardo  - Victor   */
    adicionarAresta(g,  5, 23); /* Fernanda - Yara     */
    adicionarAresta(g,  7, 14); /* Helena   - Otavio   */
    adicionarAresta(g,  8, 16); /* Igor     - Rafael   */
    adicionarAresta(g,  9, 18); /* Julia    - Thiago   */
    adicionarAresta(g, 10, 26); /* Kevin    - Bernardo */
    adicionarAresta(g, 11, 28); /* Laura    - Diego    */
    adicionarAresta(g, 12, 24); /* Marcos   - Zeca     */
    adicionarAresta(g, 16, 21); /* Rafael   - Wanessa  */
    adicionarAresta(g, 17, 29); /* Sabrina  - Elisa    */

    return g;
}

int main(void)
{
    Grafo *g;
    ListaPanelinhas panelinhas;
    Panelinha *maior;
    int i;

    g = inicializarRedeSocial();
    if (!g) { printf("Erro ao alocar grafo.\n"); return 1; }

    /* Exibe todos os detalhes da rede */
    exibirGrafo(g);

    /* Encontra e exibe todas as panelinhas */
    encontrarPanelinhas(g, &panelinhas);
    exibirPanelinhas(g, &panelinhas);

    /* Consulta as panelinhas de membros especificos */
    consultarPorMembro(g, &panelinhas,  0); /* Ana Clara      */
    consultarPorMembro(g, &panelinhas,  6); /* Gabriel        */
    consultarPorMembro(g, &panelinhas, 13); /* Natalia Souza  */
    consultarPorMembro(g, &panelinhas, 27); /* Carla Teixeira */

    /* Exibe todos os elementos influentes */
    consultarInfluentes(g, &panelinhas);

    /* Maior panelinha */
    maior = maiorPanelinha(&panelinhas);
    if (maior) {
        printf("\n=== Maior Panelinha (tamanho %d) ===\n\n  { ", maior->tamanho);
        for (i = 0; i < maior->tamanho; i++) {
            if (i) printf(", ");
            printf("%s", g->participantes[maior->membros[i]].nome);
        }
        printf(" }\n");
    }

    destruirGrafo(g);
    return 0;
}
