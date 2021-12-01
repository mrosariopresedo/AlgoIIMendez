#include <stdio.h>
#include "heap.h"

/*
 * Precondiciones: i y j estan inicializadas con enteros positivos.
 * Postcondiciones: intercambia dos elementos del vector, los cuales se encuentran en las posiciones recibidas por parametro.
 */
void swap(void** vector, size_t i, size_t j){

	void* auxiliar = vector[i];
	vector[i] = vector[j];
	vector[j] = auxiliar;
}

/*
 * Precondiciones: heap no es nulo y pos_actual esta inicializada.
 * Postcondiciones: mueve un nodo hacia arriba en el árbol, siempre que sea necesario. Lo hace bajo la condicion de arbol minimal.
 */
void sift_up(heap_t* heap, size_t pos_actual){

	if(pos_actual == 0) return;

	size_t pos_padre = posicion_padre(pos_actual);

	if(heap->comparador(heap->vector[pos_padre], heap->vector[pos_actual]) == PRIMERO_MAYOR){

		swap(heap->vector, pos_padre, pos_actual);
		sift_up(heap, pos_padre);
	}
}

/*
 * Precondiciones: heap no es nulo y pos_actual esta inicializada.
 * Postcondiciones: mueve un nodo hacia arriba en el árbol, siempre que sea necesario. Lo hace bajo la condicion de arbol minimal.
 */
void sift_down(heap_t* heap, size_t pos_actual){

	size_t pos_hijo_menor;

	size_t pos_izq = posicion_hijo_izquierdo(pos_actual);
	if(pos_izq >= heap->tope) return;

	size_t pos_der = posicion_hijo_derecho(pos_actual);
	if(pos_der >= heap->tope) pos_hijo_menor = pos_izq;
	else pos_hijo_menor = (heap->comparador(heap->vector[pos_izq], heap->vector[pos_der]) == PRIMERO_MENOR) ? pos_izq : pos_der;

	if(heap->comparador(heap->vector[pos_hijo_menor], heap->vector[pos_actual]) == PRIMERO_MENOR){

		swap(heap->vector, pos_hijo_menor, pos_actual);
		sift_down(heap, pos_hijo_menor);
	}
}

heap_t* heap_crear(heap_comparador comparador, heap_destructor destructor){

	if(!comparador) return NULL;

	heap_t* heap = calloc(1, sizeof(heap_t));
	if(!heap) return NULL;

	heap->comparador = comparador;
	heap->destructor = destructor;

	return heap;
}

size_t posicion_padre(size_t posicion_hijo){
	return (posicion_hijo - 1)/2;
}

size_t posicion_hijo_derecho(size_t posicion_padre){
	return (2*posicion_padre) + 2;
}

size_t posicion_hijo_izquierdo(size_t posicion_padre){
	return (2*posicion_padre) + 1;
}

int heap_insertar(heap_t* heap, void* nuevo_elemento){

	if(!heap) return ERROR;

	void** vector_modif = realloc(heap->vector, sizeof(size_t)*(heap->tope + 1));
	if(!vector_modif) return ERROR;

	(heap->tope)++;
	heap->vector = vector_modif;
	heap->vector[heap->tope - 1] = nuevo_elemento;

	sift_up(heap, heap->tope - 1);

	return EXITO;
}

int heap_eliminar_raiz(heap_t* heap){

	if(heap_vacio(heap)) return ERROR;

	if(heap->destructor) heap->destructor(heap->vector[0]);
	heap->vector[0] = heap->vector[heap->tope - 1];
	(heap->tope)--;

	if(!heap_vacio(heap)) sift_down(heap, 0);

	return EXITO;
}

bool heap_vacio(heap_t* heap){
	return !(heap && heap->tope > 0);
}

void* heap_raiz(heap_t* heap){

	if(heap_vacio(heap)) return NULL;

	return heap->vector[0];
}

void heap_destruir(heap_t* heap){

	if(!heap) return;

	free(heap->vector);
	free(heap); 
}

