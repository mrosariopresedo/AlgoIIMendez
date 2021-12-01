#include "entrenador.h"

/*FUNCIONES BIBLIOTECA*/

pokemon_t* pokemon_crear(){

	return calloc(1, sizeof(pokemon_t));
}

entrenador_t* entrenador_crear(){

	entrenador_t* entrenador_nuevo = calloc(1, sizeof(entrenador_t));
	if(!entrenador_nuevo) return NULL;

	/*Creo la lista asignandole un destructor para que cada entrenador le diga a la funcion lista_destruir como eliminar los pokemon*/
	entrenador_nuevo->pokemon = lista_crear(pokemon_destruir);
	if(!entrenador_nuevo->pokemon){

		free(entrenador_nuevo);
		return NULL;
	}

	return entrenador_nuevo;
}

bool entrenador_vacio(entrenador_t* entrenador){

	return (!entrenador || !entrenador->pokemon || !entrenador->pokemon->cantidad);
}

void pokemon_destruir(void* pokemon){

	if(!pokemon) return;

	free(pokemon);
}

void entrenador_destruir(entrenador_t* entrenador){

	if(!entrenador) return;

	if(entrenador->pokemon) lista_destruir(entrenador->pokemon);
	free(entrenador);
}