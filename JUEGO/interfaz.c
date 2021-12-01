#include "interfaz.h"

/*COLORES*/
#define NEGRO "\033[0;30m"
#define ROJO "\033[0;31m"
#define AMARILLO "\033[0;33m"
#define MAGENTA "\033[0;35m"
#define BLANCO "\033[0;37m"

/*FUNCIONES ENCAPSULADAS*/

//CARTELES

void cartel_juego(){

	system("clear");

	printf(ROJO"    ____        __                                 ___       __                 __                  \n");
	printf("   / __ \\____  / /_____  ____ ___  ____  ____     /   | ____/ /   _____  ____  / /___  __________ \n");
	printf("  / /_/ / __ \\/ //_/ _ \\/ __ `__ \\/ __ \\/ __ \\   / /| |/ __  / | / / _ \\/ __ \\/ __/ / / / ___/ _ \\\n");
	printf(" / ____/ /_/ / ,< /  __/ / / / / / /_/ / / / /  / ___ / /_/ /| |/ /  __/ / / / /_/ /_/ / /  /  __/\n");
	printf("/_/    \\____/_/|_|\\___/_/ /_/ /_/\\____/_/ /_/  /_/  |_\\__,_/ |___/\\___/_/ /_/\\__/\\__,_/_/   \\___/\n\n"BLANCO);
}

void cartel_combate(){

	system("clear");

	printf(ROJO"                                __________  __  _______  ___  ____________\n");
	printf("                              / ____/ __ \\/  |/  / __ )/   |/_  __/ ____/\n");
	printf("                             / /   / / / / /|_/ / __  / /| | / / / __/   \n");
	printf("                            / /___/ /_/ / /  / / /_/ / ___ |/ / / /___ \n");
	printf("                            \\____/\\____/_/  /_/_____/_/  |_/_/ /_____/\n\n"BLANCO);
}

void cartel_batalla(){

	system("clear");

	printf(ROJO"                               ____  ___  _________    __    __    ___\n");
	printf("                              / __ )/   |/_  __/   |  / /   / /   /   |\n");
	printf("                             / __  / /| | / / / /| | / /   / /   / /| |\n");
	printf("                            / /_/ / ___ |/ / / ___ |/ /___/ /___/ ___ |\n");
	printf("                           /_____/_/  |_/_/ /_/  |_/_____/_____/_/  |_|\n"BLANCO);
}

void cartel_ganador(){

	system("clear");

	printf(ROJO"                            _________    _   _____    ____  ____  ____\n");
	printf("                           / ____/   |  / | / /   |  / __ \\/ __ \\/ __ \\\n");
	printf("                          / / __/ /| | /  |/ / /| | / / / / / / / /_/ /\n");
	printf("                         / /_/ / ___ |/ /|  / ___ |/ /_/ / /_/ / _, _/\n");
	printf("                         \\____/_/  |_/_/ |_/_/  |_/_____/\\____/_/ |_|  \n\n"BLANCO);
}

void cartel_perdida(){

	system("clear");

	printf(ROJO"                           ____  __________  ____  __________  ____  ____ \n");
	printf("                          / __ \\/ ____/ __ \\/ __ \\/ ____/ __ \\/ __ \\/ __ \\\n");
	printf("                         / /_/ / __/ / /_/ / / / / __/ / / / / / / / /_/ /\n");
	printf("                        / ____/ /___/ _, _/ /_/ / /___/ /_/ / /_/ / _, _/ \n");
	printf("                       /_/   /_____/_/ |_/_____/_____/_____/\\____/_/ |_|\n\n"BLANCO);
}

void felicitaciones(){

	system("clear");

	printf(ROJO"                   ___ ___ _    ___ ___ ___ _____ _   ___ ___ ___  _  _ ___ ___ \n");
	printf("                  | __| __| |  |_ _/ __|_ _|_   _/_\\ / __|_ _/ _ \\| \\| | __/ __|\n");
	printf("                  | _|| _|| |__ | | (__ | |  | |/ _ \\ (__ | | (_) | .` | _|\\__ \\\n");
	printf("                  |_| |___|____|___\\___|___| |_/_/ \\_\\___|___\\___/|_|\\_|___|___/\n"BLANCO);
}

