CC = gcc
CFLAGS = -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0 -g

comp:
	$(CC) entrenador.c lista.c entrenador_pruebas.c -o entrenador_pruebas $(CFLAGS) 

exe: comp 
	./entrenador_pruebas

val: comp
	valgrind --leak-check=full --track-origins=yes --show-reachable=yes -s ./entrenador_pruebas

gdb: comp
	gdb ./entrenador_pruebas