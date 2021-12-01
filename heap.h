#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ERROR -1
#define EXITO 0
#define PRIMERO_MENOR -1
#define PRIMERO_MAYOR 1

/*
 * Comparador de elementos. Recibe dos elementos del heap y devuelve 0 en caso de ser iguales, 1 si el primer elemento es mayor al
 * segundo o -1 si el primer elemento es menor al segundo.
 */
typedef int (*heap_comparador)(void*, void*);

/*
 * Destructor de elementos. Cada vez que un elemento deja el heap se invoca al destructor pasandole el elemento.
 */
typedef void (*heap_destructor)(void*);

typedef struct heap{
	void** vector;
	size_t tope;
	heap_comparador comparador;
	heap_destructor destructor;
}heap_t;

/*
 * Postcondiciones: devuelve la direccion de memoria de un nuevo heap con los campos de su estructura inicializados. En el caso de que ocurra un 
 * error y este no pueda ser creado, devuelve NULL.
 */
heap_t* heap_crear(heap_comparador comparador, heap_destructor destructor);

/*
 * Precondiciones: posicion_padre esta inicializada.
 * Postcondiciones: calcula y devuelve la posicion del padre, a partir de la posicion recibida por parametro.
 */
size_t posicion_padre(size_t posicion_hijo);

/*
 * Precondiciones: posicion_hijo esta inicializada.
 * Postcondiciones: calcula y devuelve la posicion del hijo derecho, a partir de la posicion recibida por parametro.
 */
size_t posicion_hijo_derecho(size_t posicion_padre);

/*
 * Precondiciones: posicion_padre esta inicializada.
 * Postcondiciones: calcula y devuelve la posicion del hijo izquierdo, a partir de la posicion recibida por parametro.
 */
size_t posicion_hijo_izquierdo(size_t posicion_padre);

/* 
 * Postcondiciones: inserta el nuevo elemento que recibe por parametro en el heap, el cual debe existir para que la insercion sea exitosa.
 * Si la insercion fue exitosa devuelve 0, en el caso contrario, devuelve -1.
 */
int heap_insertar(heap_t* heap, void* nuevo_elemento);

/*
 * Postcondiciones: elimina el elemento que se encuentra en la raiz del heap recibido por parametro, el cual debe existir para que la 
 * extraccion sea exitosa.
 */
int heap_eliminar_raiz(heap_t* heap);

/*
 * Postcondiciones: si la cantidad de elementos en el heap es 0, o si el heap no existe, se considera que es un heap vacio. En ese caso, la 
 * funcion devuelve verdadero; caso contrario, devuelve falso.
 */
bool heap_vacio(heap_t* heap);

/*
 * Postcondiciones: devuelve el elemento que se encuentra en la raiz del heap recibido por parametro o NULL en el caso de que no exista la misma.
 */
void* heap_raiz(heap_t* heap);

/*
 * Postcondicioens: libera la memoria ocupada por el heap recibido por parametro.
 */
void heap_destruir(heap_t* heap);

