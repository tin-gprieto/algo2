
#include "juego.h"
#include "interfaz.h"
#define VACIO 0

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

typedef struct liga{
    heap_t* gimnasios;
    funcion_batalla* funciones;
    size_t tope_funciones;
}liga_t;

typedef struct juego{
    int estado;
    personaje_t* personaje;
    liga_t* liga;
    interfaz_t* interfaz;
}juego_t;

/* 
* Determina si el juego cumple las condiciones para iniciarse
* Pre : Juego creado
* Post: Verdadero si se han cargado un personaje y los gimnasios
*/
bool juego_preparado(juego_t* juego){
    return juego->personaje && juego->liga->gimnasios;
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
* Ejecuta el menu derrota dejando el juego según lo que elija el personaje
* Pre : Juego creado e iniciado, haber jugado la partida y perder en un gimnasio
* Post: Juego en estado correspondiente
*/
void gimnasio_perdido(juego_t* juego, gimnasio_t* gimnasio){
    menu_derrota(juego->interfaz, gimnasio);
    while(gimnasio_estado(gimnasio, PERDIDO) && juego_estado(juego, JUGANDO)){
        if(interfaz_estado(juego->interfaz, CAMBIAR))
            cambiar_party(juego->personaje, pedir_pokemon);
        if(interfaz_estado(juego->interfaz, REPETIR))
            gimnasio_cambiar_estado(gimnasio, ESTADO_INICIAL);
        if(interfaz_estado(juego->interfaz, SALIR)){
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
    while(!interfaz_estado(juego->interfaz, AVANZAR)){
        if(!interfaz_estado(juego->interfaz, AVANZAR)){
            if(interfaz_estado(juego->interfaz, TOMAR_PKM))
                quitar_pokemon_lider(juego->personaje, gimnasio, pedir_pokemon);
            if(interfaz_estado(juego->interfaz, CAMBIAR))
                cambiar_party(juego->personaje, pedir_pokemon);
            menu_victoria(juego->interfaz);
        }else{
            heap_borrar(juego->liga->gimnasios);
        }
    }
}

funcion_batalla obtener_funcion_batalla(juego_t *juego, gimnasio_t * gimnasio){
    return  juego->liga->funciones[gimnasio->id_batalla];
}
/* 
* Ejecuta la función de empezar un gimnasio
* Pre : Juego creado e iniciado, gimnasio en ESTADO_INICIAL
* Post: Juego perdido o avanzado al siguiente gimnasio
*/
void ejecutar_menu_gimnasio(juego_t* juego, gimnasio_t* gimnasio){
    menu_gimnasio(juego->interfaz, gimnasio);
    while(estado_juego(juego, JUGANDO)){
        if(interfaz_estado(juego->interfaz, PERSONAJE)){
            personaje_informacion(juego->personaje);
        }else if(interfaz_estado(juego->interfaz, GIMNASIO)){
            gimnasio_informacion(gimnasio);
        }else if(interfaz_estado(juego->interfaz, CAMBIAR)){
            cambiar_party(juego->personaje, pedir_pokemon);
        }else if(interfaz_estado(juego->interfaz, BATALLA)){
            funcion_batalla batalla = obtener_funcion_batalla(juego, gimnasio);
            int estado = gimnasio_batalla(juego->personaje, gimnasio, batalla, menu_batalla);
            gimnasio_cambiar_estado(gimnasio, estado);
            if(gimnasio_estado(gimnasio, PERDIDO))
                gimnasio_perdido(juego, gimnasio);
            if(gimnasio_estado(juego, GANADO))
                gimnasio_ganado(juego, gimnasio);
            if(gimnasio_estado(gimnasio, PELEANDO))
                menu_gimnasio(juego->interfaz, gimnasio);
        }
    }
}
/* 
* Juega una partida completa
* Pre : Juego creado e iniciado (con gimansio y personajes cargados)
* Post: JUego perdido o ganado
*/
void jugar_partida(juego_t* juego){
    while(estado_juego(juego, JUGANDO)){
        gimnasio_t* gimnasio_actual = (gimnasio_t*) heap_raiz(juego->liga->gimnasios);
        ejecutar_menu_gimnasio(juego, gimnasio_actual);
        if(heap_vacio(juego->liga->gimnasios))
            juego_cambiar_estado(juego, GANADO);
    }
}
/*
*
* Pre :
* Post:
*/
void juego_agregar_personaje(juego_t* juego){
    personaje_t* personaje = personaje_cargar(pedir_archivo);
    if(!personaje){
        warning("la carga del personaje");
        juego_cambiar_estado(juego, ERROR);
    }else{
        juego->personaje = personaje;
        eliminar_opcion(juego->interfaz, MENU_INICIO, PERSONAJE);
    } 
}     
/*
*
* Pre :
* Post:
*/
void juego_agregar_personaje(juego_t* juego){
    heap_t* gimnasios = gimnasios_cargar(pedir_archivo);
    if(!gimnasios){
        warning("la carga de los gimnasios");
        juego_cambiar_estado(juego, ERROR);
    }else{
        juego->liga->gimnasios = gimnasios;
        eliminar_opcion(juego->interfaz, MENU_INICIO, AGREGAR_GYM);
    } 

}

/* 
* Deja al juego en estado correspondiente para la partida
* Pre : Juego creado
* Post: Juego preaparado para ser jugado (sea para Jugar o Simular)
*/
void iniciar_partida(juego_t* juego){
     while(!juego_preparado(juego) && estado_juego(juego) == INICIO){
        menu_inicio(juego->interfaz);
        if(interfaz_estado(juego->interfaz, PERSONAJE)){
            juego_agregar_personaje(pedir_archivo);
        }else if(interfaz_estado(juego->interfaz, AGREGAR_GYM)){
            juego->liga->gimnasios = juego_agregar_gimnasios(pedir_archivo);
        }else if(interfaz_estado(juego->interfaz, INICIAR)){
            if(juego_preparado(juego))
                juego_cambiar_estado(juego, JUGANDO);
        }else if(interfaz_estado(juego->interfaz, SIMULAR)){
            if(juego_preparado(juego))
                juego_cambiar_estado(juego, SIMULANDO);
        }
    }
}
/* 
* Destruye la estructura de la liga
(Los gimnasios y la estructura de funciones batalla)
* Pre : Liga y juego creados
* Post: Memoria ocupada por la liga liberada
*/
void liga_destruir(liga_t* liga){
    if(!liga || !liga->gimnasios || !liga->funciones)
        return;
    heap_destruir(liga->gimnasios);
    free(liga->funciones);
    free(liga);
}
/* 
* Destruye la estructura del juego por completo
* Pre : Juego creado
* Post: Memoria ocupada por el juego liberada
*/
void destruir_juego(juego_t* juego){
    if(!juego) return;
    liga_destruir(juego->liga);
    interfaz_destruir(juego->interfaz);
    personaje_destruir(juego->personaje);
}
/* 
* Inicializa la liga de los gimnasios (excluyendo la carga de los mismos)
* (Estructura y funciones)
* Pre : Estructura del juego creada para almacenar a la liga
* Post: Liga con las distintas funciones de batallas
*/
liga_t* inicializar_liga(){
    liga_t* aux = malloc(sizeof(liga_t));
    if(!aux) return NULL;
    aux->gimnasios = NULL;
    funcion_batalla fun_aux = calloc(MAX_FUNCIONES, sizeof(funcion_batalla));
    if(!fun_aux) return NULL;
    aux->funciones = fun_aux;
    aux->tope_funciones = MAX_FUNCIONES;
    aux->funciones[FUNCION_1] = funcion_batalla_1; 
    aux->funciones[FUNCION_2] = funcion_batalla_2; 
    aux->funciones[FUNCION_3] = funcion_batalla_3; 
    aux->funciones[FUNCION_4] = funcion_batalla_4; 
    aux->funciones[FUNCION_5] = funcion_batalla_5;
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
    juego->interfaz = interfaz_crear();
    if(!juego->interfaz) return NULL;
    juego->liga = inicializar_liga();
    if(!juego->liga) return NULL;
    juego->personaje = NULL;
    return juego;
}
/* 
* Ejecuta el menu_derrota y sus opciones para una simulación
* Pre : Juego simulado y perdido, 
* Post:
*/
void simulacion_perdida(juego_t* juego, gimnasio_t* gimnasio, heap_t* auxiliar){
    menu_derrota(juego->interfaz, gimnasio);
    while(!interfaz_estado(juego->interfaz, REPETIR) || juego_estado(juego, PERDIDO)){
        if(interfaz_estado(juego->interfaz, CAMBIAR))
            cambiar_party(juego->personaje, pedir_pokemon);
        if(interfaz_estado(juego->interfaz, REPETIR)){
            heap_destruir(juego->liga->gimnasios);
            juego->liga->gimnasios = copiar_heap (auxiliar);
        }
        if(interfaz_estado(juego->interfaz, SALIR))
            juego_cambiar_estado(juego, PERDIDO);
    }
}
/* 
* Simula la partida completa
* Pre : Juego en estado de simulación
* Post: Juego perdido o ganado
*/
void simular_partida(juego_t* juego){
    heap_t* heap_auxiliar = copiar_heap(juego->liga->gimnasios);
    while(estado_juego(juego, SIMULANDO)){
        gimnasio_t* gym_actual = (gimnasio_t*) heap_raiz(juego->liga->gimnasios);
        gimanasio_luchar(gym_actual);
        if(gimnasio_estado(gym_actual, GANADO))
            heap_borrar(juego->liga->gimnasios);
        if(gimnasio_estado(gym_actual, PERDIDO));
            simulacion_perdida(juego, gym_actual, heap_auxiliar);
        if(heap_vacio(juego->liga->gimnasios))
            juego_cambiar_estado(juego, GANADO); 
    }
    heap_destruir(heap_auxiliar);
}

int main(){
    juego_t* juego = juego_crear();
    if(!juego){
        warning("la creación del juego");
        return ERROR;
    }
    iniciar_partida(juego);
    if(estado_juego(juego, ERROR))
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