#ifndef __INTERFAZ_H__
#define __INTERFAZ_H__

#include <ctype.h>
#include "avatar.h"
#include "gimnasio.h"

#define MENU 'M'
#define COMBATIR 'C'

/*
 * Muestra por pantalla las opciones del Menu Inicio.
 */
void menu_box_inicio();

/*
 * Muestra por pantalla las opciones del Menu Gimnasio.
 */
void menu_box_gimnasio();

/*
 * Muestra por pantalla las opciones del Menu Batalla.
 */
void menu_box_batalla();

/*
 * Muestra por pantalla las opciones del Menu Victoria (con opcion TOMAR_POKE).
 */
void menu_box_victoria_1();

/*
 * Muestra por pantalla las opciones del Menu Victoria (sin opcion TOMAR_POKE).
 */
void menu_box_victoria_2();

/*
 * Muestra por pantalla las opciones del Menu Derrota.
 */
void menu_box_derrota();

/*
 * Muestra la opcion para que el usuario pueda regresar al Menu original.
 */
void volver_a_menu();

/*
 * Muestra por pantalla la informacion de un avatar recibido por parametro.
 */
void info_avatar(personaje_t* avatar);

/*
 * Muestra por pantalla la informacion de un entrenador recibido por parametro.
 */
void info_entrenador(entrenador_t* entrenador);

/*
 * Muestra por pantalla la informacion de un gimnasio recibido por parametro.
 */
void info_gimnasio(gimnasio_t* gimnasio, int id_batalla);

/*
 * Muestra por pantalla la informacion de un arbol de gimnasios recibido por parametro.
 */
void info_gimnasios(heap_t* gimnasios);

/*
 * Muestra por pantalla las medallas recibidas por parametro que tiene un avatar.
 */
void info_medallas(lista_t* medallas);

/*
 * Muestra por pantalla la informacion de dos entrenadores a combatir recibidos por parametro.
 */
void info_entrenadores_combate(personaje_t* avatar, entrenador_t* entrenador);

/*
 * Muestra por pantalla la informacion de dos pokemon a combatir recibidos por parametro.
 */
void info_combate(pokemon_t* poke_avatar, pokemon_t* poke_entrenador);

/*
 * Muestra por pantalla el nombre del pokemon ganador recibido por parametro.
 */
void mostrar_pokemon_ganador(pokemon_t* ganador);

/*
 * Muestra por pantalla el nombre del pokemon perdedor recibido por parametro.
 */
void mostrar_pokemon_perdedor(pokemon_t* perdedor);

/*
 * Muestra por pantalla el nombre del pokemon que va a luchar en el proximo combate recibido por parametro.
 */
void aviso_cambio_poke(char* nombre_poke);

/*
 * Muestra por pantalla un aviso de que un avatar se ha convertido en Maestro Pokemon.
 */
void maestro_pokemon();

/*
 * Muestra por pantalla un aviso de que un avatar ha sido derrotado en modo simulacion.
 */
void derrota_simulacion();

#endif /*__INTERFAZ_H__*/