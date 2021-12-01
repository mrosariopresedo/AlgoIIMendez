#include <stdio.h>
#include <string.h>
#include "abb.h"
#include "pa2mm.h"

#define EXITO 0
#define ERROR -1
#define MAX_LETRAS 10
#define MAX_FLORES 10
#define MAX_NARANJAS 10
#define MAX_AGUACATES 10
#define MAX_COCHINILLAS 5000

typedef struct flor{
	char tipo[MAX_LETRAS]; 
	char color[MAX_LETRAS]; 
}flor_t;

typedef struct naranja{
	bool arrancada;
	char tipo[MAX_LETRAS];
	char vitamina[MAX_LETRAS];
}naranja_t;

typedef struct aguacate{
	bool pasado;
	char tipo[MAX_LETRAS];
	char vitamina[MAX_LETRAS];
}aguacate_t;

flor_t* crear_flor(char* tipo, char* color){

	flor_t* flor = malloc(sizeof(flor_t));
	if(!flor) return NULL;

	strcpy(flor->tipo, tipo);
	strcpy(flor->color, color);

	return flor;
}

/*COMPARADORES: METODOS DE INSPECCION*/

int comparar_flores_segun_tipo(void* primera, void* segunda){

	flor_t* flor_1 = (flor_t*)primera;
	flor_t* flor_2 = (flor_t*)segunda;

	return strcmp(flor_1->tipo, flor_2->tipo);
}

int comparar_naranjas_segun_vitamina(void* primera, void* segunda){

	naranja_t* naranja_1 = (naranja_t*)primera;
	naranja_t* naranja_2 = (naranja_t*)segunda;

	return strcmp(naranja_1->vitamina, naranja_2->vitamina);
}

int comparar_aguacate_segun_vitamina(void* primera, void* segunda){

	aguacate_t* aguacate_1 = (aguacate_t*)primera;
	aguacate_t* aguacate_2 = (aguacate_t*)segunda;

	return strcmp(aguacate_1->vitamina, aguacate_2->vitamina);
}

int comparar_cochinillas_segun_id(void* primera, void* segunda){

	int id_cochinilla_1 = *(int*)primera;
	int id_cochinilla_2 = *(int*)segunda;

	if(id_cochinilla_1 > id_cochinilla_2) return 1;
	if(id_cochinilla_1 < id_cochinilla_2) return -1;

	return 0;
}

/*DESTRUCTORES: METODOS DE RECOLECCION*/

void liberar_flor(void* elemento){

	if(!elemento) return;

	free(elemento);
}

void arrancar_naranja(void* elemento){

	if(!elemento) return;

	((naranja_t*)elemento)->arrancada = true;
}

void envenenar_cochinilla(void* elemento){

	if(!elemento) return;

	*(int*)elemento = -1;
}

/*BUSQUEDA NODOS*/

nodo_abb_t* nodo_especifico(nodo_abb_t* actual, void* elemento, abb_comparador comparador){

	if(!actual) return NULL;

   	if(comparador(elemento, actual->elemento) > 0) return nodo_especifico(actual->derecha, elemento, comparador);
    else if(comparador(elemento, actual->elemento) < 0) return nodo_especifico(actual->izquierda, elemento, comparador);
	
	return actual;
}

/*PARA EL ITERADOR INTERNO*/

bool aguacate_pasado(void* elemento, void* extra){

	aguacate_t* aguacate = (aguacate_t*)elemento;

	if(aguacate->pasado){

		*(aguacate_t*)extra = *(aguacate_t*)elemento;
		return true;
	}

	return false;
}

/*FUNCIONES PARA MOSTRAR*/

void mostrar_naranjas_inorden(nodo_abb_t* actual){

	if(actual){

		mostrar_naranjas_inorden(actual->izquierda);
		printf("%s ", ((naranja_t*)actual->elemento)->vitamina);
		mostrar_naranjas_inorden(actual->derecha);
	}
}

void mostrar_naranjas_preorden(nodo_abb_t* actual){

	if(actual){

		printf("%s ", ((naranja_t*)actual->elemento)->vitamina);
		mostrar_naranjas_preorden(actual->izquierda);
		mostrar_naranjas_preorden(actual->derecha);
	}
}

void mostrar_naranjas_postorden(nodo_abb_t* actual){

	if(actual){

		mostrar_naranjas_postorden(actual->izquierda);
		mostrar_naranjas_postorden(actual->derecha);
		printf("%s ", ((naranja_t*)actual->elemento)->vitamina);
	}
}

void mostrar_flores_inorden(nodo_abb_t* actual){

	if(actual){

		mostrar_flores_inorden(actual->izquierda);
		printf("%s ", ((flor_t*)actual->elemento)->tipo);
		mostrar_flores_inorden(actual->derecha);
	}
}

void mostrar_flores_preorden(nodo_abb_t* actual){

	if(actual){

		printf("%s ", ((flor_t*)actual->elemento)->tipo);
		mostrar_flores_preorden(actual->izquierda);
		mostrar_flores_preorden(actual->derecha);
	}
}

void mostrar_flores_postorden(nodo_abb_t* actual){

	if(actual){

		mostrar_flores_postorden(actual->izquierda);
		mostrar_flores_postorden(actual->derecha);
		printf("%s ", ((flor_t*)actual->elemento)->tipo);
	}
}

void mostrar_aguacates_inorden(nodo_abb_t* actual){

	if(actual){

		mostrar_aguacates_inorden(actual->izquierda);
		printf("%s ", ((aguacate_t*)actual->elemento)->vitamina);
		mostrar_aguacates_inorden(actual->derecha);
	}
}

void mostrar_aguacates_preorden(nodo_abb_t* actual){

	if(actual){

		printf("%s ", ((aguacate_t*)actual->elemento)->vitamina);
		mostrar_aguacates_preorden(actual->izquierda);
		mostrar_aguacates_preorden(actual->derecha);
	}
}

void mostrar_aguacates_postorden(nodo_abb_t* actual){

	if(actual){

		mostrar_aguacates_postorden(actual->izquierda);
		mostrar_aguacates_postorden(actual->derecha);
		printf("%s ", ((aguacate_t*)actual->elemento)->vitamina);
	}
}

//------------------------------------------------------------------------------------------------------------------------------------

void crear_arbol(){

	pa2m_nuevo_grupo("PRUEBAS: plantar un arbol");

	abb_t* arbol = arbol_crear(comparar_flores_segun_tipo, liberar_flor);

	pa2m_afirmar(arbol, "Planto un arbol");
	pa2m_afirmar(arbol && arbol->nodo_raiz == NULL, "La raiz no tiene vida");
	pa2m_afirmar(arbol && arbol->comparador == comparar_flores_segun_tipo, "El metodo de inspeccion es el correcto");
	pa2m_afirmar(arbol && arbol->destructor == liberar_flor, "El metodo de recoleccion es el correcto");
	arbol_destruir(arbol);
	arbol = arbol_crear(NULL, liberar_flor);
	pa2m_afirmar(arbol == NULL, "No puedo plantar un arbol sin metodo de inspeccion");
	arbol = arbol_crear(comparar_flores_segun_tipo, NULL);
	pa2m_afirmar(arbol, "Puedo plantar un arbol sin metodo de recoleccion");

	arbol_destruir(arbol);
}

