
#include "juego.h"
#include "interfaz.h"
#define VACIO 0

//funciones batalla
#define FUNCION_1 0
#define FUNCION_2 1
#define FUNCION_3 2
#define FUNCION_4 3
#define FUNCION_5 4
//estado juego
#define INICIO 0
#define JUGANDO 1
#define SIMULAR 2
#define DERROTA 3
#define VICTORIA 4
//Constantes
#define MAX_FUNCIONES 5

typedef struct batalla{
    heap_t* gimnasios;
    size_t cant_gimansios;
    int (*funciones[MAX_FUNCIONES])(void*, void*);
}batalla_t;

typedef struct juego{
    char estado;
    personaje_t* personaje;
    batalla_t batalla;
    interfaz_t menus[MAX_MENU];
}juego_t;

void jugar_partida(juego_t* juego){

}

/* 
* 
* Pre:
* Post:
*/
bool siga_en_inicio(juego_t* juego){
    return !juego->personaje && !juego->batalla.gimnasios && juego->estado == INICIO;
}
/* 
* 
* Pre:
* Post:
*/
void inicializar_batalla(batalla_t* batalla){
    batalla->gimnasios = NULL;
    batalla->cant_gimansios = VACIO;
    batalla->funciones[FUNCION_1] = funcion_batalla_1; 
    batalla->funciones[FUNCION_2] = funcion_batalla_2; 
    batalla->funciones[FUNCION_3] = funcion_batalla_3; 
    batalla->funciones[FUNCION_4] = funcion_batalla_4; 
    batalla->funciones[FUNCION_5] = funcion_batalla_5; 
}
/* 
* 
* Pre:
* Post:
*/
void inicializar_juego(juego_t* juego){
    juego->estado = INICIO;
    inicializar_menus(&(juego->menus));
    inicializar_batalla(&(juego->batalla));
    juego->personaje = NULL;
}

int main(){
    juego_t juego;
    inicializar_juego(&juego);
    //while(siga_en_inicio(&juego))
    if(juego.estado == SIMULAR)
        simular_partida(juego);
    else
        jugar_partida(&juego);
    
    if(juego.estado == VICTORIA)
        menu_maestro_pokemon();
}