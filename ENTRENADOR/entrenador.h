#ifndef __ENTRENADOR_H__
#define __ENTRENADOR_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

#define MAX_LETRAS 100
#define INICIAL 'C'
#define INICIAL_LIDER 'L'
#define INICIAL_POKEMON 'P'
#define INICIAL_ENTRENADOR 'E'

#define FORMATO_CARACTER "%c;"
#define FORMATO_LECTURA_E "%[^\n]\n"
#define FORMATO_LECTURA_P "%[^;];%[^;];%i;%i;%i\n"

typedef struct pokemon{
	char nombre[MAX_LETRAS];
	char tipo[MAX_LETRAS];
	int velocidad;
	int ataque;
	int defensa;
	int motivacion;
}pokemon_t;

typedef struct entrenador{
	char nombre[MAX_LETRAS];
	bool es_lider;
	lista_t* pokemon;
}entrenador_t;

/*
 * Reserva memoria para un nuevo pokemon inicializando los campos correspondientes. 
 * Devuelve una direccion de memoria a un pokemon. En el caso de que ocurra un error, se devolvera NULL.
 */
pokemon_t* pokemon_crear();

/*
 * Reserva memoria para un nuevo entrenador inicializando los campos correspondientes. 
 * Devuelve una direccion de memoria a un entrenador. En el caso de que ocurra un error, se devolvera NULL.
 */
entrenador_t* entrenador_crear();

/*
 * Devuelve verdadero si el entrenador no existe o si no tiene pokemon.
 * Devuelve falso si el entrenador existe y tiene pokemon.
 */
bool entrenador_vacio(entrenador_t* entrenador);

/*
 * Libera memoria reservada para un pokemon.
 */
void pokemon_destruir(void* pokemon);

/*
 * Libera memoria reservada para un entrenador.
 */
void entrenador_destruir(entrenador_t* entrenador);

#endif /* __ENTRENADOR_H__ */