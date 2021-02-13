#ifndef __JUEGO_H__
#define __JUEGO_H__

#include "../toolbox/tools.h"
#include "../toolbox/tdas/lista.h"
#include "../toolbox/tdas/abb.h"
#include "../toolbox/tdas/heap.h"
#include "batallas.h"

#define MAX_STRING 50
#define ESTADO_INICIAL -1

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

/* Funciones para el funcionamiento del main y que requieran ser testeadas*/

/* 
* Dado un archivo, crea un personaje con la información dentro
* Pre : Archivo abierto para lectura
* Post: Personaje creado en memoria dinámica
*/
personaje_t* cargar_personaje(FILE * archivo);

/* 
*  Dado un personaje, lo destruye junto a todas sus estructuras
* Pre : Personaje creado
* Post: Personaje destruido e innutilizable
*/
void personaje_destruir(personaje_t* personaje);

/* 
* Dado un archivo, crea un heap de gimnasios con la información dentro
* Pre : Archivo abierto para lectura
* Post: Heap minimal con todos los gimnasios dentro
*/
heap_t* cargar_gimnasios(FILE * archivo);

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
* Dada la posicion de un pokemon del conjunto del lider,
* lo transfiere a la caja del personaje
* Pre : Posicion del pokemon válida para la lista del lider, entrenador y personajes cargados
* Post: Caja del personaje con nuevo pokemon
*/
void tomar_pokemon(entrenador_t* lider, size_t posicion_pkm, personaje_t* personaje);
/* 
* Dadas dos posicones, una de un pokemon en el party y otro en la caja,
* Quita el pokemon del party para agregar el de la caja.
* Pre : Ambas posiciones de los pokemones que sean válidas, personaje cargado
* Post: Party con un intercambio de pokemones
*/
void intercambiar_pokemones(personaje_t* personaje, size_t pkm_party, size_t pkm_box);

/* 
* Realiza todas las batallas de un gimnasio 
* Pre : Gimnasio cargado y no vacío
* Post: Devuelve el gimnasio en el estado correspondiente
* (En caso de que gane, dejará el gimnasio con su lider)
*/
void gimanasio_luchar(gimnasio_t* gimnasio);

/* 
* Dado un heap, crea uno nuevo copiando su contenido pero sin perder el originals
* Pre : Heap creado y no vacio
* Post: Un nuevo heap con el contenido del anterior
*/
heap_t* copiar_heap (heap_t* heap);

#endif /* __AVENTURA_H__ */