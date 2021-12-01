#include "lista.h"
#include "pa2mm.h"
#include <stdio.h>
	
#define N 5
#define ERROR -1
#define EXITO 0
#define MAX_ELEMENTOS 100

//----------------------------------------------------AUXILIAR-----------------------------------------------------------

void imprimir_lista(lista_t* lista){

	for(int i = 0; i < lista_elementos(lista); i++)
		printf("Elemento %i: %i\n", i, *(int*)lista_elemento_en_posicion(lista, i));
}

//-------------------------------------------FUNCIONES PARA ITERADOR INTERNO--------------------------------------------

bool es_menor_a_n(void* elemento, void* cant){

	if(elemento && cant && *(int*)elemento < N){

		(*(int*)cant)++;
		return true;
	}

	return false;
}

bool es_mayor_a_n(void* elemento, void* cant){

	if(elemento && cant && *(int*)elemento > N){

		(*(int*)cant)++;
		return true;
	}

	return false;
}

bool mostrar_palabra(void* elemento, void* usadas){

	if(elemento && usadas){

		//printf("%c", *(char*)elemento);
		(*(int*)usadas)--;
		return true;
	}

	return false;
}

//-----------------------------------------------------------------------------------------------------------------------

void probar_lista_crear(){

	lista_t* lista = NULL;

	pa2m_afirmar((lista = lista_crear()) != NULL, "Puedo crear una lista");
	pa2m_afirmar(((*lista).cantidad) == 0, "Tiene 0 elementos");
	pa2m_afirmar(!((*lista).nodo_inicio), "El nodo inicial apunta a NULL");
	pa2m_afirmar(!((*lista).nodo_fin), "El nodo final apunta a NULL");

	lista_destruir(lista);
}

void probar_pasar_listas_nulas(){

	pa2m_afirmar(lista_insertar(NULL, NULL) == ERROR, "No se puede insertar elemento al final");
	pa2m_afirmar(lista_insertar_en_posicion(NULL, NULL, 0) == ERROR, "No se puede insertar elemento en posicion");
	pa2m_afirmar(lista_borrar(NULL) == ERROR, "No se puede borrar ultimo elemento");
	pa2m_afirmar(lista_borrar_de_posicion(NULL, 0) == ERROR, "No se puede borrar elemento de posicion");
	pa2m_afirmar(lista_elemento_en_posicion(NULL, 0) == NULL, "No se puede buscar elemento de una posicion");
	pa2m_afirmar(lista_ultimo(NULL) == NULL, "No se puede buscar ultimo elemento");
	pa2m_afirmar(lista_elementos(NULL) == 0, "Hay 0 elementos");
	pa2m_afirmar(lista_vacia(NULL), "La lista esta vacia");
	pa2m_afirmar(lista_apilar(NULL, NULL) == ERROR, "No se puede apilar un elemento");
	pa2m_afirmar(lista_desapilar(NULL) == ERROR, "No se puede desapilar un elemento");
	pa2m_afirmar(lista_tope(NULL) == NULL, "No tiene tope");
	pa2m_afirmar(lista_encolar(NULL, NULL) == ERROR, "No se puede encolar un elemento");
	pa2m_afirmar(lista_desencolar(NULL) == ERROR, "No se puede desencolar un elemento");
	pa2m_afirmar(lista_primero(NULL) == NULL, "No tiene primero");
	pa2m_afirmar(lista_iterador_crear(NULL) == NULL, "No se puede crear un iterador");
	pa2m_afirmar(!lista_iterador_tiene_siguiente(NULL), "No se puede iterar");
	pa2m_afirmar(!lista_iterador_avanzar(NULL), "No se puede avanzar");
	pa2m_afirmar(!lista_iterador_elemento_actual(NULL), "No se puede obtener elemento");
	pa2m_afirmar(lista_con_cada_elemento(NULL, &es_menor_a_n, NULL) == 0, "No se puede iterar con cada elemento");
	pa2m_afirmar(lista_con_cada_elemento(NULL, NULL, NULL) == 0, "No se puede iterar con cada elemento sin funcion");
}

void probar_lista_insertar_lista_vacia(){

	int a = 0;
	lista_t* lista = lista_crear();

	pa2m_afirmar((lista_insertar(lista, &a) == EXITO) && (*(int*)lista_primero(lista) == a) &&                          (lista_elementos(lista) == 1), "Se puede insertar elemento al final");

	lista_destruir(lista);
}

void probar_lista_insertar_en_posicion_lista_vacia(){

	int a = 0;
	lista_t* lista = lista_crear();

	pa2m_afirmar((lista_insertar_en_posicion(lista, &a, 0) == EXITO) && (*(int*)lista_primero(lista) == a) &&           (lista_elementos(lista) == 1), "Se puede insertar elemento en posicion");

	lista_destruir(lista);
}

void probar_lista_borrar_lista_vacia(){

	lista_t* lista = lista_crear();

	pa2m_afirmar(lista_borrar(lista) == ERROR, "No se puede borrar ultimo elemento");

	lista_destruir(lista);
}

