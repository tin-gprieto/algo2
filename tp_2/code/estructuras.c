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
* Destruye un pokemon (funcion para la lista_con_cada_elemento)
* Pre : Puntero a pokemon y extra == NULL
* Post: Pokemon liberado de la memoria
*/
bool pokemon_destructor(void* pokemon, void* extra){
    if(!pokemon) return false;
    free(pokemon);
    return true;
}   
/*
* Destruye una lista de pokemones
* Pre : Lista de pokemones creada
* Post: Lista destruida con sus pokemones liberados de la memoria
*/
void lista_pokemones_destruir(lista_t* pokemones){
    if(!pokemones)
        return;
    lista_con_cada_elemento(pokemones, pokemon_destructor, NULL);
    lista_destruir(pokemones);
}

/*
* Destruye un entrenador junto a la lista de pokemones
* Pre : Entrenador creado y cargado de un archivo
* Post: Memorio reservada para un entrenador liberada
*/
void entrenador_destruir(entrenador_t* entrenador){
    if(!entrenador)
        return;
    lista_pokemones_destruir(entrenador->pokemones);
    free(entrenador);
}
/*
* Destruye un pila de entrenadores en su totaldad
* Pre : Pila con entrenadores creada
* Post: Pila destruida junto a sus entrenadores
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
* Destruye un gimnasio (funcion para heap_crear)
* Pre : Puntero a gimnasio
* Post: Gimnasio destruido junto a su pila de entrenadores
*/
void gimnasio_destructor(void* elemento){
    if(!elemento)
        return;
    gimnasio_t* gimnasio = (gimnasio_t*) elemento;
    pila_entrenadores_destruir(gimnasio->entrenadores);
    free(gimnasio);
}
/*
* Condicion para el heap de gimnasios
* Pre : Punteros a gimnasios (padre e hijo)
* Post: Devuelve verdader si la dificultad
* del gimnasio padre es menor a la del gimnasio hijo
*/
bool gimnasio_condicion(void* padre, void* hijo){
    return ((gimnasio_t*)padre)->dificultad < ((gimnasio_t*)hijo)->dificultad;
}
//juego.h
bool gimnasio_vacio(gimnasio_t* gimnasio){
    return (!gimnasio || pila_vacia(gimnasio->entrenadores));
}
/*
* Dado un gimnasio, indica si su último entrenador está completo
* Pre : Gimnasio creado y leido
* Post: Verdadero si tiene al menos un entrenador y este tiene pokemones (siendo una cantidad menor al máximo)
*/
bool ultimo_entrenador_valido(gimnasio_t* gimnasio){
    if(!gimnasio)
        return false;
    if(!gimnasio->entrenadores || pila_vacia(gimnasio->entrenadores))
        return false;
    entrenador_t* ultimo = (entrenador_t*) pila_tope(gimnasio->entrenadores);
    if(lista_vacia(ultimo->pokemones) || lista_elementos(ultimo->pokemones) > MAX_POKEMONES)
        return false;
    return true;
}
/*
* Devuelve un booleano que indica si el gimnasio debe estar en el conjunto
* Pre : Gimnasio creado y leido
* Post: Verdedero si es un gimnasio válido para el conjunto
*/
bool gimnasio_valido(gimnasio_t* gimnasio){
    return (gimnasio && (pila_elementos(gimnasio->entrenadores) >= 2) && ultimo_entrenador_valido(gimnasio));

}
/*
* Destruye una pila de gimnasios
* Pre : Pila creada con gimnasios
* Post: Pila destruida junto a sus gimnasios dentro
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
* Devuelve verdadero si el personaje no tiene pokemones
* Pre : Puntero a personaje creado
* Post: Verdadero si no tiene las listas o están vacias
*/
bool personaje_vacio(personaje_t* personaje){
    if(!personaje) return true; 
    if (lista_vacia(personaje->caja) && lista_vacia(personaje->party))
        return true;
    return false;
}
/* 
* Inserta el pokemon en las listas (caja y party) del personaje según corresponda
* Pre : Personaje junto a sus listas creadas, pokemon creado e iniciaizado
* Post: Pokemon insertado minimo en la caja y determina si es elegido
* (si se inserta en el party es elegido)
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
* Crea un personaje en el heap inicializando su valores
* Pre : -
* Post: Personaje creado junto a sus listas o NULL en caso de error
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
* Inserta un pokemon en la lista del entrenador
* Pre : Entrenador creado con lista y pokemon leido del archivo
* Post: Nuevo pokemon a la lista del entrenador
*/
void entrenador_insertar_pokemon(entrenador_t** entrenador, pokemon_t* pokemon){
    if(!(*entrenador) || !(*entrenador)->pokemones)
        return;
    lista_insertar((*entrenador)->pokemones, (void*)pokemon);
}

