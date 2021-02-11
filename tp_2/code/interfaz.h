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

//opciones menus
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


interfaz_t* interfaz_crear(size_t cant_menus);

void interfaz_destruir(interfaz_t* interfaz);

char interfaz_estado(interfaz_t* interfaz);

//ELIMINAR
void inicializar_interfaz(interfaz_t* interfaz);


void cargar_opcion(interfaz_t* interfaz, size_t tipo, char opcion, const char* descripcion);

/* 
* 
* Pre : Recibe lista de pokemones y una función para mostrarlos
* Post: Devuelve el puntero al pokemon seleccionado o 
        NULL en caso de volver para atrás
*/
void* pedir_pokemon(lista_t* pokemones);


void menu_inicio(interfaz_t* interfaz);
void menu_gimnasio(interfaz_t* interfaz, const char* gimansio);
void menu_batalla(interfaz_t* interfaz, pokemon_t* pkm_1, pokemon_t* pkm_2, int estado);
void menu_victoria(interfaz_t* interfaz);
void menu_derrota(interfaz_t* interfaz, const char* gimnasio);

/* 
* Muestra por pantalla el aviso de que ganó el juego
*/
void menu_maestro();

/* 
* 
* Pre : Recibe un vector de menús, el tipo de menú en el que se encuetra
        y la opcion que se desea eliminar
* Post: Eliminar del vector opciones (dentro del menu) a la opcion deseada
*/
void eliminar_opcion(interfaz_t* interfaz, size_t menu, char opcion);

#endif /* __INTERFAZ_H__ */