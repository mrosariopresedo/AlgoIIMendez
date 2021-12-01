CC = gcc
CFLAGS = -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0 -g

compilar:
	$(CC) abb.c mis_pruebas.c -o abb $(CFLAGS) 

exe: compilar 
	./abb

val: compilar
	valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./abb