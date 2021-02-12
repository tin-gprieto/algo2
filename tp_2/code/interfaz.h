#ifndef __INTERFAZ_H__
#define __INTERFAZ_H__

#include "../toolbox/tools.h"
#include "../toolbox/tdas/lista.h"
#include "../toolbox/tdas/abb.h"
#include "../toolbox/tdas/heap.h"
#include "juego.h"

#define MAX_OPC 4
#define MAX_MENU 5
#define MAX_STR 100
#define COMBATE 0
#define CAJA 1
#define ENTRENADOR 2
#define ENTRENADOR_2 3

//Estados de la interfaz
#define PERSONAJE 'E'
#define AGREGAR_GYM 'A'
#define INICIAR 'I'
#define SIMULAR 'S'
#define GIMNASIO 'G'
#define CAMBIAR 'C'
#define BATALLA 'B'
#define AVANZAR 'N'
#define TOMAR_PKM 'T'
#define REPETIR 'R'
#define SALIR 'F'
#define ESTADO_NULO ' '

//tipos de menus
#define MENU_INICIO 0
#define MENU_GYM 1
#define MENU_BATALLA 2
#define MENU_VICTORIA 3
#define MENU_DERROTA 4

#define DERROTA -1
#define VICTORIA 1

typedef struct menu{
    char opciones[MAX_OPC];
    char descripciones[MAX_OPC][MAX_STR];
    size_t cant_opciones;
}menu_t;

typedef struct interfaz{
    char estado;
    menu_t* menus;
    size_t cant_menus;
}interfaz_t;

/* 
* Crea la interfaz en memoria dinamica
* Pre : -
* Post: Interfaz lista para usarse
*/
interfaz_t* interfaz_crear();

/* 
* Destruye el espacio asignado a la interfaz y a los menus
* Pre :  Interfaz creada
* Post:  Memoria liberada
*/
void interfaz_destruir(interfaz_t* interfaz);

/* 
* Devuelve el estado actual de la interfaz
* (Modo en el que debe ejecutarse según lo elegido por el usuario)
* Pre : Interfaz creada
* Post: Constante(letra) que representa el estado
*/
char interfaz_estado(interfaz_t* interfaz);

/* 
* Muestra el menu inicio y sus opciones
* Pre : Interfaz creada
* Post: Interfaz en el estado elegido por usuario
*/
void menu_inicio(interfaz_t* interfaz);

/* 
* Muestra el menu gimansio y sus opciones
* Pre : Interfaz creada y nombre del gimansio
* Post: Interfaz en el estado elegido por usuario 
*/
void menu_gimnasio(interfaz_t* interfaz, const char* gimansio);

/* 
* Muestra el menu batalla con la informacion de los pokemones
* Pre : Interfaz creada, los dos pokemones de la batalla y el resultado de la misma
* (Costantes VICTORIA y DERROTA)
* Post: Información por pantalla de la batalla
*/
void menu_batalla(interfaz_t* interfaz, pokemon_t* pkm_1, pokemon_t* pkm_2, int estado);

/* 
* Muestra el menu victoria y sus opciones
* Pre : Interfaz creada
* Post: Información por pantalla e interfaz en el estado elegido por usuario
*/
void menu_victoria(interfaz_t* interfaz);

/* 
* Muestra el menu derrota y sus opciones
* Pre : Interfaz creada y nombre del gimansio en donde fue derrotado
* Post: Información por pantalla e interfaz en el estado elegido por usuario 
*/
void menu_derrota(interfaz_t* interfaz, const char* gimnasio);

/* 
* Muestra por pantalla un aviso de que se superó el juego
* Pre : -
* Post: Información por pantalla
*/
void menu_maestro();

/* 
* Elimina una de las opciones del menu;
* Pre : Recibe un vector de menús, el tipo de menú en el que se encuetra
* y la opcion que se desea eliminar
* Post: Eliminar del vector opciones (dentro del menu) a la opcion deseada
*/
void eliminar_opcion(interfaz_t* interfaz, size_t menu, char opcion);

/* 
* Dada una lista de pokemones, la muestra completa por pantalla y
* devuelve la posicion del pokemon elegido por el usuario
* Pre : Recibe lista de pokemones cargada 
* Post: Información por pantalla y posicion del pokemon seleccionado 
*/
size_t pedir_pokemon(lista_t* pokemones, int lista);

/* 
* Pide una ruta de archivo al usuario y devuelve el archivo abierto
* Pre : archivo FILE* sin usar
* Post: archivo abierto para lectura
*/
void pedir_archivo(FILE* archivo);

/* 
* Muestra por pantalla la informacion de personaje
* (nombre, caja de pokemones, party de pokemones)
* Pre : Personaje previamente cargado
* Post: Información por pantalla
*/
void informacion_personaje(personaje_t* personaje);

/* 
* Muestra por pantalla la informacion de gimnasio
* (nombre, dificultad, entrenadores restantes, informacion del entrenador siguiente)
* Pre : Gimnasio previamente cargado
* Post: Información por pantalla
*/
void informacion_gimnasio(gimnasio_t* gimnasio);

#endif /* __INTERFAZ_H__ */