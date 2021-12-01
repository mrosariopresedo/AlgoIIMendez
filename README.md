# ¡Una Aventura Pokemon!

|  | |
| ----------- | ----------- |
| Fecha | 2C2020 |
| Universidad | Universidad de Buenos Aires - Facultad de Ingeniería |
| Cátedra | Méndez |
| Lenguaje | C |
| Compilación | `make` |
| Ejecución | `make exe` |
| Valgrind | `make val` | 

## Introducción

La aventura Pokémon (Pokémon journey en inglés) es como se conoce al viaje emprendido por un entrenador Pokémon desde su pueblo o ciudad natal a lo largo del mundo Pokémon con un objetivo. Este consiste generalmente en capturar y entrenar Pokémon, y hacerlos combatir contra otros entrenadores Pokémon y líderes de gimnasio para probar sus habilidades. Este objetivo culmina participando en la Liga Pokémon de su región, obteniendo previamente las ocho medallas que dan acceso a esta. Todos los entrenadores Pokémon inician su travesía a la edad de 10 años, siendo capaces de recibir su Pokémon inicial a manos de un profesor Pokémon, desde allí pueden elegir su camino y a qué se dedicarán en su aventura, dando importancia al entrenamiento de los Pokémon.

## Objetivo

El presente trabajo práctico tiene como finalidad que el alumno se familiarice con las diferentes estructuras de datos dinámicas implementadas, aplicándolas a un problema concreto y poniendo en práctica su uso integrado.

## Enunciado

Los Alto Mando de todas las regiones se han reunido en una asamblea de carácter urgente: Los líderes regionales están notando una preocupante caída de interés por parte de los jóvenes en convertirse en maestros Pokémon. Debido a las nuevas tecnologías, el interés por los nuevos videojuegos ha aumentado rotundamente, con títulos como 'PacMon' y 'Mankey Kong' que han cautivado a miles de niños y niñas en todo el mundo, han provocado que cada día hayan menos niñxs jugando afuera con los pokémon y comenzando su camino como maestro Pokémon. Es por esto que te han contactado para que lleves a cabo el primer videojuego de aventura sobre convertirse en maestro pokémon.

El **objetivo del videojuego** es simular el camino que se realiza para convertirse en maestro Pokémon. Para esto, es necesario obtener todas y cada una de las medallas de la región, comenzando con los gimnasios más sencillos y avanzando hacia los más difíciles.

La estructura general del trabajo práctico consistirá en:
1. Un heap con los gimnasios de la región.
2. Un personaje principal.
3. Lógica de combate pokémon.

### Heap de gimnasios

Los gimnasios serán cargados desde un archivo, o múltiples archivos progresivamente, es decir:

```C
/* Ejemplo carga de gimnasios */
cargar_gimnasio("gimnasios_kanto/gimnasio_brock.txt");
cargar_gimnasio("gimnasios_kanto/gimnasio_misty.txt");
...
cargar_gimnasio("gimnasios_kanto/gimnasio_giovanni.txt");
```

Este heap debe estar ordenado mediante dificultad del gimnasio, y se deberá poder recorrer siguiendo un orden creciente, es decir: del más sencillo al más difícil. Las batallas en los gimnasios serán funciones y se definirán con un id en el archivo del gimnasio. Las firmas se encuentran en el archivo batallas.h y las definiciones tendrán que ser realizadas en un archivo batallas.c.

Las estructuras tendrán que ser definidas, tomando la decisión adecuada para cada estructura de datos a utilizar, lo que quiere decir que se evaluará cómo se utilizan los TDA's implementados en la materia. 

El formato del archivo de gimnasio será el siguiente:

```
/* Formato gimnasio */
G;nombre_gimnasio; dificultad; id_puntero_funcion
L;nombre_lider
P;nombre_pokemon1; velocidad; ataque; defensa
P;nombre_pokemon2; velocidad; ataque; defensa
P;nombre_pokemon3; velocidad; ataque; defensa
E;nombre_entrenador1
P;nombre_pokemon1; velocidad; ataque; defensa
P;nombre_pokemon2; velocidad; ataque; defensa
E;nombre_entrenador2
P;nombre_pokemon1; velocidad; ataque; defensa
...
```

Siendo:
- G: Gimnasio
- L: Lider
- P: Pokémon
- E: Entrenador

Los pokémon que se encuentren entre dos entrenadores pertenecerán al entrenador de arriba. Y las batallas se realizarán de forma creciente, lo que quiere decir que el orden de enfrentamiento será: entrenador_2->entrenador_1 ->líder.

### Personaje Principal

El personaje principal contará con un conjunto de Pokémon obtenidos y con otro conjunto de hasta 6 Pokémon para combatir. Tendrá la posiblidad de actualizar la elección de Pokémon que combatirán intercambiando entre este conjunto y el conjunto de Pokémon obtenidos.

La estructura del personaje principal tendrá que ser organizada, eligiendo adecuadamente cómo almacenar los diferentes conjuntos de Pokémon.
```C
typedef struct personaje personaje_t;
```

