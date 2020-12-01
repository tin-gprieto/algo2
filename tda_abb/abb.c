#include "abb.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#define ERROR -1
#define MAYOR 1
#define MENOR -1
#define IGUAL 0
#define ERROR_PUNTERO NULL

typedef struct array{
    void** vector;
    size_t posicion;
    size_t tamanio;
} array_t;

bool es_hoja(nodo_abb_t* nodo){
    if(!nodo) return true; 
    if ((!nodo->izquierda) && (!nodo->derecha))
        return true;
    return false;
}
/*
*Destruye todos los nodos del arbol junto con sus elementos
*/
void destruir_nodos_abb(nodo_abb_t* nodo){
    if(!es_hoja(nodo)){
        if(nodo->izquierda)
            destruir_nodos_abb(nodo->izquierda);
        if(nodo->derecha)
            destruir_nodos_abb(nodo->derecha);
     }
    if(nodo)
        free(nodo);
}

/*
*Inserta un nuevo nodo según corresponda con el comparador
*Devuelve 0 si lo inserta correctamente o ERROR en caso contrario
*/
int insertar_nodo_abb(abb_comparador comparador, nodo_abb_t* nuevo_nodo, nodo_abb_t* corriente){
    if(!corriente)
        return ERROR;
    int comparacion = comparador(nuevo_nodo->elemento, corriente->elemento);
    if(comparacion == MAYOR || comparacion == IGUAL){
        if(!(corriente->derecha))
            corriente->derecha = nuevo_nodo;
        else
            insertar_nodo_abb(comparador, nuevo_nodo, corriente->derecha);
    }else if (comparacion == MENOR){
        if (!(corriente->izquierda))
            corriente->izquierda = nuevo_nodo;
        else
            insertar_nodo_abb(comparador, nuevo_nodo, corriente->izquierda);
    } 
    return 0;
}

abb_t *arbol_crear(abb_comparador comparador, abb_liberar_elemento destructor){
    if(!comparador) 
        return ERROR_PUNTERO;
    abb_t* arbol = malloc(sizeof(abb_t));
    if(!arbol) 
        return ERROR_PUNTERO;
    arbol->nodo_raiz = NULL;
    arbol->comparador = comparador;
    arbol->destructor = destructor;
    return arbol;
}
/*
*Se inicializa un nodo como hoja junto con su elemento
*/
void nodo_abb_inicializar(nodo_abb_t* nodo, void* elemento){
    nodo->elemento = elemento; 
    nodo->izquierda = NULL;
    nodo->derecha = NULL;
}

int arbol_insertar(abb_t* arbol, void* elemento){
    if(!arbol || !elemento)
        return ERROR;
    nodo_abb_t* nuevo_nodo = malloc(sizeof(nodo_abb_t));
    if(!nuevo_nodo)
        return ERROR;
    nodo_abb_inicializar(nuevo_nodo, elemento);
    if(!arbol->nodo_raiz){
        arbol->nodo_raiz = nuevo_nodo;
        return 0;
    }
    return insertar_nodo_abb(arbol->comparador, nuevo_nodo, arbol->nodo_raiz);
}
int arbol_borrar(abb_t *arbol, void *elemento){
    return ERROR;
}
void *elemento_buscar(abb_comparador comparador, nodo_abb_t *corriente, void *elemento){
    if(!corriente)
        return NULL;
    int comparacion = comparador(elemento, corriente->elemento);
    if (comparacion == MAYOR)
        return elemento_buscar(comparador, corriente->derecha, elemento);
    else if (comparacion == MENOR)
        return elemento_buscar(comparador, corriente->izquierda, elemento);
    return corriente->elemento;
}

void *arbol_buscar(abb_t *arbol, void *elemento){
    if((!arbol) || (!elemento)) 
        return ERROR_PUNTERO;
    return elemento_buscar(arbol->comparador, arbol->nodo_raiz, elemento);
}

void *arbol_raiz(abb_t *arbol){
    if((!arbol) || (!arbol->nodo_raiz))
        return ERROR_PUNTERO;
    return arbol->nodo_raiz->elemento;
}
bool arbol_vacio(abb_t *arbol){
    if (!arbol) return true;
    return !(arbol->nodo_raiz); 
}


bool funcion_cargar_array(void *elemento, void *array){
    array_t* aux = (array_t*) array;
    if(aux->posicion >= aux->tamanio)
        return false;
    aux->vector[aux->posicion] = elemento;
    aux->posicion ++;
    return true;
}

array_t inicializar_vector(void** array, size_t tamanio){
    array_t aux;
    aux.vector = array;
    aux.posicion = 0;
    aux.tamanio = tamanio;
    return aux;
}

size_t recorrer_arbol(abb_t *arbol, void **array, size_t tamanio_array, size_t (*funcion_recorrido)(nodo_abb_t*, bool(*)(void*, void*), void*)){
    if (!arbol || !arbol->nodo_raiz || tamanio_array <= 0)
        return 0;
    array_t vector = inicializar_vector(array, tamanio_array);
    return funcion_recorrido(arbol->nodo_raiz, funcion_cargar_array, (void *)&vector);
}

size_t recorrer_inorden(nodo_abb_t* corriente, bool (*funcion)(void *, void *), void* extra){
    return 0;
}

size_t recorrer_preorden(nodo_abb_t* corriente, bool (*funcion)(void *, void *), void* extra){
    return 0;
}

size_t recorrer_postorden(nodo_abb_t* corriente, bool (*funcion)(void *, void *), void* extra){
    return 0;
}

size_t arbol_recorrido_inorden(abb_t *arbol, void **array, size_t tamanio_array){
    return recorrer_arbol(arbol, array, tamanio_array, recorrer_inorden);
}

size_t arbol_recorrido_preorden(abb_t *arbol, void **array, size_t tamanio_array){
    return recorrer_arbol(arbol, array, tamanio_array, recorrer_preorden);
}

size_t arbol_recorrido_postorden(abb_t *arbol, void **array, size_t tamanio_array){
    return recorrer_arbol(arbol, array, tamanio_array, recorrer_postorden);
}

void arbol_destruir(abb_t *arbol){
    if(!arbol) return;
    if (arbol->nodo_raiz) 
        destruir_nodos_abb(arbol->nodo_raiz);
    free(arbol);

}
size_t abb_con_cada_elemento(abb_t *arbol, int recorrido, bool (*funcion)(void *, void *), void *extra){
    if(!arbol || !arbol->nodo_raiz)
        return 0;
    if(recorrido == ABB_RECORRER_INORDEN)
        return recorrer_inorden(arbol->nodo_raiz, funcion, extra);
    if (recorrido == ABB_RECORRER_PREORDEN)
        return recorrer_preorden(arbol->nodo_raiz, funcion, extra);
    return recorrer_postorden(arbol->nodo_raiz, funcion, extra);
}
