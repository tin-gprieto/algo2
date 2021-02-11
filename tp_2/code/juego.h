#ifndef __JUEGO_H__
#define __JUEGO_H__

#include "../toolbox/tools.h"
#include "../toolbox/tdas/lista.h"
#include "../toolbox/tdas/abb.h"
#include "../toolbox/tdas/heap.h"
#include "batallas.h"

#define MAX_STRING 50

typedef struct pokemon{
    char nombre[MAX_STRING];
    int velocidad;
    int ataque;
    int defensa;
    bool elegido;
}pokemon_t;

typedef struct entrenador{
    char nombre[MAX_STRING];
    lista_t* pokemones; //Cola
}entrenador_t;

typedef struct personaje{
    char nombre[MAX_STRING];
    lista_t* caja; //Lista
    lista_t* party; //Cola
}personaje_t;

typedef struct gimnasio{
    char nombre[MAX_STRING];
    int dificultad;
    int id_batalla;
    lista_t* entrenadores; //Pila
}gimnasio_t;

/* Funciones para el funcionamiento del main y que requieran ser testeadas*/

#endif /* __AVENTURA_H__ */