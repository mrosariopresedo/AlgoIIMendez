#include <stdio.h>
#include "abb.h"

#define ERROR -1
#define EXITO 0

abb_t* arbol_crear(abb_comparador comparador, abb_liberar_elemento destructor){

	if(!comparador) return NULL;
	
	abb_t* arbol = calloc(1, sizeof(abb_t));
	if(!arbol) return NULL;

	arbol->comparador = comparador;
	arbol->destructor = destructor;

	return arbol;
}

/*
 * Precondiciones: el nodo que recibe como parametro existe (contiene un elemento y apunta a un izquierdo o NULL y derecho o NULL), o es nulo.
 * Postcondiciones: inserta un nuevo nodo recibido por parametro en un arbol. Si hay duplicados, siempre se sigue el recorrido hacia la 
 * izquierda.
 */
int nodo_insertar(nodo_abb_t* actual, nodo_abb_t* nueva_hoja, abb_comparador comparador){

    if(comparador(nueva_hoja->elemento, actual->elemento) > 0){

    	if(!actual->derecha) actual->derecha = nueva_hoja;
    	else nodo_insertar(actual->derecha, nueva_hoja, comparador);
    }
    else{

    	if(!actual->izquierda) actual->izquierda = nueva_hoja;
    	else nodo_insertar(actual->izquierda, nueva_hoja, comparador);
    }

    return EXITO;
}

/*
 * Postcondiciones: crea un nuevo elemento para el arbol. Devuelve la direccion de memoria del mismo o NULL en caso de que la operacion no haya 
 * sido exitosa.
 */
nodo_abb_t* nodo_crear(void* elemento){

	nodo_abb_t* nodo_nuevo = calloc(1, sizeof(nodo_abb_t));
	if(!nodo_nuevo) return NULL;

	nodo_nuevo->elemento = elemento;

	return nodo_nuevo;
}

int arbol_insertar(abb_t* arbol, void* elemento){

	if(!arbol) return ERROR;

	nodo_abb_t* nueva_hoja = nodo_crear(elemento);
	if(!nueva_hoja) return ERROR;

	if(arbol_vacio(arbol)){

		arbol->nodo_raiz = nueva_hoja;
		return EXITO;
	}

	return nodo_insertar(arbol->nodo_raiz, nueva_hoja, arbol->comparador);
}

/*
 * Precondiciones: el nodo que recibe como parametro existe (contiene un elemento y apunta a un izquierdo o NULL y derecho o NULL), o es nulo.
 * Postcondiciones: busca el mayor del subarbol izquierdo de un nodo a eliminar, para que lo pueda reemplazar.
 */
nodo_abb_t* predecesor_inorden(nodo_abb_t* actual){

	if(!actual->derecha) return actual;
	return predecesor_inorden(actual->derecha);
}

/*
 * Precondiciones: el arbol que recibe por parametro existe o es nulo. El nodo existe (contiene un elemento y apunta a un izquierdo o NULL y 
 * derecho o NULL), o es nulo.
 * Postcondiciones: borra el elemento recibido por parametro de un arbol y devuelve el arbol modificado o como estaba originalmente dependiendo 
 * del resultado de la operacion. 
 */
nodo_abb_t* nodo_borrar(abb_t* arbol, nodo_abb_t* actual, void* elemento, int* borrado){

	if(!actual) return NULL;

	if(arbol->comparador(elemento, actual->elemento) < 0) 
		actual->izquierda = nodo_borrar(arbol, actual->izquierda, elemento, borrado);
	else if (arbol->comparador(elemento, actual->elemento) > 0) 
		actual->derecha = nodo_borrar(arbol, actual->derecha, elemento, borrado);
	else{

		if(actual->izquierda && actual->derecha){

			void* elem_a_borrar = actual->elemento;
			nodo_abb_t* reemplazo = predecesor_inorden(actual->izquierda);
			actual->elemento = reemplazo->elemento;
			reemplazo->elemento = elem_a_borrar;
			actual->izquierda = nodo_borrar(arbol, actual->izquierda, reemplazo->elemento, borrado);
		}
		else{

			nodo_abb_t* heredero = actual->izquierda ? actual->izquierda : actual->derecha;
			if(arbol->destructor) arbol->destructor(actual->elemento);
			free(actual);
			*borrado = EXITO;
			return heredero;
		}
	}

	return actual;
}

int arbol_borrar(abb_t* arbol, void* elemento){

	if(arbol_vacio(arbol)) return ERROR;

	int borrado = ERROR;
	arbol->nodo_raiz = nodo_borrar(arbol, arbol->nodo_raiz, elemento, &borrado);

	return borrado;
}

