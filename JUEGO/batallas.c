#include <string.h>
#include "batallas.h"
#include "interfaz.h"

/*FUNCIONES ENCAPSULADAS*/

/*
 * Devuelve quien gana segun el tipo de pokemon que sean.
 */
int determinar_mejor_tipo(char* tipo_1, char* tipo_2){

	if(strcmp(tipo_1, "FUEGO") == 0){

		if(strcmp(tipo_2, "AGUA")) return GANO_SEGUNDO;
		else if(strcmp(tipo_2, "HIELO")) return GANO_SEGUNDO;
		else if(strcmp(tipo_2, "DRAGON")) return GANO_SEGUNDO;
	}
	else if(strcmp(tipo_1, "AGUA") == 0){

		if(strcmp(tipo_2, "HIELO")) return GANO_SEGUNDO;
		else if(strcmp(tipo_2, "PSIQUICO")) return GANO_SEGUNDO;
		else if(strcmp(tipo_2, "ELECTRICO")) return GANO_SEGUNDO;
		else if(strcmp(tipo_2, "PLANTA")) return GANO_SEGUNDO;
	}
	else if(strcmp(tipo_1, "HIELO") == 0){

		if(strcmp(tipo_2, "ELECTRICO")) return GANO_SEGUNDO;
		else if(strcmp(tipo_2, "NORMAL")) return GANO_SEGUNDO;
		else if(strcmp(tipo_2, "ROCA")) return GANO_SEGUNDO;
	}
	else if(strcmp(tipo_1, "TIERRA") == 0){

		if(strcmp(tipo_2, "FUEGO")) return GANO_SEGUNDO;
		else if(strcmp(tipo_2, "VENENO")) return GANO_SEGUNDO;
		else if(strcmp(tipo_2, "ROCA")) return GANO_SEGUNDO;
	}
	else if(strcmp(tipo_1, "DRAGON") == 0){

		if(strcmp(tipo_2, "AGUA")) return GANO_SEGUNDO;
		else if(strcmp(tipo_2, "HIELO")) return GANO_SEGUNDO;
		else if(strcmp(tipo_2, "PSIQUICO")) return GANO_SEGUNDO;
		else if(strcmp(tipo_2, "HADA")) return GANO_SEGUNDO;
	}
	else if(strcmp(tipo_1, "PSIQUICO") == 0){

		if(strcmp(tipo_2, "VENENO")) return GANO_SEGUNDO;
		else if(strcmp(tipo_2, "HADA")) return GANO_SEGUNDO;
	}
	else if(strcmp(tipo_1, "ROCA") == 0){

		if(strcmp(tipo_2, "FUEGO")) return GANO_SEGUNDO;
		else if(strcmp(tipo_2, "DRAGON")) return GANO_SEGUNDO;
	}
	else if(strcmp(tipo_1, "NORMAL") == 0){

		if(strcmp(tipo_2, "FUEGO")) return GANO_SEGUNDO;
		else if(strcmp(tipo_2, "DRAGON")) return GANO_SEGUNDO;
		else if(strcmp(tipo_2, "PSIQUICO")) return GANO_SEGUNDO;
	}
	else if(strcmp(tipo_1, "PLANTA") == 0){

		if(strcmp(tipo_2, "FUEGO")) return GANO_SEGUNDO;
		else if(strcmp(tipo_2, "DRAGON")) return GANO_SEGUNDO;
		else if(strcmp(tipo_2, "VENENO")) return GANO_SEGUNDO;
	}
	else if(strcmp(tipo_1, "ELECTRICO") == 0){

		if(strcmp(tipo_2, "PSIQUICO")) return GANO_SEGUNDO;
		else if(strcmp(tipo_2, "VENENO")) return GANO_SEGUNDO;
		else if(strcmp(tipo_2, "ROCA")) return GANO_SEGUNDO;
	}
	else if(strcmp(tipo_1, "HADA") == 0){

		if(strcmp(tipo_2, "FUEGO")) return GANO_SEGUNDO;
		else if(strcmp(tipo_2, "VENENO")) return GANO_SEGUNDO;
		else if(strcmp(tipo_2, "TIERRA")) return GANO_SEGUNDO;
	}
	else if(strcmp(tipo_1, "VENENO") == 0){

		if(strcmp(tipo_2, "FUEGO")) return GANO_SEGUNDO;
		else if(strcmp(tipo_2, "AGUA")) return GANO_SEGUNDO;
		else if(strcmp(tipo_2, "HIELO")) return GANO_SEGUNDO;
	}

	return GANO_PRIMERO;
}

/*FUNCIONES BIBLIOTECA*/

int funcion_batalla_1(void* pkm_1, void* pkm_2){

	pokemon_t* pokemon_1 = (pokemon_t*)pkm_1;
	pokemon_t* pokemon_2 = (pokemon_t*)pkm_2;

	if(pokemon_1->ataque > pokemon_2->ataque) return GANO_PRIMERO;
	return GANO_SEGUNDO;

}

int funcion_batalla_2(void* pkm_1, void* pkm_2){

	pokemon_t* pokemon_1 = (pokemon_t*)pkm_1;
	pokemon_t* pokemon_2 = (pokemon_t*)pkm_2;

	if(pokemon_1->velocidad > pokemon_2->velocidad) return GANO_PRIMERO;
	return GANO_SEGUNDO;
}

int funcion_batalla_3(void* pkm_1, void* pkm_2){
	
	pokemon_t* pokemon_1 = (pokemon_t*)pkm_1;
	pokemon_t* pokemon_2 = (pokemon_t*)pkm_2;

	if(((pokemon_1->velocidad)/2 < pokemon_2->velocidad) && (pokemon_1->ataque > pokemon_2->ataque)) return GANO_PRIMERO;
	else if(((pokemon_1->velocidad)/2 > pokemon_2->velocidad) && (pokemon_1->ataque > pokemon_2->ataque)) return GANO_PRIMERO;

	return GANO_SEGUNDO;
}

int funcion_batalla_4(void* pkm_1, void* pkm_2){

	pokemon_t* pokemon_1 = (pokemon_t*)pkm_1;
	pokemon_t* pokemon_2 = (pokemon_t*)pkm_2;

	if((pokemon_1->ataque < pokemon_2->ataque) && (pokemon_1->defensa > pokemon_2->defensa)) return GANO_PRIMERO;
	else if((pokemon_1->ataque > pokemon_2->ataque) && (pokemon_1->defensa < pokemon_2->defensa)) return GANO_PRIMERO;
	else if((pokemon_1->ataque > pokemon_2->ataque) && (pokemon_1->defensa > pokemon_2->defensa)) return GANO_PRIMERO;

	return GANO_SEGUNDO;
}

int funcion_batalla_5(void* pkm_1, void* pkm_2){
	
	pokemon_t* pokemon_1 = (pokemon_t*)pkm_1;
	pokemon_t* pokemon_2 = (pokemon_t*)pkm_2;

	if(strcmp(pokemon_1->tipo, pokemon_2->tipo) == 0) funcion_batalla_1(pkm_1, pkm_2);

	return determinar_mejor_tipo(pokemon_1->tipo, pokemon_2->tipo);
}
