#include "avatar.h"

const int ERROR = -1;
const int EXITO = 0;
const int NECESARIOS = 6;

/*
 * Comparador de pokemons. Recibe dos pokemon de la caja y devuelve 0 en caso de ser iguales, 1 si el primer pokemon es mayor al
 * segundo o -1 si el primer pokemon es menor al segundo.
 */
int comparar_segun_nombre(void* poke_1, void* poke_2){

	pokemon_t* pokemon_1 = (pokemon_t*)poke_1;
	pokemon_t* pokemon_2 = (pokemon_t*)poke_2;

	return strcmp(pokemon_1->nombre, pokemon_2->nombre);
}

/*FUNCIONES ENCAPSULADAS*/

/*
 * Lee una linea del archivo recibido por parametro con un formato determinado y guarda la informacion en el registro pedido.
 * Devuelve verdadero si la operacion fue exitosa. De lo contrario, devuelve falso.
 */
bool linea_leida_2(FILE* archivo_gimnasio, void* registro, char formato){

	int leidos = 0;

	if(formato == INICIAL_ENTRENADOR){

		leidos = fscanf(archivo_gimnasio, FORMATO_LECTURA_E, ((personaje_t*)registro)->nombre);
		if(leidos != 1) return false;
	}
	else if(formato == INICIAL_POKEMON){

		leidos = fscanf(archivo_gimnasio, FORMATO_LECTURA_P, ((pokemon_t*)registro)->nombre, ((pokemon_t*)registro)->tipo, &(((pokemon_t*)registro)->velocidad), &(((pokemon_t*)registro)->ataque), &(((pokemon_t*)registro)->defensa));
		if(leidos != 5) return false;
	}
	else return false;

	return true;
}

/*
 * Realiza la lectura de un personaje y guarda los datos en el registro recibido por parametro.
 * Devuelve -1 si ocurrio un error en alguna de las operaciones o 0 si la lectura fue exitosa.
 */
int resultado_lectura_2(FILE* archivo_avatar, personaje_t* avatar){

	if(!archivo_avatar || !avatar) return ERROR;

	char inicial_leida;
	bool fallo = false, fallo_y_alcanza = false;
	pokemon_t* pokemon_caja, *pokemon_party;
	int leidos, resultado;

	if(!linea_leida_2(archivo_avatar, avatar, INICIAL_ENTRENADOR)) return ERROR;

	leidos = fscanf(archivo_avatar, FORMATO_CARACTER, &inicial_leida);
	while(!fallo && !fallo_y_alcanza && leidos == 1 && inicial_leida == INICIAL_POKEMON){

		pokemon_caja = pokemon_crear();
		if(pokemon_caja){

			if(linea_leida_2(archivo_avatar, pokemon_caja, inicial_leida)){

				resultado = lista_insertar(avatar->caja, pokemon_caja);
				if(resultado == ERROR){

					if(lista_elementos(avatar->caja) >= NECESARIOS) fallo_y_alcanza = true;
					else fallo = true;
					free(pokemon_caja);
				}

				if(!fallo && !fallo_y_alcanza && lista_elementos(avatar->party) < NECESARIOS){

					pokemon_party = pokemon_crear();
					if(pokemon_party){

						*pokemon_party = *pokemon_caja;
						resultado = lista_insertar(avatar->party, pokemon_party);
						if(resultado == ERROR){

							fallo = true;
							free(pokemon_party);
							free(pokemon_caja);
						}
					}
					else fallo = true;
				}
			}
			else{

				if(lista_elementos(avatar->caja) >= NECESARIOS) fallo_y_alcanza = true;
				else fallo = true;
				free(pokemon_caja);
			}
		}
		else if(lista_elementos(avatar->caja) >= NECESARIOS) fallo_y_alcanza = true;
		else fallo = true;

		if(!fallo && !fallo_y_alcanza) leidos = fscanf(archivo_avatar, FORMATO_CARACTER, &inicial_leida);
	}

	if(fallo || lista_elementos(avatar->caja) < NECESARIOS) return ERROR;

	return EXITO;
}	