void arbol_nulo(){

	pa2m_nuevo_grupo("PRUEBAS: arbol sin vida");

	void* extra = 0;
	naranja_t naranja = {false, "ombligo", "b5"}, canasta[MAX_NARANJAS];

	pa2m_afirmar(arbol_raiz(NULL) == NULL, "La raiz no tiene vida");
	pa2m_afirmar(arbol_vacio(NULL), "El arbol no tiene frutos");
	pa2m_afirmar(arbol_insertar(NULL, &naranja) == ERROR, "No pueden crecer frutos");
	pa2m_afirmar(arbol_borrar(NULL, &naranja) == ERROR, "No puedo recolectar frutos");
	pa2m_afirmar(arbol_buscar(NULL, &naranja) == NULL, "No puedo buscar frutos");
	pa2m_afirmar(arbol_recorrido_inorden(NULL, (void**)canasta, 0) == 0, "No puedo trepar en secuencia inorden");
	pa2m_afirmar(arbol_recorrido_preorden(NULL, (void**)canasta, 0) == 0, "No puedo trepar en secuencia preorden");
	pa2m_afirmar(arbol_recorrido_postorden(NULL, (void**)canasta, 0) == 0, "No puedo trepar en secuencia postorden");
	pa2m_afirmar(abb_con_cada_elemento(NULL, ABB_RECORRER_INORDEN, aguacate_pasado, extra) == 0, "No podemos recibir visitas del Control Iterador Interno Alimentario");
}

void arbol_sin_elementos(){

	pa2m_nuevo_grupo("PRUEBAS: arbol sin frutos");

	void* extra = 0;
	naranja_t naranja = {false, "ombligo", "c"}, canasta[MAX_NARANJAS];
	abb_t* arbol = arbol_crear(comparar_naranjas_segun_vitamina, arrancar_naranja);

	pa2m_afirmar(arbol_raiz(arbol) == NULL, "La raiz no tiene vida");
	pa2m_afirmar(arbol_vacio(arbol), "El arbol no tiene frutos");
	pa2m_afirmar(arbol_insertar(arbol, &naranja) == EXITO && comparar_naranjas_segun_vitamina(arbol_raiz(arbol), &naranja) == 0,  "Pueden crecer frutos");
	arbol_borrar(arbol, &naranja); //La elimino para continuar las pruebas con un arbol vacio.
	pa2m_afirmar(arbol_borrar(arbol, &naranja) == ERROR, "No puedo recolectar frutos");
	pa2m_afirmar(arbol_buscar(arbol, &naranja) == NULL, "No puedo buscar frutos");
	pa2m_afirmar(arbol_recorrido_inorden(arbol, (void**)canasta, 0) == 0, "No puedo trepar en secuencia inorden");
	pa2m_afirmar(arbol_recorrido_preorden(arbol, (void**)canasta, 0) == 0, "No puedo trepar en secuencia preorden");
	pa2m_afirmar(arbol_recorrido_postorden(arbol, (void**)canasta, 0) == 0, "No puedo trepar en secuencia postorden");
	pa2m_afirmar(abb_con_cada_elemento(arbol, ABB_RECORRER_INORDEN, aguacate_pasado, extra) == 0, "No podemos recibir visitas del Control Iterador Interno Alimentario");

	arbol_destruir(arbol);
}

