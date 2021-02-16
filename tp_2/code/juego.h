#ifndef __JUEGO_H__
#define __JUEGO_H__

#include "../toolbox/tools.h"
#include "../toolbox/tdas/lista.h"
#include "../toolbox/tdas/abb.h"
#include "../toolbox/tdas/heap.h"
#include "batallas.h"

#define MAX_STRING 50

#define MAX_MENU 5
#define MAX_OPC 4
#define MAX_STR 100

//tipo de listas
#define COMBATE 0
#define CAJA 1
#define ENTRENADOR 2

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

//apertura de archivos
#define LECTURA "r"
#define ESCRITURA "w"

//estado batalla
#define DERROTA -1
#define ESTADO_INICIAL 0
#define VICTORIA 1
#define PELEANDO 2

typedef struct pokemon{
    char nombre[MAX_STRING];
    int velocidad;
    int ataque;
    int defensa;
    bool elegido;
}pokemon_t;

typedef struct entrenador{
    char nombre[MAX_STRING];
    lista_t* pokemones;
}entrenador_t;

typedef struct personaje{
    char nombre[MAX_STRING];
    lista_t* caja; 
    lista_t* party; 
}personaje_t;

typedef struct gimnasio{
    int estado;
    char nombre[MAX_STRING];
    int dificultad;
    int id_batalla;
    pila_t* entrenadores; 
    size_t cant_entrenadores;
}gimnasio_t;

typedef void (*mostrar_batalla)(pokemon_t*, pokemon_t*, int);

typedef int (*funcion_batalla)(void*, void*);

/* Funciones para el funcionamiento del main y que requieran ser testeadas*/

personaje_t* personaje_cargar(void (*pedir_archivo)(char *));

/* 
*  Dado un personaje, lo destruye junto a todas sus estructuras
* Pre : Personaje creado
* Post: Personaje destruido e innutilizable
*/
void personaje_destruir(personaje_t* personaje);


heap_t* gimnasios_cargar(void (*pedir_archivo)(char *));

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

/* 
* Dado un heap, crea uno nuevo copiando su contenido pero sin perder el originals
* Pre : Heap creado y no vacio
* Post: Un nuevo heap con el contenido del anterior
*/
heap_t* copiar_heap (heap_t* heap);

#endif /* __AVENTURA_H__ */