//DIBUJOS

void pikachu(){

	printf(AMARILLO"                                       ,___          .-;'\n");
	printf("                                       `--.`\\_...._/`.`\n");
	printf("                                    ,      \\        /\n");
	printf("                                 .-' ',    / ()   ()\\ \n");
	printf("                                `'._   \\  /()    .  (|\n");
	printf("                                    > .' ;,     -'-  /\n");
	printf("                                   / <   |;,     __.;\n");
	printf("                                   '-.'-.|  , \\    , \\\n");
	printf("                                      `>.|;, \\_)    \\_)\n");
	printf("                                       `-;     ,    /\n");
	printf("                                          \\    /   < \n");
	printf("                                           '. <`'-,_)\n");
	printf("                                            '._) \n\n"BLANCO);
}

void pikachus(){

	printf(AMARILLO"                          ,___          .-;'            `;-.          ___,\n");
	printf("                          `--.`\\_...._/`.`               `.`\\_...._/`.--`\n");
	printf("                       ,      \\        /                   \\        /      ,\n");
	printf("                    .-' ',    / ()   ()\\                  /()   () \\    .' `-._\n");
	printf("                   `'._   \\  /()    .  (|                 |)  .    ()\\  /   _.'\n");
	printf("                       > .' ;,     -'-  /                  \\  -'-     ,; '. <\n");
	printf("                      / <   |;,     __.;                    ;.__     ,;|   > \\\n");
	printf("                      '-.'-.|  , \\    , \\                / ,    / ,  |.-'.-'\n");
	printf("                         `>.|;, \\_)    \\_)              (_/    (_/ ,;|.<`\n");
	printf("                          `-;     ,    /                    \\    ,     ;-`\n");
	printf("                             \\    /   <                     >   \\    /\n");
	printf("                              '. <`'-,_)                    (_,-'`> .'\n");
	printf("                               '._)                              (_,'\n\n"BLANCO);
}

void punio(){

	printf(AMARILLO"                                           _    ,-,    _\n");
	printf("                                    ,--, /: :\\/': :`\\/: :\\\n");
	printf("                                   |`;  ' `,'   `.;    `: |\n");
	printf("                                   |    |     |  '  |     |.\n");
	printf("                                   | :  |     |     |     ||\n");
	printf("                                   | :. |  :  |  :  |  :  | \\\n");
	printf("                                    \\__/: :.. : :.. | :.. |  )\n");
	printf("                                         `---',\\___/,\\___/ /'\n");
	printf("                                              `==._ .. . /'\n");
	printf("                                                   `-::-'\n\n"BLANCO);
}

void medalla(){

	printf("                                         _______________\n");
	printf("                                        |"ROJO"@@@@"BLANCO"|     |"ROJO"@@@@"BLANCO"|\n");
	printf("                                        |"ROJO"@@@@"BLANCO"|     |"ROJO"@@@@"BLANCO"|\n");
	printf("                                        |"ROJO"@@@@"BLANCO"|     |"ROJO"@@@@"BLANCO"|\n");
	printf("                                        \\"ROJO"@@@@"BLANCO"|     |"ROJO"@@@@"BLANCO"/\n");
	printf("                                         \\"ROJO"@@@"BLANCO"|     |"ROJO"@@@"BLANCO"/\n");
	printf("                                          `"ROJO"@@"BLANCO"|_____|"ROJO"@@"BLANCO"'\n");
	printf(AMARILLO"                                               (O)\n");
	printf("                                            .-'''''-.\n");
	printf("                                          .'  * * *  `.\n");
	printf("                                         :  *       *  :\n");
	printf("                                        :  ~ MAESTRO ~  :\n");
	printf("                                        :  ~ POKEMON ~  :\n");
	printf("                                         :  *       *  :\n");
	printf("                                          `.  * * *  .'\n");
	printf("                                            `-.....-'\n"BLANCO);

}

