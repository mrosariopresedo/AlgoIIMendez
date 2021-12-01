CC = gcc
CFLAGS = -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0 -g

comp:
	$(CC) interfaz.c batallas.c juego.c avatar.c entrenador.c gimnasio.c heap.c lista.c unidad_de_control.c -o unidad_de_control $(CFLAGS) 

exe: comp 
	./unidad_de_control

val: comp
	valgrind --leak-check=full --track-origins=yes --show-reachable=yes -s ./unidad_de_control

gdb: comp
	gdb ./unidad_de_control
