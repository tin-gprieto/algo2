#include "hash.h"

#define FACTOR_MAXIMO 0.75
#define AUMENTO_REHASH 3

#define ERROR -1
#define EXITO 0

const int INSERCION_NUEVA = 0;
const int INSERCION_REPETIDA = 1;
const int INSERCION_COLISION = 2;

typedef void (*dato_destructor_t)(dato_t *, hash_destructor_t);

void dato_destruir(dato_t * dato, hash_destructor_t destructor_elemento){
    if(destructor_elemento)
        destructor_elemento(dato->elemento);
    free(dato);
}

float factor_de_carga(hash_t* hash){
    return (float) hash->ocupado / (float) hash->tamanio;
}

size_t valor_hash(const char * clave){
    size_t valor = 0;
    for(int i=0; i < strlen(clave); i++)
        valor += (size_t) clave[i];
    return valor;
}

void lista_colisiones_destruir(lista_t* colisiones, dato_destructor_t destructor_dato, hash_destructor_t destructor_elemento){
    if(!colisiones) return;
    if(destructor_dato){
        lista_iterador_t * iterador = lista_iterador_crear(colisiones);
        if(!iterador) return;
        while(lista_iterador_tiene_siguiente(iterador)){
            dato_t* actual = lista_iterador_elemento_actual(iterador);
            destructor_dato(actual, destructor_elemento);
            lista_iterador_avanzar(iterador);
        }
        lista_iterador_destruir(iterador);
    }
    lista_destruir(colisiones);
}

void tabla_destruir(hash_t* hash, dato_destructor_t destructor_dato){
    if(!hash || !hash->tabla) return;
    for(int i=0; i < hash->tamanio; i++){
        if(hash->tabla[i]){
            lista_colisiones_destruir(hash->tabla[i], destructor_dato, hash->destructor);                

        }
    }
    free(hash->tabla);
}

lista_t** tabla_crear(size_t tamanio){
    lista_t** tabla = calloc(tamanio, sizeof(lista_t*));
    if(!tabla)
        return NULL;
    for (size_t i= 0; i < tamanio; i++)
        tabla[i] = NULL;
    return tabla;
}

//hash.h
void hash_destruir(hash_t* hash){
    tabla_destruir(hash, dato_destruir);
    free(hash);
}

//hash.h
hash_t* hash_crear(hash_destructor_t destruir_elemento, size_t capacidad){
    if(capacidad <= 0) return NULL;
    hash_t* hash = malloc(sizeof(hash_t));
    if(!hash) return NULL;
    hash->destructor = destruir_elemento;
    hash->tamanio = capacidad;
    hash->elementos = 0;
    lista_t** aux = tabla_crear(hash->tamanio);
    if(!aux){
        free(hash); 
        return NULL;
    }
    hash->tabla = aux;
    hash->tamanio = hash->tamanio * AUMENTO_REHASH;
    return hash;
}
int buscar_dato(lista_t* colisiones, const char* clave){
    lista_iterador_t* iterador = lista_iterador_crear(colisiones);
    if(!iterador) return ERROR;
    bool encontro = false;
    int pos = 0;
    while(lista_iterador_tiene_siguiente(iterador) && !encontro){
        dato_t* actual = lista_iterador_elemento_actual(iterador);
        if(strcmp(actual->clave, clave) == 0)
            encontro = true;
        else{
            lista_iterador_avanzar(iterador);
            pos++;
        }
    }
    lista_iterador_destruir(iterador);
    if(!encontro) return ERROR;
    return pos;
}

dato_t* buscar_dato_repetido(lista_t* colisiones, const char* clave){
    if(!colisiones) return NULL;
    int pos = buscar_dato(colisiones, clave);
    if(pos == ERROR) return NULL;
    dato_t* repetido = lista_elemento_en_posicion(colisiones, (size_t) pos);
    return repetido;
}

int insertar_dato_en_tabla(lista_t** tabla, size_t pos, dato_t* dato){
    int estado;

    if(!tabla[pos]){
        lista_t* lista = lista_crear();
        if(!lista)  return ERROR;
        tabla[pos] = lista;
        estado = lista_insertar(lista, dato);
        if(estado == ERROR) return ERROR;
        return INSERCION_NUEVA;
    }
    dato_t* repetido = buscar_dato_repetido(tabla[pos], dato->clave);
    if(repetido){
        repetido->elemento = dato->elemento;
        free(dato);
        return INSERCION_REPETIDA;
    }
    estado = lista_insertar(tabla[pos], dato);
    if(estado == ERROR) return ERROR;
    return INSERCION_COLISION;
}

int copiar_datos_a_lista(lista_t* datos, lista_t* lista){
    lista_iterador_t* iterador = lista_iterador_crear(datos);
    if(!iterador) return ERROR;
    int estado = EXITO;
    while(lista_iterador_tiene_siguiente(iterador) && estado != ERROR){
        dato_t* actual = lista_iterador_elemento_actual(iterador);
        estado = lista_insertar(lista, actual);
        lista_iterador_avanzar(iterador);
    }
    lista_iterador_destruir(iterador);
    return estado;
}

