#ifndef __ESTRUCTURAS_H__
#define __ESTRUCTURAS_H__

#include "../toolbox/tools.h"

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
#define MAX_FUNCIONES 5
#define MAX_STRING 100
#define MAX_NOMBRE 30

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
    bool lider;
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
}gimnasio_t;

/*
* Recibe una ruta de archivo para abrir los datos de un personaje
* Pre : El archivo debe contar solo un entrenador que encabece la lista
* y que cuente con al menos un pokemon
* Post: Personaje creado según el archivo
* o NULL en caso de error de creación o formato del archivo
*/
personaje_t* personaje_cargar(char ruta_archivo[MAX_STRING]);

/* 
* Dado un personaje, lo destruye junto a todas sus estructuras
* Pre : Personaje creado
* Post: Personaje destruido e innutilizable
*/
void personaje_destruir(personaje_t* personaje);

/*
* Recibe una ruta de archivo para abrir los datos de un personaje
* Pre : El archivo debe contar con al menos un gimnasio, que cuente con un único líder y
* como mínimo con un entrenador
* Post: Heap de gimnasios creado según el archivo
* o NULL en caso de error de creación o formato del archivo
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
* Dado un gimnasio, avanza al próximo entrenador de la pila
* y destruyendo al entrenador anterior
* Pre : gimnasio creado y no vacío
* Post: gimnasio sin el entrenador del tope de la pila
*/
void gimnasio_siguiente_entrenador(gimnasio_t* gimnasio);

/*
* Devuelve verdadero si el gimnasio no tiene entrenadores
* Pre : Puntero a gimnasio_t
* Post: Verdadero si no hay entrenadores o no existe el gimnasio
*/
bool gimnasio_vacio(gimnasio_t* gimnasio);

#endif /* __ESTRUCTURA_H__ */