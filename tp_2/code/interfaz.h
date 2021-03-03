#ifndef __INTERFAZ_H__
#define __INTERFAZ_H__

#include "../toolbox/tools.h"
#include "estructuras.h"
#include "batallas.h"

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
//tipos de menus
#define MENU_INICIO 0
#define MENU_GYM 1
#define MENU_INTERCAMBIO 2
#define MENU_VICTORIA 3
#define MENU_DERROTA 4
//tipo de listas para pedir
#define LISTA_COMBATE 0
#define LISTA_CAJA 1
#define LISTA_ENTRENADOR 2
//estados simulacion
#define SIMULACION_INICIO 0
#define SIMULACION_FIN 1
#define SIMULACION_ENTRENADOR 2
#define SIMULACION_GIMNASIO 3
//archivos
#define ARCHIVO_PERSONAJE 1
#define ARCHIVO_GIMNASIO 2
//constantes
#define MAX_MENU 5
#define MAX_OPCIONES 5

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
* Dado un nuevo estado cambia el estado actual de la interfaz
* Pre : Interfaz creada
* Post: Interfaz con nuevo estado
*/
void interfaz_cambiar_estado(interfaz_t* interfaz, char nuevo_estado);

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
void menu_gimnasio(interfaz_t* interfaz, heap_t* gimnasio);

/* 
* Muestra el menu batalla con la informacion de los pokemones
* Pre : Rival creado, la posicion válida del pokemon del rival,
* pokemon propio creado e inicializado y el resultado de la batalla
* (Costantes GANO_PRIMERO y GANO_SEGUNDO)
* Post: Información por pantalla de la batalla
*/
void menu_batalla(entrenador_t* rival, size_t pos_pkm_rival, pokemon_t* pkm_propio, int estado);

/* 
* Muestra la información de la batalla para una simulacion
* Pre : Rival creado, la posicion válida del pokemon del rival,
* pokemon propio creado e inicializado y el resultado de la batalla
* (Costantes GANO_PRIMERO y GANO_SEGUNDO)
* Post: Información por pantalla de la batalla
*/
void menu_batalla_simulada(pokemon_t* pkm_rival, pokemon_t* pkm_propio, int estado);

/* 
* Según el momento del juego muestra información sobre la simulación
* Pre : Tipo de menu válido (constantes SIMULACION) y gimnasio/entrendor 
* existente si corresponde
* Post: Información por pantalla de la simulación
*/
void menu_simulacion(int tipo_menu, gimnasio_t* gimnasio, entrenador_t* rival);

/* 
* Muestra el menu intercambio (información de las listas) y sus opciones
* Pre : Interfaz creada, personaje creado, cambio de party realizado
* Post: Información por pantalla e interfaz en el estado elegido por usuario
*/
void menu_intercambio(interfaz_t* interfaz, personaje_t* personaje);

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

/*
* El menu victoria vuelve a su estado inicial 
* (luego de quitar la opción tomar pokemon)
* Pre : Haber quitado la opción tomar pokemon del menú victoria
* Post: Menú victoria reestablecido
*/
void reiniciar_menu_victoria(interfaz_t* interfaz);

/*
* Dada una lista de pokemones, la muestra completa por pantalla y
* devuelve la posicion del pokemon elegido por el usuario
* Pre : Recibe lista de pokemones cargada y ID de lista válido
* (LISTA_CAJA, LISTA_COMBATE o LISTA_ENTRENADOR)
* Post: Información por pantalla y posicion del pokemon seleccionado 
*/
size_t pedir_pokemon(lista_t* pokemones, int id_lista);

/* 
* Pide una ruta de archivo al usuario y devuelve como parametro
* Pre : ID de archivo válido (ARCHIVO_PERSONAJE o ARCHIVO_GIMNASIO)
* Post: ruta válida del archivo (sin fallo de apertura)
*/
void pedir_archivo(char ruta_archivo[MAX_STRING], int id_archivo);

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

/*
* Dado un string constante, imprime por pantalla su mensaje de forma tal que
* el usuario sepa que hay un error
* Pre : Descripcion completa del problema
* Post: Información por pantalla
*/
void reportar_error(const char *descripcion);

#endif /* __INTERFAZ_H__ */