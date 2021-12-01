#include "juego.h"

/*INSTANCIAS*/
#define MENU_INICIO 'I'
#define MENU_GIMNASIO 'G'
#define MENU_BATALLA 'B'
#define MENU_VICTORIA 'V'
#define MENU_DERROTA 'D'

/*OPCIONES MENU*/
const char AGREGAR_AVATAR = 'E';
const char AGREGAR_GIMNASIO = 'A';
const char INICIAR_PARTIDA = 'I';
const char SIMULACION = 'S';
const char SALIR = 'X';
const char VER_AVATAR = 'E';
const char VER_GIMNASIO = 'G';
const char CAMBIAR_POKES = 'C';
const char VER_MEDALLAS = 'M';
const char BATALLA = 'B';
const char PROXIMA = 'N';
const char TOMAR_POKE = 'T';
const char REINTENTAR = 'R';
const char FINALIZAR = 'F';

const int PERDIO_BATALLA = -1;
const int GANO_BATALLA = 0;

/*FUNCIONES MENU ENCAPSULADAS*/

/*
 * Le muestra al usuario la informacion de su avatar en caso de que desee verla.
 */
void mostrar_info_avatar(personaje_t* avatar){

	if(!avatar) return;

	char inicial;
	char decision[MAX_LETRAS];

	printf("¿Desea ver la informacion de su Avatar? (S/N): ");
	scanf("%s", decision);
	inicial = (char)toupper((int)decision[0]);

	if(inicial == 'S'){

		info_avatar(avatar);
		volver_a_menu();
	}
}

/*
 * Le muestra al usuario la informacion de los gimnasios que cargo en caso de que desee verla.
 */
void mostrar_info_gimnasios(heap_t* gimnasios){

	if(!gimnasios) return;

	char inicial;
	char decision[MAX_LETRAS];

	printf("¿Desea ver la informacion de su/s gimnasio/s? (S/N): ");
	scanf("%s", decision);
	inicial = (char)toupper((int)decision[0]);

	if(inicial == 'S'){

		info_gimnasios(gimnasios);
		volver_a_menu();
	}
}

/*
 * Valida la instancia recibida por parametro.
 * Si esta dentro de las validas devuelve verdadero. De lo contrario devuelve falso.
 */
bool instancia_valida(char instancia){

	return (instancia == MENU_INICIO || instancia == MENU_GIMNASIO || instancia == MENU_BATALLA || instancia == MENU_VICTORIA || instancia == MENU_DERROTA);
}

/*
 * Valida la opcion recibida por parametro.
 * Si esta dentro de las validas devuelve verdadero. De lo contrario devuelve falso.
 */
bool opcion_valida(char opcion, char instancia, int menu_victoria){

	if(instancia == MENU_INICIO)
		return (opcion == AGREGAR_AVATAR || opcion == AGREGAR_GIMNASIO || opcion == INICIAR_PARTIDA ||                                	  opcion == SIMULACION || opcion == SALIR);

	else if(instancia == MENU_GIMNASIO)
		return (opcion == VER_AVATAR || opcion == VER_GIMNASIO || opcion == CAMBIAR_POKES || opcion == BATALLA ||						opcion == FINALIZAR);

	else if(instancia == MENU_BATALLA)
		return (opcion == PROXIMA || opcion == FINALIZAR);

	else if(instancia == MENU_VICTORIA && menu_victoria == 1)
		return (opcion == TOMAR_POKE || opcion == CAMBIAR_POKES || opcion == VER_MEDALLAS || opcion == PROXIMA || 						opcion == FINALIZAR);

	else if(instancia == MENU_VICTORIA && menu_victoria == 2)
		return (opcion == CAMBIAR_POKES || opcion == VER_MEDALLAS || opcion == PROXIMA || opcion == FINALIZAR);

	else if(instancia == MENU_DERROTA)
		return (opcion == CAMBIAR_POKES || opcion == REINTENTAR || opcion == FINALIZAR);

	return false;
}

/*
 * Muestra por pantalla un determinado Menu segun la instancia recibida por parametro.
 * Si la instancia es MENU_VICTORIA, se mostrara el Menu correspondiente dependiendo del valor del entero recibido por parametro.
 * Si el numero recibido por parametro es distinto de 1 y 2, se muestra por defecto el Menu Victoria sin opcion de tomar un pokemon
 * del lider.
 */
