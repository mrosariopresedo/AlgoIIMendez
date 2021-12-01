#include <stdio.h>
#include "avatar.h"
#include "pa2mm.h"

#define EXITO 0
#define ERROR -1
#define MAX_POKEMON 8

/*FUNCIONES EXTRA*/

/*
 * Dejo funcion para imprimir una lista de pokemon por si se desea usar.
 * Recibe un nodo de la lista e imprime el elemento que se encuentra dentro del mismo.
 * Inicialmente, hay que enviar el nodo inicial de la lista.
 */
void imprimir_pokemon_lista(nodo_t* actual){

	if(actual){

		pokemon_t* pokemon = (pokemon_t*)actual->elemento;
		printf("POKEMON: %s;%s;%i;%i;%i\n", pokemon->nombre, pokemon->tipo, pokemon->velocidad, pokemon->ataque, pokemon->defensa);
		imprimir_pokemon_lista(actual->siguiente);
	}
}

/*PRUEBAS*/

void pruebas_crear_personaje(){

	pa2m_nuevo_grupo("PRUEBAS: CREAR PERSONAJE");

	personaje_t* avatar = personaje_crear();

	pa2m_afirmar(avatar != NULL, "Se crea un Avatar");
	pa2m_afirmar(avatar->medallas != NULL, "El avatar tiene su lista de medallas obtenidas");
	pa2m_afirmar(avatar->caja != NULL, "El avatar tiene su lista de pokemon obtenidos");
	pa2m_afirmar(avatar->caja->destructor != NULL, "La lista de pokemon obtenidos tiene su destructor");
	pa2m_afirmar(personaje_vacio(avatar), "El avatar no tiene pokemon obtenidos aun");
	pa2m_afirmar(avatar->party != NULL, "El avatar tiene su lista de pokemon de combate");
	pa2m_afirmar(avatar->party->destructor != NULL, "La lista de pokemon de combate tiene su destructor");
	pa2m_afirmar(lista_elementos(avatar->party) == 0, "El avatar no tiene pokemon de combate aun");
	pa2m_afirmar(lista_elementos(avatar->medallas) == 0, "El avatar no tiene medallas obtenidAs aun");

	personaje_destruir(&avatar);
}

void pruebas_lectura_archivo(){

	pa2m_nuevo_grupo("PRUEBAS: LECTURA AVATAR");

	int i;
	nodo_t* actual;
	bool todos_correctos = true;
	personaje_t* avatar = personaje_crear();
	char* esperados[MAX_POKEMON] = {"Wobbuffet","Taillow","Claydol","Oshawott","Swampert","Vanillite","Mew","Rhyperior"};

	FILE* archivo = fopen("avatares/avatar.txt", "r");
	if(!archivo) return;

	pa2m_afirmar(personaje_cargar(archivo, avatar) == EXITO, "Se lee archivo de un Avatar");
	pa2m_afirmar(strcmp(avatar->nombre, "Rosario") == 0, "Se lee correctamente el nombre del Avatar");
	pa2m_afirmar(lista_elementos(avatar->caja) == 8, "Se lee en su totalidad los pokemon obtenidos del Avatar");
	fclose(archivo);
	
	actual = avatar->caja->nodo_inicio;
	for(i = 0; actual && todos_correctos; i++){

		if(strcmp(((pokemon_t*)actual->elemento)->nombre, esperados[i]) != 0) todos_correctos =false;
		else actual = actual->siguiente;
	}
	pa2m_afirmar(todos_correctos, "Se leen correctamente los pokemon obtenidos del avatar");

	pa2m_afirmar(lista_elementos(avatar->party) == 6, "Se asignan seis pokemon al Party del Avatar");
	
	todos_correctos = true;
	actual = avatar->party->nodo_inicio;
	for(i = 0; actual && todos_correctos; i++){

		if(strcmp(((pokemon_t*)actual->elemento)->nombre, esperados[i]) != 0) todos_correctos =false;
		else actual = actual->siguiente;
	}
	pa2m_afirmar(todos_correctos, "Los pokemon asignados al Party del Avatar son los primeros seis de la Caja");
	
	personaje_destruir(&avatar);
}

void pruebas_lectura_archivo_erroneos(){

	pa2m_nuevo_grupo("PRUEBAS: LECTURA AVATARES CONFLICTIVOS");

	FILE* archivo;
	personaje_t* avatar = personaje_crear();

	archivo = fopen("avatares/avatar_sin_entrenador.txt", "r");
	if(!archivo) return;
	pa2m_afirmar(personaje_cargar(archivo, avatar) == ERROR, "No es exitosa la lectura de un Avatar sin entrenador");
	personaje_destruir(&avatar);
	fclose(archivo);

	avatar = personaje_crear();
	archivo = fopen("avatares/avatar_sin_nombre_entrenador.txt", "r");
	if(!archivo) return;
	pa2m_afirmar(personaje_cargar(archivo, avatar) == ERROR, "No es exitosa la lectura de un Avatar sin nombre de entrenador");
	personaje_destruir(&avatar);
	fclose(archivo);

	avatar = personaje_crear();
	archivo = fopen("avatares/avatar_dos_entrenadores.txt", "r");
	if(!archivo) return;
	pa2m_afirmar(personaje_cargar(archivo, avatar) == ERROR, "No es exitosa la lectura de un Avatar con dos entrenadores y menos de seis pokemon");
	personaje_destruir(&avatar);
	fclose(archivo);

	avatar = personaje_crear();
	archivo = fopen("avatares/avatar_pocos_poke.txt", "r");
	if(!archivo) return;
	pa2m_afirmar(personaje_cargar(archivo, avatar) == ERROR, "No es exitosa la lectura de un Avatar con menos de seis pokemon");
	personaje_destruir(&avatar);
	fclose(archivo);

	avatar = personaje_crear();
	archivo = fopen("avatares/avatar_pocos_poke_erroneo.txt", "r");
	if(!archivo) return;
	pa2m_afirmar(personaje_cargar(archivo, avatar) == ERROR, "No es exitosa la lectura de un Avatar con formato erroneo y menos de seis pokemon");
	personaje_destruir(&avatar);
	fclose(archivo);

	avatar = personaje_crear();
	archivo = fopen("avatares/avatar_pokes_suficientes.txt", "r");
	if(!archivo) return;
	pa2m_afirmar(personaje_cargar(archivo, avatar) == EXITO && !personaje_vacio(avatar), "Es exitosa la lectura de un Avatar con archivo erroneo pero con al menos seis pokemon");
	personaje_destruir(&avatar);
	fclose(archivo);
}

int main(){

	pruebas_crear_personaje();
	pruebas_lectura_archivo();
	pruebas_lectura_archivo_erroneos();

	pa2m_mostrar_reporte();
	
	return 0;
}