#include "lista.h"
#include <stdio.h>
#include <stdlib.h>

#define ERROR -1
#define EXITO 0

//---------------------------------------------------AUXILIARES----------------------------------------------------------

/* 
 *Precondiciones: el nodo que recibe como parametro debe existir (contener un elemento y apuntar a un siguiente) o ser 
  nulo.
 *Postcondiciones: reserva memoria para un nuevo nodo con los datos que recibe como parametro y devuelve su direccion de 
  memoria.
 */
nodo_t* crear_nodo(void* elemento, nodo_t* siguiente){

	nodo_t* nodo_nuevo = malloc(sizeof(nodo_t));
	if(!nodo_nuevo) return NULL;

	nodo_nuevo->elemento = elemento;
	nodo_nuevo->siguiente = siguiente;

	return nodo_nuevo;
}

/*
 *Precondiciones: el nodo que recibe como parametro debe existir (contener un elemento y apuntar a un siguiente) o ser 
  nulo.
 *Postcondiciones: recorre la lista hasta llegar a la posicion pedida y devuelve el nodo que hay en la misma.
 */
nodo_t* nodo_especifico(nodo_t* nodo, size_t posicion){

	if(posicion == 0) return nodo;
	return nodo_especifico(nodo->siguiente, posicion - 1);
}

/*
 *Precondiciones: el nodo que recibe por parametro debe existir (contener un elemento y apuntar a un siguiente) o ser 
  nulo.
 *Postcondiciones: libera la memoria que ocupa el nodo que recibe como parametro.
 */
void destruir_nodo(nodo_t* nodo, nodo_destructor destructor){

	if(!nodo) return;

	nodo_t* siguiente = nodo->siguiente;
	if(destructor) destructor(nodo->elemento);
	free(nodo);
	destruir_nodo(siguiente, destructor);
}

/*
 *Precondiciones: el nodo que recibe como parametro debe existir (contener un elemento y apuntar a un siguiente) o ser 
  nulo.
 *Postcondiciones: devuelve la cantidad de nodos de la lista que pudo recorrer hasta que se dejo de cumplir la condicion
  impuesta por la funcion recibida como parametro.
 */
size_t cantidad_recorridos(nodo_t* nodo, bool (*funcion)(void*, void*), void *contexto){

	if(!nodo || !funcion(nodo->elemento, contexto)) return 0;

	return (1 + cantidad_recorridos(nodo->siguiente, funcion, contexto));
}

//---------------------------------------------------IMPLEMENTACIONES----------------------------------------------------

lista_t* lista_crear(nodo_destructor destructor){

	lista_t* lista = calloc(1, sizeof(lista_t));
	if(!lista) return NULL;

	lista->destructor = destructor;
	return lista;
}

int lista_insertar(lista_t* lista, void* elemento){

	if(!lista) return ERROR;

	nodo_t* nodo_nuevo = crear_nodo(elemento, NULL);
	if(!nodo_nuevo) return ERROR;

	if(lista_vacia(lista)) lista->nodo_inicio = nodo_nuevo;
	else lista->nodo_fin->siguiente = nodo_nuevo;

	lista->nodo_fin = nodo_nuevo;
	lista->cantidad++;

	return EXITO;
}

int lista_insertar_en_posicion(lista_t* lista, void* elemento, size_t posicion){

	if(!lista) return ERROR;

	if((posicion > (lista_elementos(lista) - 1)) || lista_vacia(lista)){

		if(lista_insertar(lista, elemento) == EXITO) return EXITO;
		else return ERROR;
	}

	nodo_t* nodo_nuevo = NULL;
	if(posicion == 0){

		nodo_nuevo = crear_nodo(elemento, lista->nodo_inicio);
		if(!nodo_nuevo) return ERROR;

		lista->nodo_inicio = nodo_nuevo;
	}
	else{

		nodo_t* anterior = nodo_especifico(lista->nodo_inicio, posicion - 1);
		nodo_nuevo = crear_nodo(elemento, anterior->siguiente);
		if(!nodo_nuevo) return ERROR;

		anterior->siguiente = nodo_nuevo;
	}

	lista->cantidad++;

	return EXITO;
}