void mostrar_menu(char instancia, int menu_victoria){

	switch (instancia){

		case MENU_INICIO:
		menu_box_inicio();
		break;

		case MENU_GIMNASIO:
		menu_box_gimnasio();
		break;

		case MENU_BATALLA:
		menu_box_batalla();
		break;

		case MENU_VICTORIA:
		if(menu_victoria == 1) menu_box_victoria_1();
		else menu_box_victoria_2();
		break;

		case MENU_DERROTA:
		menu_box_derrota();
		break;
	}
}

/*
 * Le pide al usuario que elija una opcion del Menu mostrado por pantalla (segun la instancia recibida) y guarda la misma en la
 * variable opcion. La opcion guardada siempre sera valida con respecto al Menu pedido.
 */
void menu(char instancia, int menu_victoria, char* opcion){

	if(!instancia_valida(instancia) || !opcion) return;

	char decision[MAX_LETRAS];

	do{

		mostrar_menu(instancia, menu_victoria);
		printf("\nIngrese una opcion: ");
		scanf("%s", decision);
		*opcion = (char)toupper((int)decision[0]);

	}while(!opcion_valida(*opcion, instancia, menu_victoria));
}

/*
 * Dependiendo de la opcion elegida por el usuario del Menu Gimnasio, realiza las operaciones correspondientes.
 */
void menu_gimnasio(personaje_t* avatar, gimnasio_t* gimnasio, int id_batalla, char* opcion){

	if(!avatar || !gimnasio || !opcion) return;

	do{

		menu(MENU_GIMNASIO, 0, opcion);

		if(*opcion == VER_AVATAR){

			info_avatar(avatar);
			volver_a_menu();
		}		
		else if(*opcion == VER_GIMNASIO){

			info_gimnasio(gimnasio, id_batalla);
			volver_a_menu();
		}
		else if(*opcion == CAMBIAR_POKES){

			info_avatar(avatar);
			pokemon_intercambiar(avatar);
			mostrar_info_avatar(avatar);
		}

	}while(*opcion != BATALLA && *opcion != FINALIZAR);
}

/*
 * Dependiendo de la opcion elegida por el usuario del Menu Victoria, realiza las operaciones correspondientes.
 */
void menu_victoria(personaje_t* avatar, entrenador_t* lider, char* opcion){

	if(!avatar || !lider || !opcion) return;

	bool poke_tomado = false;

	do{

		if(!poke_tomado) menu(MENU_VICTORIA, 1, opcion);
		else menu(MENU_VICTORIA, 2, opcion);

		if(*opcion == CAMBIAR_POKES){

			info_avatar(avatar);
			pokemon_intercambiar(avatar);
			mostrar_info_avatar(avatar);
		}
		else if(*opcion == TOMAR_POKE && !poke_tomado){

			system("clear");
			info_entrenador(lider);
			pokemon_agregar(avatar->caja, lider);
			mostrar_info_avatar(avatar);
			poke_tomado = true;
		}
		else if(*opcion == VER_MEDALLAS){

			info_medallas(avatar->medallas);
			volver_a_menu();
		}

	}while(*opcion != PROXIMA && *opcion != FINALIZAR);
}

/*
 * Dependiendo de la opcion elegida por el usuario del Menu Derrota, realiza las operaciones correspondientes.
 */
void menu_derrota(personaje_t* avatar, char* opcion){

	if(!avatar || !opcion) return;

	do{

		menu(MENU_DERROTA, 0, opcion);

		if(*opcion == CAMBIAR_POKES){

			info_avatar(avatar);
			pokemon_intercambiar(avatar);
			mostrar_info_avatar(avatar);
		}

		system("clear");

	}while(*opcion != REINTENTAR && *opcion != FINALIZAR);
}

/*FUNCIONES JUEGO ENCAPSULADAS*/

/*
 * Destruye un avatar recibido por parametro en el caso de que ya exista.
 */
bool avatar_reseteado(personaje_t** avatar){

	if(!*avatar) return true;

	char inicial;
	char decision[MAX_LETRAS];

	printf("Ya se cargo un avatar previamente, ¿desea cargar uno nuevo? (S/N): ");
	scanf("%s", decision);
	inicial = (char)toupper((int)decision[0]);

	if(inicial == 'S'){

		personaje_destruir(avatar);
		return true;
	}

	return false;
}

