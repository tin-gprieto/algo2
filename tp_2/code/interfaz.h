#ifndef __INTERFAZ_H__
#define __INTERFAZ_H__

#include "../toolbox/tools.h"

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

typedef struct interfaz{
    int menu;
    char clave;
    char opciones[MAX_OPC];
    char descripciones[MAX_OPC][MAX_STR];
    size_t cant_opciones;
}interfaz_t;

/* 
* 
* Pre:
* Post:
*/
void menu_maestro();

/* 
* 
* Pre:
* Post:
*/
char mostrar_menu(interfaz_t* menu, int tipo, const char* extra);

/* 
* 
* Pre:
* Post:
*/
void inicializar_menus(interfaz_t* menus);

#endif /* __INTERFAZ_H__ */