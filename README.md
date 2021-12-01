# ¡Gran Pesca Pokemon!

|  | |
| ----------- | ----------- |
| Fecha | 2C2020 |
| Universidad | Universidad de Buenos Aires - Facultad de Ingeniería |
| Cátedra | Méndez |
| Lenguaje | C |
| Compilación | `gcc *.c -Wall -Werror -Wconversion -std=c99 -o evento_pesca` |
| Ejecución | `./evento_pesca` |
| Valgrind | `valgrind --leak -check=full --track -origins=yes --show -reachable=yes ./evento_pesca` | 

## Introducción

Los pokémon son unas criaturas que se encuentran en la naturaleza. Se clasifican en 18 tipos (planta, fuego, agua, volador, tierra, etc). Cada pokémon tiene una cantidad determinada de movimientos o ataques que puede aprender, los cuales se pueden clasificar por su tipo o elemento (por ejemplo, el ataque rayo burbuja es un ataque tipo agua). Además, los pokémon cuentan con diferentes atributos que los distinguen de otros pokémon de la misma especie: Velocidad, Color, Peso, entre otros.

Los entrenadores pokémon, tienen como meta cumplir dos objetivos: capturar a todas las especies de pokémon disponibles y completar así la información de todos los pokémon en la Pokédex (Enciclopedia Pokémon). Por otro lado, deben entrenarlos y enfrentarlos a pokémones pertenecientes a otros entrenadores para demostrar sus habilidades, fortalezas, talentos y así convertirse en un Maestro Pokémon.

Para cumplir la primer meta, los entrenadores viajan a lo largo y ancho de las regiones del mundo, capturando los diferentes pokémon que encuentran en su camino. Hoy los entrenadores se encontrarán con la oportunidad de capturar pokémon de tipo agua de una manera distinta a la usual...

## Objetivo

El presente trabajo tiene como finalidad que el alumno repase algunos de los conocimientos adquiridos en Algoritmos y Programación I, así como también que comience a familiarizarse con las herramientas a utilizar a lo largo de la materia, tales como el manejo de memoria dinámica y la utilización de punteros a funciones.

## Enunciado

La líder de gimnasio Misty organizó un evento de pesca que se llevará a cabo en su acuario, ubicado en Ciudad Celeste. Para ello necesitará muchos y muy variados pokémon de tipo agua. El lugar indicado en Kanto para obtener a todos estos pokémon es el arrecife que rodea a las Islas Espuma. Para realizarlo, te pide que la ayudes a trasladar los pokémon seleccionados desde el arrecife a su acuario, donde será realizado el evento. A Misty le preocupa perjudicar la población de las especies más vulnerables, es por ello que te pide realizar una simulación del arrecife, pudiendo ver como quedará su estado dependiendo de qué especies se elijan para el evento.

Las funcionalidades que se deben implementar se detallan en evento_pesca.h. Los pokémon pertenecientes al arrecife se encontrarán en el archivo arrecife.txt cuya ruta llega como parámetro. El archivo tendrá el siguiente formato: especie;velocidad;peso;color. Los pokémon que estén registrados en el acuario de Misty serán guardados en un archivo acuario.txt con el mismo formato.


