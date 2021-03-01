#ifndef __ESTRUCTURAS_H__
#define __ESTRUCTURAS_H__

#include "../toolbox/tools.h"
<<<<<<< Updated upstream
#include "../toolbox/tdas/lista.h"
#include "../toolbox/tdas/abb.h"
#include "../toolbox/tdas/heap.h"

//tipos de menus
#define MENU_INICIO 0
#define MENU_GYM 1
#define MENU_BATALLA 2
#define MENU_VICTORIA 3
#define MENU_DERROTA 4
=======
>>>>>>> Stashed changes

//apertura de archivos
#define LECTURA "r"
#define ESCRITURA "w"

//estado gimnasios
#define GIMNASIO_DERROTA -1
#define GIMNASIO_PELEANDO 0
#define GIMNASIO_VICTORIA 1

//estado batalla
#define BATALLA_DERROTA -1
#define BATALLA_VICTORIA 0

//constantes
#define MAX_STRING 100
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
<<<<<<< Updated upstream
    pila_t* entrenadores; 
    size_t cant_entrenadores;
=======
    pila_t* entrenadores;
>>>>>>> Stashed changes
}gimnasio_t;

/* Funciones para el funcionamiento del main y que requieran ser testeadas*/

/*
* 
* Pre :
* Post:
*/
personaje_t* personaje_cargar(char ruta_archivo[MAX_STRING]);

/* 
*  Dado un personaje, lo destruye junto a todas sus estructuras
* Pre : Personaje creado
* Post: Personaje destruido e innutilizable
*/
void personaje_destruir(personaje_t* personaje);

/*
* 
* Pre :
* Post:
*/
heap_t* gimnasios_cargar(char ruta_archivo[MAX_STRING]);

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
*
* Pre :
* Post:
*/
void gimnasio_siguiente_entrenador(gimnasio_t* gimnasio);


#endif /* __ESTRUCTURA_H__ */