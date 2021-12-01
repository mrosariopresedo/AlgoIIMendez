#include <stdio.h>
#include "gimnasio.h"
#include "pa2mm.h"

/*COMPARADORES/DESTRUCTORES*/

/*
 * Compara dos elementos del heap y devuelve 0 en caso de ser iguales, 1 si el primer elemento es mayor al segundo o -1 si el primer 
 * elemento es menor al segundo.
 */
int gimnasio_comparador(void* gym_1, void* gym_2){

	gimnasio_t* gimnasio_1 = (gimnasio_t*)gym_1;
	gimnasio_t* gimnasio_2 = (gimnasio_t*)gym_2;

	if(gimnasio_1->dificultad > gimnasio_2->dificultad) return PRIMERO_MAYOR;
	if(gimnasio_1->dificultad < gimnasio_2->dificultad) return PRIMERO_MENOR;
	else return IGUALES;
}

/*
 * Libera memoria reservada para un gimnasio.
 */
void gimnasio_destructor(void* gym){

	if(!gym) return;

	gimnasio_destruir((gimnasio_t*)gym);
}

/*PRUEBAS*/

void pruebas_crear_gimnasio(){

	pa2m_nuevo_grupo("PRUEBAS: CREAR GIMNASIO");

	gimnasio_t* gimnasio = gimnasio_crear();

	pa2m_afirmar(gimnasio != NULL, "Se crea un gimnasio");
	pa2m_afirmar(strcmp(gimnasio->nombre, "\0") == 0, "No tiene nombre");
	pa2m_afirmar(strcmp(gimnasio->medalla, "\0") == 0, "No tiene medalla");
	pa2m_afirmar(gimnasio->id_batalla == 0, "No tiene ID de batalla");
	pa2m_afirmar(gimnasio->dificultad == 0, "No tiene dificultad");
	pa2m_afirmar(gimnasio->entrenadores != NULL, "El gimnasio tiene su lista de entrenadores");
	pa2m_afirmar(gimnasio->entrenadores->destructor != NULL, "La lista de entrenadores tiene su destructor");
	pa2m_afirmar(gimnasio_vacio(gimnasio), "El gimnasio no tiene entenadores disponibles");

	gimnasio_destruir(gimnasio);
}

void pruebas_lectura_archivos(){

	pa2m_nuevo_grupo("PRUEBAS: LECTURA GIMNASIOS");

	FILE* archivo;
	gimnasio_t* gimnasio_aux;
	heap_t* heap = heap_crear(gimnasio_comparador, gimnasio_destructor);

	pa2m_afirmar(heap != NULL, "Se crea un heap binario de gimnasios");
	pa2m_afirmar(heap->comparador == gimnasio_comparador, "El heap tiene su comparador");
	pa2m_afirmar(heap->destructor == gimnasio_destructor, "El heap tiene su destructor");

	/*ARCHIVO CON UN GIMNASIO*/
	archivo = fopen("gimnasios/gimnasio_de_ciudad_celeste.txt", "r");
	if(!archivo) return;
	pa2m_afirmar(gimnasio_cargar(heap, archivo) == EXITO, "Es exitosa la lectura de un archivo con un gimnasio");
	gimnasio_aux = (gimnasio_t*)heap_raiz(heap);
	pa2m_afirmar(strcmp(gimnasio_aux->nombre, "Gimnasio de Ciudad Celeste") == 0, "El gimnasio esta en la raiz del heap");
	fclose(archivo);
	pa2m_afirmar(heap->tope == 1, "El heap tiene un gimnasio");

	/*ARCHIVO CON DOS GIMNASIOS*/
	archivo = fopen("gimnasios/gimnasio_de_ciudad_plateada_&_azulona.txt", "r");
	if(!archivo) return;
	pa2m_afirmar(gimnasio_cargar(heap, archivo) == EXITO, "Es exitosa la lectura de un archivo con dos gimnasios");
	gimnasio_aux = (gimnasio_t*)heap_raiz(heap);
	pa2m_afirmar(strcmp(gimnasio_aux->nombre, "Gimnasio de Ciudad Plateada") == 0, "El gimnasio con menor dificultad se encuentra en la raiz");
	pa2m_afirmar(strcmp(((gimnasio_t*)heap->vector[1])->nombre, "Gimnasio de Ciudad Celeste") == 0 && strcmp(((gimnasio_t*)heap->vector[2])->nombre, "Gimnasio de Ciudad Azulona") == 0, "El resto de los gimnasios se encuentran en la posicion correcta");
	pa2m_afirmar(heap->tope == 3, "El heap tiene tres gimnasios");
	fclose(archivo);

	/*ARCHIVO CON TRES GIMNASIOS*/
	archivo = fopen("gimnasios/gimnasio_de_ciudad_fucsia_&_azafran_&_verde.txt", "r");
	if(!archivo) return;
	pa2m_afirmar(gimnasio_cargar(heap, archivo) == EXITO, "Es exitosa la lectura de un archivo con tres gimnasios");
	gimnasio_aux = (gimnasio_t*)heap_raiz(heap);
	pa2m_afirmar(strcmp(gimnasio_aux->nombre, "Gimnasio de Ciudad Plateada") == 0, "El gimnasio con menor dificultad se encuentra en la raiz");
	pa2m_afirmar(strcmp(((gimnasio_t*)heap->vector[1])->nombre, "Gimnasio de Ciudad Celeste") == 0 && strcmp(((gimnasio_t*)heap->vector[2])->nombre, "Gimnasio de Ciudad Azulona") == 0 && strcmp(((gimnasio_t*)heap->vector[3])->nombre, "Gimnasio de Ciudad Fucsia") == 0 && strcmp(((gimnasio_t*)heap->vector[4])->nombre, "Gimnasio de Ciudad Azafran") == 0 && strcmp(((gimnasio_t*)heap->vector[5])->nombre, "Gimnasio de Ciudad Verde") == 0, "El resto de los gimnasios se encuentran en la posicion correcta");
	pa2m_afirmar(heap->tope == 6, "El heap tiene seis gimnasios");
	fclose(archivo);
	
	heap_destruir(heap);
}