//INTERACCION

void ir_a_combate(){

	char inicial;
	char decision[MAX_LETRAS];

	printf("\n\nPresione "ROJO"C"BLANCO" para Combatir ");
	do{
	
		scanf("%s", decision);
		inicial = (char)toupper((int)decision[0]);

	}while(inicial != COMBATIR);
}

void mensaje_gimnasio(int id_batalla){

	if(id_batalla == 2) printf(" ¡Alto ahí, niño!\n ¡Todavía estás a años luz de llegar al lider de este gimnasio!\n ¡Enséñame lo que vales y muevete lo mas rapido que puedas!\n");
	else if(id_batalla == 3) printf(" ¡Muy bien! Tal como acordamos.\n ¡Prepárate con tus movimientos de ataque y velocidad!\n ¡Atrapame si puedes!\n");
	else if(id_batalla == 4) printf(" ¡Eh, tú, joven!, Tengo que reconocerlo...\n No es que sea inteligente desafiarnos...\n ¡Pero requiere agallas!\n Nunca hemos perdido una batalla, ¡prepara tu poder de defensa!\n");
	else if(id_batalla == 5) printf(" ¡Oye! ¿Pero qué haces? ¡No resistirás mucho luchando!\n Los pokemon de este gimnasio me salvaron en combate.\n ¡Paralizaron a mis enemigos gracias a su especie!\n Y eso mismo voy a hacer yo contigo...\n Veamos si los tuyos pueden salvarte...\n");
	else printf(" Los entrenadores de este gimnasio entrenan para atacar.\n Los combates pueden durar mucho rato.\n ¿Te sientes con fuerzas para pelear?\n");
}

/*FUNCIONES BIBLIOTECA*/

void menu_box_inicio(){

	cartel_juego();

	printf("                                  Bienvenido a Pokemon Adventure\n\n");
	
	printf(NEGRO"                ╔");
	for(int i = 0; i < 64; i++)
		printf("═");
	printf("╗\n"BLANCO);

	printf(NEGRO"                ║"BLANCO"                         MENU PRINCIPAL                         "NEGRO"║\n");
	printf("                ╚");
	for(int i = 0; i < 64; i++)
		printf("═");
	printf("╝\n");

	printf(NEGRO"                ║         "ROJO"E."BLANCO" Ingresa el archivo del entrenador principal         "NEGRO"║\n");
	printf(NEGRO"                ║         "ROJO"A."BLANCO" Agrega un gimnasio al árbol de gimnasios            "NEGRO"║\n");
	printf(NEGRO"                ║         "ROJO"I."BLANCO" Comienza la Partida                                 "NEGRO"║\n");
	printf(NEGRO"                ║         "ROJO"S."BLANCO" Simula la Partida                                   "NEGRO"║\n");
	printf(NEGRO"                ║         "ROJO"X."BLANCO" Salir                                               "NEGRO"║\n");
	
	printf(NEGRO"                ╚");
	for(int i = 0; i < 64; i++)
		printf("═");
	printf("╝\n"BLANCO);
}

void menu_box_gimnasio(){

	cartel_juego();

	printf(NEGRO"                ╔");
	for(int i = 0; i < 64; i++)
		printf("═");
	printf("╗\n"BLANCO);

	printf(NEGRO"                ║"BLANCO"                          MENU GIMNASIO                         "NEGRO"║\n");
	printf("                ╚");
	for(int i = 0; i < 64; i++)
		printf("═");
	printf("╝\n");

	printf(NEGRO"                ║           "ROJO"E."BLANCO" Ver informacion del entrenador principal          "NEGRO"║\n");
	printf(NEGRO"                ║           "ROJO"G."BLANCO" Ver informacion del gimnasio                      "NEGRO"║\n");
	printf(NEGRO"                ║           "ROJO"C."BLANCO" Cambiar los Pokémon de batalla                    "NEGRO"║\n");
	printf(NEGRO"                ║           "ROJO"B."BLANCO" Proxima batalla                                   "NEGRO"║\n");
	printf(NEGRO"                ║           "ROJO"F."BLANCO" Finalizar partida                                 "NEGRO"║\n");

	printf(NEGRO"                ╚");
	for(int i = 0; i < 64; i++)
		printf("═");
	printf("╝\n"BLANCO);
}

