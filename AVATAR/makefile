CC = gcc
CFLAGS = -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0 -g

comp:
	$(CC) lista.c entrenador.c avatar.c avatar_pruebas.c -o avatar_pruebas $(CFLAGS) 

exe: comp 
	./avatar_pruebas

val: comp
	valgrind --leak-check=full --track-origins=yes --show-reachable=yes -s ./avatar_pruebas

gdb: comp
	gdb ./avatar_pruebas