void probar_lista_borrar_de_posicion_lista_vacia(){

	lista_t* lista = lista_crear();

	pa2m_afirmar(lista_borrar_de_posicion(lista, 0) == ERROR, "No se puede borrar elemento de posicion");

	lista_destruir(lista);
}

void probar_lista_elemento_en_posicion_lista_vacia(){

	lista_t* lista = lista_crear();

	pa2m_afirmar(lista_elemento_en_posicion(lista, 0) == NULL, "No se puede buscar elemento de una posicion");

	lista_destruir(lista);
}
void probar_lista_ultimo_lista_vacia(){

	lista_t* lista = lista_crear();

	pa2m_afirmar(lista_ultimo(lista) == NULL, "No se puede buscar ultimo elemento");

	lista_destruir(lista);
}

void probar_lista_vacia_lista_vacia(){

	lista_t* lista = lista_crear();

	pa2m_afirmar(lista_vacia(lista), "La lista esta vacia");

	lista_destruir(lista);
}

void probar_lista_elementos_lista_vacia(){

	lista_t* lista = lista_crear();

	pa2m_afirmar(lista_elementos(lista) == 0, "Hay 0 elementos");

	lista_destruir(lista);
}

void probar_lista_apilar_lista_vacia(){

	int a = 0;
	lista_t* pila = lista_crear();

	pa2m_afirmar((lista_apilar(pila, &a) == EXITO) && (*(int*)lista_tope(pila) == a) && (lista_elementos(pila) == 1),   "Se puede apilar un elemento");

	lista_destruir(pila);
}

void probar_lista_desapilar_lista_vacia(){

	lista_t* pila = lista_crear();

	pa2m_afirmar(lista_desapilar(pila) == ERROR, "No se puede desapilar un elemento");

	lista_destruir(pila);
}

void probar_lista_tope_lista_vacia(){

	lista_t* pila = lista_crear();

	pa2m_afirmar(lista_tope(pila) == NULL, "No tiene tope");

	lista_destruir(pila);
}

void probar_lista_encolar_lista_vacia(){

	int a = 0;
	lista_t* cola = lista_crear();

	pa2m_afirmar((lista_encolar(cola, &a) == EXITO) && (*(int*)lista_primero(cola) == a) && (lista_elementos(cola) == 1), "Se puede encolar un elemento");

	lista_destruir(cola);
}

void probar_lista_desencolar_lista_vacia(){

	lista_t* cola = lista_crear();

	pa2m_afirmar(lista_desencolar(cola) == ERROR, "No se puede desencolar un elemento");

	lista_destruir(cola);
}

void probar_lista_primero_lista_vacia(){

	lista_t* cola = lista_crear();

	pa2m_afirmar(lista_primero(cola) == NULL, "No tiene primero");

	lista_destruir(cola);
}

void probar_lista_iterador_crear_lista_vacia(){

	lista_iterador_t* it;
	lista_t* lista = lista_crear();

	pa2m_afirmar((it = lista_iterador_crear(lista)) != NULL, "Se puede crear un iterador");

	lista_destruir(lista);
	lista_iterador_destruir(it);
}

void probar_lista_iterador_tiene_siguiente_lista_vacia(){

	lista_t* lista = lista_crear();
	lista_iterador_t* it = lista_iterador_crear(lista);

	pa2m_afirmar(!lista_iterador_tiene_siguiente(it), "No se puede iterar");

	lista_destruir(lista);
	lista_iterador_destruir(it);
}

void probar_lista_iterador_avanzar_lista_vacia(){

	lista_t* lista = lista_crear();
	lista_iterador_t* it = lista_iterador_crear(lista);

	pa2m_afirmar(!lista_iterador_avanzar(it), "No se puede avanzar");

	lista_destruir(lista);
	lista_iterador_destruir(it);
}

void probar_lista_iterador_elemento_actual_lista_vacia(){

	lista_t* lista = lista_crear();
	lista_iterador_t* it = lista_iterador_crear(lista);

	pa2m_afirmar(!lista_iterador_elemento_actual(it), "No se puede obtener elemento");

	lista_destruir(lista);
	lista_iterador_destruir(it);
}

void probar_lista_con_cada_elemento_lista_vacia(){

	int a = 0;
	lista_t* lista = lista_crear();

	pa2m_afirmar(lista_con_cada_elemento(lista, &es_menor_a_n, &a) == 0, "No se puede iterar con cada elemento");

	lista_destruir(lista);
}

void probar_pasar_listas_vacias(){

	probar_lista_insertar_lista_vacia();
   	probar_lista_insertar_en_posicion_lista_vacia();
   	probar_lista_borrar_lista_vacia();
   	probar_lista_borrar_de_posicion_lista_vacia();
   	probar_lista_elemento_en_posicion_lista_vacia();
   	probar_lista_ultimo_lista_vacia();
   	probar_lista_elementos_lista_vacia();
   	probar_lista_vacia_lista_vacia();
	probar_lista_apilar_lista_vacia();
	probar_lista_desapilar_lista_vacia();
	probar_lista_tope_lista_vacia();
	probar_lista_encolar_lista_vacia();
	probar_lista_desencolar_lista_vacia();
	probar_lista_primero_lista_vacia();
	probar_lista_iterador_crear_lista_vacia();
	probar_lista_iterador_tiene_siguiente_lista_vacia();
	probar_lista_iterador_avanzar_lista_vacia();
	probar_lista_iterador_elemento_actual_lista_vacia();
	probar_lista_con_cada_elemento_lista_vacia();
}