/*
 * Le asigna una direccion de memoria al avatar recibido por parametro. 
 * El mismo, quedara incializado segun la informacion leida del archivo indicado por el usuario.
 */
void agregar_avatar(personaje_t** avatar){

	if(!avatar_reseteado(avatar)) return;

	char ruta[MAX_LETRAS];
	printf("Ingrese la ruta del archivo: ");
	scanf("%s", ruta);

	FILE* archivo_avatar = fopen(ruta, "r");
	if(!archivo_avatar){

		printf("Error en apertura de archivo. Intente nuevamente.\n");
		system("sleep 2");
		return;
	}

	*avatar = personaje_crear();
	if(!*avatar) return;

	if(personaje_cargar(archivo_avatar, *avatar) == ERROR){

		printf("Error al cargar el avatar. Intente nuevamente.\n");
		system("sleep 2");
		personaje_destruir(avatar);
		fclose(archivo_avatar);
		return;
	}
	
	fclose(archivo_avatar);
	mostrar_info_avatar(*avatar);
}

/*
 * Le asigna una direccion de memoria al heap binario recibido por parametro. 
 * El mismo, quedara incializado segun la informacion leida del archivo indicado por el usuario.
 */
void agregar_gimnasio(heap_t* gimnasios){

	if(!gimnasios) return;

	char ruta[MAX_LETRAS];
	printf("Importante: una vez que se cargue un gimnasio no se podra eliminar.\n");
	printf("Ingrese la ruta del archivo: ");
	scanf("%s", ruta);

	FILE* archivo_gimnasios = fopen(ruta, "r");
	if(!archivo_gimnasios){

		printf("Error en apertura de archivo. Intente nuevamente.\n");
		system("sleep 2");
		return;
	}

	if(gimnasio_cargar(gimnasios, archivo_gimnasios) == ERROR){

		printf("Error al cargar el/los gimnasio/s. Intente nuevamente.\n");
		system("sleep 2");
		fclose(archivo_gimnasios);
		return;
	}

	fclose(archivo_gimnasios);
	mostrar_info_gimnasios(gimnasios);
}

/*
 * Devuelve un puntero a una funcion de batalla.
 * Si el id de la batalla es invalido, es decir, que es menor a 1 o mayor a 5, se devolvera un puntero a la funcion de batalla
 * numero 1.
 */
batalla elegir_batalla(int id_batalla){	

	if(id_batalla < 1 || id_batalla > 5) return funcion_batalla_1;

	if(id_batalla == 1) return funcion_batalla_1;
	else if(id_batalla == 2) return funcion_batalla_2;
	else if(id_batalla == 3) return funcion_batalla_3;
	else if(id_batalla == 4) return funcion_batalla_4;
	else return funcion_batalla_5;
}

/*PARTIDA EN TIEMPO REAL*/

/*
 * Busca un pokemon de la Caja que tambien se encuentra en el Party para asignarle los nuevos stats.
 */
void buscar_pokemon(nodo_t* caja, pokemon_t* buscado){

	if(!caja || !buscado) return;

	pokemon_t* poke_actual = (pokemon_t*)caja->elemento;
	if(strcmp(poke_actual->nombre, buscado->nombre) == 0){

		*poke_actual = *buscado;
		return;
	}

	buscar_pokemon(caja->siguiente, buscado);
}

/*
 * Le asigna a un pokemon de la Caja que tambien se encuentra en el Party los stats correspondientes obtenidos durante el juego.
 */
void entrenar_pokemon_caja(lista_t* caja, nodo_t* party){

	if(!caja || !party) return;

	buscar_pokemon(caja->nodo_inicio, (pokemon_t*)party->elemento);
	entrenar_pokemon_caja(caja, party->siguiente);
}

/*
 * Realiza los combates entre un pokemon de un entrenador y un pokemon del avatar.
 * Devuelve -1 si el pokemon del avatar pierde el combate. De lo contrario, devuelve 0.
 */