void probar_insercion(){

	pa2m_nuevo_grupo("PRUEBAS: cultivo naranjo");

	size_t insertados;
	nodo_abb_t* nodo_aux;
	bool todas_correctas = true;
	naranja_t* canasto[MAX_NARANJAS], *naranja_aux;
	abb_t* arbol = arbol_crear(comparar_naranjas_segun_vitamina, arrancar_naranja);

	naranja_t naranja_1 = {false, "ombligo", "b6"};
	naranja_t naranja_2 = {false, "jugo", "a"};
	naranja_t naranja_3 = {false, "jugo", "c"};
	naranja_t naranja_4 = {false, "ombligo", "b12"};
	naranja_t naranja_5 = {false, "jugo", "e"};
	naranja_t naranja_6 = {false, "ombligo", "b9"};
	naranja_t naranja_7 = {false, "ombligo", "d"};
	naranja_t naranja_8 = {false, "jugo", "e"};

	naranja_t* resultado_esperado[] = {&naranja_1, &naranja_2, &naranja_4, &naranja_3, &naranja_6, &naranja_5, &naranja_7, &naranja_8};

	pa2m_afirmar(arbol && !arbol->nodo_raiz && arbol->comparador == comparar_naranjas_segun_vitamina && arbol->destructor == arrancar_naranja, "Planto un naranjo");

	/*PRIMERA NARANJA*/
	pa2m_afirmar(arbol_insertar(arbol, &naranja_1) == EXITO, "Crece primera naranja del arbol:");
	naranja_aux = arbol_raiz(arbol);
	pa2m_afirmar(naranja_aux != NULL && comparar_naranjas_segun_vitamina(naranja_aux, &naranja_1) == 0, " -Es la naranja raiz del arbol");
	pa2m_afirmar(arbol->nodo_raiz != NULL && arbol->nodo_raiz->izquierda == NULL && arbol->nodo_raiz->derecha == NULL, " -Es una naranja hoja");

	/*SEGUNDA NARANJA*/
	pa2m_afirmar(arbol_insertar(arbol, &naranja_2) == EXITO, "Crece segunda naranja del arbol:");
	pa2m_afirmar(arbol->nodo_raiz != NULL && comparar_naranjas_segun_vitamina(arbol->nodo_raiz->elemento, &naranja_2) > 0, " -Es menor a la naranja raiz");
	pa2m_afirmar(arbol->nodo_raiz != NULL && comparar_naranjas_segun_vitamina(arbol->nodo_raiz->izquierda->elemento, &naranja_2) == 0, " -Crecio a la izquierda de la naranja raiz");
	nodo_aux = nodo_especifico(arbol->nodo_raiz, &naranja_2, comparar_naranjas_segun_vitamina);
	pa2m_afirmar(nodo_aux != NULL && nodo_aux->izquierda == NULL && nodo_aux->derecha == NULL, " -Es una naranja hoja");

	/*TERCERA NARANJA*/
	pa2m_afirmar(arbol_insertar(arbol, &naranja_3) == EXITO, "Crece tercera naranja del arbol:");
	pa2m_afirmar(arbol->nodo_raiz != NULL && comparar_naranjas_segun_vitamina(arbol->nodo_raiz->elemento, &naranja_3) < 0, " -Es mayor a la naranja raiz");
	pa2m_afirmar(arbol->nodo_raiz != NULL && comparar_naranjas_segun_vitamina(arbol->nodo_raiz->derecha->elemento, &naranja_3) == 0, " -Crecio a la derecha de la naranja raiz");
	nodo_aux = nodo_especifico(arbol->nodo_raiz, &naranja_3, comparar_naranjas_segun_vitamina);
	pa2m_afirmar(nodo_aux != NULL && nodo_aux->izquierda == NULL && nodo_aux->derecha == NULL, " -Es una naranja hoja");

	/*CUARTA NARANJA*/
	pa2m_afirmar(arbol_insertar(arbol, &naranja_4) == EXITO, "Crece cuarta naranja del arbol:");
	nodo_aux = nodo_especifico(arbol->nodo_raiz, &naranja_2, comparar_naranjas_segun_vitamina);
	pa2m_afirmar(nodo_aux != NULL && comparar_naranjas_segun_vitamina(nodo_aux->elemento, &naranja_4) < 0, " -Es mayor que la segunda naranja");
	pa2m_afirmar(nodo_aux != NULL && comparar_naranjas_segun_vitamina(nodo_aux->derecha->elemento, &naranja_4) == 0, " -Crecio a la derecha de la segunda naranja");
	nodo_aux = nodo_especifico(arbol->nodo_raiz, &naranja_4, comparar_naranjas_segun_vitamina);
	pa2m_afirmar(nodo_aux != NULL && nodo_aux->izquierda == NULL && nodo_aux->derecha == NULL, " -Es una naranja hoja");

	/*QUINTA NARANJA*/
	pa2m_afirmar(arbol_insertar(arbol, &naranja_5) == EXITO, "Crece quinta naranja del arbol");
	nodo_aux = nodo_especifico(arbol->nodo_raiz, &naranja_3, comparar_naranjas_segun_vitamina);
	pa2m_afirmar(nodo_aux != NULL && comparar_naranjas_segun_vitamina(nodo_aux->elemento, &naranja_5) < 0, " -Es mayor que la tercera naranja");
	pa2m_afirmar(nodo_aux != NULL && comparar_naranjas_segun_vitamina(nodo_aux->derecha->elemento, &naranja_5) == 0, " -Crecio a la derecha de la tercera naranja");
	nodo_aux = nodo_especifico(arbol->nodo_raiz, &naranja_5, comparar_naranjas_segun_vitamina);
	pa2m_afirmar(nodo_aux != NULL && nodo_aux->izquierda == NULL && nodo_aux->derecha == NULL, " -Es una naranja hoja");

	/*SEXTA NARANJA*/
	pa2m_afirmar(arbol_insertar(arbol, &naranja_6) == EXITO, "Crece sexta naranja del arbol");
	nodo_aux = nodo_especifico(arbol->nodo_raiz, &naranja_3, comparar_naranjas_segun_vitamina);
	pa2m_afirmar(nodo_aux != NULL && comparar_naranjas_segun_vitamina(nodo_aux->elemento, &naranja_6) > 0, " -Es menor que la tercera naranja");
	pa2m_afirmar(nodo_aux != NULL && comparar_naranjas_segun_vitamina(nodo_aux->izquierda->elemento, &naranja_6) == 0, " -Crecio a la izquierda de la tercera naranja");
	nodo_aux = nodo_especifico(arbol->nodo_raiz, &naranja_6, comparar_naranjas_segun_vitamina);
	pa2m_afirmar(nodo_aux != NULL && nodo_aux->izquierda == NULL && nodo_aux->derecha == NULL, " -Es una naranja hoja");

	/*SEPTIMA NARANJA*/
	pa2m_afirmar(arbol_insertar(arbol, &naranja_7) == EXITO, "Crece septima naranja del arbol");
	nodo_aux = nodo_especifico(arbol->nodo_raiz, &naranja_5, comparar_naranjas_segun_vitamina);
	pa2m_afirmar(nodo_aux != NULL && comparar_naranjas_segun_vitamina(nodo_aux->elemento, &naranja_7) > 0, " -Es menor que la quinta naranja");
	pa2m_afirmar(nodo_aux != NULL && comparar_naranjas_segun_vitamina(nodo_aux->izquierda->elemento, &naranja_7) == 0, " -Crecio a la izquierda de la quinta naranja");
	nodo_aux = nodo_especifico(arbol->nodo_raiz, &naranja_7, comparar_naranjas_segun_vitamina);
	pa2m_afirmar(nodo_aux != NULL && nodo_aux->izquierda == NULL && nodo_aux->derecha == NULL, " -Es una naranja hoja");

	/*OCTAVA NARANJA*/
	pa2m_afirmar(arbol_insertar(arbol, &naranja_8) == EXITO, "Crece octava naranja del arbol");
	nodo_aux = nodo_especifico(arbol->nodo_raiz, &naranja_7, comparar_naranjas_segun_vitamina);
	pa2m_afirmar(nodo_aux != NULL && comparar_naranjas_segun_vitamina(nodo_aux->elemento, &naranja_8) < 0, " -Es mayor que la septima naranja");
	pa2m_afirmar(nodo_aux != NULL && comparar_naranjas_segun_vitamina(nodo_aux->derecha->elemento, &naranja_8) == 0, " -Crecio a la derecha de la septima naranja");
	pa2m_afirmar(nodo_aux != NULL && nodo_aux->derecha->izquierda == NULL && nodo_aux->derecha->derecha == NULL, " -Es una naranja hoja");

	insertados = arbol_recorrido_preorden(arbol, (void**)canasto, 8);
	if(insertados == 8){

		for(int i = 0; i < insertados && todas_correctas; i++){

			if(comparar_naranjas_segun_vitamina(canasto[i], resultado_esperado[i]) != 0) todas_correctas = false;
		}
	}
	else todas_correctas = false;

	pa2m_afirmar(!arbol_vacio(arbol), "El arbol tiene frutos");
	pa2m_afirmar(insertados == 8, "El arbol tiene ocho naranjas");
	pa2m_afirmar(todas_correctas, "Las naranjas se encuentran en el orden correcto");

	arbol_destruir(arbol);
}

