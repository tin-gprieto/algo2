#include "juego.h"

#define NVL_MAX 63
#define NVL_AUMENTO 3

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
    pedir_archivo(juego->archivos.ruta_personaje, ARCHIVO_PERSONAJE);
    personaje_t* personaje = personaje_cargar(juego->archivos.ruta_personaje);
    if(!personaje){
        reportar_error("Hubo un problema con la creación del personaje o el formato del archivo");
        juego_cambiar_estado(juego, ERROR);
    }else{
        juego->personaje = personaje;
        eliminar_opcion(juego->interfaz, MENU_INICIO, OPCION_PERSONAJE);
    } 
}     
//juego.h
void juego_agregar_gimnasios(juego_t* juego){
    pedir_archivo(juego->archivos.ruta_gimnasios, ARCHIVO_GIMNASIO);    
    heap_t* gimnasios = gimnasios_cargar(juego->archivos.ruta_gimnasios);
    if(!gimnasios){
        reportar_error("Hubo un problema con la creación de los gimnasios o el formato del archivo");
        juego_cambiar_estado(juego, ERROR);
    }else{
        juego->gimnasios = gimnasios;
        eliminar_opcion(juego->interfaz, MENU_INICIO, OPCION_AGREGAR_GYM);
    } 

}
//juego.h
void juego_eliminar_gimnasio(juego_t* juego){
    if(!juego || heap_vacio(juego->gimnasios))
        return;
    int estado = heap_borrar(juego->gimnasios);
    if(estado == ERROR)
        juego_cambiar_estado(juego, estado);
}
/* 
* Destruye la estructura del juego por completo
* Pre : Juego creado
* Post: Memoria ocupada por el juego liberada
*/
void juego_destruir(juego_t* juego){
    if(!juego) return;
    heap_destruir(juego->gimnasios);
    free(juego->funciones);
    interfaz_destruir(juego->interfaz);
    personaje_destruir(juego->personaje);
    free(juego);
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
* Bonifica a un pokemon, aumentando todas sus características en 1 
* siempre y cuando tenga un nivel inferior a 63
* Pre : Pokemon creado e inicializado, que haya ganado una batalla y sea de nivel menor a 63
* Post: Pokemon bonificado y con un nuevo nivel (+3) 
*/
void bonificar_pokemon(pokemon_t * pokemon){
    if(!pokemon || pokemon->nivel > NVL_MAX)
        return;
    pokemon->ataque ++;
    pokemon->defensa ++;
    pokemon->velocidad ++;
    pokemon->nivel += NVL_AUMENTO;
}
/*
* Realiza todas las batallas con un entrenador
* Pre : Juego y rival creados e inicializados, función de batalla válida
* Post: Resultado de la batalla
*/
int batalla_entrenador(juego_t* juego, entrenador_t* rival, funcion_batalla batalla){
    personaje_t* personaje = juego->personaje;
    size_t tope_personaje = lista_elementos(personaje->party);
    size_t tope_rival = lista_elementos(rival->pokemones);
    size_t pos_lista_personaje = 0;
    size_t pos_lista_rival = 0;
    while (pos_lista_personaje < tope_personaje && pos_lista_rival < tope_rival){    
        pokemon_t* pkm_personaje = lista_elemento_en_posicion(personaje->party, pos_lista_personaje);
        pokemon_t* pkm_rival = lista_elemento_en_posicion(rival->pokemones, pos_lista_rival);
        int estado = batalla(pkm_personaje, pkm_rival);
        if(juego_estado(juego, JUEGO_JUGANDO))
            menu_batalla(rival, pos_lista_rival, pkm_personaje, estado);
        if(juego_estado(juego, JUEGO_SIMULANDO))
            menu_batalla_simulada(rival, pos_lista_rival, pkm_personaje, estado);
        if(estado == GANO_PRIMERO){
            bonificar_pokemon(pkm_personaje);
            pos_lista_rival++;
        }else if(estado == GANO_SEGUNDO)
            pos_lista_personaje++;
    }
    
    if(pos_lista_rival == tope_rival)
        return BATALLA_VICTORIA;
    return BATALLA_DERROTA;
}
/*
* Según el gimnasio y las funciones del juego, devuelve la funcion correspondiente al gimnasio
* Pre : Gimnsaio leido del juego y con id válida (1 a 5) y juego creado
* Post: Funcion batalla del gimnasio pasado por parametro
*/
funcion_batalla obtener_funcion_batalla(juego_t *juego, gimnasio_t * gimnasio){
    if(!juego || !juego->funciones || !gimnasio)
        return NULL;
    return  juego->funciones[gimnasio->id_batalla - 1];
}
/*
* Determina el estado del gimnasio ganado, si ya se ganó definitivamente o si requiere seguir luchando
* Pre : Batalla del gimnasio ganado
* Post: GIMNASIO_VICTORIA si se le ganó al lider (+1 medallas) 
*       GIMNASIO_PELEANDO si debe seguir luchando (avanza al siguiente entrenador)
*/
void batalla_ganada(gimnasio_t * gimnasio, personaje_t* personaje){
    if(pila_elementos(gimnasio->entrenadores) == 1){
        gimnasio_cambiar_estado(gimnasio, GIMNASIO_VICTORIA);
        personaje->medallas ++; 
    }else{
        gimnasio_cambiar_estado(gimnasio, GIMNASIO_PELEANDO);
        gimnasio_siguiente_entrenador(gimnasio);
    }
}

//juego.h
void jugar_gimnasio(juego_t* juego, gimnasio_t* gimnasio){
    if(!juego || !juego->personaje || gimnasio_vacio(gimnasio) ){
        juego_cambiar_estado(juego, ERROR);
        return;
    }
    funcion_batalla batalla = obtener_funcion_batalla(juego, gimnasio);

    if(!batalla){
        reportar_error("Hubo un problema con la función de un gimnasio");
        juego_cambiar_estado(juego, ERROR);
        return;
    }

    while(gimnasio_estado(gimnasio, GIMNASIO_PELEANDO)){
        if(juego_estado(juego, JUEGO_JUGANDO))
            menu_gimnasio(juego->interfaz, gimnasio);
        if(interfaz_estado(juego->interfaz, OPCION_PERSONAJE))
            personaje_informacion(juego->personaje);
        if(interfaz_estado(juego->interfaz, OPCION_GIMNASIO))
            gimnasio_informacion(gimnasio);
        if(interfaz_estado(juego->interfaz, OPCION_CAMBIAR))
            cambiar_party(juego);
        if(interfaz_estado(juego->interfaz, OPCION_SALIR))
            juego_cambiar_estado(juego, JUEGO_SALIR);
        if(interfaz_estado(juego->interfaz, OPCION_BATALLA)){
            entrenador_t* rival = gimnasio_ultimo_entrenador(gimnasio);
            int resultado = batalla_entrenador(juego, rival, batalla);
            if(resultado == BATALLA_VICTORIA)
                batalla_ganada(gimnasio, juego->personaje);
            else
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
void quitar_pokemon_lider(juego_t* juego){
    if(!juego || !juego->gimnasios || !juego->personaje){
        juego_cambiar_estado(juego, ERROR);
        return;
    }
    gimnasio_t* gimnasio = (gimnasio_t*) heap_raiz(juego->gimnasios);
    if(!gimnasio){
        juego_cambiar_estado(juego, ERROR);
        return;
    }
    entrenador_t* lider = gimnasio_ultimo_entrenador(gimnasio);
    if(!lider){
        juego_cambiar_estado(juego, ERROR);
        return;
    }
    size_t pokemon_robado = pedir_pokemon(lider->pokemones, LISTA_ENTRENADOR);
    int estado = tomar_pokemon(lider, pokemon_robado, juego->personaje);
    juego_cambiar_estado(juego, estado);
    eliminar_opcion(juego->interfaz, MENU_VICTORIA, OPCION_TOMAR_PKM);
}
/* 
* Dada una lista y un pokemon busca su posicion en la misma
* Pre : Pokemon perteneciente a la lista
* Post: Posicion del pokemon
*/
size_t lista_buscar_posicion(lista_t * lista, pokemon_t * elegido){
    size_t  posicion = 0;
    bool encontrado = false;
    lista_iterador_t* iterador = lista_iterador_crear(lista);
    while(lista_iterador_tiene_siguiente(iterador) && !encontrado){
        pokemon_t* encontrado = (pokemon_t*)lista_iterador_elemento_actual(iterador);
        if(encontrado == elegido)
            encontrado = true;
        else    
            posicion++;  

    }
    lista_iterador_destruir(iterador);
    if(encontrado)
        return posicion;
    return ERROR;
}
/* 
* Dado el personaje y dos pokemones, los intercambia de lugar el party
* Pre : Personaje creado, saliente y entrante no nulos y pertenecientes al party, pos_saliente en el party
* Post: Pokemones intercambiados de lugar en el party
*/
int intercambiar_del_party(personaje_t* personaje, pokemon_t* saliente, size_t pos_saliente, pokemon_t* entrante){
    if(entrante == saliente) return JUEGO_JUGANDO;
    size_t pos_entrante = lista_buscar_posicion(personaje->party, entrante);
    int cambio_1 = lista_borrar_de_posicion(personaje->party, pos_entrante);
    if(cambio_1 == ERROR) return ERROR;
    int cambio_2 = lista_insertar_en_posicion(personaje->party, entrante, pos_saliente);
    if(cambio_2 == ERROR) return ERROR;
    int cambio_3 = lista_insertar_en_posicion(personaje->party, saliente, pos_entrante);
    if(cambio_3 == ERROR) return ERROR;
}
/* 
* Dadas dos posicones, una de un pokemon en el party y otro en la caja,
* Quita el pokemon del party para agregar el de la caja.
* Pre : Ambas posiciones de los pokemones que sean válidas, personaje cargado
* Post: Party con un intercambio de pokemones
*/
int intercambiar_pokemones(personaje_t* personaje, size_t pkm_party, size_t pkm_box){
    pokemon_t* saliente = lista_elemento_en_posicion(personaje->party, pkm_party);
    saliente->elegido = false;

    int salida = lista_borrar_de_posicion(personaje->party, pkm_party);
    if(salida == ERROR) return ERROR;

    pokemon_t* entrante = lista_elemento_en_posicion(personaje->caja, pkm_box);
    if(!entrante) return ERROR;
    
    if(entrante->elegido)
        return intercambiar_del_party(personaje, saliente, pkm_party, entrante);
    
    entrante->elegido = true;
    int entrada = lista_insertar_en_posicion(personaje->party, entrante, pkm_party);
    if(entrada == ERROR) return ERROR;
    return JUEGO_JUGANDO;
}
//juego.h
void cambiar_party(juego_t* juego){
    if(!juego || !juego->personaje){
        juego_cambiar_estado(juego, ERROR);
        return;
    }       
    while(estado_interafaz(juego->interfaz, OPCION_CAMBIAR) && !estado_juego(juego, ERROR)){
        size_t pokemon_party = pedir_pokemon(juego->personaje->party, LISTA_COMBATE);
        size_t pokemon_caja = pedir_pokemon(juego->personaje->caja, LISTA_CAJA);
        int estado = intercambiar_pokemones(juego->personaje, pokemon_party, pokemon_caja);
        if(estado == ERROR)
            juego_cambiar_estado(juego, estado);
        menu_intercambio(juego->interfaz, juego->personaje);
    }     
}
