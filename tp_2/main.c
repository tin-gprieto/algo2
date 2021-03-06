#include "code/juego.h"

/* 
* Deja al juego en estado correspondiente para la partida
* Pre : Juego creado
* Post: Juego preaparado para ser jugado 
* (sea para jugar manual (JUGANDO) o simular (SIMULANDO))
*/
void iniciar_partida(juego_t* juego){
     while(juego_estado(juego, JUEGO_INICIO)){
        menu_inicio(juego->interfaz);
        if(interfaz_estado(juego->interfaz, OPCION_PERSONAJE))
            juego_agregar_personaje(juego);
        if(interfaz_estado(juego->interfaz, OPCION_AGREGAR_GYM))
            juego_agregar_gimnasios(juego);
        if(interfaz_estado(juego->interfaz, OPCION_SALIR))
            juego_cambiar_estado(juego, JUEGO_SALIR);
        if(interfaz_estado(juego->interfaz, OPCION_INICIAR)){
            if(juego_preparado(juego))
                juego_cambiar_estado(juego, JUEGO_JUGANDO);
            else
                reportar_error("Deben ingresarse los archivos");
        }else if(interfaz_estado(juego->interfaz, OPCION_SIMULAR)){
            if(juego_preparado(juego))
                juego_cambiar_estado(juego, JUEGO_SIMULANDO);
            else
                reportar_error("Deben ingresarse los archivos");
        }
    }
}
/* 
* Ejecuta el menu derrota dejando el juego según lo que elija el personaje
* Pre : Juego creado e iniciado, haber jugado la partida y perder en un gimnasio
* Post: Juego en estado correspondiente
*/
void gimnasio_perdido(juego_t* juego, gimnasio_t* gimnasio){
    while(gimnasio_estado(gimnasio, GIMNASIO_DERROTA) && !juego_estado(juego, JUEGO_PERDIDO)){
        menu_derrota(juego->interfaz, gimnasio);
        if(interfaz_estado(juego->interfaz, OPCION_CAMBIAR))
            cambiar_party(juego);
        if(interfaz_estado(juego->interfaz, OPCION_REPETIR))
            gimnasio_cambiar_estado(gimnasio, GIMNASIO_PELEANDO);
        if(interfaz_estado(juego->interfaz, OPCION_SALIR))
            juego_cambiar_estado(juego, JUEGO_PERDIDO);
        
    }
}
/* 
* Ejecuta el menu victoria dejando el juego según lo que elija el personaje
* Pre : Juego creado e iniciado, haber jugado la partida y ganar un gimnasio
* Post: Juego en estado correspondiente
*/
void gimnasio_ganado(juego_t* juego, gimnasio_t* gimnasio){
    bool bonificacion = false;
    while(!interfaz_estado(juego->interfaz, OPCION_AVANZAR) && !juego_estado(juego, ERROR) && !juego_estado(juego, JUEGO_SALIR)){
        menu_victoria(juego->interfaz);
        if(interfaz_estado(juego->interfaz, OPCION_AVANZAR))
            juego_eliminar_gimnasio(juego);
        else if(interfaz_estado(juego->interfaz, OPCION_CAMBIAR)){
            cambiar_party(juego);
        }else if(interfaz_estado(juego->interfaz, OPCION_TOMAR_PKM)){
            quitar_pokemon_lider(juego);
            bonificacion = true;
        }else if(interfaz_estado(juego->interfaz, OPCION_SALIR))
            juego_cambiar_estado(juego, JUEGO_SALIR);
    }
    if(bonificacion)
        reiniciar_menu_victoria(juego->interfaz);
}

