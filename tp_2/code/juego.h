#ifndef __JUEGO_H__
#define __JUEGO_H__

#include "batallas.h"
#include "estructuras.h"
#include "interfaz.h"
#include "../toolbox/tools.h"

//funciones batalla
#define FUNCION_1 0
#define FUNCION_2 1
#define FUNCION_3 2
#define FUNCION_4 3
#define FUNCION_5 4
//estado juego
#define JUEGO_INICIO 0
#define JUEGO_JUGANDO 1
#define JUEGO_SIMULANDO 2
#define JUEGO_PERDIDO 4
#define JUEGO_GANADO 5
#define JUEGO_SALIR 6
//constantes
#define MAX_FUNCIONES 5
#define VACIO 0


typedef int (*funcion_batalla)(void*, void*);

typedef struct archivos{
    char ruta_personaje[MAX_STRING];
    char ruta_gimnasios[MAX_STRING];
}archivos_t;

typedef struct juego{
    int estado;
    personaje_t* personaje;
    heap_t* gimnasios;
    archivos_t archivos;
    interfaz_t* interfaz;
    funcion_batalla* funciones;
}juego_t;


/* 
* Crea la estructura del juego
* Pre : -
* Post: Estructura del juego creada en memoria dinámica, listo para ser iniciado
*/
juego_t* juego_crear();

/* 
* Destruye la estructura del juego por completo
* Pre : Juego creado
* Post: Memoria ocupada por el juego liberada
*/
void juego_destruir(juego_t* juego);

/* 
* Determina si el juego cumple las condiciones para iniciarse
* Pre : Juego creado
* Post: Verdadero si se han cargado un personaje y los gimnasios
*/
bool juego_preparado(juego_t* juego);

/* 
* Determina si el estado del juego coincide con el estado pasado
* Pre : Juego creado
* Post: Verdadero si el estado del juego y el estado coindiden
*/
int juego_estado(juego_t* juego, int estado);

/* 
* Cambia el estado del juedo dado un nuevo estado
* Pre : Juego creado
* Post: Juego con un nuevo estado
*/
void juego_cambiar_estado(juego_t* juego, int nuevo_estado);

/*
* Pide la ruta del archivo y agrega el personaje a la estructura del juego
* Pre : Juego creado e inicializado
* Post: Juego en el estado correspondiente
* (ERROR si no pudo cargar al personaje o INICIO si cargó el personaje)
*/
void juego_agregar_personaje(juego_t* juego);

/*
* Pide la ruta del archivo y agrega el personaje a la estructura del juego
* Pre : Juego creado e inicializado
* Post: Juego en el estado correspondiente
* (ERROR si no pudo cargar al personaje o INICIO si cargó el personaje)
*/
void juego_agregar_gimnasios(juego_t* juego);

/*
* Borra la raiz del heap de gimnasios y deja el juego en el estado correspondiente
* Pre : Juego creado e inicializado y gimnasios creados
* Post: Estado del juego que corresponda
*/
void juego_eliminar_gimnasio(juego_t* juego);

/* 
* Realiza todas las batalla de un gimnasio, informando al usuario de cada batalla, 
* según si se juegue manual o simulado 
* Pre : Gimnasio cargado y no vacío, personaje cargado, estado del juego correcto
* Post: Devuelve al gimnasio en su estado correspondiente
* (En caso de que gane, dejará el gimnasio con su lider)
*/
void jugar_gimnasio(juego_t* juego, gimnasio_t* gimnasio);

/* 
* Se ejecuta la opción de tomar un pokemon del lider
* (Muestra los pokemones del lider para que el usuario elija uno)
* Pre : Gimnasio creado y unicamento con el último entrenador(lider), funcion para pedir pokemones al usuario 
* Post: Devuelve la caja del personaje con un nuevo pokemón y el estado del juego
*/
void quitar_pokemon_lider(juego_t* juego);

/* 
* Se ejecuta la opción de cambiar el party
* (Muestra los pokemones del party 
* y la caja para que el usuario elija cual intercambiar)
* Pre : Personaje creado, funcion para pedir pokemones al usuario 
* Post: Devuelve el Party modificado y el estado del juego
*/
void cambiar_party(juego_t* juego);

#endif /* __JUEGO_H__ */