CC = gcc
CFLAGS = -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0 -g

comp:
	$(CC) heap.c heap_pruebas.c -o heap $(CFLAGS) 

exe: comp 
	./heap

val: comp
	valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./heap