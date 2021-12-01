CC = gcc
CFLAGS = -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0 -g

comp:
	$(CC) heap.c lista.c entrenador.c gimnasio.c gimnasio_pruebas.c -o gimnasio_pruebas $(CFLAGS) 

exe: comp 
	./gimnasio_pruebas

val: comp
	valgrind --leak-check=full --track-origins=yes --show-reachable=yes -s ./gimnasio_pruebas

gdb: comp
	gdb ./gimnasio_pruebas