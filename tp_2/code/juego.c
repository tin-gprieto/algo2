#include "juego.h"

//juego.h
bool juego_preparado(juego_t* juego){
    return juego->personaje && juego->gimnasios;
}
//juego.h
int juego_estado(juego_t* juego, int estado){
    return juego->estado == estado;
}
//juego.h
void juego_cambiar_estado(juego_t* juego, int nuevo_estado){
    juego->estado = nuevo_estado;
}
//juego.h
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
//juego.h
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
//juego.h
juego_t* juego_crear(){
    juego_t* juego = malloc(sizeof(juego_t));
    if(!juego) return NULL;
    juego->estado = JUEGO_INICIO;
    juego->gimnasios = NULL;
    juego->personaje = NULL;
    juego->interfaz = interfaz_crear();
    if(!juego->interfaz) return NULL;
    juego->funciones = funciones_crear();
    if(!juego->funciones) return NULL;
    return juego;
}

/*
*
* Pre :
* Post:
*/
int batalla_luchar(personaje_t* personaje, entrenador_t* rival, funcion_batalla batalla){
    size_t tope_personaje = lista_elementos(personaje->party);
    size_t tope_rival = lista_elementos(rival->pokemones);
    int pos_lista_personaje = 0;
    int pos_lista_rival = 0;
    while (pos_lista_personaje < tope_personaje && pos_lista_rival < tope_rival){    
        pokemon_t* pkm_personaje = lista_elemento_en_posicion(personaje->party, pos_lista_personaje);
        pokemon_t* pkm_rival = lista_elemento_en_posicion(rival->pokemones, pos_lista_rival);
        int estado = batalla(pkm_personaje, pkm_rival);
        menu_batalla(pkm_personaje, pkm_rival, estado);
        if(estado == BATALLA_VICTORIA)
            pos_lista_rival++;
        else if(estado == BATALLA_DERROTA)
            pos_lista_personaje++;
    }
    
    
    if(tope_personaje > tope_rival)
        return GIMNASIO_VICTORIA;
    return GIMNASIO_DERROTA;
}
//juego.h
void jugar_gimnasio(gimnasio_t* gimnasio, personaje_t* personaje, funcion_batalla batalla){
    if(!gimnasio || gimnasio_vacio(gimnasio) || !personaje || !batalla)
        return GIMNASIO_DERROTA;
    
    while(gimnasio_estado(gimnasio, GIMNASIO_PELEANDO)){
        entrenador_t* rival = gimnasio_ultimo_entrenador(gimnasio);
        int resultado = batalla_luchar(personaje, rival, batalla);
        if(resultado == BATALLA_VICTORIA){
            if(pila_elementos(gimnasio->entrenadores) == 1){
                gimnasio_cambiar_estado(gimnasio, GIMNASIO_VICTORIA); 
            }else{
                gimnasio_siguiente_entrenador(gimnasio);
                gimnasio_cambiar_estado(gimnasio, GIMNASIO_PELEANDO);
            }
        }else{
            gimnasio_cambiar_estado(gimnasio, GIMNASIO_DERROTA);
        }
    }
}

/* 
* Dada la posicion de un pokemon del conjunto del lider,
* lo transfiere a la caja del personaje
* Pre : Posicion del pokemon válida para la lista del lider, entrenador y personajes cargados
* Post: 0 si la caja del personaje tiene al nuevo pokemon o 
* -1 en caso de que no haya podido hacer alguna operación
*/
int tomar_pokemon(entrenador_t* lider, size_t posicion_pkm, personaje_t* personaje){
    pokemon_t* aux = lista_elemento_en_posicion(lider->pokemones, posicion_pkm);
    if(!aux) return ERROR;
    int estado = lista_insertar(personaje->caja, aux);
    if(estado == ERROR) return ERROR;
    estado = lista_borrar_de_posicion(lider->pokemones, posicion_pkm);
    if(estado == ERROR) return ERROR;   
    return JUEGO_JUGANDO;
}
//juego.h
int quitar_pokemon_lider(personaje_t* personaje, gimnasio_t* gimnasio, size_t (*pedir_pokemon)(lista_t*, int)){
    if(!gimnasio || !personaje || !pedir_pokemon)
        return ERROR;
    entrenador_t* lider = gimnasio_ultimo_entrenador(gimnasio);
    if(!lider) return ERROR;
    size_t pokemon_robado = pedir_pokemon(lider->pokemones, LISTA_ENTRENADOR);
    return tomar_pokemon(lider, pokemon_robado, personaje);
}

/* 
* Dadas dos posicones, una de un pokemon en el party y otro en la caja,
* Quita el pokemon del party para agregar el de la caja.
* Pre : Ambas posiciones de los pokemones que sean válidas, personaje cargado
* Post: Party con un intercambio de pokemones
*/
int intercambiar_pokemones(personaje_t* personaje, size_t pkm_party, size_t pkm_box){
    int salida = lista_borrar_de_posicion(personaje->party, pkm_party);
    if(salida == ERROR) return ERROR;
    pokemon_t* entrante = lista_elemento_en_posicion(personaje->caja, pkm_box);
    if(!entrante) return ERROR;
    int entrada = lista_insertar_en_posicion(personaje->party, entrante, pkm_party);
    if(entrada == ERROR) return ERROR;
    return JUEGO_JUGANDO;
}
//juego.h
int cambiar_party(personaje_t* personaje, size_t (*pedir_pokemon)(lista_t*, int)){
    if(!personaje || !pedir_pokemon)
        return ERROR;
    size_t pokemon_party = pedir_pokemon(personaje->party, LISTA_COMBATE);
    size_t pokemon_caja = pedir_pokemon(personaje->caja, LISTA_CAJA);
    return intercambiar_pokemones(personaje, pokemon_party, pokemon_caja);
}
