# TDA LISTA SE, PILA Y COLA

|  | |
| ----------- | ----------- |
| Fecha | 2C2020 |
| Universidad | Universidad de Buenos Aires - Facultad de Ingeniería |
| Cátedra | Méndez |
| Lenguaje | C |
| Compilación | gcc *.c -g -Wall -Wconversion -Werror -Wtype-limits -pedantic -O0 -o lista |
| Ejecución | ./lista |
| Valgrind | valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./lista | 

### Objetivo

Se pide implementar una **Lista Simplemente Enlazada**. Para ello se brindan las firmas de las funciones públicas a implementar y se deja a criterio del alumno la creación de las 
funciones privadas del TDA para el correcto funcionamiento de la Lista cumpliendo con las buenas prácticas de programación. Dentro de este TDA, se pide incluir también la 
implementación de las funciones básicas de los **TDAs Pila y Cola**, cumpliendo así que este satisfaga el comportamiento de las tres estructuras. Adicionalmente se pide la creación
de un **iterador interno** y uno **externo** para la lista.

en el caso de las **pruebas** el objetivo fue siempre respetar la *anatomía de una prueba*. Esto es: inicialización, afirmación, destrucción. También usé mucho las 
funciones de la biblioteca con el propósito de hacer más legible el código y poner todo el conjunto de funciones a prueba en determinados momentos, ya que justamente lo 
importante es que funcionen en conjunto. Al principio corro las pruebas que son comúnes a todas o varias funciones de la biblioteca y luego me enfoco mas en una implementación 
en especifico.

Dado que **PILA** y **COLA** son casos particulares de lista, reutilicé las funciones relacionadas con una lista para la implementación de las mismas. Para las pruebas me 
enfoque en verificar que se cumplan las políticas de entrada y salida de datos, esto es **LIFO** y **FIFO**, respectivamente, y en utilizar únicamente las funciones relacionadas
con PILA y COLA (a excepción de `lista_elementos()` que nos brinda también información sobre las mismas respetando los limites de lo que uno puede conocer de una PILA y una 
COLA).

Con respecto a los valores de retorno, en las funciones: `lista_borrar()`, `lista_borrar_de_posicion()`, `lista_elemento_en_posicion()` y `lista_ultimo()`, cuando recibo una 
lista vacía devuelvo lo que para dicha función es considerado un error, en el caso de las dos primeras **-1** y en las restantes, **NULL**. Esto es porque si una lista no 
contiene elementos, no hay ningún elemento que se pueda borrar o pueda ser devuelto como retorno de una función. 

Sobre *iteradores*, en `lista_iterador_avanzar()` una vez que llego al ultimo elemento y quiero avanzar, devuelvo **falso**. De todas maneras avanzo igual hasta NULL, ya 
que `lista_iterador_tiene_siguiente()` recién devuelve **falso** cuando corriente no existe mas, y `lista_iterador_elemento_actual()` también, solo que en vez de devolver 
falso devuelve **NULL**. 

Por último, en mis_pruebas.c hay una función `imprimir_lista()` en caso de que se necesite para verificar el contenido de una lista. Uso la  especificación de formato para 
int porque trabaje siempre con enteros, pero esto puede ser modificado sin problema.
