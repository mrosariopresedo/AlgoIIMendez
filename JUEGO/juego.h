#ifndef __JUEGO_H__
#define __JUEGO_H__

#include "batallas.h"
#include "interfaz.h"

/*
 * Introduce al juego al usuario.
 * Dependiendo de la opcion elegida por el usuario del Menu Inicio, realiza las operaciones correspondientes.
 */
void menu_inicio(personaje_t** avatar, heap_t* gimnasios);

/*
 * Realiza las batallas entre los gimnasios y el avatar en tiempo real.
 */
void iniciar_partida(personaje_t* avatar, heap_t* gimnasios);

/*
 * Realiza las batallas entre los gimnasios y el avatar en modo simulacion.
 */
void simulacion_partida(personaje_t* avatar, heap_t* gimnasios);

#endif /*__JUEGO_H__*/