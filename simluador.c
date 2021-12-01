#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "evento_pesca.h"

#define ERROR -1
#define ARGS_MAXIMOS 2
#define COINCIDENCIA 0
#define PRIMERA_LETRA 0
#define MAX_TRASLADOS 5
#define PESO_MAX 100
#define MEJOR_LETRA 'R'
#define VELOCIDAD_MAX 50
#define VELOCIDAD_MIN 100
#define MEJOR_COLOR_1 "rosa"
#define MEJOR_COLOR_2 "morado"

/*
 * sPrecondiciones: recibe un pokemon con todas sus estructuas validas.
 * Postcondiciones: devuelve verdadero si el pokemon es de los mas veloces, caso contrario devuelve falso.
 */
bool es_formula_1(pokemon_t* pokemon){
	return ((*pokemon).velocidad >= VELOCIDAD_MIN);
}

/*
 * Precondiciones: recibe un pokemon con todas sus estructuas validas.
 * Postcondiciones: devuelve verdadero si el pokemon es tierno (segun los colores considerados tiernos), caso contrario devuelve falso.
 */
bool es_cuchurrumin(pokemon_t* pokemon){
	return ((strcmp((*pokemon).color, MEJOR_COLOR_1) == COINCIDENCIA) || (strcmp((*pokemon).color, MEJOR_COLOR_2) == COINCIDENCIA));
}

/*
 * Precondiciones: recibe un pokemon con todas sus estructuas validas.
 * Postcondiciones: devuelve verdadero si el pokemon es de los mas gigantes, caso contrario devuelve falso.
 */
bool toma_prote(pokemon_t* pokemon){
	return ((*pokemon).peso >= PESO_MAX);
}

/*
 * Precondiciones: recibe un pokemon con todas sus estructuas validas.
 * Postcondiciones: devuelve verdadero si el pokemon es de la mejor especie (o sea que su especie comienza con la letra R), caso contrario 
 * devuelve falso.
 */
bool es_mejor_especie(pokemon_t* pokemon){
	return ((*pokemon).especie[PRIMERA_LETRA] == MEJOR_LETRA);
}

/*
 * Precondiciones: recibe un pokemon con todas sus estructuas validas.
 * Postcondiciones: devuelve verdadero si el pokemon es de los mas lentos, caso contrario devuelve falso.
 */
bool es_un_caracol(pokemon_t* pokemon){
	return ((*pokemon).velocidad <= VELOCIDAD_MAX);
}

/*
 * Precondiciones: recibe un pokemon con todas sus estructuas validas.
 * Postcondiciones: muestra por pantalla las caracteristicas del pokemon.
 */
void censar_pokemon(pokemon_t* pokemon){
	printf("|%13s|%13i|%13i|%13s|\n", (*pokemon).especie, (*pokemon).velocidad, (*pokemon).peso, (*pokemon).color);
}

int main(int argv, char *argc[]){

	srand((unsigned)time(NULL));

	if(argv < ARGS_MAXIMOS){

		printf("No recibimos ningun archivo para comenzar la operacion, ingrese una ruta\n");
	}
	else{

		arrecife_t* arrecife = crear_arrecife(argc[1]);
		if(arrecife){

			acuario_t* acuario = crear_acuario();

			if(acuario && (*acuario).pokemon){

				int i = 0;
				int traslado;
				int cant_seleccion = 0;
				bool (*seleccionar_pokemon[])(pokemon_t*) = {es_formula_1, es_cuchurrumin, toma_prote, es_mejor_especie, 										 es_un_caracol};
				void (*mostrar_pokemon)(pokemon_t*) = censar_pokemon;

				while((i < MAX_TRASLADOS) && ((*arrecife).cantidad_pokemon > 0)){

					while(cant_seleccion == 0)
						cant_seleccion = rand() % 10;
					
					traslado = trasladar_pokemon(arrecife, acuario, seleccionar_pokemon[i], cant_seleccion);

					if(traslado == ERROR){
						printf("No se ha podido realizar el traslado numero %i\n\n", i + 1);
					}

					censar_arrecife(arrecife, mostrar_pokemon);
					i++;
				}

				guardar_datos_acuario(acuario, "acuario.txt");
				liberar_acuario(acuario);
			}	

			liberar_arrecife(arrecife);
		}
	}

	return 0;<
}