void probar_lista_insertar_null(){

	lista_t* lista = lista_crear();

	pa2m_afirmar((lista_insertar(lista, NULL) == EXITO) && (lista_primero(lista) == NULL) && (lista_elementos(lista)   == 1), "Inserto al final un elemento nulo");

	lista_destruir(lista);
}

void probar_lista_insertar_en_posicion_null(){

	lista_t* lista = lista_crear();

	pa2m_afirmar((lista_insertar_en_posicion(lista, NULL, 0) == EXITO) && (lista_ultimo(lista) == NULL) &&              (lista_elementos(lista) == 1), "Inserto en posicion un elemento nulo");

	lista_destruir(lista);
}

void probar_lista_apilar_null(){

	lista_t* pila = lista_crear();

	pa2m_afirmar((lista_apilar(pila, NULL) == EXITO) && (lista_tope(pila) == NULL) && (lista_elementos(pila) == 1),      "Apilo un elemento nulo");

	lista_destruir(pila);
}

void probar_lista_encolar_null(){

	lista_t* cola = lista_crear();

	pa2m_afirmar((lista_encolar(cola, NULL) == EXITO) && (lista_primero(cola) == NULL) && (lista_elementos(cola) == 1), "Encolo un elemento nulo");

	lista_destruir(cola);
}

void probar_insertar_null(){

	probar_lista_insertar_null();
	probar_lista_insertar_en_posicion_null();
	probar_lista_apilar_null();
	probar_lista_encolar_null();
}

void probar_lista_insertar_en_posicion_lista_con_un_elemento(){

	int a = 0, b = 1;
	lista_t* lista = lista_crear();
	lista_insertar(lista, &b);

	pa2m_afirmar((lista_insertar_en_posicion(lista, &a, 0) == EXITO) && (*(int*)lista_primero(lista) == a) &&           (*(int*)lista_ultimo(lista) == b) && (lista_elementos(lista) == 2), "Inserto en primera posicion un elemento habiendo ya un elemento");

	lista_destruir(lista);
}

void probar_lista_borrar_lista_con_un_elemento(){

	int a = 0;
	lista_t* lista = lista_crear();
	lista_insertar(lista, &a);

	pa2m_afirmar((lista_borrar(lista) == EXITO) && (lista_elementos(lista) == 0), "Borro unico y ultimo elemento");

	lista_destruir(lista);
}

void probar_lista_borrar_de_posicion_lista_con_un_elemento(){

	int a = 0;
	lista_t* lista = lista_crear();

	lista_insertar(lista, &a);
	pa2m_afirmar((lista_borrar_de_posicion(lista, 7) == EXITO) && (lista_elementos(lista) == 0), "Borro unico y ultimo elemento si paso posicion inexistente");

	lista_insertar(lista, &a);
	pa2m_afirmar((lista_borrar_de_posicion(lista, 0) == EXITO) && (lista_elementos(lista) == 0), "Borro unico y ultimo elemento si paso posicion existente");

	lista_destruir(lista);
}

void probar_lista_ultimo_lista_con_un_elemento(){

	int a = 0;
	lista_t* lista = lista_crear();

	lista_insertar(lista, &a);
	pa2m_afirmar(*(int*)lista_ultimo(lista) == a, "Obtengo unico elemento como ultimo");

	lista_destruir(lista);
}

void probar_lista_desapilar_pila_con_un_elemento(){

	int a = 0;
	lista_t* pila = lista_crear(pila);
	lista_apilar(pila, &a);

	pa2m_afirmar((lista_desapilar(pila) == EXITO) && (lista_elementos(pila) == 0), "Desapilo unico y ultimo elemento");

	lista_destruir(pila);
}

void probar_lista_desencolar_cola_con_un_elemento(){

	int a = 0;
	lista_t* cola = lista_crear(cola);
	lista_encolar(cola, &a);

	pa2m_afirmar((lista_desencolar(cola) == EXITO) && (lista_elementos(cola) == 0), "Desencolo unico y ultimo elemento");

	lista_destruir(cola);
}

void probar_listas_con_un_elemento(){

	probar_lista_insertar_en_posicion_lista_con_un_elemento();
   	probar_lista_borrar_lista_con_un_elemento();
   	probar_lista_borrar_de_posicion_lista_con_un_elemento();
   	probar_lista_ultimo_lista_con_un_elemento();
   	probar_lista_desapilar_pila_con_un_elemento();
   	probar_lista_desencolar_cola_con_un_elemento();
}