/*
 * Intercambia un pokemon del PARTY con uno de la CAJA.
 * En caso de error, no intercambia los pokemon.
 */
void intercambiar(lista_t* party, lista_t* caja, size_t pokemon_party, size_t pokemon_caja){

	if(!party || !caja) return;

	pokemon_t* poke_party = (pokemon_t*)lista_elemento_en_posicion(party, pokemon_party);
	pokemon_t* poke_caja = (pokemon_t*)lista_elemento_en_posicion(caja, pokemon_caja);
	*poke_party = *poke_caja;
}

/*FUNCIONES BIBLIOTECA*/

personaje_t* personaje_crear(){

	personaje_t* avatar = calloc(1, sizeof(personaje_t));
	if(!avatar) return NULL;

	avatar->medallas = lista_crear(NULL);
	if(!avatar->medallas){

		personaje_destruir(&avatar);
		return NULL;
	}

	avatar->party = lista_crear(pokemon_destruir);
	if(!avatar->party){

		personaje_destruir(&avatar);
		return NULL;
	}

	avatar->caja = lista_crear(pokemon_destruir);
	if(!avatar->caja){

		personaje_destruir(&avatar);
		return NULL;
	}

	return avatar;
}

int personaje_cargar(FILE* archivo_avatar, personaje_t* avatar){

	if(!archivo_avatar || !avatar) return ERROR;

	int leidos;
	char inicial_leida;

	leidos = fscanf(archivo_avatar, FORMATO_CARACTER, &inicial_leida);
	if(leidos != 1 || inicial_leida != INICIAL_ENTRENADOR) return ERROR;

	return resultado_lectura_2(archivo_avatar, avatar);
}

void pokemon_agregar(lista_t* caja, entrenador_t* lider){

	if(!caja || !lider) return;

	size_t pokemon_lider = lista_elementos(lider->pokemon);

	printf("\nIngrese el numero del pokemon que desea tomar del lider (0 <= x <= %zu): ", lista_elementos(lider->pokemon) - 1);
	while(pokemon_lider >= lista_elementos(lider->pokemon)) scanf("%zu", &pokemon_lider);

	pokemon_t* pokemon = pokemon_crear();
	if(!pokemon) return;

	*pokemon = *(pokemon_t*)lista_elemento_en_posicion(lider->pokemon, pokemon_lider);

	lista_insertar(caja, pokemon);
}

void pokemon_intercambiar(personaje_t* avatar){

	if(!avatar) return;

	size_t pokemon_party = lista_elementos(avatar->party);
	size_t pokemon_caja = lista_elementos(avatar->caja);

	printf("\nIngrese el numero del pokemon que desea quitar del PARTY (0 <= x <= %zu): ", lista_elementos(avatar->party) - 1);
	while(pokemon_party >= lista_elementos(avatar->party)) scanf("%zu", &pokemon_party);
	
	printf("Ingrese el numero del pokemon que desea agregar al PARTY (0 <= x <= %zu): ", lista_elementos(avatar->caja) - 1);
	while(pokemon_caja >= lista_elementos(avatar->caja)) scanf("%zu", &pokemon_caja);

	intercambiar(avatar->party, avatar->caja, pokemon_party, pokemon_caja);
}

void pokemon_entrenar(pokemon_t* pokemon){

	if(!pokemon || pokemon->motivacion >= 63) return;

	(pokemon->velocidad)++;
	(pokemon->ataque)++;
	(pokemon->defensa)++;
	(pokemon->motivacion)++;
}

void medalla_agregar(lista_t* medallas, char* medalla){

	if(!medallas) return;

	lista_insertar(medallas, medalla);
}

bool personaje_vacio(personaje_t* avatar){

	return(!avatar || !lista_elementos(avatar->party));
}

void personaje_destruir(personaje_t** avatar){

	if(!*avatar) return;

	if((*avatar)->medallas) lista_destruir((*avatar)->medallas);
	if((*avatar)->party) lista_destruir((*avatar)->party);
	if((*avatar)->caja) lista_destruir((*avatar)->caja);

	free(*avatar);
	*avatar = NULL;
}
