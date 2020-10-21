CC=gcc

CFLAGS=-Wall

all: genysis

genysis: src/genysis.c
	$(CC) $(CFLAGS) $< -o $@


clean:
	rm -Rf *~ genysis src/*~