void pruebas_lectura_archivos_erroneos(){

	pa2m_nuevo_grupo("PRUEBAS: LECTURA GIMNASIOS CONFLICTIVOS");

	FILE* archivo;
	heap_t* heap = heap_crear(gimnasio_comparador, gimnasio_destructor);

	pa2m_afirmar(heap != NULL, "Se crea un heap binario de gimnasios");
	pa2m_afirmar(heap->comparador == gimnasio_comparador, "El heap tiene su comparador");
	pa2m_afirmar(heap->destructor == gimnasio_destructor, "El heap tiene su destructor");
		
	/*ARCHIVOS CON FORMATO ERRONEO*/
	archivo = fopen("gimnasios/gimnasio_caracter_erroneo_suficiente.txt", "r");
	if(!archivo) return;
	pa2m_afirmar(gimnasio_cargar(heap, archivo) == EXITO, "Es exitosa la lectura de un archivo erroneo pero con informacion suficiente");
	pa2m_afirmar(lista_elementos(((gimnasio_t*)heap->vector[0])->entrenadores) == 1, "El gimnasio tiene un entrenador");
	pa2m_afirmar(heap->tope == 1, "El heap tiene un gimnasio");
	fclose(archivo);

	archivo = fopen("gimnasios/gimnasio_caracter_erroneo_no_suficiente.txt", "r");
	if(!archivo) return;
	pa2m_afirmar(gimnasio_cargar(heap, archivo) == ERROR, "No es exitosa la lectura de un archivo erroneo con informacion insuficiente");
	pa2m_afirmar(heap->tope == 1, "No se guarda el gimnasio");
	fclose(archivo);

	archivo = fopen("gimnasios/gimnasio_entrenador_sin_pokes.txt", "r");
	if(!archivo) return;
	pa2m_afirmar(gimnasio_cargar(heap, archivo) == EXITO, "Es exitosa la lectura de un archivo con un entrenador sin pokemon pero con informacion suficiente");
	pa2m_afirmar(heap->tope == 2, "Se guarda el gimnasio");
	fclose(archivo);

	archivo = fopen("gimnasios/gimnasio_entrenador_sin_pokes_insuf.txt", "r");
	if(!archivo) return;
	pa2m_afirmar(gimnasio_cargar(heap, archivo) == ERROR, "No es exitosa la lectura de un archivo con un entrenador sin pokemon pero con informacion insuficiente");
	pa2m_afirmar(heap->tope == 2, "No se guarda el gimnasio");
	fclose(archivo);

	archivo = fopen("gimnasios/gimnasio_mas_de_un_lider.txt", "r");
	if(!archivo) return;
	pa2m_afirmar(gimnasio_cargar(heap, archivo) == EXITO, "Es exitosa la lectura de un archivo con mas de un lider pero con informacion suficiente");
	pa2m_afirmar(heap->tope == 3, "Se guarda el gimnasio");
	fclose(archivo);
	
	heap_destruir(heap);
}

int main(){

	pruebas_crear_gimnasio();
	pruebas_lectura_archivos();
	pruebas_lectura_archivos_erroneos();

	pa2m_mostrar_reporte();
	
	return 0;
}