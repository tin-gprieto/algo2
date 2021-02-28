#include "juego.h"
#include "interfaz.h"

/* 
* Deja al juego en estado correspondiente para la partida
* Pre : Juego creado
* Post: Juego preaparado para ser jugado (sea para Jugar o Simular)
*/
void iniciar_partida(juego_t* juego){
     while(!juego_preparado(juego) && juego_estado(juego, JUEGO_INICIO)){
        menu_inicio(juego->interfaz);
        if(interfaz_estado(juego->interfaz, OPCION_PERSONAJE)){
            juego_agregar_personaje(juego);
        }else if(interfaz_estado(juego->interfaz, OPCION_AGREGAR_GYM)){
            juego_agregar_gimnasios(juego);
        }else if(interfaz_estado(juego->interfaz, OPCION_INICIAR)){
            if(juego_preparado(juego))
                juego_cambiar_estado(juego, JUEGO_JUGANDO);
        }else if(interfaz_estado(juego->interfaz, OPCION_SIMULAR)){
            if(juego_preparado(juego))
                juego_cambiar_estado(juego, JUEGO_SIMULANDO);
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
    while(gimnasio_estado(gimnasio, JUEGO_PERDIDO) && juego_estado(juego, JUEGO_JUGANDO)){
        if(interfaz_estado(juego->interfaz, OPCION_CAMBIAR))
            cambiar_party(juego->personaje, pedir_pokemon); //chequear
        if(interfaz_estado(juego->interfaz, OPCION_REPETIR))
            gimnasio_cambiar_estado(gimnasio, GIMNASIO_PELEANDO);
        if(interfaz_estado(juego->interfaz, OPCION_SALIR)){
            juego_cambiar_estado(juego, JUEGO_PERDIDO);
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
        if(interfaz_estado(juego->interfaz, OPCION_AVANZAR)){
            heap_borrar(juego->gimnasios); //Chequear
        }else{
            if(interfaz_estado(juego->interfaz, OPCION_TOMAR_PKM))
                quitar_pokemon_lider(juego->personaje, gimnasio, pedir_pokemon);//chequear
            if(interfaz_estado(juego->interfaz, OPCION_CAMBIAR))
                cambiar_party(juego->personaje, pedir_pokemon);//chequear
            menu_victoria(juego->interfaz);
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
    while(juego_estado(juego, JUEGO_JUGANDO)){
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
            int estado = jugar_gimnasio(gimnasio_actual, juego->personaje, batalla);
            gimnasio_cambiar_estado(gimnasio_actual, estado);
            if(gimnasio_estado(gimnasio_actual, GIMNASIO_DERROTA))
                gimnasio_perdido(juego, gimnasio_actual);
            if(gimnasio_estado(gimnasio_actual, GIMNASIO_VICTORIA))
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
    while(!interfaz_estado(juego->interfaz, OPCION_REPETIR) || juego_estado(juego, JUEGO_PERDIDO)){
        if(interfaz_estado(juego->interfaz, OPCION_CAMBIAR))
            cambiar_party(juego->personaje, pedir_pokemon);
        if(interfaz_estado(juego->interfaz, OPCION_REPETIR)){
            heap_destruir(juego->gimnasios);
            juego->gimnasios = gimnasios_cargar(juego->archivos.ruta_gimnasios);
        }
        if(interfaz_estado(juego->interfaz, OPCION_SALIR))
            juego_cambiar_estado(juego, JUEGO_PERDIDO);
    }
}
/* 
* Simula la partida completa
* Pre : Juego en estado de simulación
* Post: Juego perdido o ganado
*/
void simular_partida(juego_t* juego){
    while(juego_estado(juego, JUEGO_SIMULANDO)){
        gimnasio_t* gimnasio_actual = (gimnasio_t*) heap_raiz(juego->gimnasios);
        funcion_batalla batalla = obtener_funcion_batalla(juego, gimnasio_actual);
        int estado = jugar_gimnasio(gimnasio_actual, juego->personaje, batalla);
        gimnasio_cambiar_estado(gimnasio_actual, estado);
        if(gimnasio_estado(gimnasio_actual, JUEGO_GANADO))
            heap_borrar(juego->gimnasios);
        if(gimnasio_estado(gimnasio_actual, JUEGO_PERDIDO))
            simulacion_perdida(juego, gimnasio_actual);
        if(heap_vacio(juego->gimnasios))
            juego_cambiar_estado(juego, JUEGO_GANADO); 
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

    if(juego_estado(juego, JUEGO_SIMULANDO))
        simular_partida(juego);
    else
        jugar_partida(juego);
    
    if(juego_estado(juego, JUEGO_GANADO))
        menu_maestro_pokemon();

    destruir_juego(juego);
    return EXITO;
}