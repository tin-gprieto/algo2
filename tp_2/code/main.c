
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

typedef int (*funciones_batalla)(void*, void*);

typedef struct liga{
    heap_t* gimnasios;
    funciones_batalla* funciones;
    size_t cant_funciones;
}liga_t;

typedef struct juego{
    int estado;
    personaje_t* personaje;
    liga_t* liga;
    interfaz_t* interfaz;
}juego_t;

/* 
* 
* Pre :
* Post:
*/
bool juego_preparado(juego_t* juego){
    return juego->personaje && juego->liga->gimnasios;
}
/* 
* 
* Pre :
* Post:
*/
int juego_estado(juego_t* juego, int estado){
    return juego->estado == estado;
}
/* 
* 
* Pre :
* Post:
*/
void juego_cambiar_estado(juego_t* juego, int nuevo_estado){
    juego->estado = nuevo_estado;
}

/* 
* 
* Pre :
* Post:
*/
void cambiar_party(personaje_t* personaje){
    size_t pokemon_party = pedir_pokemon(personaje->party, COMBATE);
    size_t pokemon_caja = pedir_pokemon(personaje->caja, CAJA);
    intercambiar_pokemones(personaje, pokemon_party, pokemon_caja);
}
/* 
* 
* Pre :
* Post:
*/
void quitar_pokemon_lider(personaje_t* personaje, gimnasio_t* gimnasio){
    entrenador_t* lider = gimnasio_ultimo_entrenador(gimnasio);
    size_t pokemon_robado = pedir_pokemon(lider->pokemones, ENTRENADOR);
    tomar_pokemon(lider, pokemon_robado, personaje);
}
/* 
* 
* Pre :
* Post:
*/
void gimnasio_perdido(juego_t* juego, gimnasio_t* gimnasio){
    menu_derrota(juego->interfaz, gimnasio->nombre);
    if(interfaz_estado(juego->interfaz, CAMBIAR))
        cambiar_party(juego->personaje);
    if(interfaz_estado(juego->interfaz, REPETIR))
        gimnasio_cambiar_estado(gimnasio, ESTADO_INICIAL);
    if(interfaz_estado(juego->interfaz, SALIR))
        juego_cambiar_estado(juego, PERDIDO);
}
/* 
* 
* Pre :
* Post:
*/
void gimnasio_ganado(juego_t* juego, gimnasio_t* gimnasio){
    menu_victoria(juego->interfaz);
    if(interfaz_estado(juego->interfaz, TOMAR_PKM))
        quitar_pokemon_lider(juego->personaje, gimnasio);
    if(interfaz_estado(juego->interfaz, CAMBIAR))
        cambiar_party(juego->personaje);
    if(interfaz_estado(juego->interfaz, AVANZAR))
        heap_borrar(juego->liga->gimnasios);
}
/* 
* 
* Pre :
* Post:
*/
void jugar_partida(juego_t* juego){
    while(estado_juego(juego, JUGANDO)){
        gimnasio_t* gym_actual = (gimnasio_t*) heap_raiz(juego->liga->gimnasios);
        menu_gimnasio(juego->interfaz, gym_actual->nombre);
        if(interfaz_estado(juego->interfaz, PERSONAJE)){
            personaje_informacion(juego->personaje);
        }else if(interfaz_estado(juego->interfaz, GIMNASIO)){
            gimnasio_informacion(gym_actual);
        }else if(interfaz_estado(juego->interfaz, CAMBIAR)){
            cambiar_party(juego->personaje);
        }else if(interfaz_estado(juego->interfaz, BATALLA)){
            gimanasio_luchar(gym_actual);
            if(gimnasio_estado(gym_actual, PERDIDO))
                gimnasio_perdido(juego, gym_actual);
            if(gimnasio_estado(juego, GANADO))
                gimnasio_ganado(juego, gym_actual);
        }
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
     FILE * archivo = pedir_archivo(LECTURA);
    juego->personaje = personaje_cargar(archivo);
    fclose(archivo);
    if(!juego->personaje){
        warning("la carga del personaje");
        juego_cambiar_estado(juego, ERROR);
    }else{
        eliminar_opcion(juego->interfaz, MENU_INICIO, PERSONAJE);
    }
}
/* 
* 
* Pre :
* Post:
*/
void juego_agregar_gimnasios(juego_t* juego){
    FILE * archivo = pedir_archivo(LECTURA);
    juego->liga->gimnasios = gimnasio_cargar(archivo);
    fclose(archivo);
    if(!juego->liga->gimnasios){
        warning("la carga de los gimnasios");
        juego_cambiar_estado(juego, ERROR);
    }else{
        eliminar_opcion(juego->interfaz, MENU_INICIO, AGREGAR_GYM);
    }
}           
/* 
* 
* Pre :
* Post:
*/
void iniciar_partida(juego_t* juego){
     while(!juego_preparado(juego) && estado_juego(juego) == INICIO){
        menu_inicio(juego->interfaz);
        if(interfaz_estado(juego->interfaz, PERSONAJE)){
            juego_agregar_personaje(juego);
        }else if(interfaz_estado(juego->interfaz, AGREGAR_GYM)){
            juego_agregar_gimnasios(juego);
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
* 
* Pre :
* Post:
*/
liga_t* inicializar_liga(){
    liga_t* aux = malloc(sizeof(liga_t));
    if(!aux) return NULL;
    aux->gimnasios = NULL;
    funciones_batalla fun_aux = calloc(MAX_FUNCIONES, sizeof(funciones_batalla));
    if(!fun_aux) return NULL;
    aux->funciones = fun_aux;
    aux->cant_funciones = MAX_FUNCIONES;
    aux->funciones[FUNCION_1] = funcion_batalla_1; 
    aux->funciones[FUNCION_2] = funcion_batalla_2; 
    aux->funciones[FUNCION_3] = funcion_batalla_3; 
    aux->funciones[FUNCION_4] = funcion_batalla_4; 
    aux->funciones[FUNCION_5] = funcion_batalla_5;
    return aux;
}
/* 
* 
* Pre :
* Post:
*/
juego_t* inicializar_juego(){
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
* 
* Pre :
* Post:
*/
void liga_destruir(liga_t* liga){
    heap_destruir(liga->gimnasios);
    free(liga->funciones);
    free(liga);
}
/* 
* 
* Pre :
* Post:
*/
void destruir_juego(juego_t* juego){
    liga_destruir(juego->liga);
    interfaz_destruir(juego->interfaz);
    personaje_destruir(juego->personaje);
}
/* 
* 
* Pre :
* Post:
*/
void simulacion_perdida(juego_t* juego, gimnasio_t* gimnasio, heap_t* auxiliar){
    menu_derrota(juego->interfaz, gimnasio->nombre);
    if(interfaz_estado(juego->interfaz, CAMBIAR))
        cambiar_party(juego->personaje);
    if(interfaz_estado(juego->interfaz, REPETIR)){
        heap_destruir(juego->liga->gimnasios);
        juego->liga->gimnasios = copiar_heap (auxiliar);
    }
    if(interfaz_estado(juego->interfaz, SALIR))
        juego_cambiar_estado(juego, PERDIDO);
}
/* 
* 
* Pre :
* Post:
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
    juego_t* juego = inicializar_juego(&juego);
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