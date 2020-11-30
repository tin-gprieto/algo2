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

bool es_hoja(nodo_abb_t* nodo){
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
    free(nodo);
}

/*
*Inserta un nuevo nodo según corresponda con el comparador
*Devuelve 0 si lo inserta correctamente o ERROR en caso contrario
*/
int insertar_nodo_abb(abb_t* arbol, nodo_abb_t* nuevo_nodo, nodo_abb_t* corriente){
    if(!corriente)
        return ERROR;
    int orden = arbol->comparador(nuevo_nodo->elemento, corriente->elemento);
    if(orden == MAYOR || orden == IGUAL){
        if(!(corriente->derecha))
            corriente->derecha = nuevo_nodo;
        else
            insertar_nodo_abb(arbol, nuevo_nodo, corriente->derecha);
    }
    else if (orden == MENOR){
        if (!(corriente->izquierda))
            corriente->izquierda = nuevo_nodo;
        else
            insertar_nodo_abb(arbol, nuevo_nodo, corriente->izquierda);
    } 
    return 0;

}
/*
*Inserta un nuevo nodo como raiz dentro del árbol
*Devuelve 0 si lo inserta correctamente o ERROR en caso contrario
*/
int insertar_nodo_raiz(abb_t* arbol, nodo_abb_t* nodo){
    if((!arbol) || (!nodo)) return ERROR;
    arbol->nodo_raiz = nodo;
    nodo->izquierda = NULL;
    nodo->derecha = NULL;
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

int arbol_insertar(abb_t *arbol, void *elemento){
    if(!arbol || !elemento)
        return ERROR;
    nodo_abb_t* nuevo_nodo = malloc(sizeof(nodo_abb_t));
    if(!nuevo_nodo)
        return ERROR;
    nuevo_nodo->elemento = elemento;
    if(!arbol->nodo_raiz)
        return  insertar_nodo_raiz(arbol, nuevo_nodo);
    return insertar_nodo_abb(arbol, nuevo_nodo, arbol->nodo_raiz);
}
int arbol_borrar(abb_t *arbol, void *elemento){
    return ERROR;
}
void *elemento_buscar(abb_comparador comparador, nodo_abb_t *corriente, void *elemento){
    if(!corriente)
        return NULL;
    int orden = comparador(elemento, corriente->elemento);
    if (orden == MAYOR)
        return elemento_buscar(comparador, corriente->derecha, elemento);
    else if (orden == MENOR)
        return elemento_buscar(comparador, corriente->izquierda, elemento);
    return corriente->elemento;
}

void *arbol_buscar(abb_t *arbol, void *elemento){
    if(!arbol) 
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
size_t arbol_recorrido_inorden(abb_t *arbol, void **array, size_t tamanio_array){
    return 0;
}
size_t arbol_recorrido_preorden(abb_t *arbol, void **array, size_t tamanio_array){
    return 0;
}
size_t arbol_recorrido_postorden(abb_t *arbol, void **array, size_t tamanio_array){
    return 0;
}
void arbol_destruir(abb_t *arbol){
    if(!arbol) return;
    if (arbol->nodo_raiz) 
        destruir_nodos_abb(arbol->nodo_raiz);
    free(arbol);

}
size_t abb_con_cada_elemento(abb_t *arbol, int recorrido, bool (*funcion)(void *, void *), void *extra){
    return 0;
}