Al comienzo, los pokemones del entrenador estarán en un archivo con el siguiente formato:
```
/* Ejemplo formato de entrenador principal */
E;Ash
P;Pikachu ;70;30;30
P;Butterfree ;50;40;50
P;Pidgeotto ;65;40;30
P;Bulbasaur ;20;40;30
P;Charmander ;40;30;20
P;Squirtle ;30;20;40
P;Krabby ;20;30;20
P;Raticate ;30;50;20
P;Haunter ;40;60;20
P;Primeape ;50;60;30
P;Muk ;20;40;60
```

Este archivo se deberá interpretar de la siguiente forma:
1. Si hay menos de 6 pokémon, entonces, todos ellos se almacenan en el conjunto de pokemon_para_combatir
2. Si hay más de 6 pokémon, los primeros 6 irán al conjunto de pokemon_para_combatir y todos los demás irán al conjunto de pokemon_obtenidos
Y a medida que se avance en la aventura se irán consiguiendo más.

### Batalla frente a un gimnasio

Para ganar un gimnasio se debe derrotar a todos los entrenadores y, por último, al líder. Cada vez que un pokémon del usuario gane una batalla, este será recompensado con una mejora de sus características: cada combate ganado aumenta en 1 todas las características. El máximo valor posible para el bonificador será de 63 puntos.

Si se sufre una derrota, contra un líder o contra un entrenador se podrá:
1. Rearmar tu equipo eligiendo nuevos Pokémon para combatir y reintentar el mismo combate.
2. Terminar la partida.

Si, en cambio, se ha ganado el contra el líder se podrá:
1. Tomar prestado (NO ROBAR) como premio un Pokémon del líder que acabas de derrotar para incorporarlo a tus Pokémon obtenidos.
2. Avanzar al siguiente combate, teniendo la posibilidad de intercambiar Pokémon de tu conjunto de combate por algún Pokémon de tu conjunto de obtenidos.

Aclaración: una vez derrotado un entrenador rival no se volverá a combatir con él. Sin embargo, si se ha derrotado a un Pokémon del entrenador rival pero no a todos ellos se deberá repetir el combate, es decir, se deberá volver a combatir con el Pokémon que antes fue derrotado.

Una vez que se alcanzaron las medallas del juego (es decir, se ganaron todos los gimnasios), se terminará la partida informando al usuario del logro.

Además, también se pide en el trabajo práctico que se incluya la funcionalidad de simular una partida, para lo cual, no se pedirá ninguna entrada por teclado, jugándose así todos los combates hasta ganar o perder, mostrando al usuario hasta dónde se llegó.
En esta modalidad se tomarán los primeros 6 Pokémon del archivo y sólo se utilizarán esos, es decir, no habrán reemplazos, ni tampoco se tomará prestado del líder un Pokémon.

### Interacción con el usuario

El programa debe comunicarse con el usuario a través de diferentes menús.

#### Menú de inicio
- E: Ingresa el archivo del entrenador principal.
- A: Agrega un gimnasio al árbol de gimnasios.
- I: Comienza la partida.
- S: Simula la partida.

#### Menú de gimnasio
- E: Muestra al entrenador principal junto a sus Pokémon.
- G: Muestra la información del gimnasio actual.
- C: Permite cambiar los Pokémon de batalla.
- B: Realiza la próxima batalla planificada.
	- Si se derrotó al líder del gimnasio se deberá mostrar el Menú de victoria
	- Si se sufre una derrota frente a cualquier entrenador se deberá mostrar el Menú de derrota.

#### Menú de Batalla
Aquí se mostrará la información de la batalla, Pokémon vs Pokémon. Deberá ser informativa: mostrar cuál es el Pokémon del rival y cuál es el tuyo, sus características y el resultado del combate.
- N: Próximo combate.

#### Menú de victoria
- T: Toma un Pokémon del líder y lo incorpora en los Pokémon obtenidos del jugador.
	- Una vez realizada dicha operación, esta opción desaparece del menú.
- C: Permite cambiar los Pokémon de batalla.
- N: Próximo gimnasio.
	- Si no hay próximo gimnasio, se deberá notificar al usuario que se convirtió en Maestro Pokémon.

#### Menú de derrota
- C: Permite cambiar los Pokémon de batalla.
- R: Reintenta el gimnasio.
- F: Finaliza la partida.

## Especificaciones

En esta ocasión, me concentre en lograr un código robusto, donde haya la menor posibilidad de error. Mi objetivo era tener en cuenta todos los casos posibles, por ejemplo, en donde pueda fallar la lectura de un archivo, donde pueda haber problemas con la memoria o que el usuario tenga la opción de salir de una determinada instancia sin tener que cerrar abruptamente el programa.

A continuación, justificare el uso de Lista y Pila para mi trabajo practico:

