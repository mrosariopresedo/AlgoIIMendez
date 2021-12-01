#include "gimnasio.h"

#define INICIAL_GIMNASIO 'G'
#define FORMATO_LECTURA_G "%[^;];%[^;];%i;%i\n"

const int SEGUIR = 1;
const int MAX_GIMNASIOS = 20;

/*DESTRUCTOR*/

/*
 * Libera memoria reservada para un entrenador.
 */
void entrenador_destructor(void* entrenador){

	if(!entrenador) return;

	entrenador_destruir((entrenador_t*)entrenador);
}

/*FUNCIONES ENCAPSULADAS*/

/*
 * Realiza las operaciones necesarias para poder abortar una funcion sin dejar cabos sueltos.
 */
void abortar_lectura(gimnasio_t* gimnasio, bool* fallo){

	if(gimnasio) gimnasio_destruir(gimnasio);
	if(fallo) *fallo = true;
}

/*
 * Lee una linea del archivo recibido por parametro con un formato determinado y guarda la informacion en el registro pedido.
 * Devuelve verdadero si la operacion fue exitosa. De lo contrario, devuelve falso.
 */
bool linea_leida(FILE* archivo_gimnasio, void* registro, char formato){

	int leidos;

	if(formato == INICIAL_GIMNASIO){

		leidos = fscanf(archivo_gimnasio, FORMATO_LECTURA_G, ((gimnasio_t*)registro)->nombre, ((gimnasio_t*)registro)->medalla,       &(((gimnasio_t*)registro)->dificultad), &(((gimnasio_t*)registro)->id_batalla));
		if(leidos != 4) return false;
	}
	else if(formato == INICIAL_LIDER || formato == INICIAL_ENTRENADOR){

		leidos = fscanf(archivo_gimnasio, FORMATO_LECTURA_E, ((entrenador_t*)registro)->nombre);
		if(leidos != 1) return false;
	}
	else if(formato == INICIAL_POKEMON){

		leidos = fscanf(archivo_gimnasio, FORMATO_LECTURA_P, ((pokemon_t*)registro)->nombre, ((pokemon_t*)registro)->tipo,            &(((pokemon_t*)registro)->velocidad), &(((pokemon_t*)registro)->ataque), &(((pokemon_t*)registro)->defensa));
		if(leidos != 5) return false;
	}
	else return false;

	return true;
}

/*
 *Devuelve verdadero si la inicial recibida por parametro esta dentro de las deseadas. De lo contrario, devuelve falso.
 */
bool inicial_permitida(char inicial){

	return (inicial == INICIAL_LIDER || inicial == INICIAL_ENTRENADOR || inicial == INICIAL_POKEMON);
}

/*
 * Realiza la lectura de un gimnasio y guarda los datos en el registro recibido por parametro.
 * Devuelve -1 si ocurrio un error en alguna de las operaciones, 0 si la lectura fue exitosa y llego al final del archivo, o 1 si la
 * lectura fue exitosa pero aun quedan mas gimnasios por leer.
 */
int resultado_lectura(FILE* archivo_gimnasio, gimnasio_t* gimnasio){

	if(!archivo_gimnasio || !gimnasio) return ERROR;

	int leidos;
	char inicial_leida;
	pokemon_t* pokemon;
	entrenador_t* entrenador;
	bool fallo = false, fallo_y_alcanza = false;

	if(!linea_leida(archivo_gimnasio, gimnasio, INICIAL_GIMNASIO)){

		abortar_lectura(gimnasio, NULL);
		return ERROR;
	}

	leidos = fscanf(archivo_gimnasio, FORMATO_CARACTER, &inicial_leida);
	while(!fallo && !fallo_y_alcanza && leidos > 0 && inicial_permitida(inicial_leida)){

		if(inicial_leida == INICIAL_LIDER || inicial_leida == INICIAL_ENTRENADOR){

			entrenador = entrenador_crear();
			if(entrenador){

				if(inicial_leida == INICIAL_LIDER) entrenador->es_lider = true;
				if(linea_leida(archivo_gimnasio, entrenador, inicial_leida)){

					leidos = fscanf(archivo_gimnasio, FORMATO_CARACTER, &inicial_leida);
					if(leidos > 0 && (leidos != 1 || inicial_leida != INICIAL_POKEMON)){

						entrenador_destruir(entrenador);
						if(gimnasio_vacio(gimnasio)) abortar_lectura(gimnasio, &fallo);
						else fallo_y_alcanza = true;
					}
					else lista_apilar(gimnasio->entrenadores, entrenador);
				}
				else{

					entrenador_destruir(entrenador);
					if(gimnasio_vacio(gimnasio)) abortar_lectura(gimnasio, &fallo);
					else fallo_y_alcanza = true;
				}
			}
			else{

				if(gimnasio_vacio(gimnasio)) abortar_lectura(gimnasio, &fallo);
				else fallo_y_alcanza = true;
			}
		}
		else if(inicial_leida == INICIAL_POKEMON){

			pokemon = pokemon_crear();
			if(pokemon){

				if(linea_leida(archivo_gimnasio, pokemon, inicial_leida)){

					leidos = fscanf(archivo_gimnasio, FORMATO_CARACTER, &inicial_leida);
					if(leidos > 0 && (leidos != 1 || inicial_leida == INICIAL_LIDER)) fallo_y_alcanza = true;
					
					if(lista_elementos(entrenador->pokemon) < 6) lista_insertar(entrenador->pokemon, pokemon);
					else pokemon_destruir(pokemon);
				}
				else{

					pokemon_destruir(pokemon);
					if(gimnasio_vacio(gimnasio) && entrenador_vacio(entrenador)) abortar_lectura(gimnasio, &fallo);
					if(!gimnasio_vacio(gimnasio) && entrenador_vacio(entrenador)){

						lista_desapilar(gimnasio->entrenadores);
						fallo_y_alcanza = true;
					}
					else fallo_y_alcanza = true;
				}
			}
			else{

				if(gimnasio_vacio(gimnasio) && entrenador_vacio(entrenador)) abortar_lectura(gimnasio, &fallo);
				if(!gimnasio_vacio(gimnasio) && entrenador_vacio(entrenador)){

					lista_desapilar(gimnasio->entrenadores);
					fallo_y_alcanza = true;
				}
				else fallo_y_alcanza = true;
			}
		}	
	}

	if(fallo) return ERROR;
	else if(leidos < 0) return EXITO;
	
	return SEGUIR;
}	

