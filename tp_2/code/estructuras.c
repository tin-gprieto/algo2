#include "estructuras.h"

static const char CLAVE_GIMNASIO   = 'G';
static const char CLAVE_LIDER      = 'L';
static const char CLAVE_ENTRENADOR = 'E';
static const char CLAVE_POKEMON    = 'P';

//static const int LEIDOS_CLAVE      = 1;
static const int LEIDOS_POKEMON    = 4;
static const int LEIDOS_GIMNASIO   = 3;
static const int LEIDOS_ENTRENADOR = 1;

static const int LECTURA_CONTINUAR = 1;
static const int LECTURA_ERROR     = -1;
static const int LECTURA_FIN       = 0;

static const int MAX_POKEMONES         = 6;

//#define FORMATO_CLAVE "%c;"
#define FORMATO_ENTRENADOR ";%49[^\n]\n"
#define FORMATO_GIMNASIO ";%49[^;];%i;%i\n"
#define FORMATO_POKEMON ";%49[^;];%i;%i;%i\n"

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
void gimnasio_destructor(void* elemento){
    if(!elemento)
        return;
    gimnasio_t* gimnasio = (gimnasio_t*) elemento;
    pila_entrenadores_destruir(gimnasio->entrenadores);
    free(gimnasio);
}
/*
*
* Pre :
* Post:
*/
bool gimnasio_condicion(void* padre, void* hijo){
    return ((gimnasio_t*)padre)->dificultad < ((gimnasio_t*)hijo)->dificultad;
}
/*
*
* Pre :
* Post:
*/
bool gimnasio_vacio(gimnasio_t* gimnasio){
    return (!gimnasio || pila_vacia(gimnasio->entrenadores));
}
/*
*
* Pre :
* Post:
*/
void pila_gimnasios_destruir(pila_t* gimnasios){
    if(!gimnasios)
        return;
    while(!pila_vacia(gimnasios)){
        gimnasio_t* actual = (gimnasio_t*) pila_tope(gimnasios);
        gimnasio_destructor(actual);
        pila_desapilar(gimnasios);
    }
    pila_destruir(gimnasios);    
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
void personaje_insertar_pokemon(personaje_t* personaje, pokemon_t* pokemon){
    if(!personaje || !personaje->party || !personaje->caja)
        return;
    if(lista_elementos(personaje->party) < MAX_POKEMONES){
        pokemon->elegido = true;
        lista_insertar(personaje->party, (void*) pokemon);
    }
    lista_insertar(personaje->caja, (void*) pokemon);
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
bool es_clave_valida(char clave){
    return (clave == CLAVE_GIMNASIO || clave == CLAVE_LIDER || clave == CLAVE_ENTRENADOR || clave == CLAVE_POKEMON);
}
/* 
*
* Pre :
* Post:
*/
int clave_leer(FILE* archivo, char* clave){
    int leido = fgetc(archivo);
    if(leido == EOF)
        return LECTURA_FIN;
    
    (*clave) = (char) leido;
    if(es_clave_valida(*clave))
        return LECTURA_CONTINUAR;
    return LECTURA_ERROR;
}
/* 
*
* Pre :
* Post:
*/
pokemon_t* linea_pokemon_leer(FILE * archivo){
    pokemon_t* pokemon = malloc(sizeof(pokemon_t));
    if(!pokemon)
        return NULL;
    int leidos = fscanf(archivo, FORMATO_POKEMON, pokemon->nombre, 
                                                &(pokemon->velocidad),
                                                &(pokemon->ataque),
                                                &(pokemon->defensa));   
    if(leidos != LEIDOS_POKEMON){
        free(pokemon);
        return NULL;
    }
    pokemon->nivel = 0;
    pokemon->elegido = false;
    return pokemon;
}
/* 
*
* Pre :
* Post:
*/
int pokemon_personaje_leer(FILE * archivo, personaje_t** personaje){
    if(!(*personaje))
        return LECTURA_ERROR;
    pokemon_t* pkm_actual = NULL;
    pkm_actual = linea_pokemon_leer(archivo);
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
personaje_t* linea_personaje_leer(FILE * archivo){
    personaje_t* personaje = personaje_crear();
    if(!personaje)
        return NULL;
    int leidos = fscanf(archivo, FORMATO_ENTRENADOR, personaje->nombre);
    if(leidos != LEIDOS_ENTRENADOR){
        personaje_destruir(personaje);
        return NULL;
    }
    return personaje;
}
/* 
*
* Pre :
* Post:
*/
int personaje_leer(FILE * archivo, personaje_t** personaje){
    if((*personaje))
        return LECTURA_ERROR;
    (*personaje) = linea_personaje_leer(archivo);
    if(!(*personaje))
        return LECTURA_ERROR;
    return LECTURA_CONTINUAR;
}
/* 
* Dado un archivo, crea un personaje con la información dentro
* Pre : Archivo abierto para lectura
* Post: Personaje creado en memoria dinámica
*/
personaje_t* archivo_personaje_leer(FILE * archivo){
    personaje_t* personaje = NULL;
    char clave;
    int lectura = clave_leer(archivo, &clave);
    while(lectura == LECTURA_CONTINUAR){
        if(clave == CLAVE_ENTRENADOR)
            lectura = personaje_leer(archivo, &personaje);
        else if(clave == CLAVE_POKEMON)
            lectura = pokemon_personaje_leer(archivo, &personaje);
        else
            lectura = LECTURA_ERROR;
    
        if(lectura == LECTURA_CONTINUAR)
            lectura= clave_leer(archivo, &clave);
    }
    if(personaje_vacio(personaje) || lectura == LECTURA_ERROR){
        personaje_destruir(personaje);
        return NULL;
    }
    return personaje;
}
/* 
* 
* Pre :
* Post:
*/
int pokemon_entrenador_leer(FILE* archivo, pila_t* gimnasios){
    if(!gimnasios || pila_vacia(gimnasios))
        return LECTURA_ERROR;
    gimnasio_t* gym_actual = (gimnasio_t*) pila_tope(gimnasios);
    if(!gym_actual->entrenadores || pila_vacia(gym_actual->entrenadores))
        return LECTURA_ERROR;
    entrenador_t* maestro = (entrenador_t*)pila_tope(gym_actual->entrenadores);
    pokemon_t* pokemon = linea_pokemon_leer(archivo);
    if(!pokemon || lista_elementos(maestro->pokemones) > MAX_POKEMONES)
        return LECTURA_ERROR;

    int estado = lista_insertar(maestro->pokemones, (void*)pokemon);
    if(estado == ERROR)
        return LECTURA_ERROR;
    return LECTURA_CONTINUAR;
}
/* 
* 
* Pre :
* Post:
*/
entrenador_t* linea_entrenador_leer(FILE * archivo){
    entrenador_t* entrenador = malloc(sizeof(entrenador_t));
    if(!entrenador)
        return NULL;
    int leidos = fscanf(archivo, FORMATO_ENTRENADOR, entrenador->nombre);
    if(leidos != LEIDOS_ENTRENADOR){
        entrenador_destruir(entrenador);
        return NULL;
    }
    entrenador->pokemones = lista_crear();
    if(!entrenador->pokemones)
        return NULL;
    return entrenador;
}
/* 
* 
* Pre :
* Post:
*/
int entrenador_leer(FILE* archivo, pila_t* gimnasios){
    if(!gimnasios || pila_vacia(gimnasios)) return LECTURA_ERROR;
    gimnasio_t* gym_actual = (gimnasio_t*) pila_tope(gimnasios);
    if(!(gym_actual->entrenadores) || pila_elementos(gym_actual->entrenadores) < 1 )
        return LECTURA_ERROR;
    entrenador_t* ultimo_entrenador = (entrenador_t*) pila_tope(gym_actual->entrenadores);
    if(lista_vacia(ultimo_entrenador->pokemones))
        return LECTURA_ERROR;

    entrenador_t* entrenador = linea_entrenador_leer(archivo);
    if(!entrenador)
        return LECTURA_ERROR;

    int estado = pila_apilar(gym_actual->entrenadores, (void*) entrenador);
    if(estado == ERROR){
        entrenador_destruir(entrenador);
        return LECTURA_ERROR;
    }
    return LECTURA_CONTINUAR;
}
/* 
* 
* Pre :
* Post:
*/
int lider_leer(FILE* archivo, pila_t* gimnasios){
<<<<<<< Updated upstream
    if(!gimnasios || !pila_vacia(gimnasios))
=======
    if(pila_vacia(gimnasios))
>>>>>>> Stashed changes
        return LECTURA_ERROR;
    gimnasio_t* ultimo_gimnasio = (gimnasio_t*)pila_tope(gimnasios);
    if(!ultimo_gimnasio)
        return LECTURA_ERROR;

    pila_t* aux = pila_crear();
    if(!aux)
        return LECTURA_ERROR;
    ultimo_gimnasio->entrenadores = aux;
    
    entrenador_t* lider = linea_entrenador_leer(archivo);
    if(!lider){
        return LECTURA_ERROR;
    }

    int estado = pila_apilar(ultimo_gimnasio->entrenadores, (void*)lider);

    if(estado == ERROR)
        return LECTURA_ERROR;

    return LECTURA_CONTINUAR;
    
}
/* 
* 
* Pre :
* Post:
*/
gimnasio_t* linea_gimnasio_leer(FILE* archivo){
    gimnasio_t auxiliar;
    int leidos = fscanf(archivo, FORMATO_GIMNASIO, auxiliar.nombre, &(auxiliar.dificultad), &(auxiliar.id_batalla));
    if(leidos != LEIDOS_GIMNASIO)
        return NULL;
    gimnasio_t* gimnasio = malloc(sizeof(gimnasio_t));
    if(!gimnasio)
        return NULL;
    (*gimnasio) = auxiliar;
    gimnasio->estado = GIMNASIO_PELEANDO;
    gimnasio->entrenadores = NULL;
    return gimnasio;
}
/* 
* 
* Pre :
* Post:
*/
int gimnasio_leer(FILE* archivo, pila_t* gimnasios){
    if(!gimnasios)
        return LECTURA_ERROR;
    gimnasio_t* actual = linea_gimnasio_leer(archivo);
    if(!actual) return LECTURA_ERROR;
    pila_apilar(gimnasios, (void*)actual);
    return LECTURA_CONTINUAR;
}
/* 
* 
* Pre :
* Post:
*/
heap_t* pasar_pila_a_heap(pila_t* gimnasios){
    if(!gimnasios || pila_vacia(gimnasios))
        return NULL;
    heap_t* heap = heap_crear(gimnasio_condicion, gimnasio_destructor);
    if(!heap) return NULL;
    
    while(!pila_vacia(gimnasios)){
        gimnasio_t* aux = (gimnasio_t*)pila_tope(gimnasios);
        heap_insertar(heap, aux);
        pila_desapilar(gimnasios);
    }
    pila_destruir(gimnasios);
    return NULL;
}
/* 
* Dado un archivo, crea un heap de gimnasios con la información dentro
* Pre : Archivo abierto para lectura
* Min un gimnansio, cada gimnasio debe tener mínimo un líder y un entrenador 
* (con al menos un pokemon cada uno)
* Post: Heap minimal con todos los gimnasios dentro
*/
heap_t* archivo_gimnasios_leer(FILE * archivo){
    pila_t * gimnasios = pila_crear();
    if(!gimnasios)
        return NULL;
    char clave;
    int lectura = clave_leer(archivo, &clave);
    while(lectura == LECTURA_CONTINUAR){
        if(clave == CLAVE_GIMNASIO){
            if(pila_vacia(gimnasios) || !gimnasio_vacio((gimnasio_t*)pila_tope(gimnasios)))
                lectura = gimnasio_leer(archivo, gimnasios);
            else
                lectura = LECTURA_ERROR;
        }else if(clave == CLAVE_LIDER){
            lectura = lider_leer(archivo, gimnasios);
        }else if(clave == CLAVE_ENTRENADOR){
            lectura = entrenador_leer(archivo, gimnasios);
        }else if(clave == CLAVE_POKEMON){
            lectura = pokemon_entrenador_leer(archivo, gimnasios);
        }
            lectura = LECTURA_ERROR;
        
        if(lectura == LECTURA_CONTINUAR)
            lectura= clave_leer(archivo, &clave);
    }

    if(pila_vacia(gimnasios) || lectura == LECTURA_ERROR){
        pila_gimnasios_destruir(gimnasios);
        return NULL;
    }
    return pasar_pila_a_heap(gimnasios);  
}
//estructuras.h
personaje_t* personaje_cargar(char ruta_archivo[MAX_STRING]){
    FILE * archivo = fopen(ruta_archivo, LECTURA);
    if(!archivo)
        return NULL;
    personaje_t* personaje = archivo_personaje_leer(archivo);
    fclose(archivo);
    return personaje;
}
//estructuras.h
void personaje_destruir(personaje_t* personaje){
    if(!personaje)
        return;
    lista_pokemones_destruir(personaje->caja);
    lista_destruir(personaje->party);
    free(personaje);
}
//estructuras.h
heap_t* gimnasios_cargar(char ruta_archivo[MAX_STRING]){
    FILE * archivo = fopen(ruta_archivo, LECTURA);
    if(!archivo)
        return NULL;
    heap_t* gimnasios = archivo_gimnasios_leer(archivo);
    fclose(archivo);
    return gimnasios;
}
//estructuras.h
bool gimnasio_estado(gimnasio_t* gimnasio, int estado){
    if(gimnasio)
        return gimnasio->estado == estado;
    return false;
}
//estructuras.h
void gimnasio_cambiar_estado(gimnasio_t* gimnasio, int nuevo_estado){
    if(gimnasio)
        gimnasio->estado = nuevo_estado;
}
//estructuras.h
entrenador_t* gimnasio_ultimo_entrenador(gimnasio_t* gimnasio){
    if(gimnasio_vacio(gimnasio))
        return NULL;
    return (entrenador_t*) pila_tope(gimnasio->entrenadores); 
}
//estructuras.h
void gimnasio_siguiente_entrenador(gimnasio_t* gimnasio){
    if(!gimnasio) return;
    entrenador_destruir(gimnasio_ultimo_entrenador(gimnasio));
    pila_desapilar(gimnasio->entrenadores);
}
