#include <stdio.h>
#include "heap.h"
#include "pa2mm.h"

/*
 * Compara dos elementos del heap y devuelve 0 en caso de ser iguales, 1 si el primer elemento es mayor al segundo o -1 si el primer 
 * elemento es menor al segundo.
 */
int comparar_enteros(void* numero_a, void* numero_b){

	if(*(int*)numero_a > *(int*)numero_b) return 1;
	else if(*(int*)numero_a < *(int*)numero_b) return -1;
	
	return 0;
} 

/*
 * Pone en 0 un numero. 
 */
void destruir_enteros(void* numero){
	*(int*)numero = 0;
}

void pruebas_creacion_heap(){

	pa2m_nuevo_grupo("PRUEBAS: CREACION HEAP");

	heap_t* heap = heap_crear(comparar_enteros, destruir_enteros);

	pa2m_afirmar(heap, "Se crea un heap");
	pa2m_afirmar(heap && heap->tope == 0, "El heap no tiene elementos");
	pa2m_afirmar(heap && heap->comparador == comparar_enteros, "El metodo de comparacion es el correcto");
	pa2m_afirmar(heap && heap->destructor == destruir_enteros, "El metodo de destruccion es el correcto");
	heap_destruir(heap);
	heap = heap_crear(NULL, destruir_enteros);
	pa2m_afirmar(heap == NULL, "No se crea un heap sin metodo de comparacion");
	heap = heap_crear(comparar_enteros, NULL);
	pa2m_afirmar(heap, "Se crea un heap sin metodo de destruccion");

	heap_destruir(heap);
}

void pruebas_heap_nulo(){

	pa2m_nuevo_grupo("PRUEBAS: HEAP NULO");

	int numero_prueba = 10;

	pa2m_afirmar(heap_raiz(NULL) == NULL, "El heap no tiene raiz");
	pa2m_afirmar(heap_vacio(NULL), "El heap no tiene elementos");
	pa2m_afirmar(heap_insertar(NULL, &numero_prueba) == ERROR, "No se insertan elementos");
	pa2m_afirmar(heap_eliminar_raiz(NULL) == ERROR, "No se elimina la raiz");
}

void pruebas_heap_vacio(){

	pa2m_nuevo_grupo("PRUEBAS: HEAP VACIO");

	int numero_prueba = 10;
	heap_t* heap = heap_crear(comparar_enteros, destruir_enteros);

	pa2m_afirmar(heap_raiz(heap) == NULL, "El heap no tiene raiz");
	pa2m_afirmar(heap_vacio(heap), "El heap no tiene elementos");
	pa2m_afirmar(heap_insertar(heap, &numero_prueba) == EXITO && comparar_enteros(heap_raiz(heap), &numero_prueba) == 0,  "Se inserta primer elemento");
	heap_eliminar_raiz(heap); //La elimino para continuar las pruebas con un heap vacio.
	pa2m_afirmar(heap_eliminar_raiz(heap) == ERROR, "No se elimina raiz");

	heap_destruir(heap);
}