/* 
* Juega una partida completa
* Pre : Juego creado, iniciado (con gimansio y personajes cargados), y en modo jugando (manual)
* Post: Juego perdido, ganado, ERROR o salir
*/
void jugar_partida(juego_t* juego){
    while(juego_estado(juego, JUEGO_JUGANDO)){
        gimnasio_t* gimnasio_actual = (gimnasio_t*) heap_raiz(juego->gimnasios);
        jugar_gimnasio(juego);
        if(gimnasio_estado(gimnasio_actual, GIMNASIO_DERROTA))
            gimnasio_perdido(juego, gimnasio_actual);
        if(gimnasio_estado(gimnasio_actual, GIMNASIO_VICTORIA)){
            gimnasio_ganado(juego, gimnasio_actual);
            if(heap_vacio(juego->gimnasios))
                juego_cambiar_estado(juego,JUEGO_GANADO);
        }
    }
}

/* 
* Ejecuta el menu_derrota para la simulación y sus opciones, 
* dejando el juego en el estado que decida el jugador 
* Pre : Juego simulado y perdido
* Post: Estado del juego según la decisión del jugador
*/
void simulacion_perdida(juego_t* juego, gimnasio_t* gimnasio){
    while(!interfaz_estado(juego->interfaz, OPCION_REPETIR) && !juego_estado(juego, JUEGO_PERDIDO)){
        menu_derrota(juego->interfaz, gimnasio);
        if(interfaz_estado(juego->interfaz, OPCION_CAMBIAR))
            cambiar_party(juego);
        if(interfaz_estado(juego->interfaz, OPCION_REPETIR)){
            heap_destruir(juego->gimnasios);
            juego->gimnasios = gimnasios_cargar(juego->archivos.ruta_gimnasios);
            if(!juego->gimnasios)
                juego_cambiar_estado(juego, ERROR);
            else{
                juego_cambiar_estado(juego, JUEGO_SIMULANDO);
                menu_simulacion(SIMULACION_INICIO, NULL, NULL);
            }
        }
        if(interfaz_estado(juego->interfaz, OPCION_SALIR))
            juego_cambiar_estado(juego, JUEGO_PERDIDO);
    }
    if(interfaz_estado(juego->interfaz, OPCION_REPETIR))
        interfaz_cambiar_estado(juego->interfaz, OPCION_AVANZAR);
}
/* 
* Simula la partida completa
* Pre : Juego creado, iniciado (con gimansio y personajes cargados), y en modo simulación
* Post: Juego perdido, ganado, o ERROR 
*/
void simular_partida(juego_t* juego){
    
    menu_simulacion(SIMULACION_INICIO, NULL, NULL);
    
    while(juego_estado(juego, JUEGO_SIMULANDO)){
        gimnasio_t* gimnasio_actual = (gimnasio_t*) heap_raiz(juego->gimnasios);
        simular_gimnasio(juego);
        if(gimnasio_estado(gimnasio_actual, GIMNASIO_VICTORIA))
            juego_eliminar_gimnasio(juego);
        else if(gimnasio_estado(gimnasio_actual, GIMNASIO_DERROTA)){
            menu_simulacion(SIMULACION_FIN, NULL, NULL);
            simulacion_perdida(juego, gimnasio_actual);
        }
        if(heap_vacio(juego->gimnasios)){
            menu_simulacion(SIMULACION_FIN, NULL, NULL);
            juego_cambiar_estado(juego, JUEGO_GANADO); 
        }
    }
}

int main(){
    juego_t* juego = juego_crear();
    if(!juego){
        reportar_error("Problema con la creación del juego");
        return ERROR;
    }
    iniciar_partida(juego);
    if(juego_estado(juego, ERROR)){
        reportar_error("Problema con la creación del juego");
        juego_destruir(juego);
        return ERROR;
    }

    if(juego_estado(juego, JUEGO_SIMULANDO))
        simular_partida(juego);

    if(juego_estado(juego, JUEGO_JUGANDO))
        jugar_partida(juego);
    
    if(juego_estado(juego, JUEGO_GANADO))
        menu_maestro_pokemon();

    if(juego_estado(juego, ERROR)){
        juego_destruir(juego);
        reportar_error("Problema con la ejecución del juego");
        return ERROR;
    }
    juego_destruir(juego);
    return EXITO;
}