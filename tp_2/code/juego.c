#include "juego.h"

void personaje_destruir(personaje_t* personaje){

}
/* 
* Dado un archivo, crea un personaje con la información dentro
* Pre : Archivo abierto para lectura
* Post: Personaje creado en memoria dinámica
*/
personaje_t* leer_archivo_personaje(FILE * archivo){
    return NULL;
}
/* 
* Dado un archivo, crea un heap de gimnasios con la información dentro
* Pre : Archivo abierto para lectura
* Post: Heap minimal con todos los gimnasios dentro
*/
heap_t* leer_archivo_gimnasios(FILE * archivo){
    return NULL;    
}

personaje_t* cargar_personaje(void (*pedir_archivo)(char *)){
    char ruta_archivo[MAX_STR];
    pedir_archivo(ruta_archivo);
    FILE * archivo = fopen(ruta_archivo, LECTURA);
    personaje_t* personaje = leer_archivo_personaje(archivo);
    fclose(archivo);
    return personaje;
}

heap_t* cargar_gimnasios(void (*pedir_archivo)(char *)){
    char ruta_archivo[MAX_STR];
    pedir_archivo(ruta_archivo);
    FILE * archivo = fopen(ruta_archivo, LECTURA);
    heap_t* gimnasios = leer_archivo_gimnasios(archivo);
    fclose(archivo);
    return gimnasios;
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

int gimnasio_batalla(gimnasio_t* gimnasio, personaje_t* personaje, funcion_batalla batalla, mostrar_batalla menu){
    entrenador_t* entrenador = gimnasio_ultimo_entrenador(gimnasio);
    int resultado = luchar_batalla(personaje, entrenador, batalla, menu);
    if(resultado == VICTORIA){
        if(pila_elementos(gimnasio->entrenadores) == 1){
            return VICTORIA; 
        }else{
            destruir_entrenador(gimnasio_ultimo_entrenador(gimnasio));
            pila_desapilar(gimnasio->entrenadores);
            return PELEANDO;
        }
    }else if (resultado == DERROTA){
            return DERROTA;
    }
}

/* 
* Dada la posicion de un pokemon del conjunto del lider,
* lo transfiere a la caja del personaje
* Pre : Posicion del pokemon válida para la lista del lider, entrenador y personajes cargados
* Post: Caja del personaje con nuevo pokemon
*/
void tomar_pokemon(entrenador_t* lider, size_t posicion_pkm, personaje_t* personaje){
    
}

void quitar_pokemon_lider(personaje_t* personaje, gimnasio_t* gimnasio, size_t (*pedir_pokemon)(lista_t*, int)){
    entrenador_t* lider = gimnasio_ultimo_entrenador(gimnasio);
    size_t pokemon_robado = pedir_pokemon(lider->pokemones, ENTRENADOR);
    tomar_pokemon(lider, pokemon_robado, personaje);
}

/* 
* Dadas dos posicones, una de un pokemon en el party y otro en la caja,
* Quita el pokemon del party para agregar el de la caja.
* Pre : Ambas posiciones de los pokemones que sean válidas, personaje cargado
* Post: Party con un intercambio de pokemones
*/
void intercambiar_pokemones(personaje_t* personaje, size_t pkm_party, size_t pkm_box){
    
}

void cambiar_party(personaje_t* personaje, size_t (*pedir_pokemon)(lista_t*, int)){
    size_t pokemon_party = pedir_pokemon(personaje->party, COMBATE);
    size_t pokemon_caja = pedir_pokemon(personaje->caja, CAJA);
    intercambiar_pokemones(personaje, pokemon_party, pokemon_caja);
}

heap_t* copiar_heap (heap_t* heap){
    return NULL;
}
