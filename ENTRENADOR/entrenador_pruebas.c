#include "entrenador.h"
#include "pa2mm.h"

#define ERROR -1
#define MAX_POKEMON 10
#define FORMATO_LECTURA "%[^;];%[^;];%i;%i;%i\n"

void pruebas_crear_entrenador(){

	pa2m_nuevo_grupo("PRUEBAS: CREAR ENTRENADOR");

	entrenador_t* entrenador = entrenador_crear();

	pa2m_afirmar(entrenador != NULL, "Se crea un entrenador");
	pa2m_afirmar(strcmp(entrenador->nombre, "\0") == 0, "No tiene nombre");
	pa2m_afirmar(entrenador->pokemon != NULL, "El entrenador tiene su lista de pokemon");
	pa2m_afirmar(entrenador->pokemon->destructor != NULL, "La lista de pokemon tiene su destructor");
	pa2m_afirmar(entrenador_vacio(entrenador), "El entrenador no tiene pokemon capturados aun")

	entrenador_destruir(entrenador);
}

void pruebas_crear_pokemon(){

	pa2m_nuevo_grupo("PRUEBAS: CREAR POKEMON");

	pokemon_t* pokemon = pokemon_crear();

	pa2m_afirmar(pokemon != NULL, "Se crea un pokemon");
	pa2m_afirmar(strcmp(pokemon->nombre, "\0") == 0, "No tiene nombre");
	pa2m_afirmar(strcmp(pokemon->tipo, "\0") == 0, "No tiene tipo");
	pa2m_afirmar(pokemon->velocidad == 0, "No tiene velocidad");
	pa2m_afirmar(pokemon->ataque == 0, "No tiene ataque");
	pa2m_afirmar(pokemon->defensa == 0, "No tiene defensa");
	pa2m_afirmar(pokemon->motivacion == 0, "No tiene puntos de motivacion");

	pokemon_destruir(pokemon);
}

void pruebas_cadena_libreacion_memoria(){

	pa2m_nuevo_grupo("PRUEBAS: INSERTAR POKEMON");

	FILE* archivo_pokemon = fopen("pokemon.txt", "r");
	entrenador_t* entrenador = entrenador_crear();
	pokemon_t* pokemon_1 = pokemon_crear();
	pokemon_t* pokemon_2 = pokemon_crear();
	pokemon_t* pokemon_3 = pokemon_crear();
	pokemon_t* pokemon_4 = pokemon_crear();
	pokemon_t* pokemon_5 = pokemon_crear();
	pokemon_t* pokemon[] = {pokemon_1, pokemon_2, pokemon_3, pokemon_4, pokemon_5};

	pa2m_afirmar(archivo_pokemon, "Se abre una lista de pokemon");

	int i = 0;
	int leidos = fscanf(archivo_pokemon, FORMATO_LECTURA, pokemon[i]->nombre, pokemon[i]->tipo, &(pokemon[i]->velocidad), &(pokemon[i]->ataque), &(pokemon[i]->defensa));

	while(leidos == 5 && i < 4){

		i++;
		leidos = fscanf(archivo_pokemon, FORMATO_LECTURA, pokemon[i]->nombre, pokemon[i]->tipo, &(pokemon[i]->velocidad), &(pokemon[i]->ataque), &(pokemon[i]->defensa));
	}

	pa2m_afirmar(i == 4, "Se seleccionan cinco pokemon de la lista");

	i = 0;
	bool fallo = false;
	pokemon_t* pokemon_aux = NULL;

	while(!fallo && i < 5){

		if(lista_apilar(entrenador->pokemon, pokemon[i]) == ERROR) fallo = true;
		if(!fallo){

			pokemon_aux = (pokemon_t*)lista_tope(entrenador->pokemon);
			if(strcmp(pokemon_aux->nombre, pokemon[i]->nombre) != 0) fallo = true;
			if(!fallo) i++;
		}
	}

	pa2m_afirmar(!fallo && i == 5, "Se asignan los pokemon seleccionados al entrenador");

	fclose(archivo_pokemon);
	/*Lo que realmente quiero probar con Valgrind*/
	entrenador_destruir(entrenador);
}

int main(){

	pruebas_crear_entrenador();
	pruebas_crear_pokemon();
	pruebas_cadena_libreacion_memoria();

	pa2m_mostrar_reporte();

	return 0;
}