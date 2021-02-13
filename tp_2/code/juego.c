#include "juego.h"

personaje_t* cargar_personaje(FILE * archivo){

}

void personaje_destruir(personaje_t* personaje){

}

heap_t* cargar_gimnasios(FILE * archivo){

}

bool gimnasio_estado(gimnasio_t* gimnasio, int estado){
    return gimnasio->estado == estado;
}

void gimnasio_cambiar_estado(gimnasio_t* gimnasio, int nuevo_estado){
    gimnasio->estado = nuevo_estado;
}

entrenador_t* gimnasio_ultimo_entrenador(gimnasio_t* gimnasio){
    return (entrenador_t*) pila_tope(gimnasio->entrenadores); 
}

void gimanasio_luchar(gimnasio_t* gimnasio){

}

void tomar_pokemon(entrenador_t* lider, size_t posicion_pkm, personaje_t* personaje){
    
}

void intercambiar_pokemones(personaje_t* personaje, size_t pkm_party, size_t pkm_box){
    
}

heap_t* copiar_heap (heap_t* heap){

}