void menu_box_batalla(){

	printf(NEGRO"                ╔");
	for(int i = 0; i < 64; i++)
		printf("═");
	printf("╗\n"BLANCO);

	printf(NEGRO"                ║"BLANCO"                           MENU BATALLA                         "NEGRO"║\n");
	printf("                ╚");
	for(int i = 0; i < 64; i++)
		printf("═");
	printf("╝\n");

	printf(NEGRO"                ║                      "ROJO" N."BLANCO" Proximo combate                       "NEGRO"║\n");
	printf(NEGRO"                ║                      "ROJO" F."BLANCO" Finalizar partida                     "NEGRO"║\n");
	
	printf(NEGRO"                ╚");
	for(int i = 0; i < 64; i++)
		printf("═");
	printf("╝\n"BLANCO);
}

void menu_box_victoria_1(){

	cartel_juego();

	printf(NEGRO"                ╔");
	for(int i = 0; i < 64; i++)
		printf("═");
	printf("╗\n"BLANCO);

	printf(NEGRO"                ║"BLANCO"                           MENU VICTORIA                        "NEGRO"║\n");
	printf("                ╚");
	for(int i = 0; i < 64; i++)
		printf("═");
	printf("╝\n");

	printf(NEGRO"                ║                 "ROJO" T."BLANCO" Tomar lo que te pertenece                  "NEGRO"║\n");
	printf(NEGRO"                ║                 "ROJO" M."BLANCO" Ver medallas                               "NEGRO"║\n");
	printf(NEGRO"                ║                 "ROJO" C."BLANCO" Cambiar los Pokémon de batalla             "NEGRO"║\n");
	printf(NEGRO"                ║                 "ROJO" N."BLANCO" Proxima batalla                            "NEGRO"║\n");
	printf(NEGRO"                ║                 "ROJO" F."BLANCO" Finalizar partida                          "NEGRO"║\n");
	
	printf(NEGRO"                ╚");
	for(int i = 0; i < 64; i++)
		printf("═");
	printf("╝\n"BLANCO);
}

void menu_box_victoria_2(){

	cartel_juego();

	printf(NEGRO"                ╔");
	for(int i = 0; i < 64; i++)
		printf("═");
	printf("╗\n"BLANCO);

	printf(NEGRO"                ║"BLANCO"                           MENU VICTORIA                        "NEGRO"║\n");
	printf("                ╚");
	for(int i = 0; i < 64; i++)
		printf("═");
	printf("╝\n");

	printf(NEGRO"                ║                 "ROJO" C."BLANCO" Cambiar los Pokémon de batalla             "NEGRO"║\n");
	printf(NEGRO"                ║                 "ROJO" M."BLANCO" Ver medallas                               "NEGRO"║\n");
	printf(NEGRO"                ║                 "ROJO" N."BLANCO" Proxima batalla                            "NEGRO"║\n");
	printf(NEGRO"                ║                 "ROJO" F."BLANCO" Finalizar partida                          "NEGRO"║\n");
	
	printf(NEGRO"                ╚");
	for(int i = 0; i < 64; i++)
		printf("═");
	printf("╝\n"BLANCO);
}

void menu_box_derrota(){

	printf(NEGRO"                ╔");
	for(int i = 0; i < 64; i++)
		printf("═");
	printf("╗\n"BLANCO);

	printf(NEGRO"                ║"BLANCO"                            MENU DERROTA                        "NEGRO"║\n");
	printf("                ╚");
	for(int i = 0; i < 64; i++)
		printf("═");
	printf("╝\n");

	printf(NEGRO"                ║                 "ROJO" C."BLANCO" Cambiar los Pokémon de batalla             "NEGRO"║\n");
	printf(NEGRO"                ║                 "ROJO" R."BLANCO" Reintentar gimnasio                        "NEGRO"║\n");
	printf(NEGRO"                ║                 "ROJO" F."BLANCO" Finalizar partida                          "NEGRO"║\n");
	
	printf(NEGRO"                ╚");
	for(int i = 0; i < 64; i++)
		printf("═");
	printf("╝\n"BLANCO);
}

