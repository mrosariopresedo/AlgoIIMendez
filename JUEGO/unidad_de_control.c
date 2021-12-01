#include "juego.h"

/*
 * Recibe dos elementos del heap y devuelve 0 en caso de ser iguales, 1 si el primer elemento es mayor al
 * segundo o -1 si el primer elemento es menor al segundo.
 */
int gimnasios_comparador(void* gym_1, void* gym_2){

	gimnasio_t* gimnasio_1 = (gimnasio_t*)gym_1;
	gimnasio_t* gimnasio_2 = (gimnasio_t*)gym_2;

	if(gimnasio_1->dificultad > gimnasio_2->dificultad) return PRIMERO_MAYOR;
	else if(gimnasio_1->dificultad < gimnasio_2->dificultad) return PRIMERO_MENOR;

	return IGUALES;
}

/*
 * Libera memoria reservada para un gimnasio.
 */
void gimnasios_destructor(void* gimnasio){

	if(!gimnasio) return;

	gimnasio_destruir((gimnasio_t*)gimnasio);
}

int main(){

	personaje_t* avatar = NULL;
	heap_t* gimnasios = heap_crear(gimnasios_comparador, gimnasios_destructor);
	if(!gimnasios){

		printf("Error de memoria. Si el problema persiste, reinice su PC\n");
		return ERROR;
	}

	menu_inicio(&avatar, gimnasios);

	if(avatar) personaje_destruir(&avatar);
	if(gimnasios) heap_destruir(gimnasios);

	return 0;
}