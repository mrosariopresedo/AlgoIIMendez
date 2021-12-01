#ifndef __GIMNASIO_H__
#define __GIMNASIO_H__

#include "heap.h"
#include "entrenador.h"

typedef struct gimnasio{
	char nombre[MAX_LETRAS];
	char medalla[MAX_LETRAS];
	int dificultad;
	int id_batalla;
	lista_t* entrenadores;
}gimnasio_t;

/*
 * Reserva memoria para un nuevo gimnasio inicializando los campos correspondientes. 
 * Devuelve una direccion de memoria a un gimnasio. En el caso de que ocurra un error, se devolvera NULL.
 */
gimnasio_t* gimnasio_crear();

/*
 * Realiza la lectura de un archivo y carga los datos en el heap binario recibido por parametro.
 * Devuelve 0 si la operacion fue exitosa o -1 en caso de error.
 */
int gimnasio_cargar(heap_t* heap, FILE* archivo_gimnasio);

/*
 * Devuelve verdadero si el gimnasio no existe o esta vacio.
 * Devuelve falso si el gimnasio existe y no esta vacio.
 */
bool gimnasio_vacio(gimnasio_t* gimnasio);

/*
 * Libera la memoria reservada para un gimnasio.
 */
void gimnasio_destruir(gimnasio_t* gimnasio);

#endif /* __GIMNASIO_H__ */