void probar_busqueda(){

	pa2m_nuevo_grupo("PRUEBAS: busqueda en naranjo");

	abb_t* arbol = arbol_crear(comparar_naranjas_segun_vitamina, arrancar_naranja);

	int i;
	bool fallo = false;
	naranja_t* naranja_aux;

	naranja_t naranja_1 = {false, "ombligo", "b6"};
	naranja_t naranja_2 = {false, "jugo", "a"};
	naranja_t naranja_3 = {false, "jugo", "c"};
	naranja_t naranja_4 = {false, "ombligo", "b12"};
	naranja_t naranja_5 = {false, "jugo", "e"};
	naranja_t naranja_6 = {false, "ombligo", "b9"};
	naranja_t naranja_7 = {false, "ombligo", "d"};
	naranja_t naranja_8 = {false, "jugo", "e"};

	naranja_t* naranjas[] = {&naranja_1, &naranja_2, &naranja_3, &naranja_4, &naranja_5, &naranja_6, &naranja_7, &naranja_8};

	pa2m_afirmar(arbol && !arbol->nodo_raiz && arbol->comparador == comparar_naranjas_segun_vitamina && arbol->destructor == arrancar_naranja, "Tengo un naranjo");

	for(i = 0; i < 8 && !fallo; i++){

		if(arbol_insertar(arbol, naranjas[i]) == ERROR) fallo = true;
	}
	pa2m_afirmar(!arbol_vacio(arbol), "El arbol tiene frutos");
	pa2m_afirmar(!fallo && i == 8, "El arbol tiene ocho naranjas");

	naranja_aux = arbol_buscar(arbol, &naranja_1);
	pa2m_afirmar(naranja_aux != NULL, "Busco primera naranja que crecio en arbol");
	pa2m_afirmar(comparar_naranjas_segun_vitamina(naranja_aux, &naranja_1) == 0, " -Inspecciono la misma: es la primera naranja");

	naranja_aux = arbol_buscar(arbol, &naranja_2);
	pa2m_afirmar(naranja_aux != NULL, "Busco segunda naranja que crecio en arbol");
	pa2m_afirmar(comparar_naranjas_segun_vitamina(naranja_aux, &naranja_2) == 0, " -Inspecciono la misma: es la segunda naranja");

	naranja_aux = arbol_buscar(arbol, &naranja_3);
	pa2m_afirmar(naranja_aux != NULL, "Busco tercera naranja que crecio en arbol");
	pa2m_afirmar(comparar_naranjas_segun_vitamina(naranja_aux, &naranja_3) == 0, " -Inspecciono la misma: es la tercera naranja");

	naranja_aux = arbol_buscar(arbol, &naranja_4);
	pa2m_afirmar(naranja_aux != NULL, "Busco cuarta naranja que crecio en arbol");
	pa2m_afirmar(comparar_naranjas_segun_vitamina(naranja_aux, &naranja_4) == 0, " -Inspecciono la misma: es la cuarta naranja");

	naranja_aux = arbol_buscar(arbol, &naranja_5);
	pa2m_afirmar(naranja_aux != NULL, "Busco quinta naranja que crecio en arbol");
	pa2m_afirmar(comparar_naranjas_segun_vitamina(naranja_aux, &naranja_5) == 0, " -Inspecciono la misma: es la quinta naranja");

	naranja_aux = arbol_buscar(arbol, &naranja_6);
	pa2m_afirmar(naranja_aux != NULL, "Busco sexta naranja que crecio en arbol");
	pa2m_afirmar(comparar_naranjas_segun_vitamina(naranja_aux, &naranja_6) == 0, " -Inspecciono la misma: es la sexta naranja");

	naranja_aux = arbol_buscar(arbol, &naranja_7);
	pa2m_afirmar(naranja_aux != NULL, "Busco septima naranja que crecio en arbol");
	pa2m_afirmar(comparar_naranjas_segun_vitamina(naranja_aux, &naranja_7) == 0, " -Inspecciono la misma: es la septima naranja");

	naranja_aux = arbol_buscar(arbol, &naranja_8);
	pa2m_afirmar(naranja_aux != NULL, "Busco octava naranja que crecio en arbol");
	pa2m_afirmar(comparar_naranjas_segun_vitamina(naranja_aux, &naranja_8) == 0, " -Inspecciono la misma: es la octava naranja");

	arbol_destruir(arbol);	
}