void probar_lista_insertar(){

	bool todos_correctos = true;
	lista_t* lista = lista_crear();
	int a = 0, b = 1, c = 2, d = 3, e = 4, i = 0;

	pa2m_afirmar(lista_insertar(lista, &a) == EXITO, "Inserto primer elemento");
	pa2m_afirmar(lista_insertar(lista, &b) == EXITO, "Inserto segundo elemento");
	pa2m_afirmar(lista_insertar(lista, &c) == EXITO, "Inserto tercer elemento");
	pa2m_afirmar(lista_insertar(lista, &d) == EXITO, "Inserto cuarto elemento");
	pa2m_afirmar(lista_insertar(lista, &e) == EXITO, "Inserto quinto elemento");
	pa2m_afirmar(lista_elementos(lista) == 5, "Hay 5 elementos en la lista");

	while(todos_correctos && (i < lista_elementos(lista))){

		if(*(int*)lista_elemento_en_posicion(lista, i) != i) todos_correctos = false;
		i++;
	}
	pa2m_afirmar(todos_correctos, "Todos los elementos insertados son correctos");

	lista_destruir(lista);
}

void probar_lista_insertar_en_posicion(){

	bool todos_correctos = true;
	int elementos[] = {1,2,3,5,6};
	lista_t* lista = lista_crear();
	int a = 8, b = 0, c = 7, d = 4, i = 0;

	for(int i = 0; i < 5; i++)
		lista_insertar(lista, elementos + i);

	pa2m_afirmar(lista_elementos(lista) == 5, "Hay 5 elementos en la lista");
	pa2m_afirmar(lista_insertar_en_posicion(lista, &a, 5) == EXITO, "Inserto al final si no existe la posicion");
	pa2m_afirmar(lista_insertar_en_posicion(lista, &b, 0) == EXITO, "Inserto al principio");
	pa2m_afirmar(lista_insertar_en_posicion(lista, &c, 6) == EXITO, "Inserto en ultima posicion");
	pa2m_afirmar(lista_insertar_en_posicion(lista, &d, 4) == EXITO, "Inserto en posicion distinta de ppio/fin");
	pa2m_afirmar(lista_elementos(lista) == 9, "Hay 9 elementos en la lista");

	while(todos_correctos && (i < lista_elementos(lista))){

		if(*(int*)lista_elemento_en_posicion(lista, i) != i) todos_correctos = false;
		i++;
	}
	pa2m_afirmar(todos_correctos && (lista_elementos(lista) == 9), "Todos los elementos insertados son correctos");

	lista_destruir(lista);
}

void probar_lista_borrar(){

	int i = 0;
	int elementos[MAX_ELEMENTOS];
	lista_t* lista = lista_crear();
	bool borrados = true, todos_correctos = true;

	for(int i = 1; i <= 10; i++){ 

		elementos[i] = i;
		lista_insertar(lista, elementos + i);
	}

	pa2m_afirmar(lista_elementos(lista) == 10, "Hay 10 elementos en la lista");
	pa2m_afirmar((lista_borrar(lista) == EXITO) && (*(int*)lista_ultimo(lista) == 9) && (lista_elementos(lista) == 9),   "Borro un elemento");

	for(int i = 0; i < 3; i++){

		if(lista_borrar(lista) == ERROR) borrados = false;
		if(*(int*)lista_ultimo(lista) != lista_elementos(lista)) borrados = false;
	}

	pa2m_afirmar(borrados && (lista_elementos(lista) == 6), "Borro tres elementos mas");

	while(todos_correctos && (i < lista_elementos(lista))){

		if(*(int*)lista_elemento_en_posicion(lista, i) != (i + 1)) todos_correctos = false;
		i++;
	}
	pa2m_afirmar(todos_correctos && (lista_elementos(lista) == 6), "Todos los elementos borrados son correctos");

	borrados = true;
	for(int i = 0; i < 6; i++){

		if(lista_borrar(lista) == ERROR) borrados = false;
		if((lista_elementos(lista) > 1) && (*(int*)lista_ultimo(lista) != lista_elementos(lista))) borrados = false;
	}

	pa2m_afirmar(borrados && (lista_elementos(lista) == 0), "Borro los elementos restantes");

	lista_destruir(lista);
}

void probar_lista_borrar_de_posicion(){

	int i = 0;		
	lista_t* lista = lista_crear();
	int elementos[] = {0,1,2,3,6,4,5,6,7,8};
	bool todos_correctos = true, borrados = true;

	for(int i = 0; i < 10; i++)
		lista_insertar(lista, elementos + i);

	pa2m_afirmar(lista_elementos(lista) == 10, "Hay 10 elementos en la lista");
	pa2m_afirmar(lista_borrar_de_posicion(lista, 10) == EXITO, "Borro ultimo elemento si no existe la posicion");
	pa2m_afirmar(lista_borrar_de_posicion(lista, 8) == EXITO, "Borro ultimo elemento");
	pa2m_afirmar(lista_borrar_de_posicion(lista, 0) == EXITO, "Borro primer elemento");
	pa2m_afirmar(lista_borrar_de_posicion(lista, 3) == EXITO, "Borro elemento distinto de ppio/fin");

	while(todos_correctos && (i < lista_elementos(lista))){

		if(*(int*)lista_elemento_en_posicion(lista, i) != (i + 1)) todos_correctos = false;
		i++;
	}
	pa2m_afirmar(todos_correctos && (lista_elementos(lista) == 6), "Todos los elementos borrados son correctos");

	for(int i = 0; i < 6; i++){

		if(lista_borrar_de_posicion(lista, lista_elementos(lista) - 1) == ERROR) borrados = false;
		if((lista_elementos(lista) > 1) && (*(int*)lista_ultimo(lista) != lista_elementos(lista))) borrados = false;
	}

	pa2m_afirmar(borrados && lista_elementos(lista) == 0, "Borro los elementos restantes");

	lista_destruir(lista);
}