void volver_a_menu(){

	char inicial;
	char decision[MAX_LETRAS];

	printf("\n\nPresione "ROJO"M"BLANCO" para volver al Menu ");
	do{
	
		scanf("%s", decision);
		inicial = (char)toupper((int)decision[0]);

	}while(inicial != MENU);
}

void info_pokemon(nodo_t* pokemon, int id_pokemon){

	if(!pokemon) return;

	pokemon_t* poke = (pokemon_t*)pokemon->elemento;
	printf("\n"ROJO"%i Nombre:"BLANCO" %s"ROJO" Tipo:"BLANCO" %s"ROJO" Velocidad:"BLANCO" %i"ROJO" Ataque:"BLANCO" %i"ROJO" Defensa:"BLANCO" %i\n\n", id_pokemon, poke->nombre, poke->tipo, poke->velocidad, poke->ataque, poke->defensa);

	info_pokemon(pokemon->siguiente, id_pokemon+1);
}

void info_avatar(personaje_t* avatar){

	if(!avatar) return;

	system("clear");

	int i; 

	for(i = 0; i < 80; i++)
		printf(NEGRO"═"BLANCO);
	
	printf("\n\t\t\t\t%s\n", avatar->nombre);

	for(i = 0; i < 80; i++)
		printf(NEGRO"═"BLANCO);

	printf("\n\t\t\t\t   PARTY\n");

	for(i = 0; i < 80; i++)
		printf(NEGRO"═"BLANCO);
	printf("\n");

	info_pokemon(avatar->party->nodo_inicio, 0);

	for(i = 0; i < 80; i++)
		printf(NEGRO"═"BLANCO);

	printf("\n\t\t\t\t   CAJA\n");

	for(i = 0; i < 80; i++)
		printf(NEGRO"═"BLANCO);

	info_pokemon(avatar->caja->nodo_inicio, 0);

	for(i = 0; i < 80; i++)
		printf(NEGRO"═"BLANCO);
}

void info_entrenador(entrenador_t* entrenador){

	if(!entrenador) return;

	int i; 

	for(i = 0; i < 80; i++)
		printf(NEGRO"═"BLANCO);
	
	printf("\n%s\n", entrenador->nombre);
	if(entrenador->es_lider) printf("CATEGORIA: Lider\n");
	else printf("CATEGORIA: Entrenador\n");

	for(i = 0; i < 80; i++)
		printf(NEGRO"═"BLANCO);
	printf("\n");

	info_pokemon(entrenador->pokemon->nodo_inicio, 0);

	printf("\n");
	for(i = 0; i < 80; i++)
		printf(NEGRO"═"BLANCO);
	printf("\n");
}

void info_gimnasio(gimnasio_t* gimnasio, int id_batalla){

	if(!gimnasio) return;

	system("clear");

	int i;

	for(i = 0; i < 80; i++)
		printf(NEGRO"═"BLANCO);

	printf("\n\t\t\t%s\n", gimnasio->nombre);

	for(i = 0; i < 80; i++)
			printf(NEGRO"═"BLANCO);

	printf("\n"ROJO" Medalla:"BLANCO" %s\n"ROJO" Dificultad:"BLANCO" %i\n"ROJO" ID BATALLA:"BLANCO" %i\n", gimnasio->medalla, gimnasio->dificultad, gimnasio->id_batalla);

	mensaje_gimnasio(id_batalla);

	for(i = 0; i < 80; i++)
		printf(NEGRO"═"BLANCO);
}

