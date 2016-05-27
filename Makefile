CC = gcc
CFLAGS = -Wall -Wextra -g -O0

all: tp2.exe

tp2.exe: tp2.o function_tp2.o
	$(CC) $(CFLAGS) tp2.o function_tp2.o -o tp2.exe

tp2.o: tp2.c graph.h
	$(CC) $(CFLAGS) -c tp2.c

function_tp2.o: function_tp2.c graph.h
	$(CC) $(CFLAGS) -c function_tp2.c

clean:
	rm *.o tp2.exe