void pruebas_insercion_heap(){

	pa2m_nuevo_grupo("PRUEBAS: INSERCION");

	void* numero_aux;
	bool todos_correctos = true;
	heap_t* heap = heap_crear(comparar_enteros, destruir_enteros);

	int num_1 = 47;
	int num_2 = 5;
	int num_3 = 23;
	int num_4 = 12;
	int num_5 = 33;
	int num_6 = 1;

	int* resultado_esperado[] = {&num_6, &num_4, &num_2, &num_1, &num_5, &num_3};

	pa2m_afirmar(heap && heap->tope == 0 && heap->comparador == comparar_enteros && heap->destructor == destruir_enteros, "Se crea un heap");

	/*PRIMER NUMERO*/
	pa2m_afirmar(heap_insertar(heap, &num_1) == EXITO, "Se inserta primer elemento (47):");
	numero_aux = heap_raiz(heap);
	pa2m_afirmar(numero_aux != NULL && comparar_enteros(numero_aux, &num_1) == 0, " -Es la raiz del heap");

	/*SEGUNDO NUMERO*/
	pa2m_afirmar(heap_insertar(heap, &num_2) == EXITO, "Se inserta segundo elemento (5):");
	numero_aux = heap_raiz(heap);
	pa2m_afirmar(numero_aux != NULL && comparar_enteros(numero_aux, &num_2) == 0, " -Es la raiz del heap");
	pa2m_afirmar(posicion_hijo_izquierdo(0) == 1, " -Su hijo izquierdo es mayor y correcto");

	/*TERCER NUMERO*/
	pa2m_afirmar(heap_insertar(heap, &num_3) == EXITO, "Se inserta tercer elemento (23):");
	numero_aux = heap_raiz(heap);
	pa2m_afirmar(posicion_padre(2) == 0 && *(int*)(heap->vector[posicion_padre(2)]) == num_2, " -Su padre es la raiz");
	pa2m_afirmar(posicion_hijo_izquierdo(posicion_padre(2)) == 1 && *(int*)(heap->vector[posicion_hijo_izquierdo(posicion_padre(2))]) == num_1, " -Su hermano izquierdo es el correcto");

	/*CUARTO NUMERO*/
	pa2m_afirmar(heap_insertar(heap, &num_4) == EXITO, "Se inserta cuarto elemento (12):");
	pa2m_afirmar(*(int*)(heap->vector[1]) == num_4, " -Esta en la posicion correcta");
	pa2m_afirmar(posicion_padre(1) == 0 && *(int*)(heap->vector[posicion_padre(1)]) == num_2, " -Su padre es la raiz");
	pa2m_afirmar(posicion_hijo_derecho(posicion_padre(1)) == 2 && *(int*)(heap->vector[posicion_hijo_derecho(posicion_padre(1))]) == num_3, " -Su hermano derecho es el correcto");
	pa2m_afirmar(posicion_hijo_izquierdo(1) == 3 && *(int*)(heap->vector[posicion_hijo_izquierdo(1)]) == num_1, " -Su hijo izquierdo es mayor y correcto");

	/*QUINTO NUMERO*/
	pa2m_afirmar(heap_insertar(heap, &num_5) == EXITO, "Se inserta quinto elemento (33):");
	pa2m_afirmar(*(int*)(heap->vector[4]) == num_5, " -Esta en la posicion correcta");
	pa2m_afirmar(posicion_padre(4) == 1 && *(int*)(heap->vector[posicion_padre(4)]) == num_4, " -Su padre es menor y correcto");
	pa2m_afirmar(posicion_hijo_izquierdo(posicion_padre(4)) == 3 && *(int*)(heap->vector[posicion_hijo_izquierdo(posicion_padre(4))]) == num_1, " -Su hermano izquierdo es el correcto");

	/*SEXTO NUMERO*/
	pa2m_afirmar(heap_insertar(heap, &num_6) == EXITO, "Se inserta sexto elemento (1):");
	numero_aux = heap_raiz(heap);
	pa2m_afirmar(numero_aux != NULL && comparar_enteros(numero_aux, &num_6) == 0, " -Es la raiz del heap");
	pa2m_afirmar(posicion_hijo_izquierdo(0) == 1 && *(int*)(heap->vector[posicion_hijo_izquierdo(0)]) == num_4, " -Su hijo izquierdo es mayor y correcto");
	pa2m_afirmar(posicion_hijo_derecho(0) == 2 && *(int*)(heap->vector[posicion_hijo_derecho(0)]) == num_2, " -Su hijo derecho es mayor y correcto");

	for(size_t i = 0; i < heap->tope && todos_correctos; i++){

		if(comparar_enteros(heap->vector[i], resultado_esperado[i]) != 0) todos_correctos = false;
	}

	pa2m_afirmar(!heap_vacio(heap) && heap->tope == 6, "El heap tiene seis elementos");
	pa2m_afirmar(todos_correctos, "Los numeros se encuentran en el orden correcto");

	heap_destruir(heap);
}