/*
 * Precondiciones: el nodo que recibe como parametro existe (contiene un elemento y apunta a un izquierdo o NULL y derecho o NULL), o es nulo.
 * Postcondiciones: busca el elemento recibido como parametro dentro del arbol. Devuelve un elemento valido o NULL dependiendo de si encontro o 
 * no el elemento buscado.
 */
void* elemento_buscar(nodo_abb_t* actual, void* elemento, abb_comparador comparador){

    if(!actual) return NULL;

   	if(comparador(elemento, actual->elemento) > 0) return elemento_buscar(actual->derecha, elemento, comparador);
    else if(comparador(elemento, actual->elemento) < 0) return elemento_buscar(actual->izquierda, elemento, comparador);
	
	return actual->elemento;
}

void* arbol_buscar(abb_t* arbol, void* elemento){

	if(arbol_vacio(arbol)) return NULL;

	return elemento_buscar(arbol->nodo_raiz, elemento, arbol->comparador);
}

void* arbol_raiz(abb_t* arbol){

	if(arbol_vacio(arbol)) return NULL;

	return arbol->nodo_raiz->elemento;
}

bool arbol_vacio(abb_t* arbol){
	return !(arbol && arbol->nodo_raiz);
}

/*
 * Precondiciones: el nodo que recibe como parametro existe (contiene un elemento y apunta a un izquierdo o NULL y derecho o NULL), o es nulo. 
 * La variable que lleva la cuenta de cuantos elementos se insertaron esta previamente inicializada en 0.
 * Postcondiciones: llena el arreglo del tamaño dado con los elementos de arbol en secuencia inorden (IND) y modifica la variable insertados cada 
 * vez que agrega un elemento al vector.
 */
void insercion_inorden(nodo_abb_t* actual, void** array, size_t tamanio_array, size_t* insertados){

    if(actual){

    	insercion_inorden(actual->izquierda, array, tamanio_array, insertados);

    	if(*insertados < tamanio_array){

	    	array[*insertados] = actual->elemento;
	    	(*insertados)++;
	    }

    	insercion_inorden(actual->derecha, array, tamanio_array, insertados);
	}
}

size_t arbol_recorrido_inorden(abb_t* arbol, void** array, size_t tamanio_array){

	if(arbol_vacio(arbol)) return 0;

	size_t insertados = 0;
	insercion_inorden(arbol->nodo_raiz, array, tamanio_array, &insertados);

	return insertados;
}

/*
 * Precondiciones: el nodo que recibe como parametro existe (contiene un elemento y apunta a un izquierdo o NULL y derecho o NULL), o es nulo. 
 * La variable que lleva la cuenta de cuantos elementos se insertaron esta previamente inicializada en 0.
 * Postcondiciones: llena el arreglo del tamaño dado con los elementos de arbol en secuencia preorden (NID) y modifica la variable insertados 
 * cada vez que agrega un elemento al vector.
 */
void insercion_preorden(nodo_abb_t* actual, void** array, size_t tamanio_array, size_t* insertados){

    if(actual){

    	if(*insertados < tamanio_array){

	    	array[*insertados] = actual->elemento;
	    	(*insertados)++;
	    }

    	insercion_preorden(actual->izquierda, array, tamanio_array, insertados);
    	insercion_preorden(actual->derecha, array, tamanio_array, insertados);
	}
}

size_t arbol_recorrido_preorden(abb_t* arbol, void** array, size_t tamanio_array){

	if(arbol_vacio(arbol)) return 0;

	size_t insertados = 0;
	insercion_preorden(arbol->nodo_raiz, array, tamanio_array, &insertados);

	return insertados;
}

/*
 * Precondiciones: el nodo que recibe como parametro existe (contiene un elemento y apunta a un izquierdo o NULL y derecho o NULL), o es nulo. 
 * La variable que lleva la cuenta de cuantos elementos se insertaron esta previamente inicializada en 0.
 * Postcondiciones: llena el arreglo del tamaño dado con los elementos de arbol en secuencia postorden(IDN) y modifica la variable insertados 
 * cada vez que agrega un elemento al vector.
 */
void insercion_postorden(nodo_abb_t* actual, void** array, size_t tamanio_array, size_t* insertados){

    if(actual){

    	insercion_postorden(actual->izquierda, array, tamanio_array, insertados);
    	insercion_postorden(actual->derecha, array, tamanio_array, insertados);
    	
    	if(*insertados < tamanio_array){

	    	array[*insertados] = actual->elemento;
	    	(*insertados)++;
	    }
	}
}

