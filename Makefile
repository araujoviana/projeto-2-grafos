CC      = gcc
CFLAGS  = -ansi -Wall -pedantic
SRC     = src/main.c src/Grafo_2026-1.c src/panelinhas.c
TARGET  = programa

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -I src -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)

test: all
	python3 tests/test_panelinhas.py -v

.PHONY: all clean test