lista_t* traspasar_tabla(lista_t** tabla, size_t tamanio){
    lista_t* datos = lista_crear();
    if(!datos) return NULL;
    int estado = EXITO;
    size_t i = 0;
    while((i < tamanio) && (estado != ERROR)){
        if(tabla[i])
            estado = copiar_datos_a_lista(tabla[i], datos);
        i++;
    }
    if(estado == ERROR){
        lista_destruir(datos);
        return NULL;
    }
    return datos;
}

int reinsertar_datos(lista_t** tabla, size_t tamanio, lista_t* datos){
    lista_iterador_t * iterador = lista_iterador_crear(datos);
    if(!iterador) return ERROR;
    int insercion = EXITO;
    int ocupado = 0;
    while(lista_iterador_tiene_siguiente(iterador) && insercion != ERROR){
        dato_t* dato = lista_iterador_elemento_actual(iterador);
        size_t pos = valor_hash(dato->clave) % tamanio;
        insercion = insertar_dato_en_tabla(tabla, pos, dato);
        if(insercion == INSERCION_NUEVA)
            ocupado ++;
        lista_iterador_avanzar(iterador);
    }
    lista_iterador_destruir(iterador);
    if(insercion == ERROR)
        return ERROR;
    return ocupado;

}

int rehashear_tabla(hash_t* hash){
    lista_t* datos = traspasar_tabla(hash->tabla, hash->tamanio);
    if(!datos) return ERROR;
    size_t nuevo_tamanio = hash->tamanio * AUMENTO_REHASH;
    lista_t** nueva_tabla = tabla_crear(nuevo_tamanio);
    if(!nueva_tabla){
        lista_destruir(datos);
        return ERROR;
    } 
    int estado = reinsertar_datos(nueva_tabla, nuevo_tamanio, datos);
    if(estado == ERROR){
        lista_destruir(datos);
        return ERROR;
    }
    tabla_destruir(hash, NULL); //Destruir tabla anterior (sin destruir los datos)
    lista_destruir(datos); //Destruir lista auxiliar (sin destruir los datos)
    hash->tabla = nueva_tabla; 
    hash->tamanio = nuevo_tamanio;
    hash->ocupado = (size_t) estado;
    return EXITO;
}

//hash.h
int hash_insertar(hash_t* hash, const char* clave, void* elemento){
    if(!hash || !clave) return ERROR;
    dato_t* dato = malloc(sizeof(dato_t));
    if(!dato) return ERROR;
    dato->clave = clave;
    dato->elemento = elemento;
    size_t pos = valor_hash(clave) % hash->tamanio;
    int insercion = insertar_dato_en_tabla(hash->tabla, pos, dato);
    if(insercion == ERROR) return ERROR;
    if(insercion == INSERCION_NUEVA)
        hash->ocupado++;
    hash->elementos ++;
    if(factor_de_carga(hash) > FACTOR_MAXIMO)
        return rehashear_tabla(hash);
    return EXITO;
}
//hash.h
int hash_quitar(hash_t* hash, const char* clave){
    if(!hash || !clave) return ERROR;
    size_t pos_tabla = valor_hash(clave) % hash->tamanio;
    int pos_lista = buscar_dato(hash->tabla[pos_tabla], clave);
    if(pos_lista == ERROR) return ERROR;
    dato_t* eliminado = lista_elemento_en_posicion(hash->tabla[pos_tabla], (size_t)pos_lista);
    if(!eliminado) return ERROR;
    dato_destruir(eliminado, hash->destructor);
    return lista_borrar_de_posicion(hash->tabla[pos_tabla], (size_t) pos_lista);
}
//hash.h
void* hash_obtener(hash_t* hash, const char* clave){
    if(!hash || !clave) return NULL;
    size_t pos_tabla = valor_hash(clave) % hash->tamanio;
    int pos_lista = buscar_dato(hash->tabla[pos_tabla], clave);
    if(pos_lista == ERROR) return NULL;
    dato_t* dato = lista_elemento_en_posicion(hash->tabla[pos_tabla], (size_t)pos_lista);
    if(!dato) return NULL;
    return dato->elemento;
}
//hash.h
bool hash_contiene(hash_t* hash, const char* clave){
    if(!hash || !clave) return false;
    size_t pos_tabla = valor_hash(clave) % hash->tamanio;
    int pos_lista = buscar_dato(hash->tabla[pos_tabla], clave);
    if(pos_lista == ERROR) return false;
    return true;
}
//hash.h
size_t hash_cantidad(hash_t* hash){
    if(hash) return hash->elementos;
    return 0;
}
//hash.h
size_t hash_con_cada_clave(hash_t* hash, bool (*funcion)(hash_t* hash, const char* clave, void* aux), void* aux){
    return 0;
}