int lista_borrar(lista_t* lista){

	if(lista_vacia(lista)) return ERROR;

	nodo_t* nodo_eliminar = lista->nodo_fin;

	if(lista_elementos(lista) > 1){

		lista->nodo_fin = nodo_especifico(lista->nodo_inicio, lista_elementos(lista) - 2);
		lista->nodo_fin->siguiente = NULL;
	}

	if(lista->destructor) lista->destructor(nodo_eliminar->elemento);
	free(nodo_eliminar);
	lista->cantidad--;

	return EXITO;
}

int lista_borrar_de_posicion(lista_t* lista, size_t posicion){

	if(lista_vacia(lista)) return ERROR;

	if(posicion >= (lista_elementos(lista) - 1) || lista_elementos(lista) == 1){

		if(lista_borrar(lista) == EXITO) return EXITO;
		else return ERROR;
	}

	if(posicion == 0){

		nodo_t* nuevo_inicio = lista->nodo_inicio->siguiente;
		if(lista->destructor) lista->destructor(lista->nodo_inicio->elemento);
		free(lista->nodo_inicio);
		lista->nodo_inicio = nuevo_inicio;
	}
	else{

		nodo_t* anterior = nodo_especifico(lista->nodo_inicio, posicion - 1);
		nodo_t* posterior = anterior->siguiente->siguiente;
		if(lista->destructor) lista->destructor(anterior->siguiente->elemento);
		free(anterior->siguiente);
		anterior->siguiente = posterior;
	}

	lista->cantidad--;

	return EXITO;
}

void* lista_elemento_en_posicion(lista_t* lista, size_t posicion){

	if(lista_vacia(lista) || posicion > (lista_elementos(lista) - 1)) return NULL;

	return nodo_especifico(lista->nodo_inicio, posicion)->elemento;
}

void* lista_ultimo(lista_t* lista){

	if(lista_vacia(lista)) return NULL;

	return lista->nodo_fin->elemento;
}

bool lista_vacia(lista_t* lista){

	if(!lista || (lista->cantidad == 0)) return true;

	return false;
}

size_t lista_elementos(lista_t* lista){

	if(lista_vacia(lista)) return 0;

	return lista->cantidad;
}

int lista_apilar(lista_t* lista, void* elemento){

	return lista_insertar(lista, elemento);
}

int lista_desapilar(lista_t* lista){

	return lista_borrar(lista);
}

void* lista_tope(lista_t* lista){

	return lista_ultimo(lista);
}

int lista_encolar(lista_t* lista, void* elemento){

	return lista_insertar(lista, elemento);
}

int lista_desencolar(lista_t* lista){

	return lista_borrar_de_posicion(lista, 0);
}

void* lista_primero(lista_t* lista){

	return lista_elemento_en_posicion(lista, 0);
}

void lista_destruir(lista_t* lista){

	if(!lista) return;

	if(!lista_vacia(lista)) destruir_nodo(lista->nodo_inicio, lista->destructor);
	free(lista);
}

lista_iterador_t* lista_iterador_crear(lista_t* lista){

	if(!lista) return NULL;

	lista_iterador_t* iterador = malloc(sizeof(lista_iterador_t));
	if(!iterador) return NULL;

	iterador->lista = lista;
	iterador->corriente = lista->nodo_inicio;

	return iterador;
}

bool lista_iterador_tiene_siguiente(lista_iterador_t* iterador){

	return (iterador && iterador->corriente);
}

bool lista_iterador_avanzar(lista_iterador_t* iterador){

	if(!lista_iterador_tiene_siguiente(iterador)) return false;

	iterador->corriente = iterador->corriente->siguiente;

	return iterador->corriente;
}

void* lista_iterador_elemento_actual(lista_iterador_t* iterador){

	if(!lista_iterador_tiene_siguiente(iterador)) return NULL;

	return iterador->corriente->elemento;
}

void lista_iterador_destruir(lista_iterador_t* iterador){

	if(!iterador) return;
	
	free(iterador);
}

size_t lista_con_cada_elemento(lista_t* lista, bool (*funcion)(void*, void*), void *contexto){

	if(lista_vacia(lista) || !funcion) return 0;

	return cantidad_recorridos(lista->nodo_inicio, funcion, contexto);
}