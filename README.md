# Panelinhas em um Grupo Social

Projeto 2 - Teoria dos Grafos (Mackenzie 2026/1)

## Como compilar

```bash
gcc -ansi -Wall -o programa src/main.c src/Grafo_2026-1.c src/panelinhas.c -I src
./programa
```

Ou com o Makefile:

```bash
make
./programa
```

## O que o programa faz

Modela uma rede social de 30 pessoas como um grafo nao-dirigido.
Encontra as panelinhas (grupos fechados com no minimo 3 membros) e
identifica os membros influentes (quem faz parte de duas ou mais
panelinhas que nao compartilham outros membros).
