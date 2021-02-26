#ifndef __JUEGO_H__
#define __JUEGO_H__

#include "../toolbox/tools.h"
#include "../toolbox/tdas/lista.h"
#include "../toolbox/tdas/abb.h"
#include "../toolbox/tdas/heap.h"
#include "batallas.h"

//tipo de listas
#define COMBATE 0
#define CAJA 1
#define ENTRENADOR 2

//tipos de menus
#define MENU_INICIO 0
#define MENU_GYM 1
#define MENU_BATALLA 2
#define MENU_VICTORIA 3
#define MENU_DERROTA 4

//apertura de archivos
#define LECTURA "r"
#define ESCRITURA "w"

//estado batalla
#define DERROTA -1
#define ESTADO_INICIAL 0
#define VICTORIA 1
#define PELEANDO 2

//constantes
#define MAX_MENU 5
#define MAX_OPC 4
#define MAX_STR 100
#define MAX_NOMBRE 50

typedef struct pokemon{
    char nombre[MAX_NOMBRE];
    int velocidad;
    int ataque;
    int defensa;
    bool elegido;
    int nivel;
}pokemon_t;

typedef struct entrenador{
    char nombre[MAX_NOMBRE];
    lista_t* pokemones;
}entrenador_t;

typedef struct personaje{
    char nombre[MAX_NOMBRE];
    int medallas;
    lista_t* caja; 
    lista_t* party; 
}personaje_t;

typedef struct gimnasio{
    int estado;
    char nombre[MAX_NOMBRE];
    int dificultad;
    int id_batalla;
    pila_t* entrenadores; 
    size_t cant_entrenadores;
}gimnasio_t;

typedef void (*mostrar_batalla)(pokemon_t*, pokemon_t*, int);

typedef int (*funcion_batalla)(void*, void*);

/* Funciones para el funcionamiento del main y que requieran ser testeadas*/

personaje_t* personaje_cargar(char ruta_archivo[MAX_STR]);

/* 
*  Dado un personaje, lo destruye junto a todas sus estructuras
* Pre : Personaje creado
* Post: Personaje destruido e innutilizable
*/
void personaje_destruir(personaje_t* personaje);


heap_t* gimnasios_cargar(char ruta_archivo[MAX_STR]);

/* 
* Dado un gimansio y un estado, devuelve si el ambos coinciden
* Pre : Gimnasio cargado
* Post: Verdadero si el estado del gimnasio y el pasado coinciden
*/
bool gimnasio_estado(gimnasio_t* gimnasio, int estado);

/* 
* Dado un gimnasio y un nuevo estado, actualiza el estado del mismo
* Pre : Gimnasio cargado
* Post: Gimnasio con nuevo estado
*/
void gimnasio_cambiar_estado(gimnasio_t* gimnasio, int nuevo_estado);

/* 
* Dado un gimnasio devuelve el último entrenador que se encuentre en el mismo
* (próximo a ser enfrentado)
* Pre : Gimnasio cargado
* Post: Puntero a entrenador en última posicion
*/
entrenador_t* gimnasio_ultimo_entrenador(gimnasio_t* gimnasio);

/* 
* Realiza una batalla del gimnasio
* Pre : Gimnasio cargado y no vacío, personaje cargado, 
* funcion batalla corriespondiente al gimnasio y un menú batalla que muestre los datos de la misma
* Post: Devuelve el estado que debe tener el gimnasio
* (En caso de que gane, dejará el gimnasio con su lider)
*/
int gimnasio_batalla(gimnasio_t* gimnasio, personaje_t* personaje, funcion_batalla batalla, mostrar_batalla menu);


/* 
* Se ejecuta la opción de tomar un pokemon del lider
* (Muestra los pokemones del lider para que el usuario elija uno)
* Pre : Gimnasio creado y unicamento con el último entrenador(lider), funcion para pedir pokemones al usuario 
* Post: Caja del personaje con un nuevo pokemón
*/
void quitar_pokemon_lider(personaje_t* personaje, gimnasio_t* gimnasio, size_t (*pedir_pokemon)(lista_t*, int));

/* 
* Se ejecuta la opción de cambiar el party
* (Muestra los pokemones del party 
* y la caja para que el usuario elija cual intercambiar)
* Pre : Personaje creado, funcion para pedir pokemones al usuario 
* Post: Party modificado
*/
void cambiar_party(personaje_t* personaje, size_t (*pedir_pokemon)(lista_t*, int));

#endif /* __AVENTURA_H__ */