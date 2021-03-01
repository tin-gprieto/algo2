#ifndef __INTERFAZ_H__
#define __INTERFAZ_H__

#include "../toolbox/tools.h"
#include "estructuras.h"

//Estados de la interfaz
#define OPCION_PERSONAJE 'E'
#define OPCION_AGREGAR_GYM 'A'
#define OPCION_INICIAR 'I'
#define OPCION_SIMULAR 'S'
#define OPCION_GIMNASIO 'G'
#define OPCION_CAMBIAR 'C'
#define OPCION_BATALLA 'B'
#define OPCION_AVANZAR 'N'
#define OPCION_TOMAR_PKM 'T'
#define OPCION_REPETIR 'R'
#define OPCION_SALIR 'F'
#define ESTADO_NULO ' '
<<<<<<< Updated upstream

=======
//tipos de menus
#define MENU_INICIO 0
#define MENU_GYM 1
#define MENU_BATALLA 2
#define MENU_VICTORIA 3
#define MENU_DERROTA 4
>>>>>>> Stashed changes
//tipo de listas para pedir
#define LISTA_COMBATE 0
#define LISTA_CAJA 1
#define LISTA_ENTRENADOR 2

//constantes
#define MAX_MENU 5
#define MAX_OPCIONES 4

typedef struct menu{
    char opciones[MAX_OPCIONES];
    char descripciones[MAX_OPCIONES][MAX_STRING];
    size_t cant_opciones;
}menu_t;

typedef struct interfaz{
    char estado;
    menu_t* menus;
}interfaz_t;

/* 
* Crea la interfaz en memoria dinamica
* Pre : -
* Post: puntero a interfaz lista para usarse o NULL en caso de algún error
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
* Pre : Interfaz creada y estado válido
* Post: Verdadero si el estado de la interfaz coincide con el pasado
* falso en el caso de no cumplirse
*/
bool interfaz_estado(interfaz_t* interfaz, char estado);

/* 
* Muestra el menu inicio y sus opciones
* Pre : Interfaz creada
* Post: Interfaz en el estado elegido por usuario
*/
void menu_inicio(interfaz_t* interfaz);

/* 
* Muestra el menu gimnasio y sus opciones
* Pre : Interfaz creada y nombre del gimnasio
* Post: Interfaz en el estado elegido por usuario 
*/
void menu_gimnasio(interfaz_t* interfaz, gimnasio_t* gimnasio);

/* 
* Muestra el menu batalla con la informacion de los pokemones
* Pre : Interfaz creada, los dos pokemones de la batalla y el resultado de la misma
* (Costantes VICTORIA y DERROTA)
* Post: Información por pantalla de la batalla
*/
void menu_batalla(pokemon_t* pkm_propio, pokemon_t* pkm_rival, int estado);

/* 
* Muestra el menu victoria y sus opciones
* Pre : Interfaz creada
* Post: Información por pantalla e interfaz en el estado elegido por usuario
*/
void menu_victoria(interfaz_t* interfaz);

/* 
* Muestra el menu derrota y sus opciones
* Pre : Interfaz creada y nombre del gimnasio en donde fue derrotado
* Post: Información por pantalla e interfaz en el estado elegido por usuario 
*/
void menu_derrota(interfaz_t* interfaz, gimnasio_t* gimnasio);

/* 
* Muestra por pantalla un aviso de que se superó el juego
* Pre : -
* Post: Información por pantalla
*/
void menu_maestro_pokemon();

/* 
* Elimina una de las opciones del menu;
* Pre : Recibe un vector de menús, el tipo de menú en el que se encuetra
* y la opcion que se desea eliminar
* Post: Eliminar del vector opciones (dentro del menu) a la opcion deseada
*/
void eliminar_opcion(interfaz_t* interfaz, size_t menu, char opcion);

<<<<<<< Updated upstream
/* 
=======
/*
* El menu victoria vuelve a su estado inicial 
* (luego de quitar la opción tomar pokemon)
* Pre : Haber quitado la opción tomar pokemon del menú victoria
* Post: Menú victoria reestablecido
*/
void reiniciar_menu_victoria(interfaz_t* interfaz);

/*
>>>>>>> Stashed changes
* Dada una lista de pokemones, la muestra completa por pantalla y
* devuelve la posicion del pokemon elegido por el usuario
* Pre : Recibe lista de pokemones cargada 
* Post: Información por pantalla y posicion del pokemon seleccionado 
*/
size_t pedir_pokemon(lista_t* pokemones, int lista);

/* 
* Pide una ruta de archivo al usuario y devuelve como parametro
* Pre : -
* Post: ruta válida del archivo (sin fallo de apertura)
*/
void pedir_archivo(char ruta_archivo[MAX_STRING]);

/* 
* Muestra por pantalla la informacion de personaje
* (nombre, caja de pokemones, party de pokemones)
* Pre : Personaje previamente cargado
* Post: Información por pantalla
*/
void personaje_informacion(personaje_t* personaje);

/* 
* Muestra por pantalla la informacion de gimnasio
* (nombre, dificultad, entrenadores restantes, informacion del entrenador siguiente)
* Pre : Gimnasio previamente cargado
* Post: Información por pantalla
*/
void gimnasio_informacion(gimnasio_t* gimnasio);

#endif /* __INTERFAZ_H__ */