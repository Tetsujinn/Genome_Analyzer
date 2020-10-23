CC=gcc

CFLAGS=-Wall
OFLAGS=-O3

all: genysis split

genysis: src/genysis.c
	$(CC) $(CFLAGS) $(OFLAGS) $< -o $@

split: src/split.c
	$(CC) $(CFLAGS) $(OFLAGS) $< -o $@

clean:
	rm -Rf *~ src/*~ genysis split

