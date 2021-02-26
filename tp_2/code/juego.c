#include "juego.h"

static const char CLAVE_GIMNASIO= 'G';
static const char CLAVE_LIDER = 'L';
static const char CLAVE_ENTRENADOR = 'E';
static const char CLAVE_POKEMON = 'P';

static const int LEIDOS_POKEMON = 4;
//static const int LEIDOS_GIMNASIO = 3;
static const int LEIDOS_CLAVE = 1;
static const int LEIDOS_ENTRENADOR = 1;

static const int LECTURA_CONTINUAR = 1;
static const int LECTURA_ERROR = -1;
static const int LECTURA_FIN = 0;

static const int MAX_PARTY= 6;

#define FORMATO_CLAVE "%c;"
#define FORMATO_ENTRENADOR "%50[^\n]\n"
#define FORMATO_GIMNASIO "%50[^;];%i;%i\n"
#define FORMATO_POKEMON "%50[^;];%i;%i;%i\n"

/*
*
* Pre :
* Post:
*/
bool pokemon_destructor(void* pokemon, void* extra){
    if(pokemon)
        free(pokemon);
    return true;
}   
/*
*
* Pre :
* Post:
*/
void lista_pokemones_destruir(lista_t* pokemones){
    if(!pokemones)
        return;
    lista_con_cada_elemento(pokemones, pokemon_destructor, NULL);
    lista_destruir(pokemones);
}