void probar_eliminacion(){

	pa2m_nuevo_grupo("PRUEBAS: cosecha naranjo");

	abb_t* arbol = arbol_crear(comparar_naranjas_segun_vitamina, arrancar_naranja);

	int i;
	bool fallo = false;
	nodo_abb_t* nodo_aux;
	naranja_t* naranja_aux;

	naranja_t naranja_1 = {false, "ombligo", "b6"};
	naranja_t naranja_2 = {false, "jugo", "a"};
	naranja_t naranja_3 = {false, "jugo", "c"};
	naranja_t naranja_4 = {false, "ombligo", "b12"};
	naranja_t naranja_5 = {false, "jugo", "e"};
	naranja_t naranja_6 = {false, "ombligo", "b9"};
	naranja_t naranja_7 = {false, "ombligo", "d"};
	naranja_t naranja_8 = {false, "jugo", "e"};

	naranja_t* naranjas[] = {&naranja_1, &naranja_2, &naranja_3, &naranja_4, &naranja_5, &naranja_6, &naranja_7, &naranja_8};

	pa2m_afirmar(arbol && !arbol->nodo_raiz && arbol->comparador == comparar_naranjas_segun_vitamina && arbol->destructor == arrancar_naranja, "Tengo un naranjo");

	for(i = 0; i < 8 && !fallo; i++){

		if(arbol_insertar(arbol, naranjas[i]) == ERROR) fallo = true;
	}
	pa2m_afirmar(!arbol_vacio(arbol), "El arbol tiene frutos");
	pa2m_afirmar(!fallo && i == 8, "El arbol tiene ocho naranjas");

	pa2m_nuevo_grupo("1. Recolecta");

	/*Aca tambien me fijo que arbol_borrar() este funcionando bien con respecto al destructor*/
	pa2m_afirmar(arbol_borrar(arbol, &naranja_3) == EXITO && naranja_3.arrancada, "Recolecto naranja con dos hijos");
	pa2m_afirmar(comparar_naranjas_segun_vitamina(arbol->nodo_raiz->derecha->elemento, &naranja_6) == 0, " -Su naranja hija izquierda hereda su lugar");
	pa2m_afirmar(comparar_naranjas_segun_vitamina(arbol->nodo_raiz->derecha->derecha->elemento, &naranja_5) == 0, " -Su naranja hija derecha fue adoptada por la heredera");
	pa2m_afirmar(arbol_buscar(arbol, &naranja_3) == NULL, " -No vuelvo a encontrar una naranja con dichas propiedades");
	pa2m_afirmar(arbol_borrar(arbol, &naranja_3) == ERROR, " -No puedo recolectar nuevamente naranja con dichas propiedades");

	pa2m_afirmar(arbol_borrar(arbol, &naranja_6) == EXITO && naranja_6.arrancada, "Recolecto naranja con un hijo");
	pa2m_afirmar(comparar_naranjas_segun_vitamina(arbol->nodo_raiz->derecha->elemento, &naranja_5) == 0, " -Su naranja hija hereda su lugar");
	pa2m_afirmar(arbol_buscar(arbol, &naranja_6) == NULL, " -No vuelvo a encontrar una naranja con dichas propiedades");
	pa2m_afirmar(arbol_borrar(arbol, &naranja_6) == ERROR, " -No puedo recolectar nuevamente naranja con dichas propiedades");

	pa2m_afirmar(arbol_borrar(arbol, &naranja_4) == EXITO && naranja_4.arrancada, "Recolecto naranja sin hijos");
	pa2m_afirmar(arbol->nodo_raiz->izquierda->derecha == NULL, " -Su naranja padre ya no la tiene de hija");
	pa2m_afirmar(arbol_buscar(arbol, &naranja_4) == NULL, " -No vuelvo a encontrar una naranja con dichas propiedades");
	pa2m_afirmar(arbol_borrar(arbol, &naranja_4) == ERROR, " -No puedo recolectar nuevamente naranja con dichas propiedades");

	pa2m_afirmar(arbol_borrar(arbol, &naranja_1) == EXITO && naranja_1.arrancada, "Recolecto naranja raiz");
	pa2m_afirmar(comparar_naranjas_segun_vitamina(arbol->nodo_raiz->elemento, &naranja_2) == 0, " -Su naranja hija izquierda hereda su lugar");
	pa2m_afirmar(comparar_naranjas_segun_vitamina(arbol->nodo_raiz->derecha->elemento, &naranja_5) == 0, " -Su naranja hija derecha fue adoptada por la heredera");
	pa2m_afirmar(arbol_buscar(arbol, &naranja_1) == NULL, " -No vuelvo a encontrar una naranja con dichas propiedades");
	pa2m_afirmar(arbol_borrar(arbol, &naranja_1) == ERROR, " -No puedo recolectar nuevamente naranja con dichas propiedades");

	pa2m_afirmar(arbol_borrar(arbol, &naranja_8) == EXITO && naranja_5.arrancada, "Recolecto naranja duplicada con un hijo")
	pa2m_afirmar(comparar_naranjas_segun_vitamina(arbol->nodo_raiz->derecha->elemento, &naranja_7) == 0, " -Su naranja hija hereda su lugar");
	naranja_aux = arbol_buscar(arbol, &naranja_8);
	pa2m_afirmar(naranja_aux != NULL && comparar_naranjas_segun_vitamina(naranja_aux, &naranja_8) == 0, " -Vuelvo a encontrar una naranja con dichas propiedades");
	nodo_aux = nodo_especifico(arbol->nodo_raiz, &naranja_8, comparar_naranjas_segun_vitamina);
	pa2m_afirmar(nodo_aux != NULL && nodo_aux->izquierda == NULL && nodo_aux->derecha == NULL, " -Es una naranja hoja");
	pa2m_afirmar(arbol_borrar(arbol, &naranja_8) == EXITO && naranja_8.arrancada, " -Recolecto nuevamente naranja con dichas propiedades");
	pa2m_afirmar(arbol->nodo_raiz->derecha->derecha == NULL, " -Su naranja padre ya no la tiene de hija");
	pa2m_afirmar(arbol_buscar(arbol, &naranja_8) == NULL, " -No vuelvo a encontrar una naranja con dichas propiedades");
	pa2m_afirmar(arbol_borrar(arbol, &naranja_8) == ERROR, " -No puedo recolectar nuevamente naranja con dichas propiedades");

	pa2m_nuevo_grupo("2. Observacion restantes");

	naranja_aux = arbol_raiz(arbol);
	pa2m_afirmar(naranja_aux != NULL, "Busco naranja raiz");
	pa2m_afirmar(comparar_naranjas_segun_vitamina(naranja_aux, &naranja_2) == 0, " -Inspecciono la misma: es la naranja raiz");

	naranja_aux = arbol_buscar(arbol, &naranja_7);
	pa2m_afirmar(naranja_aux != NULL, "Busco naranja en rama");
	pa2m_afirmar(comparar_naranjas_segun_vitamina(naranja_aux, &naranja_7) == 0, " -Inspecciono la misma: es la naranja buscada");

	pa2m_afirmar(comparar_naranjas_segun_vitamina(arbol->nodo_raiz->elemento, &naranja_2) == 0 && comparar_naranjas_segun_vitamina(arbol->nodo_raiz->derecha->elemento, &naranja_7) == 0, " -Esta en el lugar correcto");

	pa2m_afirmar(!arbol_vacio(arbol), "El arbol tiene frutos");

	pa2m_nuevo_grupo("3. Recolecta restantes");

	pa2m_afirmar(arbol_borrar(arbol, &naranja_2) == EXITO && naranja_2.arrancada, "Recolecto naranja raiz");
	pa2m_afirmar(arbol_buscar(arbol, &naranja_2) == NULL, " -No vuelvo a encontrar una naranja con dichas propiedades");
	pa2m_afirmar(arbol_borrar(arbol, &naranja_2) == ERROR, " -No puedo recolectar nuevamente naranja con dichas propiedades");

	pa2m_afirmar(comparar_naranjas_segun_vitamina(arbol->nodo_raiz->elemento, &naranja_7) == 0, "La nueva naranja raiz es correcta");
	pa2m_afirmar(!arbol_vacio(arbol) && arbol->nodo_raiz->izquierda == NULL && arbol->nodo_raiz->izquierda == NULL, "La naranja raiz es la unica naranja del arbol");

	pa2m_afirmar(arbol_borrar(arbol, &naranja_7) == EXITO && naranja_7.arrancada, "Recolecto naranja raiz");
	pa2m_afirmar(arbol_buscar(arbol, &naranja_7) == NULL, " -No vuelvo a encontrar una naranja con dichas propiedades");
	pa2m_afirmar(arbol_borrar(arbol, &naranja_7) == ERROR, " -No puedo recolectar nuevamente naranja con dichas propiedades");
	pa2m_afirmar(arbol_vacio(arbol), "El arbol no tiene frutos");

	arbol_destruir(arbol);
}

