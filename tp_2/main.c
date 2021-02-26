
#include "juego.h"
#include "interfaz.h"

//funciones batalla
#define FUNCION_1 1
#define FUNCION_2 2
#define FUNCION_3 3
#define FUNCION_4 4
#define FUNCION_5 5
//estado juego
#define INICIO 0
#define JUGANDO 1
#define SIMULANDO 2
#define PERDIDO 4
#define GANADO 5
//Constantes
#define MAX_FUNCIONES 5
#define VACIO 0

typedef struct archivos{
    char ruta_personaje[MAX_STR];
    char ruta_gimnasios[MAX_STR];
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
* Determina si el juego cumple las condiciones para iniciarse
* Pre : Juego creado
* Post: Verdadero si se han cargado un personaje y los gimnasios
*/
bool juego_preparado(juego_t* juego){
    return juego->personaje && juego->gimnasios;
}
/* 
* Determina si el estado del juego coincide con el estado pasado
* Pre : Juego creado
* Post: Verdadero si el estado del juego y el estado coindiden
*/
int juego_estado(juego_t* juego, int estado){
    return juego->estado == estado;
}
/* 
* Cambia el estado del juedo dado un nuevo estado
* Pre : Juego creado
* Post: Juego con un nuevo estado
*/
void juego_cambiar_estado(juego_t* juego, int nuevo_estado){
    juego->estado = nuevo_estado;
}
/*
*
* Pre :
* Post:
*/
void juego_agregar_personaje(juego_t* juego){
    pedir_archivo(juego->archivos.ruta_personaje);
    personaje_t* personaje = personaje_cargar(juego->archivos.ruta_personaje);
    if(!personaje){
        warning("la creación del personaje o el formato del archivo");
        juego_cambiar_estado(juego, ERROR);
    }else{
        juego->personaje = personaje;
        eliminar_opcion(juego->interfaz, MENU_INICIO, OPCION_PERSONAJE);
    } 
}     
/*
*
* Pre :
* Post:
*/
void juego_agregar_gimnasios(juego_t* juego){
    pedir_archivo(juego->archivos.ruta_gimnasios);    
    heap_t* gimnasios = gimnasios_cargar(juego->archivos.ruta_gimnasios);
    if(!gimnasios){
        warning("la creación de los gimnasios o el formato del archivo");
        juego_cambiar_estado(juego, ERROR);
    }else{
        juego->gimnasios = gimnasios;
        eliminar_opcion(juego->interfaz, MENU_INICIO, OPCION_AGREGAR_GYM);
    } 

}
/* 
* Destruye la estructura del juego por completo
* Pre : Juego creado
* Post: Memoria ocupada por el juego liberada
*/
void destruir_juego(juego_t* juego){
    if(!juego) return;
    heap_destruir(juego->gimnasios);
    free(juego->funciones);
    interfaz_destruir(juego->interfaz);
    personaje_destruir(juego->personaje);
}
/* 
* Inicializa la liga de los gimnasios (excluyendo la carga de los mismos)
* (Estructura y funciones)
* Pre : Estructura del juego creada para almacenar a la liga
* Post: Liga con las distintas funciones de batallas
*/
funcion_batalla*  funciones_crear(){
    funcion_batalla* aux = calloc(MAX_FUNCIONES, sizeof(funcion_batalla));
    if(!aux) return NULL;
    aux[FUNCION_1] = funcion_batalla_1; 
    aux[FUNCION_2] = funcion_batalla_2; 
    aux[FUNCION_3] = funcion_batalla_3; 
    aux[FUNCION_4] = funcion_batalla_4; 
    aux[FUNCION_5] = funcion_batalla_5;
    return aux;
}
/* 
* Crea la estructura del juego
* Pre : -
* Post: Estructura del juego creada en memoria dinámica, listo para ser iniciado
*/
juego_t* juego_crear(){
    juego_t* juego = malloc(sizeof(juego_t));
    if(!juego) return NULL;
    juego->estado = INICIO;
    juego->gimnasios = NULL;
    juego->personaje = NULL;
    juego->interfaz = interfaz_crear();
    if(!juego->interfaz) return NULL;
    juego->funciones = funciones_crear();
    if(!juego->funciones) return NULL;
    return juego;
}
/* 
* Deja al juego en estado correspondiente para la partida
* Pre : Juego creado
* Post: Juego preaparado para ser jugado (sea para Jugar o Simular)
*/
void iniciar_partida(juego_t* juego){
     while(!juego_preparado(juego) && juego_estado(juego, INICIO)){
        menu_inicio(juego->interfaz);
        if(interfaz_estado(juego->interfaz, OPCION_PERSONAJE)){
            juego_agregar_personaje(juego);
        }else if(interfaz_estado(juego->interfaz, OPCION_AGREGAR_GYM)){
            juego_agregar_gimnasios(juego);
        }else if(interfaz_estado(juego->interfaz, OPCION_INICIAR)){
            if(juego_preparado(juego))
                juego_cambiar_estado(juego, JUGANDO);
        }else if(interfaz_estado(juego->interfaz, OPCION_SIMULAR)){
            if(juego_preparado(juego))
                juego_cambiar_estado(juego, SIMULANDO);
        }
    }
}
/* 
* Ejecuta el menu derrota dejando el juego según lo que elija el personaje
* Pre : Juego creado e iniciado, haber jugado la partida y perder en un gimnasio
* Post: Juego en estado correspondiente
*/
void gimnasio_perdido(juego_t* juego, gimnasio_t* gimnasio){
    menu_derrota(juego->interfaz, gimnasio);
    while(gimnasio_estado(gimnasio, PERDIDO) && juego_estado(juego, JUGANDO)){
        if(interfaz_estado(juego->interfaz, OPCION_CAMBIAR))
            cambiar_party(juego->personaje, pedir_pokemon);
        if(interfaz_estado(juego->interfaz, OPCION_REPETIR))
            gimnasio_cambiar_estado(gimnasio, PELEANDO);
        if(interfaz_estado(juego->interfaz, OPCION_SALIR)){
            juego_cambiar_estado(juego, PERDIDO);
        }
    }
}
/* 
* Ejecuta el menu victoria dejando el juego según lo que elija el personaje
* Pre : Juego creado e iniciado, haber jugado la partida y ganar un gimnasio
* Post: Juego en estado correspondiente
*/
void gimnasio_ganado(juego_t* juego, gimnasio_t* gimnasio){
    menu_victoria(juego->interfaz);
    while(!interfaz_estado(juego->interfaz, OPCION_AVANZAR)){
        if(!interfaz_estado(juego->interfaz, OPCION_AVANZAR)){
            if(interfaz_estado(juego->interfaz, OPCION_TOMAR_PKM))
                quitar_pokemon_lider(juego->personaje, gimnasio, pedir_pokemon);
            if(interfaz_estado(juego->interfaz, OPCION_CAMBIAR))
                cambiar_party(juego->personaje, pedir_pokemon);
            menu_victoria(juego->interfaz);
        }else{
            heap_borrar(juego->gimnasios); //Chequear
        }
    }
}

funcion_batalla obtener_funcion_batalla(juego_t *juego, gimnasio_t * gimnasio){
    return  juego->funciones[gimnasio->id_batalla - 1];
}
/* 
* Juega una partida completa
* Pre : Juego creado e iniciado (con gimansio y personajes cargados)
* Post: JUego perdido o ganado
*/
void jugar_partida(juego_t* juego){
    while(juego_estado(juego, JUGANDO)){
        gimnasio_t* gimnasio_actual = (gimnasio_t*) heap_raiz(juego->gimnasios);
        menu_gimnasio(juego->interfaz, gimnasio_actual);
        if(interfaz_estado(juego->interfaz, OPCION_PERSONAJE)){
            personaje_informacion(juego->personaje);
        }else if(interfaz_estado(juego->interfaz, OPCION_GIMNASIO)){
            gimnasio_informacion(gimnasio_actual);
        }else if(interfaz_estado(juego->interfaz, OPCION_CAMBIAR)){
            cambiar_party(juego->personaje, pedir_pokemon);
        }else if(interfaz_estado(juego->interfaz, OPCION_BATALLA)){
            funcion_batalla batalla = obtener_funcion_batalla(juego, gimnasio_actual);
            int estado = gimnasio_batalla(gimnasio_actual, juego->personaje, batalla, menu_batalla);
            gimnasio_cambiar_estado(gimnasio_actual, estado);
            if(gimnasio_estado(gimnasio_actual, PERDIDO))
                gimnasio_perdido(juego, gimnasio_actual);
            if(gimnasio_estado(gimnasio_actual, GANADO))
                gimnasio_ganado(juego, gimnasio_actual);
        }
    }
}

/* 
* Ejecuta el menu_derrota y sus opciones para una simulación
* Pre : Juego simulado y perdido, previamente iniciado
* Post:
*/
void simulacion_perdida(juego_t* juego, gimnasio_t* gimnasio){
    menu_derrota(juego->interfaz, gimnasio);
    while(!interfaz_estado(juego->interfaz, OPCION_REPETIR) || juego_estado(juego, PERDIDO)){
        if(interfaz_estado(juego->interfaz, OPCION_CAMBIAR))
            cambiar_party(juego->personaje, pedir_pokemon);
        if(interfaz_estado(juego->interfaz, OPCION_REPETIR)){
            heap_destruir(juego->gimnasios);
            juego->gimnasios = gimnasios_cargar(juego->archivos.ruta_gimnasios);
        }
        if(interfaz_estado(juego->interfaz, OPCION_SALIR))
            juego_cambiar_estado(juego, PERDIDO);
    }
}
/* 
* Simula la partida completa
* Pre : Juego en estado de simulación
* Post: Juego perdido o ganado
*/
void simular_partida(juego_t* juego){
    while(juego_estado(juego, SIMULANDO)){
        gimnasio_t* gimnasio_actual = (gimnasio_t*) heap_raiz(juego->gimnasios);
        funcion_batalla batalla = obtener_funcion_batalla(juego, gimnasio_actual);
        int estado = gimnasio_batalla(gimnasio_actual, juego->personaje, batalla, menu_batalla);
        gimnasio_cambiar_estado(gimnasio_actual, estado);
        if(gimnasio_estado(gimnasio_actual, GANADO))
            heap_borrar(juego->gimnasios);
        if(gimnasio_estado(gimnasio_actual, PERDIDO))
            simulacion_perdida(juego, gimnasio_actual);
        if(heap_vacio(juego->gimnasios))
            juego_cambiar_estado(juego, GANADO); 
    }
}

int main(){
    juego_t* juego = juego_crear();
    if(!juego){
        warning("la creación del juego");
        return ERROR;
    }
    iniciar_partida(juego);
    if(juego_estado(juego, ERROR))
        return ERROR;

    if(juego_estado(juego, SIMULANDO))
        simular_partida(juego);
    else
        jugar_partida(juego);
    
    if(juego_estado(juego, VICTORIA))
        menu_maestro_pokemon();

    destruir_juego(juego);
    return EXITO;
}