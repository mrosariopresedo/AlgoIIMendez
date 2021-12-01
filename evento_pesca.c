#include <stdlib.h>
#include <string.h>
#include "evento_pesca.h"

#define ERROR -1
#define EXITO 0
#define FORMATOS_MAX 4
#define MAX_POKEMONES 80
#define FORMATO_LECTURA "%100[^;];%i;%i;%100[^\n]\n"
#define FORMATO_ESCRITURA "\t|%13s|%13i|%13i|%13s|\n"

/*
 *Precondiciones: cantidad_pokemon esta inicializada.
 *Postconiciones: devuelve verdadero si la operacion fue exitosa, caso contrario devuelve falso.
 */
bool pokemon_agregado(pokemon_t** pokemon, int cantidad_pokemon, pokemon_t pokemon_nuevo){
	
	bool agregado = true;

	pokemon_t* pokemones_nuevo = (pokemon_t*)realloc(*pokemon, sizeof(pokemon_t)*(size_t)cantidad_pokemon);

	if(pokemones_nuevo == NULL) agregado = false;
	else{
		*pokemon = pokemones_nuevo;
		(*pokemon)[cantidad_pokemon - 1] = pokemon_nuevo;
	}

	return agregado;
}

//---------------------------------------------------CREAR ARRECIFE-----------------------------------------------------

arrecife_t* crear_arrecife(const char* ruta_archivo){

	FILE* lista_arrecife = fopen(ruta_archivo, "r");
	if(!lista_arrecife){

		printf("Error al intentar abrir el archivo que lista los pokemones del arrecife\n");
		return NULL;
	}

	arrecife_t* arrecife = malloc(sizeof(arrecife_t)); //reservo memoria en el HEAP para un arrecife
	if(arrecife == NULL){

		printf("Error al reservar memoria para el arrecife\n");
		fclose(lista_arrecife);
		return NULL;
	}

	(*arrecife).pokemon = malloc(sizeof(pokemon_t)); //reservo lugar en el HEAP para un pokemon que voy a leer
	if((*arrecife).pokemon == NULL){

		printf("Error al reservar memoria para los pokemones del arrecife\n");
		fclose(lista_arrecife);
		liberar_arrecife(arrecife);
		return NULL;
	}

	pokemon_t pokemon_leido;
	(*arrecife).cantidad_pokemon = 0;
	int leidos = fscanf(lista_arrecife, FORMATO_LECTURA, pokemon_leido.especie, &(pokemon_leido.velocidad), &(pokemon_leido.peso), pokemon_leido.color);

	while(leidos == FORMATOS_MAX){

		if(pokemon_agregado(&((*arrecife).pokemon), (*arrecife).cantidad_pokemon, pokemon_leido)) (*arrecife).cantidad_pokemon++;
		
		leidos = fscanf(lista_arrecife, FORMATO_LECTURA, pokemon_leido.especie, &(pokemon_leido.velocidad), &(pokemon_leido.peso), pokemon_leido.color);
	}

	if((*arrecife).cantidad_pokemon == 0){

		printf("No se han podido leer pokemones de manera exitosa, operacion abortada\n");
		fclose(lista_arrecife);
		liberar_arrecife(arrecife);
		return NULL;
	}

	fclose(lista_arrecife);

	return arrecife;
}

//---------------------------------------------------CREAR ACUARIO------------------------------------------------------

acuario_t* crear_acuario(){

	acuario_t* acuario = malloc(sizeof(acuario_t));
	if(acuario == NULL){

		printf("Error al reservar memoria para el acuario\n");
		return NULL;
	}

	(*acuario).pokemon = malloc(sizeof(pokemon_t));
	if((*acuario).pokemon == NULL){

		printf("Error al reservar memoria para los pokemones del acuario\n");
		liberar_acuario(acuario);
		return NULL;
	}

	(*acuario).cantidad_pokemon = 0;

	return acuario;
}

//---------------------------------------------------TRASLADAR POKEMON--------------------------------------------------

/*
 * Precondiciones: el arrecife tiene todas sus estructuras validas.
 * Postconiciones: devuelve verdadero si la operacion fue exitosa, caso contrario devuelve falso
 */
bool arrecife_achicado(arrecife_t* arrecife){

	bool achicado = true;
	size_t nuevo_tamanio = (size_t)((*arrecife).cantidad_pokemon - 1);
	pokemon_t* pokemones_nuevo = (pokemon_t*)realloc((*arrecife).pokemon, sizeof(pokemon_t)*nuevo_tamanio);

	if(!pokemones_nuevo){

		if((*arrecife).cantidad_pokemon == 1){

			(*arrecife).pokemon = NULL;
			(*arrecife).cantidad_pokemon--;
			achicado = true;
		}
		else achicado = false;
	}
	else{

		(*arrecife).pokemon = pokemones_nuevo;
		(*arrecife).cantidad_pokemon--;
	}
	
	return achicado;
}

/*
 *Precondiciones: posicion_1 y posicion_2 estan inicializadas.
 *Postcondiciones: los pokemones que estan en las posiciones recibidas como parametros se intercambian entre si.
 */
void intercambiar_pokemones(pokemon_t* pokemon, int posicion_1, int posicion_2){

	pokemon_t pokemon_aux;

	pokemon_aux = pokemon[posicion_1];
	pokemon[posicion_1] = pokemon[posicion_2];
	pokemon[posicion_2] = pokemon_aux;	
}