void vaciar_arbol_de_raiz(){

	pa2m_nuevo_grupo("PRUEBAS: arrancar de raiz");

	abb_t* arbol = arbol_crear(comparar_flores_segun_tipo, liberar_flor);

	int i;
	flor_t* ramo[MAX_FLORES];
	bool fallo = false, todas_correctas = true;

	flor_t* flor_1 = crear_flor("Narciso", "blanco");
	flor_t* flor_2 = crear_flor("Tulipan", "violeta");
	flor_t* flor_3 = crear_flor("Dalia", "amarillo");
	flor_t* flor_4 = crear_flor("Lirio", "rojo");
	flor_t* flor_5 = crear_flor("Petunia", "rosa");
	flor_t* flor_6 = crear_flor("Clavel", "rosa");
	flor_t* flor_7 = crear_flor("Girasol", "amarillo");

	flor_t* flores[] = {flor_1, flor_2, flor_3, flor_4, flor_5, flor_6, flor_7};
	flor_t* resultado_esperado_1[] = {flor_4, flor_3, flor_6, flor_7, flor_2, flor_5};
	flor_t* resultado_esperado_2[] = {flor_7, flor_3, flor_6, flor_2, flor_5};
	flor_t* resultado_esperado_3[] = {flor_3, flor_6, flor_2, flor_5};
	flor_t* resultado_esperado_4[] = {flor_6, flor_2, flor_5};
	flor_t* resultado_esperado_5[] = {flor_2, flor_5};

	pa2m_afirmar(arbol && !arbol->nodo_raiz && arbol->comparador == comparar_flores_segun_tipo && arbol->destructor == liberar_flor, "Tengo un arbol floral");

	for(i = 0; i < 7 && !fallo; i++){

		if(arbol_insertar(arbol, flores[i]) == ERROR){

			fallo = true;
			liberar_flor(flores[i]);
		}	
	}	
	pa2m_afirmar(!arbol_vacio(arbol), "El arbol tiene frutos");
	pa2m_afirmar(!fallo && i == 7, "El arbol tiene siete flores");

	pa2m_afirmar(arbol_borrar(arbol, arbol_raiz(arbol)) == EXITO, "Recolecto raiz");
	pa2m_afirmar(arbol->nodo_raiz != NULL && comparar_flores_segun_tipo(arbol->nodo_raiz->elemento, flor_4) == 0, " -La nueva raiz es correcta");

	if(arbol_recorrido_preorden(arbol, (void**)ramo, 6) == 6){

		for(int i = 0; i < 6 && todas_correctas; i++){

			if(strcmp(ramo[i]->tipo, resultado_esperado_1[i]->tipo) != 0) todas_correctas = false;
		}
	}
	pa2m_afirmar(todas_correctas, " -Las flores estan en el orden correcto");

	pa2m_afirmar(arbol_borrar(arbol, arbol_raiz(arbol)) == EXITO, "Recolecto raiz");
	pa2m_afirmar(arbol->nodo_raiz != NULL && comparar_flores_segun_tipo(arbol->nodo_raiz->elemento, flor_7) == 0, " -La nueva raiz es correcta");

	if(arbol_recorrido_preorden(arbol, (void**)ramo, 5) == 5){

		for(int i = 0; i < 5 && todas_correctas; i++){

			if(strcmp(ramo[i]->tipo, resultado_esperado_2[i]->tipo) != 0) todas_correctas = false;
		}
	}
	pa2m_afirmar(todas_correctas, " -Las flores estan en el orden correcto");

	pa2m_afirmar(arbol_borrar(arbol, arbol_raiz(arbol)) == EXITO, "Recolecto raiz");
	pa2m_afirmar(arbol->nodo_raiz != NULL && comparar_flores_segun_tipo(arbol->nodo_raiz->elemento, flor_3) == 0, " -La nueva raiz es correcta");

	if(arbol_recorrido_preorden(arbol, (void**)ramo, 4) == 4){

		for(int i = 0; i < 4 && todas_correctas; i++){

			if(strcmp(ramo[i]->tipo, resultado_esperado_3[i]->tipo) != 0) todas_correctas = false;
		}
	}
	pa2m_afirmar(todas_correctas, " -Las flores estan en el orden correcto");

	pa2m_afirmar(arbol_borrar(arbol, arbol_raiz(arbol)) == EXITO, "Recolecto raiz");
	pa2m_afirmar(arbol->nodo_raiz != NULL && comparar_flores_segun_tipo(arbol->nodo_raiz->elemento, flor_6) == 0, " -La nueva raiz es correcta");

	if(arbol_recorrido_preorden(arbol, (void**)ramo, 3) == 3){

		for(int i = 0; i < 3 && todas_correctas; i++){

			if(strcmp(ramo[i]->tipo, resultado_esperado_4[i]->tipo) != 0) todas_correctas = false;
		}
	}
	pa2m_afirmar(todas_correctas, " -Las flores estan en el orden correcto");

	pa2m_afirmar(arbol_borrar(arbol, arbol_raiz(arbol)) == EXITO, "Recolecto raiz");
	pa2m_afirmar(arbol->nodo_raiz != NULL && comparar_flores_segun_tipo(arbol->nodo_raiz->elemento, flor_2) == 0, " -La nueva raiz es correcta");

	if(arbol_recorrido_preorden(arbol, (void**)ramo, 2) == 2){

		for(int i = 0; i < 2 && todas_correctas; i++){

			if(strcmp(ramo[i]->tipo, resultado_esperado_5[i]->tipo) != 0) todas_correctas = false;
		}
	}
	pa2m_afirmar(todas_correctas, " -Las flores estan en el orden correcto");

	pa2m_afirmar(arbol_borrar(arbol, arbol_raiz(arbol)) == EXITO, "Recolecto raiz");
	pa2m_afirmar(arbol->nodo_raiz != NULL && comparar_flores_segun_tipo(arbol->nodo_raiz->elemento, flor_5) == 0, " -La nueva raiz es correcta");
	pa2m_afirmar(arbol->nodo_raiz != NULL && arbol->nodo_raiz->izquierda == NULL && arbol->nodo_raiz->derecha == NULL, " -Es la unica flor en el arbol")

	pa2m_afirmar(arbol_borrar(arbol, arbol_raiz(arbol)) == EXITO, "Recolecto raiz");
	pa2m_afirmar(arbol_vacio(arbol), "El arbol no tiene frutos");

	arbol_destruir(arbol);
}

