CC=gcc
CFLAGS=-g -O3

all: fmm

fmm: fmm.o utilities.o main.o
	$(CC) $(CFLAGS) -o fmm fmm.o main.o utilities.o

fmm.o: fmm.c fmm.h
	$(CC) $(CFLAGS) -c fmm.c -o fmm.o

utilities.o: utilities.c fmm.h
	$(CC) $(CFLAGS) -c utilities.c -o utilities.o

main.o: main.c fmm.h
	$(CC) $(CFLAGS) -c main.c -o main.o


clean:
	rm -f fmm *.o