void probar_lista_elemento_en_posicion(){

	int elementos[MAX_ELEMENTOS];
	lista_t* lista = lista_crear();

	for(int i = 0; i < 5; i++){ 

		elementos[i] = i;
		lista_insertar(lista, elementos + i);
	}

	pa2m_afirmar(lista_elementos(lista) == 5, "Hay 5 elementos en la lista");
	pa2m_afirmar(*(int*)lista_elemento_en_posicion(lista, 0) == 0, "Obtengo primer elemento");
	pa2m_afirmar(*(int*)lista_elemento_en_posicion(lista, 1) == 1, "Obtengo segundo elemento");
	pa2m_afirmar(*(int*)lista_elemento_en_posicion(lista, 2) == 2, "Obtengo tercer elemento");
	pa2m_afirmar(*(int*)lista_elemento_en_posicion(lista, 3) == 3, "Obtengo cuarto elemento");
	pa2m_afirmar(*(int*)lista_elemento_en_posicion(lista, 4) == 4, "Obtengo quinto elemento");
	pa2m_afirmar(lista_elemento_en_posicion(lista, 5) == NULL, "Obtengo NULL con posicion que no existe");

	lista_destruir(lista);
}

void probar_lista_ultimo(){

	int elementos[MAX_ELEMENTOS];
	lista_t* lista = lista_crear();

	for(int i = 0; i < 5; i++){ 

		elementos[i] = i;
		lista_insertar(lista, elementos + i);
	}

	pa2m_afirmar(lista_elementos(lista) == 5, "Hay una lista con elementos")
	pa2m_afirmar(*(int*)lista_ultimo(lista) == 4, "Obtengo ultimo elemento");
	pa2m_afirmar(lista_borrar(lista) == EXITO, "Borro ultimo elemento");
	pa2m_afirmar(*(int*)lista_ultimo(lista) == 3, "Obtengo ultimo elemento nuevamente");

	lista_destruir(lista);
}

void probar_lista_vacia(){

	int a = 0;
	lista_t* lista = lista_crear();
	lista_insertar(lista, &a);

	pa2m_afirmar(lista_elementos(lista) == 1, "Hay una lista con al menos un elemento")
	pa2m_afirmar(!lista_vacia(lista), "La lista no esta vacia");

	lista_destruir(lista);
}

void probar_lista_elementos(){

	int a = 0;
	lista_t* lista = lista_crear();
	lista_insertar(lista, &a);

	pa2m_afirmar((*lista).cantidad == 1, "Hay una lista con al menos un elemento")
	pa2m_afirmar(lista_elementos(lista) == 1, "Obtengo la cantidad correcta de elementos");

	lista_destruir(lista);
}

void probar_lista_apilar(){

	bool todos_correctos = true;
	lista_t* pila = lista_crear();
	int a = 0, b = 1, c = 2, d = 3, e = 4, i = 0;

	pa2m_afirmar((lista_apilar(pila, &a) == EXITO) && (*(int*)lista_tope(pila) == a), "Apilo primer elemento");
	pa2m_afirmar((lista_apilar(pila, &b) == EXITO) && (*(int*)lista_tope(pila) == b), "Apilo segundo elemento");
	pa2m_afirmar((lista_apilar(pila, &c) == EXITO) && (*(int*)lista_tope(pila) == c), "Apilo tercer elemento");
	pa2m_afirmar((lista_apilar(pila, &d) == EXITO) && (*(int*)lista_tope(pila) == d), "Apilo cuarto elemento");
	pa2m_afirmar((lista_apilar(pila, &e) == EXITO) && (*(int*)lista_tope(pila) == e), "Apilo quinto elemento");
	pa2m_afirmar(!lista_vacia(pila) && (lista_elementos(pila) == 5), "Hay 5 elementos en la PILA");

	lista_destruir(pila);
}

void probar_lista_desapilar(){

	bool desapilados = true;
	int elementos[MAX_ELEMENTOS];
	lista_t* pila = lista_crear();

	for(int i = 1; i <= 10; i++){ 

		elementos[i] = i;
		lista_apilar(pila, elementos + i);
	}

	pa2m_afirmar((lista_desapilar(pila) == EXITO) && (*(int*)lista_tope(pila) == 9) && (lista_elementos(pila) == 9),     "Desapilo un elemento");

	for(int i = 0; i < 3; i++){

		if(lista_desapilar(pila) == ERROR) desapilados = false;
		if(*(int*)lista_tope(pila) != lista_elementos(pila)) desapilados = false;
	}
	pa2m_afirmar(desapilados && (lista_elementos(pila) == 6), "Desapilo tres elementos mas");

	desapilados = true;
	for(int i = 0; i < 6; i++){

		if(lista_desapilar(pila) == ERROR) desapilados = false;
		if((lista_elementos(pila) > 1) && (*(int*)lista_tope(pila) != lista_elementos(pila))) desapilados = false;
	}
	pa2m_afirmar(desapilados && (lista_elementos(pila) == 0), "Desapilo elementos restantes");

	lista_destruir(pila);
}