int jugar_combate(lista_iterador_t* it_avatar, lista_iterador_t* it_entrenador, batalla func_batalla, char* opcion){

	if(!lista_iterador_tiene_siguiente(it_entrenador)){

		system("sleep 2");
		return GANO_BATALLA;
	}

	menu(MENU_BATALLA, 0, opcion);
	if(*opcion == FINALIZAR){

		system("clear");
		return PERDIO_BATALLA;
	}

	info_combate((pokemon_t*)lista_iterador_elemento_actual(it_avatar), (pokemon_t*)lista_iterador_elemento_actual(it_entrenador));
	int resultado = func_batalla(lista_iterador_elemento_actual(it_avatar), lista_iterador_elemento_actual(it_entrenador));
	if(resultado == GANO_PRIMERO){

		pokemon_entrenar((pokemon_t*)lista_iterador_elemento_actual(it_avatar));
		mostrar_pokemon_ganador((pokemon_t*)lista_iterador_elemento_actual(it_avatar));
		lista_iterador_avanzar(it_entrenador);
	}
	else{

		mostrar_pokemon_perdedor((pokemon_t*)lista_iterador_elemento_actual(it_avatar));
		if(lista_iterador_avanzar(it_avatar)) aviso_cambio_poke(((pokemon_t*)lista_iterador_elemento_actual(it_avatar))->nombre);
		else{

			system("sleep 2");
			return PERDIO_BATALLA;
		}
	}

	return jugar_combate(it_avatar, it_entrenador, func_batalla, opcion);
}

/*
 * Realiza las batallas entre los entrenadores de un gimnasio y el avatar.
 * Devuelve -1 si el avatar pierde la batalla. De lo contrario, devuelve 0.
 */
int jugar_partida(personaje_t* avatar, lista_t* entrenadores, batalla func_batalla, char* opcion, char* medalla){

	if(lista_elementos(entrenadores) == 1 && *opcion != REINTENTAR){

		medalla_agregar(avatar->medallas, medalla);
		menu_victoria(avatar, (entrenador_t*)lista_tope(entrenadores), opcion);
		lista_desapilar(entrenadores);
		return GANO_BATALLA;
	}

	entrenador_t* entrenador = lista_tope(entrenadores);
	lista_iterador_t* it_avatar = lista_iterador_crear(avatar->party);
	lista_iterador_t* it_entrenador = lista_iterador_crear(entrenador->pokemon);
	if(!it_avatar || !it_entrenador){

		printf("Error de memoria. Si el problema persiste, reinice su PC\n");
		*opcion = FINALIZAR;
		return PERDIO_BATALLA;
	}

	info_entrenadores_combate(avatar, entrenador);
	int resultado = jugar_combate(it_avatar, it_entrenador, func_batalla, opcion);
	entrenar_pokemon_caja(avatar->caja, avatar->party->nodo_inicio);

	lista_iterador_destruir(it_entrenador);
	lista_iterador_destruir(it_avatar);
	
	if(resultado == GANO_BATALLA){
		
		if(!entrenador->es_lider) lista_desapilar(entrenadores);
		return jugar_partida(avatar, entrenadores, func_batalla, opcion, medalla);
	}
	else{

		menu_derrota(avatar, opcion);
		if(*opcion == FINALIZAR) return PERDIO_BATALLA;
		return jugar_partida(avatar, entrenadores, func_batalla, opcion, medalla);
	}
}

/*SIMULACION*/

/*
 * Realiza los combates entre un pokemon de un entrenador y un pokemon del avatar.
 * Devuelve -1 si el pokemon del avatar pierde el combate. De lo contrario, devuelve 0.
 */
int simulacion_combate(lista_iterador_t* it_avatar, lista_iterador_t* it_entrenador, batalla func_batalla){

	if(!lista_iterador_tiene_siguiente(it_entrenador)) return GANO_BATALLA;

	int resultado = func_batalla(lista_iterador_elemento_actual(it_avatar), lista_iterador_elemento_actual(it_entrenador));
	if(resultado == GANO_PRIMERO){

		pokemon_entrenar((pokemon_t*)lista_iterador_elemento_actual(it_avatar));
		lista_iterador_avanzar(it_entrenador);
	}
	else if(!lista_iterador_avanzar(it_avatar)) return PERDIO_BATALLA;

	return simulacion_combate(it_avatar, it_entrenador, func_batalla);
}

/*
 * Realiza las batallas entre los entrenadores de un gimnasio y el avatar.
 * Devuelve -1 si el avatar pierde la batalla. De lo contrario, devuelve 0.
 */
