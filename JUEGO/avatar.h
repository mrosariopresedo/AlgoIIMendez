#ifndef __AVATAR_H__
#define __AVATAR_H__

#include "entrenador.h"

typedef struct personaje{
	char nombre[MAX_LETRAS];
	lista_t* medallas;
	lista_t* party;
	lista_t* caja;
}personaje_t;

/*
 * Reserva memoria para un nuevo personaje inicializando los campos correspondientes. 
 * Devuelve una direccion de memoria a un personaje. En el caso de que ocurra un error, se devolvera NULL.
 */
personaje_t* personaje_crear();

/*
 * Realiza la lectura de un archivo y carga los datos en el avatar recibido por parametro.
 * Devuelve 0 si la operacion fue exitosa o -1 en caso de error.
 */
int personaje_cargar(FILE* archivo_avatar, personaje_t* avatar);

/*
 * Agrega un pokemon a la CAJA de un personaje.
 * En caso de error, no lo agrega.
 */
void pokemon_agregar(lista_t* caja, entrenador_t* lider);

/*
 * Intercambia un pokemon del PARTY con un pokemon de la CAJA.
 * En caso de error, no realiza el intercambio.
 */
void pokemon_intercambiar(personaje_t* avatar);

/*
 * Mejora las habilidades de un pokemon.
 * En caso de error, no lo entrena.
 */
void pokemon_entrenar(pokemon_t* pokemon);

/*
 * Agrega una medalla a la lista de medallas de un avatar.
 * En caso de error, no la agrega
 */
void medalla_agregar(lista_t* medallas, char* medalla);

/*
 * Devuelve verdadero si el personaje no existe o no tiene pokemon para combatir.
 * Devuelve falso si el personaje existe y tiene pokemon para combatir.
 */
bool personaje_vacio(personaje_t* avatar);

/*
 * Libera la memoria reservada para un avatar.
 */
void personaje_destruir(personaje_t** avatar);

#endif /* __AVATAR_H__ */