void probar_lista_tope(){

	int elementos[MAX_ELEMENTOS];
	lista_t* pila = lista_crear();

	for(int i = 0; i < 5; i++){ 

		elementos[i] = i;
		lista_apilar(pila, elementos + i);
	}

	pa2m_afirmar(lista_elementos(pila) == 5, "Hay una PILA con elementos");
	pa2m_afirmar(*(int*)lista_tope(pila) == 4, "Obtengo elemento en tope");
	pa2m_afirmar(lista_desapilar(pila) == EXITO, "Desapilo un elemento");
	pa2m_afirmar(*(int*)lista_tope(pila) == 3, "Obtengo elemento en tope nuevamente");

	lista_destruir(pila);
}
 
void probar_lista_encolar(){

	bool todos_correctos = true;
	lista_t* cola = lista_crear();
	int a = 0, b = 1, c = 2, d = 4, e = 5, i = 0;

	pa2m_afirmar((lista_encolar(cola, &a) == EXITO) && (*(int*)lista_primero(cola) == a), "Encolo primer elemento");
	pa2m_afirmar((lista_encolar(cola, &b) == EXITO) && (*(int*)lista_primero(cola) == a), "Encolo segundo elemento");
	pa2m_afirmar((lista_encolar(cola, &c) == EXITO) && (*(int*)lista_primero(cola) == a), "Encolo tercer elemento");
	pa2m_afirmar((lista_encolar(cola, &d) == EXITO) && (*(int*)lista_primero(cola) == a), "Encolo cuarto elemento");
	pa2m_afirmar((lista_encolar(cola, &e) == EXITO) && (*(int*)lista_primero(cola) == a), "Encolo quinto elemento");
	pa2m_afirmar(!lista_vacia(cola) && (lista_elementos(cola) == 5), "Hay 5 elementos en la COLA");

	lista_destruir(cola);
}

void probar_lista_desencolar(){

	bool desencolados = true;
	int elementos[MAX_ELEMENTOS];
	lista_t* cola = lista_crear();

	for(int i = 1; i <= 10; i++){ 

		elementos[i] = i;
		lista_encolar(cola, elementos + i);
	}

	pa2m_afirmar((lista_desencolar(cola) == EXITO) && (*(int*)lista_primero(cola) == 2) && (lista_elementos(cola) == 9), "Desencolo un elemento");

	for(int i = 0; i < 3; i++){

		if(lista_desencolar(cola) == ERROR) desencolados = false;
		if(*(int*)lista_primero(cola) != (i + 3)) desencolados = false;
	}
	pa2m_afirmar(desencolados && (lista_elementos(cola) == 6), "Desencolo tres elementos mas");

	desencolados = true;
	for(int i = 0; i < 6; i++){

		if(lista_desencolar(cola) == ERROR) desencolados = false;
		if((lista_elementos(cola) > 1) && (*(int*)lista_primero(cola) != (i + 6))) desencolados = false;
	}
	pa2m_afirmar(desencolados && (lista_elementos(cola) == 0), "Desencolo elementos restantes");

	lista_destruir(cola);
}

void probar_lista_primero(){

	int elementos[MAX_ELEMENTOS];
	lista_t* cola = lista_crear();

	for(int i = 0; i < 5; i++){ 

		elementos[i] = i;
		lista_encolar(cola, elementos + i);
	}

	pa2m_afirmar(lista_elementos(cola) == 5, "Hay una COLA con elementos");
	pa2m_afirmar(*(int*)lista_primero(cola) == 0, "Obtengo el primer elemento");
	pa2m_afirmar(lista_desencolar(cola) == EXITO, "Desencolo un elemento");
	pa2m_afirmar(*(int*)lista_primero(cola) == 1, "Obtengo primer elemento nuevamente");

	lista_destruir(cola);
}

void probar_lista_iterador_crear(){

	int a = 0;
	lista_iterador_t* it;
	lista_t* lista = lista_crear();
	lista_insertar(lista, &a);

	pa2m_afirmar((it = lista_iterador_crear(lista)) != NULL, "Creo iterador con lista no vacia");
	pa2m_afirmar((*it).lista == lista && (*it).corriente == (*lista).nodo_inicio, "La estructura se crea correctamente");
	pa2m_afirmar(*(int*)lista_iterador_elemento_actual(it) == a, "El iterador queda listo para devolver el primer elemento");

	lista_destruir(lista);
	lista_iterador_destruir(it);
}