- ***Lista***: utilice el TDA Lista para los pokemon del PARTY y CAJA de un avatar porque era el que dejaba las tareas mas simples gracias al fácil acceso del mismo. Por ejemplo, al momento de intercambiar un pokemon entre una categoría u otra, cuando hay que batallar contra un entrenador el recorrido se realiza mas fácilmente (ademas, provee un iterador externo que es útil en dicho momento) o, por ejemplo, si hay que agregar un pokemon a la lista cuando se "roba" uno del líder. Ademas requiere de menos memoria que otras estructuras vistas en la materia 

	También use lista para las medallas. En un momento fue opción un vector de strings, pero hubiera sido mas rebuscado al momento de insertar una medalla obtenida en una batalla. Tener el TDA ya implementado simplifico muchas de las tareas para este trabajo practico, ya que se trata simplemente de hacer una llamada a una función y la misma se encarga de lo que necesitas.

- ***Pila***: en un archivo de gimnasio, el líder se encuentra primero en la lista de entrenadores. Este formato es un problema ya que según la lógica las batallas se realizan en orden creciente con respecto a los entrenadores, la ultima batalla en un gimnasio debe ser contra el líder.  El TDA Pila nos provee una estructura ideal para esta situación. Cuando leemos un entrenador de un archivo simplemente lo apilamos en la pila de entrenadores de un gimnasio. De esta manera, el líder siempre quedara en el fondo de la pila e iremos jugando contra el entrenador que se encuentre en el tope. Así, el líder, sera la ultima batalla del gimnasio.

- ***Heap Minimal***: el TDA Heap es útil cuando se trata de los gimnasios porque permite siempre tener en la raíz el gimnasio de menor dificultad, lo cual es útil al momento de jugar una partida porque se debe jugar del mas fácil al mas difícil.

Algunas aclaraciones:

1. Avatar == Personaje == Entrenador Principal.
2. Una vez cargado un archivo de gimnasio/s no se puede/n eliminar, solo agregar.
3. Los avatares están en una carpeta que se llama avatares, dentro de la carpeta ***Juego***. Por lo tanto al momento de cargar un avatar, si es que se desea utilizar uno de ellos, hay que ingresar como ruta `avatares/nombre_del_archivo.txt`. 
4. Los gimnasios están en una carpeta que se llama gimnasios, dentro de la carpeta ***Juego***. Por lo tanto al momento de cargar un/os gimnasio/s, si es que se desea utilizar uno de ellos, hay que ingresar como ruta `gimnasios/nombre_del_archivo.txt`.   En total son 8, ya que en el juego original hay que derrotar 8 gimnasios para convertirte en Maestro Pokemon. 
5. El ***TDA Entrenador*** es el principal ya que contiene la estructura de un entrenador y un pokemon. La misma se utilizara en el ***TDA Avatar*** para los pokemon y en el ***TDA Gimnasio*** para los entrenadores (y sus pokemon) del mismo.
6. La carpeta ***Gimnasio*** contiene el ***TDA Gimnasio***, un programa de pruebas y archivos erróneos para verificar que el mismo funcione correctamente. También adjunto un makefile para correr las pruebas (las instrucciones son las mismas mencionadas arriba, personalizadas para las pruebas del gimnasio).
7. La carpeta ***Entrenador*** contiene el ***TDA Entrenador*** y un programa de pruebas para verificar que el mismo funcione correctamente. También adjunto un makefile para correr las pruebas (las instrucciones son las mismas mencionadas arriba, personalizadas para las pruebas del entrenador).
8. La carpeta ***Avatar*** contiene el ***TDA Avatar***, un programa de pruebas y archivos erróneos para verificar que el mismo funcione correctamente. También adjunto un makefile para correr las pruebas (las instrucciones son las mismas mencionadas arriba, personalizadas para las pruebas del avatar). 
	- Las funciones `pokemon_agregar()`, `pokemon_intercambiar()`, `pokemon_entrenar()` y `medalla_agregar()` se prueban junto con el funcionamiento del juego. Las pruebas de este TDA están orientadas a la creación, lectura y destrucción correcta de un avatar. La función `pokemon_cargar()` lee con el siguiente formato: 
    
	```c
    	P;nombre;tipo;velocidad;ataque;defensa
    	```
    
9. La carpeta ***Heap*** contiene el ***TDA Heap*** y un programa de pruebas. También adjunto un makefile para correr las pruebas (las instrucciones son las mismas mencionadas arriba, personalizadas para las pruebas del heap). 
10. La carpeta ***Juego*** contiene todo lo necesario para poder jugar a ***Pokemon Adventure***. También adjunto un makefile para correr el programa (las instrucciones son las mencionadas arriba). 
11. La biblioteca ***Interfaz*** contiene todo lo relacionado a mostrar información por pantalla.
12. La biblioteca ***Juego*** contiene todo lo relacionado al flujo del juego y los menús, como también la interacción con el usuario.
13. La ***Unidad de Control*** es simplemente el punto de inicio del juego.
14. En la función `menu_inicio()`, cuando hardcodeo para que la opción sea `AGREGAR_AVATAR` es para que no salga del Menú Inicio.
15. Cuando se muestra la información de los gimnasios, también se muestran pistas sobre las batallas contra los mismos. Esto permite armar una estrategia para batallar.