void pruebas_eliminacion_heap(){

	pa2m_nuevo_grupo("PRUEBAS: eliminar raices");

	size_t i;
	void* numero_aux;
	bool fallo = false;
	heap_t* heap = heap_crear(comparar_enteros, destruir_enteros);

	int num_1 = 47;
	int num_2 = 5;
	int num_3 = 23;
	int num_4 = 12;
	int num_5 = 33;
	int num_6 = 1;

	int* numeros_insertar[] = {&num_1, &num_2, &num_3, &num_4, &num_5, &num_6};

	pa2m_afirmar(heap && heap->tope == 0 && heap->comparador == comparar_enteros && heap->destructor == destruir_enteros, "Creo un heap");

	for(i = 0; i < 6 && !fallo; i++){

		if(heap_insertar(heap, numeros_insertar[i]) == ERROR) fallo = true;
	}
	pa2m_afirmar(!fallo && !heap_vacio(heap), "El heap tiene seis elementos");

	pa2m_afirmar(heap_eliminar_raiz(heap) == EXITO && num_6 == 0, "Se elimina raiz (1):");
	numero_aux = heap_raiz(heap);
	pa2m_afirmar(numero_aux != NULL && comparar_enteros(numero_aux, &num_2) == 0, " -La nueva raiz es correcta");
	pa2m_afirmar(*(int*)(heap->vector[1]) == num_4, " -Su hijo izquierdo es mayor y correcto");
	pa2m_afirmar(*(int*)(heap->vector[2]) == num_3, " -Su hijo derecho es mayor y correcto");

	pa2m_afirmar(heap_eliminar_raiz(heap) == EXITO && num_2 == 0, "Se elimina raiz (5):");
	numero_aux = heap_raiz(heap);
	pa2m_afirmar(numero_aux != NULL && comparar_enteros(numero_aux, &num_4) == 0, " -La nueva raiz es correcta");
	pa2m_afirmar(*(int*)(heap->vector[1]) == num_5, " -Su hijo izquierdo es mayor y correcto");
	pa2m_afirmar(*(int*)(heap->vector[2]) == num_3, " -Su hijo derecho es mayor y correcto");

	pa2m_afirmar(heap_eliminar_raiz(heap) == EXITO && num_4 == 0, "Se elimina raiz (12):");
	numero_aux = heap_raiz(heap);
	pa2m_afirmar(numero_aux != NULL && comparar_enteros(numero_aux, &num_3) == 0, " -La nueva raiz es correcta");
	pa2m_afirmar(*(int*)(heap->vector[1]) == num_5, " -Su hijo izquierdo es mayor y correcto");
	pa2m_afirmar(*(int*)(heap->vector[2]) == num_1, " -Su hijo derecho es mayor y correcto");

	pa2m_afirmar(heap_eliminar_raiz(heap) == EXITO && num_3 == 0, "Se elimina raiz (23):");
	numero_aux = heap_raiz(heap);
	pa2m_afirmar(numero_aux != NULL && comparar_enteros(numero_aux, &num_5) == 0, " -La nueva raiz es correcta");
	pa2m_afirmar(*(int*)(heap->vector[1]) == num_1, " -Su hijo izquierdo es mayor y correcto");

	pa2m_afirmar(heap_eliminar_raiz(heap) == EXITO && num_5 == 0, "Se elimina raiz (33):");
	numero_aux = heap_raiz(heap);
	pa2m_afirmar(numero_aux != NULL && comparar_enteros(numero_aux, &num_1) == 0, " -La nueva raiz es correcta");

	pa2m_afirmar(heap_eliminar_raiz(heap) == EXITO && num_1 == 0, "Se elimina raiz (47):");
	pa2m_afirmar(heap_vacio(heap), " -El heap esta vacio");

	heap_destruir(heap);
}

int main(){

	pruebas_creacion_heap();
	pruebas_heap_nulo();
	pruebas_heap_vacio();
	pruebas_insercion_heap();
	pruebas_eliminacion_heap();

	pa2m_mostrar_reporte();
	
	return 0;
}