/* 
* Dada una clave, evala si coincide con alguna de las claves válidas
* Pre : Clave prevaimente leida del archivo
* Post: Verdadero si es alguna de las clave posibles
*/
bool es_clave_valida(char clave){
    return (clave == CLAVE_GIMNASIO || clave == CLAVE_LIDER || clave == CLAVE_ENTRENADOR || clave == CLAVE_POKEMON);
}
/* 
* Lee una letra del archivo y según eso devuelve el estado de la lectura
* Pre : Archivo abierto y comienzo de la línea
* Post: LECTURA_CONTINUAR si la clave es válida
*       LECTURA_ERROR si no lo es o
*       LECTURA_FIN si se llegó al final del archivo
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
* Crea un pokemon el heap, inicializandolo con lo que lee de la linea
* Pre : Archivo abierto y CLAVE_POKEMON previamente leida
* Post: Puntero a pokemon con los datos del archivo
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
* Dado un archivo, lee un pokemon agregandolo a
* las listas del personaje según corresponda
* Pre : Archivo abierto, personaje creado y CLAVE_POKEMON previamente leida
* Post: Línea de pokemon leida y datos agregados como pokemon del personaje
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
* Dado un archico, crea un personaje con los datos de la linea
* Pre : Archivo abierto y CLAVE_ENTRENADOR previamente leida
* Post: Puntero a personaje o NULL en caso de error de creacion o lectura
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
* Crea un personaje a partir del archivo
* Pre : Archivo abierto y CLAVE_ENTRENADOR previamente leida
* Post: Estado de la lectura, LECTURA_ERROR si no pudo crear el personaje
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
* Carga un pokemon al último entrenador de la pila del último gimnasio
* Pre : Archivo abierto, pila de gimnasios creada y no vacía, y último gimnasio con entrenador
* Post: Pokemon cargado al último entrenador
*/
int pokemon_entrenador_leer(FILE* archivo, pila_t* gimnasios){
    if(!gimnasios || pila_vacia(gimnasios))
        return LECTURA_ERROR;
    gimnasio_t* gym_actual = (gimnasio_t*) pila_tope(gimnasios);
    if(!gym_actual->entrenadores || pila_vacia(gym_actual->entrenadores))
        return LECTURA_ERROR;
    entrenador_t* maestro = (entrenador_t*)pila_tope(gym_actual->entrenadores);
    if(!maestro)
        return LECTURA_ERROR;
    pokemon_t* pokemon = linea_pokemon_leer(archivo);
    if(!pokemon)
        return LECTURA_ERROR;
    int estado = lista_insertar(maestro->pokemones, (void*)pokemon);
    if(estado == ERROR || lista_elementos(maestro->pokemones) > MAX_POKEMONES)
        return LECTURA_ERROR;
    return LECTURA_CONTINUAR;
}
/* 
* Crea un entrenador a partir de la línea actual del archivo
* Pre : Archivo abierto, clave leida e igual a CLAVE_ENTRENADOR
* Post: Entrenador crado con lista de pokemones vacía
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
* Dado un archivo y una pila de gimnasios, agrega un entrenador al último de estos
* Pre : Archivo abierto, pila de gimnasios creada y no vacía
* Último gimnasio de la pila previamente cargado con un líder
* Post: Ultimo gimnasio con un nuevo entrenador(LECTURA_CONTINUAR) o LECTURA_ERROR
*/
int entrenador_leer(FILE* archivo, pila_t* gimnasios){
    if(!gimnasios || pila_vacia(gimnasios)) return LECTURA_ERROR;
    gimnasio_t* gym_actual = (gimnasio_t*) pila_tope(gimnasios);
    if(!(gym_actual->entrenadores) || pila_elementos(gym_actual->entrenadores) < 1)
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
* Dado un archivo abierto y una pila de gimnasios, agrega un líder
* al úĺtimo gimnasio de la lista (a su vez crea la pila de entrenadores)
* Pre : Archivo abierto y pila de gimnasios creada y no vacía
* Clave leida e igual a CLAVE_LIDER
* Post: Ultimo gimnasio con la pila de entrenadores creada y con el líder (LECTURA_CONTINUAR)
* o LECTURA_ERROR si no se pudo Realizar
*/
int lider_leer(FILE* archivo, pila_t* gimnasios){
    if(!gimnasios || pila_vacia(gimnasios))
        return LECTURA_ERROR;
    gimnasio_t* ultimo_gimnasio = (gimnasio_t*)pila_tope(gimnasios);
    if(!ultimo_gimnasio || ultimo_gimnasio->entrenadores)
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
* Dado un archivo, crea un gimnasio según la linea actual
* Pre : Archivo abierto y clave leida e igual a CLAVE_GIMNASIO
* Post: Gimnasio creado o NULL en caso de error
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
* Dado un archivo y una pila de gimnasios, inserta un gimnasio
* leyendolo desde el archivo
* Pre : Archivo abierto y pila de gimnasios creado
* Post: Pila de gimnasios con un nuevo gimnasio (LECTURA_CONTINUAR)
* o LECTURA_ERROR en caso de que haya un error
*/
int gimnasio_leer(FILE* archivo, pila_t* gimnasios){
    if(!gimnasios)
        return LECTURA_ERROR;
    if(!pila_vacia(gimnasios)){
        gimnasio_t* gimnasio_anterior = (gimnasio_t*)pila_tope(gimnasios);
        if(!gimnasio_valido(gimnasio_anterior))
            return LECTURA_ERROR;
    }
    gimnasio_t* actual = linea_gimnasio_leer(archivo);
    if(!actual) return LECTURA_ERROR;
    pila_apilar(gimnasios, (void*)actual);
    return LECTURA_CONTINUAR;
}
/*
* Traspasa los gimnasios de una pila a un heap
* Pre :  Pila de gimnasios creada y no vacia
* Post: Heap creado con gimnasios y Pila destruida
*/
heap_t* pasar_pila_a_heap(pila_t* gimnasios){
    if(!gimnasios || pila_vacia(gimnasios)){
        if(gimnasios)
            pila_gimnasios_destruir(gimnasios);
        return NULL;
    }
    heap_t* heap = heap_crear(gimnasio_condicion, gimnasio_destructor);
    if(!heap){
        pila_gimnasios_destruir(gimnasios);
        return NULL;
    }
    while(!pila_vacia(gimnasios)){
        gimnasio_t* aux = (gimnasio_t*)pila_tope(gimnasios);
        heap_insertar(heap, aux);
        pila_desapilar(gimnasios);
    }
    pila_destruir(gimnasios);
    return heap;
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
            lectura = gimnasio_leer(archivo, gimnasios);
        }else if(clave == CLAVE_LIDER){
            lectura = lider_leer(archivo, gimnasios);
        }else if(clave == CLAVE_ENTRENADOR){
            lectura = entrenador_leer(archivo, gimnasios);
        }else if(clave == CLAVE_POKEMON){
            lectura = pokemon_entrenador_leer(archivo, gimnasios);
        }else
            lectura = LECTURA_ERROR;
        
        if(lectura == LECTURA_CONTINUAR)
            lectura= clave_leer(archivo, &clave);
    }
    if(pila_vacia(gimnasios) || lectura == LECTURA_ERROR){
        pila_gimnasios_destruir(gimnasios);
        return NULL;
    }
    gimnasio_t* gimnasio_anterior = (gimnasio_t*)pila_tope(gimnasios);
    if(!gimnasio_valido(gimnasio_anterior)){
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
