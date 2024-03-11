# 315144907 Gili Wolf
CC=gcc
CFLAGS=-g

all: cache

cache: cache.o main.o
	$(CC) $(CFLAGS) -o cache cache.o main.o

cache.o: cache.c cache.h
	$(CC) $(CFLAGS) -c cache.c -o cache.o

main.o: main.c cache.h
	$(CC) $(CFLAGS) -c main.c -o main.o

clean:
	rm -f cache *.o