void probar_lista_iterador_tiene_siguiente(){

	int a = 0, b = 1;
	lista_t* lista = lista_crear();
	lista_insertar(lista, &a);
	lista_insertar(lista, &b);
	lista_iterador_t* it = lista_iterador_crear(lista);

	pa2m_afirmar(lista_elementos((*it).lista) == 2, "Hay una lista con 2 elementos");
	pa2m_afirmar(lista_iterador_tiene_siguiente(it), "Puedo iterar sobre el primer elemento");
	lista_iterador_avanzar(it);
	pa2m_afirmar(lista_iterador_tiene_siguiente(it), "Puedo iterar sobre el segundo elemento");
	lista_iterador_avanzar(it);
	pa2m_afirmar(!lista_iterador_tiene_siguiente(it), "No puedo iterar si ya llegue al final");

	lista_destruir(lista);
	lista_iterador_destruir(it);
}

void probar_lista_iterador_avanzar(){

	int a = 0, b = 1;
	lista_t* lista = lista_crear();
	lista_insertar(lista, &a);
	lista_insertar(lista, &b);
	lista_iterador_t* it = lista_iterador_crear(lista);

	pa2m_afirmar(lista_elementos((*it).lista) == 2, "Hay una lista con 2 elementos");
	pa2m_afirmar(lista_iterador_avanzar(it) && (*(int*)(*(*it).corriente).elemento == 1), "Puedo avanzar del primero al segundo");
	pa2m_afirmar(!lista_iterador_avanzar(it), "Ya no puedo seguir avanzando");

	lista_destruir(lista);
	lista_iterador_destruir(it);	
}

void probar_lista_iterador_elemento_actual(){

	int i = 1;
	bool falla = false;
	int elementos[MAX_ELEMENTOS];
	lista_t* lista = lista_crear();

	for(int i = 0; i < 10; i++){ 

		elementos[i] = i;
		lista_insertar(lista, elementos + i);
	}
	lista_iterador_t* it = lista_iterador_crear(lista);

	while(lista_iterador_tiene_siguiente(it) && !falla){

		lista_iterador_avanzar(it);
		if((*it).corriente && (*(int*)lista_iterador_elemento_actual(it) != i)) falla = true;
		i++;
	}

	pa2m_afirmar(!falla, "Hay una lista con elementos, obtengo elemento de cada posicion");
	pa2m_afirmar(!lista_iterador_elemento_actual(it), "No puedo obtener un elemento si ya llegue al final");

	lista_destruir(lista);
	lista_iterador_destruir(it);	
}

void probar_lista_con_cada_elemento(){

	size_t cant_recorridos;
	int elementos[MAX_ELEMENTOS];
	char nombre[] = "ROSARIO PRESEDO";
	int cant_1 = 0, cant_2 = 0, cant_3 = 0, usadas = 15;

	lista_t* lista_1 = lista_crear();
	lista_t* lista_2 = lista_crear();
	for(int i = 0; i < 10; i++){ 

		elementos[i] = i;
		lista_insertar(lista_1, elementos + i);
	}
	for(int i = 0; i < 15; i++)
		lista_insertar(lista_2, nombre + i);

	cant_recorridos = lista_con_cada_elemento(lista_1, &es_menor_a_n, &cant_1);
	pa2m_afirmar((cant_recorridos == 5) && (cant_1 == 5), "Itera hasta que encuentra elemento mayor/igual a n");

	cant_recorridos = lista_con_cada_elemento(lista_1, &es_mayor_a_n, &cant_2);
	pa2m_afirmar((cant_recorridos == 0) && (cant_2 == 0), "Itera hasta que encuentro elemento menor/igual a n");

	cant_recorridos = lista_con_cada_elemento(lista_2, &mostrar_palabra, &usadas);
	pa2m_afirmar((cant_recorridos == 15) && (usadas == 0), "Itera hasta que termina de escribir un texto");

	lista_destruir(lista_1);
	lista_destruir(lista_2);
}

void sobrecargar_lista_insertar_borrar(){

	int i = 0, a = 0;
	bool falla = false;
	lista_t* lista = lista_crear();

	while((i < 20000) && !falla){

		if(lista_insertar(lista, &a) == ERROR) falla = true;
		i++;
	}
	pa2m_afirmar(!falla & (lista_elementos(lista) == 20000), "Inserto al final de la lista 20.000 elementos");

	i = 0;
	while((i < 20000) && !falla){

		if(lista_borrar(lista) == ERROR) falla = true;
		i++;
	}

	pa2m_afirmar(!falla & (lista_elementos(lista) == 0), "Borro del final de la lista los 20.000 elementos");

	lista_destruir(lista);
}

void sobrecargar_lista_insertar_borrar_en_posicion(){

	int i = 0, a = 0;
	bool falla = false;
	lista_t* lista = lista_crear();

	while((i < 20000) && !falla){

		if(lista_insertar_en_posicion(lista, &a, 0) == ERROR) falla = true;
		i++;
	}
	pa2m_afirmar(!falla & (lista_elementos(lista) == 20000), "Inserto en posicion de la lista 20.000 elementos");

	i = 0;
	while((i < 20000) && !falla){

		if(lista_borrar_de_posicion(lista, 0) == ERROR) falla = true;
		i++;
	}

	pa2m_afirmar(!falla & (lista_elementos(lista) == 0), "Borro de posicion de la lista los 20.000 elementos");

	lista_destruir(lista);
}