size_t arbol_recorrido_postorden(abb_t* arbol, void** array, size_t tamanio_array){

	if(arbol_vacio(arbol)) return 0;

	size_t insertados = 0;
	insercion_postorden(arbol->nodo_raiz, array, tamanio_array, &insertados);

	return insertados;
}

/*
 * Precondiciones: el nodo que recibe como parametro existe (contiene un elemento y apunta a un izquierdo o NULL y derecho o NULL), o es nulo.
 * Postcondiciones: borra cada nodo de un arbol en secuencia postorden, lo cual nos asegura de siempre estar liberando hojas y no perder 
 * referencias.
 */
void nodo_destruir(abb_liberar_elemento destructor, nodo_abb_t* nodo){

	if(nodo){

		nodo_destruir(destructor, nodo->izquierda);
		nodo_destruir(destructor, nodo->derecha);

		if(destructor) destructor(nodo->elemento);
		free(nodo);
	}
}

void arbol_destruir(abb_t* arbol){

	if(!arbol) return;
	
	if(!arbol_vacio(arbol)) nodo_destruir(arbol->destructor, arbol->nodo_raiz);
	free(arbol);
}

/*
 * Precondiciones: el nodo que recibe como parametro existe (contiene un elemento y apunta a un izquierdo o NULL y derecho o NULL), o es nulo. 
 * La variable que lleva la cuenta de cuantos elementos se insertaron esta previamente inicializada en 0.
 * Postcondiciones: llama a la funcion recibida por parametro enviandole los elementos de arbol en secuencia inorden (IND) y modifica la variable 
 * visitados cada vez que visita un nodo.
 */
void iterador_inorden(nodo_abb_t* actual, bool (*funcion)(void*, void*), void* extra, size_t* visitados, bool* terminar){

	if(actual){

    	iterador_inorden(actual->izquierda, funcion, extra, visitados, terminar);

    	if(!(*terminar)){

    		*terminar = funcion(actual->elemento, extra);
    		(*visitados)++;
    	}
  
    	iterador_inorden(actual->derecha, funcion, extra, visitados, terminar);
	}
}

/*
 * Precondiciones: el nodo que recibe como parametro existe (contiene un elemento y apunta a un izquierdo o NULL y derecho o NULL), o es nulo. 
 * La variable que lleva la cuenta de cuantos elementos se insertaron esta previamente inicializada en 0.
 * Postcondiciones: llama a la funcion recibida por parametro enviandole los elementos de arbol en secuencia preorden (NID) y modifica la variable 
 * visitados cada vez que visita un nodo.
 */
void iterador_preorden(nodo_abb_t* actual, bool (*funcion)(void*, void*), void* extra, size_t* visitados, bool* terminar){

	if(actual){

    	if(!(*terminar)){
    		
    		*terminar = funcion(actual->elemento, extra);
    		(*visitados)++;
    	}

    	iterador_preorden(actual->izquierda, funcion, extra, visitados, terminar);
    	iterador_preorden(actual->derecha, funcion, extra, visitados, terminar);
	}
}

/*
 * Precondiciones: el nodo que recibe como parametro existe (contiene un elemento y apunta a un izquierdo o NULL y derecho o NULL), o es nulo. 
 * La variable que lleva la cuenta de cuantos elementos se insertaron esta previamente inicializada en 0.
 * Postcondiciones: llama a la funcion recibida por parametro enviandole los elementos de arbol en secuencia postorden (IDN) y modifica la variable 
 * visitados cada vez que visita un nodo.
 */
void iterador_postorden(nodo_abb_t* actual, bool (*funcion)(void*, void*), void* extra, size_t* visitados, bool* terminar){

	if(actual){

    	iterador_postorden(actual->izquierda, funcion, extra, visitados, terminar);
    	iterador_postorden(actual->derecha, funcion, extra, visitados, terminar);

    	if(!(*terminar)){
    		
    		*terminar = funcion(actual->elemento, extra);
    		(*visitados)++;
    	}
	}
}

size_t abb_con_cada_elemento(abb_t* arbol, int recorrido, bool (*funcion)(void*, void*), void* extra){

	if(arbol_vacio(arbol) || !funcion) return 0;

	size_t visitados = 0;
	bool terminar = false;

	if(recorrido == ABB_RECORRER_INORDEN) iterador_inorden(arbol->nodo_raiz, funcion, extra, &visitados, &terminar);
	else if(recorrido == ABB_RECORRER_PREORDEN) iterador_preorden(arbol->nodo_raiz, funcion, extra, &visitados, &terminar);
 	else if(recorrido == ABB_RECORRER_POSTORDEN) iterador_postorden(arbol->nodo_raiz, funcion, extra, &visitados, &terminar);
 	else return 0;

 	return visitados;
}