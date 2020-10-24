CC=gcc

CFLAGS=-Wall
OFLAGS=-O3

all: genysis split split2

genysis: src/genysis.c
	$(CC) $(CFLAGS) $(OFLAGS) $< -o $@

split: src/split.c
	$(CC) $(CFLAGS) $(OFLAGS) $< -o $@

split2: src/split2.c
	$(CC) $(CFLAGS) $(OFLAGS) $< -o $@

clean:
	rm -Rf *~ src/*~ genysis split split2

clean_file:
	rm 6* 7* L* MN* MT* MW* N* description.txt