void probar_recorridos(){

	pa2m_nuevo_grupo("PRUEBAS: trepar arbol floral");

	abb_t* arbol = arbol_crear(comparar_flores_segun_tipo, liberar_flor);

	int i;
	size_t insertados;
	flor_t* ramo[MAX_FLORES];
	bool todas_correctas = true, fallo = false;

	flor_t* flor_1 = crear_flor("Margarita", "blanco");
	flor_t* flor_2 = crear_flor("Zarzamora", "violeta");
	flor_t* flor_3 = crear_flor("Orquidea", "blanco");
	flor_t* flor_4 = crear_flor("Hortensia", "violeta");
	flor_t* flor_5 = crear_flor("Begonia", "rojo");
	flor_t* flor_6 = crear_flor("Jazmin", "blanco");
	flor_t* flor_7 = crear_flor("Azucena", "blanco");

	flor_t* flores[] = {flor_1, flor_2, flor_3, flor_4, flor_5, flor_6, flor_7};
	flor_t* esperado_inorden_1[] = {flor_7, flor_5, flor_4, flor_6, flor_1, flor_3, flor_2};
	flor_t* esperado_inorden_2[] = {flor_7, flor_5, flor_4};
	flor_t* esperado_preorden_1[] = {flor_1, flor_4, flor_5, flor_7, flor_6, flor_2, flor_3};
	flor_t* esperado_preorden_2[] = {flor_1, flor_4, flor_5};
	flor_t* esperado_postorden_1[] = {flor_7, flor_5, flor_6, flor_4, flor_3, flor_2, flor_1};
	flor_t* esperado_postorden_2[] = {flor_7, flor_5, flor_6};

	pa2m_afirmar(arbol && !arbol->nodo_raiz && arbol->comparador == comparar_flores_segun_tipo && arbol->destructor == liberar_flor, "Tengo un arbol floral");

	for(i = 0; i < 7 && !fallo; i++){

		if(arbol_insertar(arbol, flores[i]) == ERROR){

			fallo = true;
			liberar_flor(flores[i]);
		}
	}
	pa2m_afirmar(!arbol_vacio(arbol), "El arbol tiene frutos");
	pa2m_afirmar(!fallo && i == 7, "El arbol tiene siete flores");

	/*RECORRIDO INORDEN*/
	pa2m_nuevo_grupo("1. Trepar en secuencia inorden");
	insertados = arbol_recorrido_inorden(arbol, (void**)ramo, 7);
	pa2m_afirmar(insertados == 7, "Trepo el arbol en secuencia inorden, pido siete flores");

	if(insertados == 7){

		for(i = 0; i < insertados && todas_correctas; i++){

			if(comparar_flores_segun_tipo(ramo[i], esperado_inorden_1[i]) != 0) todas_correctas = false;
		}
	}
	else todas_correctas = false;

	pa2m_afirmar(i == 7, " -El ramo tiene siete flores");
	pa2m_afirmar(todas_correctas, " -Las flores del ramo estan en el orden correcto");

	insertados = arbol_recorrido_inorden(arbol, (void**)ramo, 3);
	pa2m_afirmar(insertados == 3, "Trepo el arbol en secuencia inorden, pido tres flores");

	if(insertados == 3){

		todas_correctas = true;
		for(i = 0; i < insertados && todas_correctas; i++){

			if(comparar_flores_segun_tipo(ramo[i], esperado_inorden_2[i]) != 0) todas_correctas = false;
		}
	}
	else todas_correctas = false;

	pa2m_afirmar(i == 3, " -El ramo tiene tres flores");
	pa2m_afirmar(todas_correctas, " -Las flores del ramo estan en el orden correcto");

	insertados = arbol_recorrido_inorden(arbol, (void**)ramo, 10);
	pa2m_afirmar(insertados == 7, "Trepo el arbol en secuencia inorden, pido diez flores");

	if(insertados == 7){

		todas_correctas = true;
		for(i = 0; i < insertados && todas_correctas; i++){

			if(comparar_flores_segun_tipo(ramo[i], esperado_inorden_1[i]) != 0) todas_correctas = false;
		}
	}
	else todas_correctas = false;

	pa2m_afirmar(i == 7, " -El ramo tiene siete flores");
	pa2m_afirmar(todas_correctas, " -Las flores del ramo estan en el orden correcto");

	/*RECORRIDO PREORDEN*/
	pa2m_nuevo_grupo("2. Trepar en secuencia preorden");
	insertados = arbol_recorrido_preorden(arbol, (void**)ramo, 7);
	pa2m_afirmar(insertados == 7, "Trepo el arbol en secuencia preorden, pido siete flores");

	if(insertados == 7){

		todas_correctas = true; 
		for(i = 0; i < insertados && todas_correctas; i++){

			if(comparar_flores_segun_tipo(ramo[i], esperado_preorden_1[i]) != 0) todas_correctas = false;
		}
	}
	else todas_correctas = false;

	pa2m_afirmar(i == 7, " -El ramo tiene siete flores");
	pa2m_afirmar(todas_correctas, " -Las flores del ramo estan en el orden correcto");

	insertados = arbol_recorrido_preorden(arbol, (void**)ramo, 3);
	pa2m_afirmar(insertados == 3, "Trepo el arbol en secuencia preorden, pido tres flores");

	if(insertados == 3){

		todas_correctas = true; 
		for(i = 0; i < insertados && todas_correctas; i++){

			if(comparar_flores_segun_tipo(ramo[i], esperado_preorden_2[i]) != 0) todas_correctas = false;
		}
	}
	else todas_correctas = false;

	pa2m_afirmar(i == 3, " -El ramo tiene tres flores");
	pa2m_afirmar(todas_correctas, " -Las flores del ramo estan en el orden correcto");

	insertados = arbol_recorrido_preorden(arbol, (void**)ramo, 10);
	pa2m_afirmar(insertados == 7, "Trepo el arbol en secuencia preorden, pido diez flores");

	if(insertados == 7){

		todas_correctas = true; 
		for(i = 0; i < insertados && todas_correctas; i++){

			if(comparar_flores_segun_tipo(ramo[i], esperado_preorden_1[i]) != 0) todas_correctas = false;
		}
	}
	else todas_correctas = false;

	pa2m_afirmar(i == 7, " -El ramo tiene siete flores");
	pa2m_afirmar(todas_correctas, " -Las flores del ramo estan en el orden correcto");

	/*RECORRIDO POSTORDEN*/
	pa2m_nuevo_grupo("3. Trepar en secuencia postorden");
	insertados = arbol_recorrido_postorden(arbol, (void**)ramo, 7);
	pa2m_afirmar(insertados == 7, "Trepo el arbol en secuencia postorden");

	if(insertados == 7){

		todas_correctas = true; 
		for(i = 0; i < insertados && todas_correctas; i++){

			if(comparar_flores_segun_tipo(ramo[i], esperado_postorden_1[i]) != 0) todas_correctas = false;
		}
	}
	else todas_correctas = false;

	pa2m_afirmar(i == 7, " -El ramo tiene siete flores");
	pa2m_afirmar(todas_correctas, " -Las flores del ramo estan en el orden correcto");

	insertados = arbol_recorrido_postorden(arbol, (void**)ramo, 3);
	pa2m_afirmar(insertados == 3, "Trepo el arbol en secuencia postorden, pido tres flores");

	if(insertados == 3){

		todas_correctas = true; 
		for(i = 0; i < insertados && todas_correctas; i++){

			if(comparar_flores_segun_tipo(ramo[i], esperado_postorden_2[i]) != 0) todas_correctas = false;
		}
	}
	else todas_correctas = false;

	pa2m_afirmar(i == 3, " -El ramo tiene tres flores");
	pa2m_afirmar(todas_correctas, " -Las flores del ramo estan en el orden correcto");

	insertados = arbol_recorrido_postorden(arbol, (void**)ramo, 10);
	pa2m_afirmar(insertados == 7, "Trepo el arbol en secuencia postorden, pido diez flores");

	if(insertados == 7){

		todas_correctas = true; 
		for(i = 0; i < insertados && todas_correctas; i++){

			if(comparar_flores_segun_tipo(ramo[i], esperado_postorden_1[i]) != 0) todas_correctas = false;
		}
	}
	else todas_correctas = false;

	pa2m_afirmar(i == 7, " -El ramo tiene siete flores");
	pa2m_afirmar(todas_correctas, " -Las flores del ramo estan en el orden correcto");


	arbol_destruir(arbol);
}

