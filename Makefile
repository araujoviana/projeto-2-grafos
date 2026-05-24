CC     = gcc
CFLAGS = -ansi -Wall -pedantic
SRC    = src/main.c src/Grafo_2026-1.c src/panelinhas.c

all: programa

programa: $(SRC)
	$(CC) $(CFLAGS) -I src -o programa $(SRC)

clean:
	rm -f programa

.PHONY: all clean