void sobrecargar_pila(){

	int i = 0, a = 0;
	bool falla = false;
	lista_t* pila = lista_crear();

	while((i < 20000) && !falla){

		if(lista_apilar(pila, &a) == ERROR) falla = true;
		i++;
	}
	pa2m_afirmar(!falla & (lista_elementos(pila) == 20000), "Apilo 20.000 elementos");

	i = 0;
	while((i < 20000) && !falla){

		if(lista_desapilar(pila) == ERROR) falla = true;
		i++;
	}

	pa2m_afirmar(!falla & (lista_elementos(pila) == 0), "Desapilo los 20.000 elementos");

	lista_destruir(pila);
}

void sobrecargar_cola(){

	int i = 0, a = 0;
	bool falla = false;
	lista_t* cola = lista_crear();

	while((i < 20000) && !falla){

		if(lista_encolar(cola, &a) == ERROR) falla = true;
		i++;
	}
	pa2m_afirmar(!falla & (lista_elementos(cola) == 20000), "Encolo 20.000 elementos");

	i = 0;
	while((i < 20000) && !falla){

		if(lista_desencolar(cola) == ERROR) falla = true;
		i++;
	}

	pa2m_afirmar(!falla & (lista_elementos(cola) == 0), "Desencolo los 20.000 elementos");

	lista_destruir(cola);
}

void sobrecargar_lista_iterador_avanzar(){

	int i = 0, a = 0;
	bool falla = false;
	lista_t* lista = lista_crear();

	while((i < 20000) && !falla){

		if(lista_insertar(lista, &a) == ERROR) falla = true;
		i++;
	}
	lista_iterador_t* it = lista_iterador_crear(lista);

	falla = false;
	while(lista_iterador_tiene_siguiente(it) && !falla)
		if(!lista_iterador_avanzar(it) && (*it).corriente) falla = true;

	pa2m_afirmar(!falla && (lista_elementos(lista) == 20000), "Avanzo hasta el final de una lista con 20.000 elementos");

	lista_destruir(lista);
	lista_iterador_destruir(it);	
}

void probar_sobrecargas(){

	sobrecargar_lista_insertar_borrar();
   	sobrecargar_lista_insertar_borrar_en_posicion();
   	sobrecargar_pila();
   	sobrecargar_cola();
   	sobrecargar_lista_iterador_avanzar();
}

int main(){

    pa2m_nuevo_grupo("PRUEBAS: creo una lista");
   	probar_lista_crear();

   	pa2m_nuevo_grupo("PRUEBAS: pasar lista nula a funcion");
   	probar_pasar_listas_nulas();

   	pa2m_nuevo_grupo("PRUEBAS: pasar lista vacia a funcion");
   	probar_pasar_listas_vacias();

	pa2m_nuevo_grupo("PRUEBAS: insertar elemento NULL");
	probar_insertar_null();

	pa2m_nuevo_grupo("PRUEBAS: listas con un elemento");
	probar_listas_con_un_elemento();

   	pa2m_nuevo_grupo("PRUEBAS: insertar al final");
   	probar_lista_insertar();

   	pa2m_nuevo_grupo("PRUEBAS: insertar en posicion");
   	probar_lista_insertar_en_posicion();

   	pa2m_nuevo_grupo("PRUEBAS: borrar al final");
   	probar_lista_borrar();

   	pa2m_nuevo_grupo("PRUEBAS: borrar de posicion");
   	probar_lista_borrar_de_posicion();

   	pa2m_nuevo_grupo("PRUEBAS: buscar elemento de la lista");
   	probar_lista_elemento_en_posicion();

   	pa2m_nuevo_grupo("PRUEBAS: buscar ultimo elemento de la lista");
   	probar_lista_ultimo();

   	pa2m_nuevo_grupo("PRUEBAS: lista vacia");
   	probar_lista_vacia();

   	pa2m_nuevo_grupo("PRUEBAS: cantidad de elementos de la lista");
   	probar_lista_elementos();

   	pa2m_nuevo_grupo("PRUEBAS: PILA");
   	probar_lista_apilar();
   	probar_lista_desapilar();
   	probar_lista_tope();

   	pa2m_nuevo_grupo("PRUEBAS: COLA");
   	probar_lista_encolar();
   	probar_lista_desencolar();
   	probar_lista_primero();

   	pa2m_nuevo_grupo("PRUEBAS: crear un iterador externo");
   	probar_lista_iterador_crear();

   	pa2m_nuevo_grupo("PRUEBAS: puedo iterar");
   	probar_lista_iterador_tiene_siguiente();

   	pa2m_nuevo_grupo("PRUEBAS: puedo avanzar el iterador");
   	probar_lista_iterador_avanzar();

   	pa2m_nuevo_grupo("PRUEBAS: ver elemento actual");
   	probar_lista_iterador_elemento_actual();

   	pa2m_nuevo_grupo("PRUEBAS: iterador interno");
   	probar_lista_con_cada_elemento();

    pa2m_nuevo_grupo("PRUEBAS: pruebas de sobrecarga");
   	probar_sobrecargas();

    pa2m_mostrar_reporte();   	
}