/*
 * Guarda los gimnasios leidos de un archivo en un arbol. Todos los datos son recibidos por parametro.
 * En el caso de que uno o mas gimnasios no se hayan podido agregar al arbol, se encargara de liberar el espacio que ocupan en 
 * memoria.
 */
void agregar_gimnasios(heap_t* heap, gimnasio_t** lista_gimnasios, int cant_gimnasios){

	if(!heap) return;

	bool fallo = false;
	int cant_agregados = 0, i;
	for(i = 0; i < cant_gimnasios && !fallo; i++){

		if(heap_insertar(heap, lista_gimnasios[i]) == ERROR) fallo = true;
		else cant_agregados++;
	}

	if(cant_agregados < cant_gimnasios){

		for(i = cant_agregados; i < cant_gimnasios; i++)
			gimnasio_destruir(lista_gimnasios[i]);
	}
}

/*FUNCIONES BIBLIOTECA*/

gimnasio_t* gimnasio_crear(){

	gimnasio_t* gimnasio_nuevo = calloc(1, sizeof(gimnasio_t));
	if(!gimnasio_nuevo) return NULL;

	gimnasio_nuevo->entrenadores = lista_crear(entrenador_destructor);
	if(!gimnasio_nuevo->entrenadores){

		free(gimnasio_nuevo);
		return NULL;
	}

	return gimnasio_nuevo;
}

int gimnasio_cargar(heap_t* heap, FILE* archivo_gimnasio){

	if(!heap || !archivo_gimnasio) return ERROR;

	char inicial_leida;
	bool fallo = false, termino = false;
	int cant_gimnasios = 0, resultado, leidos;
	gimnasio_t* lista_gimnasios[MAX_GIMNASIOS];

	leidos = fscanf(archivo_gimnasio, FORMATO_CARACTER, &inicial_leida);
	if(leidos != 1 || inicial_leida != INICIAL_GIMNASIO) return ERROR;

	gimnasio_t* gimnasio = gimnasio_crear();
	if(!gimnasio) return ERROR;

	while(!fallo && !termino){

		resultado = resultado_lectura(archivo_gimnasio, gimnasio);

		if(resultado == SEGUIR || resultado == EXITO){

			lista_gimnasios[cant_gimnasios] = gimnasio;
			cant_gimnasios++;

			if(resultado == SEGUIR){

				gimnasio = gimnasio_crear();
				if(!gimnasio) fallo = true;
			}
			else termino = true;
		}
		else fallo = true;
	}

	if(cant_gimnasios > 0) agregar_gimnasios(heap, lista_gimnasios, cant_gimnasios);

	if(fallo) return ERROR;

	return EXITO;
}

bool gimnasio_vacio(gimnasio_t* gimnasio){

	return (!gimnasio || !gimnasio->entrenadores || !lista_elementos(gimnasio->entrenadores));
}

void gimnasio_destruir(gimnasio_t* gimnasio){

	if(!gimnasio) return;

	if(gimnasio->entrenadores) lista_destruir(gimnasio->entrenadores);
	free(gimnasio);
}