/*
 * Precondiciones: el arrecife tiene todas sus estructuras validas y pos_a_eliminar esta inicializada.
 * Postcondiciones: devuelve verdadero si la operacion fue exitosa, caso contrario devuelve falso.
 */
bool pokemon_quitado(arrecife_t* arrecife, int pos_a_eliminar){

	bool quitado = true;

	if(pos_a_eliminar == (*arrecife).cantidad_pokemon - 1){
		if(!arrecife_achicado(arrecife)) quitado = false;
	}
	else{

		intercambiar_pokemones((*arrecife).pokemon, pos_a_eliminar, ((*arrecife).cantidad_pokemon - 1));

		if(!arrecife_achicado(arrecife)){

			intercambiar_pokemones((*arrecife).pokemon, ((*arrecife).cantidad_pokemon - 1), pos_a_eliminar);
			quitado = false;
		}
	}

	return quitado;
}

/*
 * Precondiciones: el arrecife y el acuario tienen todas sus estructuras validas, posiciones_selecc contiene todas posiciones positivas y 
 * cant_seleccion esta inicializada.
 * Postcondiciones: se agregan los pokemones seleccionados del arrecife, al acuario. 
 */
void llenar_acuario(arrecife_t* arrecife, acuario_t* acuario, pokemon_t pokes_selecc[MAX_POKEMONES], int posiciones_selecc[MAX_POKEMONES], int cant_seleccion){

	for(int i = (cant_seleccion - 1); i >= 0; i--){

		if(pokemon_quitado(arrecife, posiciones_selecc[i])){

			(*acuario).cantidad_pokemon++;
			if(!pokemon_agregado(&((*acuario).pokemon), (*acuario).cantidad_pokemon, pokes_selecc[i])){

				printf("\nNo se pudo agregar al acuario: %s;%i;%i;%s\n", pokes_selecc[i].especie, pokes_selecc[i].velocidad, pokes_selecc[i].peso, pokes_selecc[i].color);
				(*acuario).cantidad_pokemon--;
			}
		}
		else{
			printf("\nNo se pudo quitar del arrecife: %s;%i;%i;%s. Por lo tanto, tampoco se agrego al acuario\n", pokes_selecc[i].especie, pokes_selecc[i].velocidad, pokes_selecc[i].peso, pokes_selecc[i].color);
		}
	}
}

int trasladar_pokemon(arrecife_t* arrecife, acuario_t* acuario, bool (*seleccionar_pokemon)(pokemon_t*), int 							  cant_seleccion){

	int i = 0;
	bool suficientes = false;
	int resultado_traslado = ERROR;

	int seleccionados = 0;
	int posiciones_selecc[MAX_POKEMONES];
	pokemon_t pokes_selecc[MAX_POKEMONES];

	if(((*arrecife).cantidad_pokemon >= cant_seleccion) && (cant_seleccion >= 0)){

		while((i < (*arrecife).cantidad_pokemon) && (!suficientes)){

			if(seleccionar_pokemon((*arrecife).pokemon + i)){

				pokes_selecc[seleccionados] = (*arrecife).pokemon[i];
				posiciones_selecc[seleccionados] = i;
				seleccionados++;
			}

			if(seleccionados == cant_seleccion){

				suficientes = true;
				resultado_traslado = EXITO;
				llenar_acuario(arrecife, acuario, pokes_selecc, posiciones_selecc, cant_seleccion);
			}

			i++;
		}
	}

	if(cant_seleccion == 0) resultado_traslado = EXITO;

	return resultado_traslado;
}

//---------------------------------------------------CENSAR ACUARIO-----------------------------------------------------

void censar_arrecife(arrecife_t* arrecife, void (*mostrar_pokemon)(pokemon_t*)){

	printf("Censo: Pokemones del arrecife\n");
	printf("|%13s|%13s|%13s|%13s|\n", "Especie", "Velocidad", "Peso", "Color");

	for(int i = 0; i < (*arrecife).cantidad_pokemon; i++)
		mostrar_pokemon((*arrecife).pokemon + i);

	printf("\nPokemones totales: %i\n\n", (*arrecife).cantidad_pokemon);
}

//---------------------------------------------------GUARDAR ACUARIO----------------------------------------------------

int guardar_datos_acuario(acuario_t* acuario, const char* nombre_archivo){

	int i = 0;
	int estado_guardado = 0;

	FILE* lista_acuario = fopen(nombre_archivo, "w");
	if(!lista_acuario){

		printf("Error al crear el archivo para listar los datos del acuario\n");
		estado_guardado = -1;
	}
	else{

		fprintf(lista_acuario, "Pokemones Acuario\n\n");
		fprintf(lista_acuario, "\t|%13s|%13s|%13s|%13s|\n", "Especie", "Velocidad", "Peso", "Color");

		while(i < (*acuario).cantidad_pokemon){

			fprintf(lista_acuario, FORMATO_ESCRITURA, (*acuario).pokemon[i].especie, (*acuario).pokemon[i].velocidad, (*acuario).pokemon[i].peso, (*acuario).pokemon[i].color);
			i++;
		}
	}

	fprintf(lista_acuario, "\nPokemones totales: %i", (*acuario).cantidad_pokemon);

	fclose(lista_acuario);

	return estado_guardado;
}

//---------------------------------------------------LIBERAR MEMORIA----------------------------------------------------

void liberar_arrecife(arrecife_t* arrecife){

	if((*arrecife).pokemon) free((*arrecife).pokemon);

	free(arrecife);
}

void liberar_acuario(acuario_t* acuario){

	if((*acuario).pokemon) free((*acuario).pokemon);

	free(acuario);
}