void probar_iterador_interno(){

	pa2m_nuevo_grupo("PRUEBAS: Control Iterador Interno Alimentario (CIIA)");

	abb_t* arbol = arbol_crear(comparar_aguacate_segun_vitamina, NULL);

	int i;
	size_t visitados;
	aguacate_t pasado;
	aguacate_t* canasto[MAX_AGUACATES];
	bool fallo = false, todas_correctas = true;

	aguacate_t aguacate_1 = {false, "Fuerte", "c"};
	aguacate_t aguacate_2 = {false, "Criolla", "k"};
	aguacate_t aguacate_3 = {true, "Hass", "e"};
	aguacate_t aguacate_4 = {true, "Bacon", "b1"};
	aguacate_t aguacate_5 = {false, "Pinkerton", "b6"};
	aguacate_t aguacate_6 = {true, "Reed", "b3"};

	aguacate_t* aguacates[] = {&aguacate_1, &aguacate_2, &aguacate_3, &aguacate_4, &aguacate_5, &aguacate_6};
	aguacate_t* resultado_esperado[] = {&aguacate_1, &aguacate_5, &aguacate_2};

	pa2m_afirmar(arbol && !arbol->nodo_raiz && arbol->comparador == comparar_aguacate_segun_vitamina && !arbol->destructor, "Tengo un aguacatero");

	for(i = 0; i < 6 && !fallo; i++){

		if(arbol_insertar(arbol, aguacates[i]) == ERROR) fallo = true;
	}
	pa2m_afirmar(!arbol_vacio(arbol) && !fallo && i == 6, "El arbol tiene siete aguacates");

	visitados = abb_con_cada_elemento(arbol, ABB_RECORRER_INORDEN, aguacate_pasado, &pasado);
	pa2m_afirmar(visitados == 1, "Trepan el arbol en secuencia inorden");
	pa2m_afirmar(visitados == 1 && comparar_aguacate_segun_vitamina(&pasado, &aguacate_4) == 0, "Encuentran un aguacate pasado");
	pa2m_afirmar(arbol_borrar(arbol, &aguacate_4) == EXITO && arbol_buscar(arbol, &aguacate_4) == NULL, "Arrancan aguacate pasado");

	visitados = abb_con_cada_elemento(arbol, ABB_RECORRER_PREORDEN, aguacate_pasado, &pasado);
	pa2m_afirmar(visitados == 3, "Trepan el arbol en secuencia preorden");
	pa2m_afirmar(visitados == 3 && comparar_aguacate_segun_vitamina(&pasado, &aguacate_6) == 0, "Encuentran otro aguacate pasado");
	pa2m_afirmar(arbol_borrar(arbol, &aguacate_6) == EXITO && arbol_buscar(arbol, &aguacate_6) == NULL, "Arrancan aguacate pasado");

	visitados = abb_con_cada_elemento(arbol, ABB_RECORRER_POSTORDEN, aguacate_pasado, &pasado);
	pa2m_afirmar(visitados == 2, "Trepan el arbol en secuencia postorden");
	pa2m_afirmar(visitados == 2 && comparar_aguacate_segun_vitamina(&pasado, &aguacate_3) == 0, "Encuentran ultimo aguacate pasado");
	pa2m_afirmar(arbol_borrar(arbol, &aguacate_3) == EXITO && arbol_buscar(arbol, &aguacate_3) == NULL, "Arrancan aguacate pasado");

	if(arbol_recorrido_preorden(arbol, (void**)canasto, 3) == 3){

		for(i = 0; i < 3 && todas_correctas; i++){

			if(comparar_aguacate_segun_vitamina(canasto[i], resultado_esperado[i]) != 0) todas_correctas = false;
		}
	}
	else todas_correctas = false;

	pa2m_afirmar(todas_correctas, "El resto de los aguacates se encuentran en el orden y estado correcto");

	arbol_destruir(arbol);
}

void pruebas_de_estres(){

	pa2m_nuevo_grupo("PRUEBAS: fumigacion");

	int i;
	size_t insertados;
	int* plaga[MAX_COCHINILLAS], *id_aux;
	bool fallo = false, todas_correctas = true;

	int id_cochinillas[MAX_COCHINILLAS];
	size_t tope_cochinillas = 0;

	abb_t* arbol = arbol_crear(comparar_cochinillas_segun_id, envenenar_cochinilla);

	pa2m_nuevo_grupo("Analizando el enemigo");

	pa2m_afirmar(arbol, "Tengo un arbol plagado");

	for(i = 0; i < 5000 && !fallo; i++){

		id_cochinillas[i] = i;
		if(arbol_insertar(arbol, &id_cochinillas[i]) == ERROR) fallo = true;
	}
	pa2m_afirmar(!arbol_vacio(arbol) && !fallo, "El arbol esta en peligro");

	fallo = false;
	for(i = 0; i < 5000 && !fallo; i++){

		id_aux = arbol_buscar(arbol, &id_cochinillas[i]);
		if(id_aux == NULL || comparar_cochinillas_segun_id(id_aux, &id_cochinillas[i]) != 0) fallo = true;
	}
	pa2m_afirmar(!fallo, "Hay cinco mil cochinillas en el arbol listas para atacar");

	insertados = arbol_recorrido_inorden(arbol, (void**)plaga, tope_cochinillas);
	if(insertados == 5000){

		for(int i = 0; i < insertados; i++){

			if(comparar_cochinillas_segun_id(plaga[i], &id_cochinillas[i]) != 0) todas_correctas = false;
		}
	}
	pa2m_afirmar(todas_correctas, "Todas estan en sus posiciones correctas");

	pa2m_nuevo_grupo("Eliminando el enemigo");

	fallo = false;
	for(i = 0; i < 5000 && !fallo; i++){

		if(arbol_borrar(arbol, &id_cochinillas[i]) == ERROR && id_cochinillas[i] == -1) fallo = true;
	}
	pa2m_afirmar(!fallo, "El ataque fue exitoso");
	pa2m_afirmar(arbol_vacio(arbol), "No hay cochinillas en la costa");

	arbol_destruir(arbol);
}

int main(){

	crear_arbol();
	arbol_nulo();
	arbol_sin_elementos();
	probar_insercion();
	probar_busqueda();
	probar_eliminacion();
	vaciar_arbol_de_raiz();
	probar_recorridos();
	probar_iterador_interno();
	pruebas_de_estres();

	pa2m_mostrar_reporte();

	return 0;
}