int simulacion_batalla(personaje_t* avatar, lista_t* entrenadores, batalla func_batalla){

	if(lista_vacia(entrenadores)) return GANO_BATALLA;

	entrenador_t* entrenador = lista_tope(entrenadores);
	lista_iterador_t* it_avatar = lista_iterador_crear(avatar->party);
	lista_iterador_t* it_entrenador = lista_iterador_crear(entrenador->pokemon);
	if(!it_avatar || !it_entrenador){

		printf("Error de memoria. Si el problema persiste, reinice su PC\n");
		return PERDIO_BATALLA;
	}

	int resultado = simulacion_combate(it_avatar, it_entrenador, func_batalla);
	entrenar_pokemon_caja(avatar->caja, avatar->party->nodo_inicio);

	lista_iterador_destruir(it_entrenador);
	lista_iterador_destruir(it_avatar);
	
	if(resultado == GANO_BATALLA){
		
		lista_desapilar(entrenadores);
		return simulacion_batalla(avatar, entrenadores, func_batalla);
	}
	else{

		derrota_simulacion();
		return PERDIO_BATALLA;
	}
}

/*FUNCIONES BIBLIOTECA*/

void menu_inicio(personaje_t** avatar, heap_t* gimnasios){

	if(!gimnasios) return;

	char opcion;

	do{

		menu(MENU_INICIO, 0, &opcion);

		if(opcion == AGREGAR_AVATAR) agregar_avatar(avatar);

		else if(opcion == AGREGAR_GIMNASIO) agregar_gimnasio(gimnasios);

		else if((opcion == INICIAR_PARTIDA || opcion == SIMULACION) && (personaje_vacio(*avatar) || heap_vacio(gimnasios))){

			printf("No se puede iniciar una simulacion/partida sin gimnasios o avatar\n");
			system("sleep 3");
			opcion = AGREGAR_AVATAR;
		}
		else if((opcion == INICIAR_PARTIDA || opcion == SIMULACION) && (!personaje_vacio(*avatar) && !heap_vacio(gimnasios))){

			if(opcion == INICIAR_PARTIDA) iniciar_partida(*avatar, gimnasios);
			else simulacion_partida(*avatar, gimnasios);
		}

	}while(opcion == AGREGAR_AVATAR || opcion == AGREGAR_GIMNASIO);
}

void iniciar_partida(personaje_t* avatar, heap_t* gimnasios){

	if(!avatar || !gimnasios) return;

	if(heap_vacio(gimnasios)){

		maestro_pokemon(avatar->nombre);
		return;
	}

	char opcion;
	menu_gimnasio(avatar, (gimnasio_t*)heap_raiz(gimnasios), ((gimnasio_t*)heap_raiz(gimnasios))->id_batalla, &opcion);
	if(opcion == FINALIZAR) return;
	
	batalla func_batalla = elegir_batalla(((gimnasio_t*)heap_raiz(gimnasios))->id_batalla);
	if(!func_batalla) return;

	char nueva_medalla[MAX_LETRAS];
	strcpy(nueva_medalla, ((gimnasio_t*)heap_raiz(gimnasios))->medalla);

	int resultado = jugar_partida(avatar, ((gimnasio_t*)heap_raiz(gimnasios))->entrenadores, func_batalla, &opcion, nueva_medalla);
	if(opcion == FINALIZAR) return;

	if(resultado == PERDIO_BATALLA) return;
	else heap_eliminar_raiz(gimnasios);

	iniciar_partida(avatar, gimnasios);
}

void simulacion_partida(personaje_t* avatar, heap_t* gimnasios){

	if(!avatar || !gimnasios) return;

	if(heap_vacio(gimnasios)){

		maestro_pokemon(avatar->nombre);
		return;
	}

	batalla func_batalla = elegir_batalla(((gimnasio_t*)heap_raiz(gimnasios))->id_batalla);
	if(!func_batalla) return;

	int resultado = simulacion_batalla(avatar, ((gimnasio_t*)heap_raiz(gimnasios))->entrenadores, func_batalla);

	if(resultado == PERDIO_BATALLA) return;
	else heap_eliminar_raiz(gimnasios);

	simulacion_partida(avatar, gimnasios);
}