void info_gimnasios(heap_t* heap){

	if(!heap) return;

	system("clear");

	int i, j;
	gimnasio_t* gimnasio_actual = NULL;

	for(i = 0; i < heap->tope; i++){
 
		gimnasio_actual = (gimnasio_t*)heap->vector[i];

		for(j = 0; j < 80; j++)
			printf(NEGRO"═"BLANCO);

		printf("\n\t\t\t%s\n", gimnasio_actual->nombre);

		for(j = 0; j < 80; j++)
			printf(NEGRO"═"BLANCO);

		printf("\n"ROJO" Medalla:"BLANCO" %s\n"ROJO" Dificultad:"BLANCO" %i\n"ROJO" ID BATALLA:"BLANCO" %i\n", gimnasio_actual->medalla, gimnasio_actual->dificultad, gimnasio_actual->id_batalla);

		mensaje_gimnasio(gimnasio_actual->id_batalla);
	}

	for(i = 0; i < 80; i++)
		printf(NEGRO"═"BLANCO);
}

void info_medallas(lista_t* medallas){

	if(!medallas) return;

	system("clear");

	int i;

	for(i = 0; i < 80; i++)
		printf(NEGRO"═"BLANCO);

	nodo_t* actual = medallas->nodo_inicio;
	for(i = 0; actual && i < medallas->cantidad; i++){

		printf("\n"ROJO" Medalla:"BLANCO" %s\n", (char*)actual->elemento);
		actual = actual->siguiente;
	}

	for(i = 0; i < 80; i++)
			printf(NEGRO"═"BLANCO);
}

void info_entrenadores_combate(personaje_t* avatar, entrenador_t* entrenador){

	if(!avatar || !entrenador) return;

	cartel_batalla();
	printf("\n                         %s", avatar->nombre);
	printf("          vs.        %s\n\n", entrenador->nombre);
	punio();
}

void info_combate(pokemon_t* poke_avatar, pokemon_t* poke_entrenador){

	if(!poke_avatar || !poke_entrenador) return;	

	cartel_combate();
	printf("                               %s", poke_avatar->nombre);
	printf("          vs.        %s\n\n", poke_entrenador->nombre);
	pikachus();
	printf(ROJO"			     Tipo:"BLANCO" %s"ROJO"		    Tipo:"BLANCO" %s\n"ROJO"			     Velocidad:"BLANCO" %i"ROJO"		    Velocidad:"BLANCO" %i\n"ROJO"			     Ataque:"BLANCO" %i"ROJO"		            Ataque:"BLANCO" %i\n"ROJO"			     Defensa:"BLANCO" %i"ROJO"		    Defensa:"BLANCO" %i\n\n", poke_avatar->tipo, poke_entrenador->tipo, poke_avatar->velocidad, poke_entrenador->velocidad, poke_avatar->ataque, poke_entrenador->ataque, poke_avatar->defensa, poke_entrenador->defensa);
	
	ir_a_combate();
}

void mostrar_pokemon_ganador(pokemon_t* ganador){

	if(!ganador) return;

	cartel_ganador();
	printf("                                Tu pokemon %s ha ganado!\n\n", ganador->nombre);
	pikachu();
}

void mostrar_pokemon_perdedor(pokemon_t* perdedor){

	if(!perdedor) return;

	cartel_perdida();
	printf("                                Tu pokemon %s ha perdido :(\n\n", perdedor->nombre);
	pikachu();
}

void aviso_cambio_poke(char* nombre_poke){

	printf("                             Pelearas con %s tu proxima batalla!\n\n", nombre_poke);
}

void maestro_pokemon(char* nombre_maestro){

	felicitaciones();
	printf("\n                          Eres nuestro nuevo Maestro Pokemon %s\n", nombre_maestro);
	medalla();
}

void derrota_simulacion(){

	system("clear");

	printf(MAGENTA" ____  _____ _____ _____ _____ _____ _____ ____  _____ \n");
	printf("|    \\|   __| __  | __  |     |_   _|  _  |    \\|     |\n");
	printf("|  |  |   __|    -|    -|  |  | | | |     |  |  |  |  |\n");
	printf("|____/|_____|__|__|__|__|_____| |_| |__|__|____/|_____|\n\n"BLANCO);
}