/*
*
* Pre :
* Post:
*/
void entrenador_destruir(entrenador_t* entrenador){
    if(!entrenador)
        return;
    lista_pokemones_destruir(entrenador->pokemones);
    free(entrenador);
}
/*
*
* Pre :
* Post:
*/
void pila_entrenadores_destruir(pila_t* entrenadores){
    if(!entrenadores)
        return;
    while(!pila_vacia(entrenadores)){
        entrenador_t* actual = (entrenador_t*) pila_tope(entrenadores);
        entrenador_destruir(actual);
        pila_desapilar(entrenadores);
    }
    pila_destruir(entrenadores);    
}
/*
*
* Pre :
* Post:
*/
void gimnasio_destructor(gimnasio_t* gimnasio){
    if(!gimnasio)
        return;
    pila_entrenadores_destruir(gimnasio->entrenadores);
    free(gimnasio);
}
//juego.h
void personaje_destruir(personaje_t* personaje){
    if(!personaje)
        return;
    lista_pokemones_destruir(personaje->caja);
    lista_destruir(personaje->party);
    free(personaje);
}
/* 
*
* Pre :
* Post:
*/
bool personaje_vacio(personaje_t* personaje){
    if(!personaje) return true; 
    if (lista_vacia(personaje->caja) && lista_vacia(personaje->party))
        return true;
    return false;
}
/* 
*
* Pre :
* Post:
*/
personaje_t* personaje_crear(){
    personaje_t* aux = malloc(sizeof(personaje_t));
    if(!aux)
        return NULL;
    aux->medallas = 0;
    lista_t* lista_aux = lista_crear();
    if(!lista_aux){
        free(aux);
        return NULL;
    }
    aux->caja = lista_aux;
    lista_aux = lista_crear();
    if(!lista_aux){
        lista_destruir(aux->caja);
        free(aux);
        return NULL;
    }
    aux->party = lista_aux;
    return aux;
}
/* 
*
* Pre :
* Post:
*/
personaje_t* leer_linea_personaje(FILE * archivo){
    personaje_t* auxiliar = personaje_crear();
    if(!auxiliar)
        return NULL;
    int leidos = fscanf(archivo, FORMATO_ENTRENADOR, auxiliar->nombre);
    if(leidos != LEIDOS_ENTRENADOR){
        personaje_destruir(auxiliar);
        return NULL;
    }
    return auxiliar;
}
/* 
*
* Pre :
* Post:
*/
void personaje_insertar_pokemon(personaje_t* personaje, pokemon_t* pokemon){
    if(!personaje || !personaje->party || !personaje->caja)
        return;
    if(lista_elementos(personaje->party) < MAX_PARTY){
        pokemon->elegido = true;
        lista_insertar(personaje->party, (void*) pokemon);
    }else{
        pokemon->elegido = false;
    }
    lista_insertar(personaje->caja, (void*) pokemon);
}
/* 
*
* Pre :
* Post:
*/
void entrenador_insertar_pokemon(entrenador_t** entrenador, pokemon_t* pokemon){
    if(!(*entrenador) || !(*entrenador)->pokemones)
        return;
    lista_insertar((*entrenador)->pokemones, (void*)pokemon);
}
/* 
*
* Pre :
* Post:
*/
pokemon_t* leer_linea_pokemon(FILE * archivo){
    pokemon_t* auxiliar = malloc(sizeof(pokemon_t));
    if(!auxiliar)
        return NULL;
    int leidos = fscanf(archivo, FORMATO_POKEMON, auxiliar->nombre, 
                                                &(auxiliar->velocidad),
                                                &(auxiliar->ataque),
                                                &(auxiliar->defensa));   
    if(leidos != LEIDOS_POKEMON){
        free(auxiliar);
        return NULL;
    }
    auxiliar->nivel = 0;
    return auxiliar;
}
/* 
*
* Pre :
* Post:
*/
int leer_personaje(FILE * archivo, personaje_t** personaje){
    if((*personaje))
        return LECTURA_ERROR;

    (*personaje) = leer_linea_personaje(archivo);
    if(!(*personaje))
        return LECTURA_ERROR;
    return LECTURA_CONTINUAR;
}
/* 
*
* Pre :
* Post:
*/
int leer_pokemon_personaje(FILE * archivo, personaje_t** personaje){
    if(!(*personaje))
        return LECTURA_ERROR;
    
    pokemon_t* pkm_actual = NULL;
    pkm_actual = leer_linea_pokemon(archivo);
    if(!pkm_actual)
        return LECTURA_ERROR;
    personaje_insertar_pokemon(*personaje, pkm_actual);
    return LECTURA_CONTINUAR;
}
/* 
*
* Pre :
* Post:
*/
bool es_clave_valida(char clave){
    return (clave == CLAVE_GIMNASIO || clave == CLAVE_LIDER || clave == CLAVE_ENTRENADOR || clave == CLAVE_POKEMON);
}
/* 
*
* Pre :
* Post:
*/
int hay_clave(FILE* archivo, char* clave){
    int leidos = fscanf(archivo, FORMATO_CLAVE, clave);
    if(leidos != LEIDOS_CLAVE){
        if(leidos == EOF)
            return LECTURA_FIN;
        return LECTURA_ERROR;
    }
    if(es_clave_valida(*clave))
        return LECTURA_CONTINUAR;
    return LECTURA_ERROR;
}
/* 
* Dado un archivo, crea un personaje con la información dentro
* Pre : Archivo abierto para lectura
* Post: Personaje creado en memoria dinámica
*/
personaje_t* leer_archivo_personaje(FILE * archivo){
    personaje_t* personaje = NULL;
    char clave;
    int lectura = hay_clave(archivo, &clave);
    while(lectura == LECTURA_CONTINUAR){
        if(clave == CLAVE_ENTRENADOR)
            lectura = leer_personaje(archivo, &personaje);
        else if(clave == CLAVE_POKEMON)
            lectura = leer_pokemon_personaje(archivo, &personaje);
        else
            lectura = LECTURA_ERROR;
    
        if(lectura == LECTURA_CONTINUAR)
            lectura= hay_clave(archivo, &clave);
    }

    if(lectura == LECTURA_ERROR){
        personaje_destruir(personaje);
        return NULL;
    }
    if(personaje_vacio(personaje)){
        personaje_destruir(personaje);
        return NULL;
    }
    return personaje;
}
/* 
* Dado un archivo, crea un heap de gimnasios con la información dentro
* Pre : Archivo abierto para lectura
* Post: Heap minimal con todos los gimnasios dentro
*/
heap_t* leer_archivo_gimnasios(FILE * archivo){
    return NULL;    
}
//juego.h
personaje_t* personaje_cargar(char ruta_archivo[MAX_STR]){
    FILE * archivo = fopen(ruta_archivo, LECTURA);
    if(!archivo)
        return NULL;
    personaje_t* personaje = leer_archivo_personaje(archivo);
    fclose(archivo);
    return personaje;
}
//juego.h
heap_t* gimnasios_cargar(char ruta_archivo[MAX_STR]){
    FILE * archivo = fopen(ruta_archivo, LECTURA);
    if(!archivo)
        return NULL;
    heap_t* gimnasios = leer_archivo_gimnasios(archivo);
    fclose(archivo);
    return gimnasios;
}
//juego.h
bool gimnasio_estado(gimnasio_t* gimnasio, int estado){
    return gimnasio->estado == estado;
}
//juego.h
void gimnasio_cambiar_estado(gimnasio_t* gimnasio, int nuevo_estado){
    gimnasio->estado = nuevo_estado;
}
//juego.h
entrenador_t* gimnasio_ultimo_entrenador(gimnasio_t* gimnasio){
    return (entrenador_t*) pila_tope(gimnasio->entrenadores); 
}
/*
*
* Pre :
* Post:
*/
int batalla_luchar(personaje_t* personaje, entrenador_t* entrenador, funcion_batalla batalla, mostrar_batalla menu){
    return DERROTA;
}
/*
*
* Pre :
* Post:
*/
void gimnasio_siguiente_entrenador(gimnasio_t* gimnasio){
    entrenador_destruir(gimnasio_ultimo_entrenador(gimnasio));
    pila_desapilar(gimnasio->entrenadores);
}
//juego.h
int gimnasio_batalla(gimnasio_t* gimnasio, personaje_t* personaje, funcion_batalla batalla, mostrar_batalla menu){
    entrenador_t* entrenador = gimnasio_ultimo_entrenador(gimnasio);
    int resultado = batalla_luchar(personaje, entrenador, batalla, menu);
    if(resultado == VICTORIA){
        if(pila_elementos(gimnasio->entrenadores) == 1){
            return VICTORIA; 
        }else{
            gimnasio_siguiente_entrenador(gimnasio);
            return PELEANDO;
        }
    }
    return DERROTA;
    
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
