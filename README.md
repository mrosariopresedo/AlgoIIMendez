# TDA ABB

|  | |
| ----------- | ----------- |
| Fecha | 2C2020 |
| Universidad | Universidad de Buenos Aires - Facultad de Ingeniería |
| Cátedra | Méndez |
| Lenguaje | C |
| Compilación | `make` |
| Ejecución | `make exe` |
| Valgrind | `make val` | 

### Objetivo
Se pide implementar un **Arbol Binario de Búsqueda**. Para ello se brindan las firmas de las funciones públicas a implementar y se deja a criterio del alumno la creación de 
las funciones privadas del TDA para el correcto funcionamiento del Arbol cumpliendo con las buenas prácticas de programación. Adicionalmente se pide la implementación de un 
**iterador interno** para la estructura.

### Especificaciones

Inicialmente realizo pruebas que se enfocan en verificar que las funciones de la biblioteca *abb.h* reaccionen bien frente a situaciones como: un árbol nulo y un árbol 
vacío, esto es, que devuelvan los valores de respuesta correctos. En el caso de `arbol_buscar()` y `arbol_raiz()` es NULL, para `arbol_raiz()` false, para los recorridos y 
el iterador interno 0 y para `arbol_insertar()` y `arbol_borrar()` -1. Además, es interesante la idea de ver lo que se puede y no se puede hacer con un árbol nulo y un árbol 
vacío, es decir, las diferencias.

Luego, la idea es primero verificar las funciones principales que son `arbol_insertar()`, `arbol_borrar()`  y `arbol_buscar()`. Esto no solo da lugar a corroborar el correcto 
funcionamiento de las mismas, si no que da lugar a corroborar que funciones secundarias como `arbol_vacio()` y `arbol_raiz()` respondan también como se espera.

Por último, dado que ya se que las funciones anteriores responden bien, las utilizo para realizar pruebas sobre otro conjunto de funciones: `arbol_recorrido_inorden()`, 
`arbol_recorrido_preorden()`, `arbol_recorrido_postorden()` y `abb_con_cada_elemento()`.

A continuación menciono las analogías usadas en los mensajes de las pruebas:

- "Plantar" = Crear 🌲
- "No tiene vida" = nulo/a 🧬
- "Método de inspección" = comparador 🔍
- "Método de recolección" = destructor 🧺💐
- "No tiene frutos" o "Sin frutos" = vacío 🍊🌺🥑
- "Trepar" = recorrer 🧗🏽‍♀️
- "Crecer" = insertar 🌱
- "Recolectar" o "Arrancar" = borrar ✋🏽🧺💐
- "Control Iterador Interno Alimentario (CIIA)" = iterador interno 🔁
