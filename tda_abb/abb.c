#include "abb.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#define ERROR -1
#define MAYOR 1
#define MENOR -1
#define DERECHA 1
#define IZQUIERDA -1
#define IGUAL 0
#define ERROR_PUNTERO NULL

typedef struct array{
    void** vector;
    size_t posicion;
    size_t tamanio;
} array_t;

typedef struct familia{
    nodo_abb_t* nodo_padre;
    nodo_abb_t* nodo_hijo;
    int descendecia;
} familia_t;

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
int nodo_abb_insertar(abb_comparador comparador, nodo_abb_t* nuevo_nodo, nodo_abb_t* corriente){
    if(!corriente)
        return ERROR;
    int comparacion = comparador(nuevo_nodo->elemento, corriente->elemento);
    if(comparacion == MAYOR || comparacion == IGUAL){
        if(!(corriente->derecha))
            corriente->derecha = nuevo_nodo;
        else
            nodo_abb_insertar(comparador, nuevo_nodo, corriente->derecha);
    }else if (comparacion == MENOR){
        if (!(corriente->izquierda))
            corriente->izquierda = nuevo_nodo;
        else
            nodo_abb_insertar(comparador, nuevo_nodo, corriente->izquierda);
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

nodo_abb_t* nodo_abb_buscar(abb_comparador comparador, nodo_abb_t *corriente, void *elemento){
    if(!corriente)
        return NULL;
    int comparacion = comparador(elemento, corriente->elemento);
    if (comparacion == MAYOR)
        return nodo_abb_buscar(comparador, corriente->derecha, elemento);
    else if (comparacion == MENOR)
        return nodo_abb_buscar(comparador, corriente->izquierda, elemento);
    return corriente;
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
    return nodo_abb_insertar(arbol->comparador, nuevo_nodo, arbol->nodo_raiz);
}
bool es_padre(nodo_abb_t * padre, nodo_abb_t* hijo, int* descendencia){
    if(padre->izquierda == hijo){
        *descendencia = IZQUIERDA;
        return true;
    }
    if(padre->derecha == hijo){
        *descendencia = DERECHA;
        return true;
    }
    return false;
}

void buscar_nodo_padre(abb_comparador comparador, nodo_abb_t* corriente, familia_t* familia){
    if (!corriente)
        familia->nodo_padre = NULL;
    if(es_padre(corriente, familia->nodo_hijo, &(familia->descendecia)))
        familia->nodo_padre = corriente;
    int comparacion = comparador(familia->nodo_hijo->elemento, corriente->elemento);
    if (comparacion == MAYOR)
        buscar_nodo_padre(comparador, corriente->derecha, familia);
    else if (comparacion == MENOR)
        buscar_nodo_padre(comparador, corriente->izquierda, familia);
    else if (comparacion == IGUAL)
        familia->nodo_padre = NULL;
}

nodo_abb_t* nodo_abb_buscar_predecesor_inorden(nodo_abb_t* hijo){
    if(!hijo->derecha) //es el mayor de los predecesores
        return hijo;
    return nodo_abb_buscar_predecesor_inorden(hijo->derecha);
}

nodo_abb_t* nodo_abb_buscar_reemplazo(nodo_abb_t* reemplazado){
    if(es_hoja(reemplazado)) //no tiene hijos
        return NULL;
    if(!reemplazado->izquierda) //no tiene hijos menores
        return reemplazado->derecha;
    return nodo_abb_buscar_predecesor_inorden(reemplazado->izquierda);
}

void nodo_abb_liberar(nodo_abb_t* nodo_borrar, abb_liberar_elemento destructor){
    if(nodo_borrar && destructor)
        destructor(nodo_borrar->elemento);
    free(nodo_borrar);
}

int nodo_raiz_borrar(abb_t* arbol, familia_t borrado, familia_t reemplazo){
    if (borrado.nodo_hijo != reemplazo.nodo_padre){
        //hijos menores del reemplazo son hijos mayores del padre
        reemplazo.nodo_padre->derecha = reemplazo.nodo_hijo->izquierda;
        //hereda sus hijos
        reemplazo.nodo_hijo->derecha = borrado.nodo_hijo->derecha;
        reemplazo.nodo_hijo->izquierda = borrado.nodo_hijo->izquierda;
    }
    arbol->nodo_raiz = reemplazo.nodo_hijo;
    nodo_abb_liberar(borrado.nodo_hijo, arbol->destructor);
    return 0;
}

/*
*Según la descendecia del nodo borrado (si es hijo izquierdo o derecho),
*el nodo reemplazado pasa a ser su hijo. 
*/
void heredar_padre(familia_t borrado, familia_t reemplazo){
    if (borrado.descendecia == IZQUIERDA)
        borrado.nodo_padre->izquierda = reemplazo.nodo_hijo;
    if (borrado.descendecia == DERECHA)
        borrado.nodo_padre->derecha = reemplazo.nodo_hijo;
}

int nodo_abb_borrar(familia_t borrado, familia_t reemplazo, abb_liberar_elemento destructor){
    if (borrado.nodo_hijo == reemplazo.nodo_padre){
        if(reemplazo.descendecia == IZQUIERDA){
            reemplazo.nodo_hijo->derecha = borrado.nodo_hijo->derecha;
            heredar_padre(borrado, reemplazo);
        }
        else if (reemplazo.descendecia == DERECHA)
            heredar_padre(borrado, reemplazo);
    }else{
        //hijos menores del reemplazo son hijos mayores del padre
        reemplazo.nodo_padre->derecha = reemplazo.nodo_hijo->izquierda;
        heredar_padre(borrado, reemplazo);
        //hereda sus hijos
        reemplazo.nodo_hijo->derecha = borrado.nodo_hijo->derecha;
        reemplazo.nodo_hijo->izquierda = borrado.nodo_hijo->izquierda;
    }
    nodo_abb_liberar(borrado.nodo_hijo, destructor);
    return 0;
}

int nodo_hoja_borrar(familia_t borrado, abb_liberar_elemento destructor){
    borrado.nodo_padre = NULL;
    nodo_abb_liberar(borrado.nodo_hijo, destructor);
    return 0;
}

int arbol_borrar(abb_t *arbol, void *elemento){
    if(!arbol || !arbol->nodo_raiz || !elemento)
        return ERROR;
    familia_t borrado; 
    borrado.nodo_hijo = nodo_abb_buscar(arbol->comparador, arbol->nodo_raiz, elemento);
    if (!borrado.nodo_hijo) //No existe elemento en árbol
        return ERROR;
    buscar_nodo_padre(arbol->comparador, arbol->nodo_raiz, &borrado);
    familia_t reemplazo;
    reemplazo.nodo_hijo = nodo_abb_buscar_reemplazo(borrado.nodo_hijo);
    if (reemplazo.nodo_hijo){ //no es hoja
        buscar_nodo_padre(arbol->comparador, arbol->nodo_raiz, &reemplazo);
        if (!borrado.nodo_padre){
            return nodo_raiz_borrar(arbol, borrado, reemplazo);
        }
        return nodo_abb_borrar(borrado, reemplazo, arbol->destructor);
    }
    return nodo_hoja_borrar(borrado, arbol->destructor);
    
}

void * arbol_buscar(abb_t *arbol, void *elemento){
    if((!arbol) || (!elemento)) 
        return ERROR_PUNTERO;
    nodo_abb_t *nodo_buscado = nodo_abb_buscar(arbol->comparador, arbol->nodo_raiz, elemento);
    if(!nodo_buscado)
        return NULL;
    return nodo_buscado->elemento;
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


bool funcion_cargar_array(void* elemento, void* array){
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


void recorrer_inorden(nodo_abb_t* corriente, bool (*funcion)(void *, void *), void* extra, bool* sigue, size_t* contador){
    if(!corriente || !sigue)
        return;
    if(corriente->izquierda) recorrer_inorden(corriente->izquierda, funcion, extra, sigue, contador);
    if(corriente && sigue){
        *sigue = funcion(corriente->elemento, extra);
        //*contador++;
    }
    if(corriente->derecha) recorrer_inorden(corriente->derecha, funcion, extra, sigue, contador);
}

void recorrer_preorden(nodo_abb_t* corriente, bool (*funcion)(void *, void *), void* extra, bool* sigue, size_t* contador){
    if(!corriente || !sigue)
        return;
    if(corriente && sigue){
        *sigue = funcion(corriente->elemento, extra);
        //*contador++;
    }
    if(corriente->izquierda) recorrer_preorden(corriente->izquierda, funcion, extra, sigue, contador);
    if(corriente->derecha) recorrer_preorden(corriente->derecha, funcion, extra, sigue, contador);
}

void recorrer_postorden(nodo_abb_t* corriente, bool (*funcion)(void *, void *), void* extra, bool* sigue, size_t *contador){
    if(!corriente || !sigue)
        return;
    if(corriente->derecha) recorrer_postorden(corriente->derecha, funcion, extra, sigue, contador);
    if(corriente && sigue){
        *sigue = funcion(corriente->elemento, extra);
        //*contador++;
    }
    if(corriente->izquierda) recorrer_postorden(corriente->izquierda, funcion, extra, sigue, contador);
}

size_t recorrer_arbol(abb_t *arbol, void **array, size_t tamanio_array, void (*funcion_recorrido)(nodo_abb_t*, bool(*)(void*, void*), void*, bool* , size_t*)){
    if (!arbol || !arbol->nodo_raiz || tamanio_array <= 0)
        return 0;
    array_t vector = inicializar_vector(array, tamanio_array);
    bool estado = true;
    size_t cant_iterada = 0;
    funcion_recorrido(arbol->nodo_raiz, funcion_cargar_array, (void *)&vector, &estado, &cant_iterada);
    return cant_iterada;
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
    if(!arbol || !arbol->nodo_raiz || !funcion)
        return 0;
    bool estado = true;
    size_t cant_iterada = 0;
    if(recorrido == ABB_RECORRER_INORDEN)
        recorrer_inorden(arbol->nodo_raiz, funcion, extra, &estado, &cant_iterada);
    if (recorrido == ABB_RECORRER_PREORDEN)
        recorrer_preorden(arbol->nodo_raiz, funcion, extra, &estado, &cant_iterada);
    if (recorrido == ABB_RECORRER_POSTORDEN)
        recorrer_postorden(arbol->nodo_raiz, funcion, extra, &estado, &cant_iterada);
    return cant_iterada;
}
