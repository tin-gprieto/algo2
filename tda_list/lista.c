#include "lista.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#define ERROR -1

/*
*Dado un nuevo nodo los inserta al final de la lista 
inicializandolo con un elemento
*/
void insertar_al_final(lista_t *lista, nodo_t* nuevo_nodo){
    if (lista->cantidad == 0) {
        lista->nodo_inicio = nuevo_nodo;
    }else{
        (lista->nodo_fin)->siguiente = nuevo_nodo;
    }
    lista->nodo_fin = nuevo_nodo;
}

/*
*Devuelve el puntero actual si es anterior al posterior
sino avanza de forma recursiva
*/
nodo_t* nodo_buscar_anterior(nodo_t* actual, nodo_t* posterior){
    if(actual->siguiente == posterior)
        return actual;
    return nodo_buscar_anterior(actual->siguiente, posterior);
}

/*
*Borra el ultimo elemento de la lista
*/
void borrar_ultimo_elemento(lista_t* lista){
    nodo_t *antecesor = nodo_buscar_anterior(lista->nodo_inicio,
                                             lista->nodo_fin);
    free(antecesor->siguiente);
    antecesor->siguiente = NULL;
    lista->nodo_fin = antecesor;
}
/*
*Borra el primer elemento de la lista
*/
void borrar_primer_elemento(lista_t* lista){
    nodo_t *aux;
    aux = (lista->nodo_inicio)->siguiente;
    free(lista->nodo_inicio);
    lista->nodo_inicio = aux;
}
/*
*Devuelve el puntero al nodo que se encuentre en la posicion 
*pasada por parametro
*/
nodo_t* nodo_en_posicion(nodo_t* nodo, size_t contador, size_t posicion){
    if(contador == posicion)
        return nodo;
    return nodo_en_posicion(nodo->siguiente, contador + 1, posicion);
}

/*
*Destruye todos los nodos
*/
void nodo_destruir(nodo_t* nodo){
    if(!nodo) 
        return;
    nodo_destruir(nodo->siguiente);
    free(nodo);
}

lista_t* lista_crear(){
    lista_t* lista = malloc(sizeof(lista_t));
    if(!lista)
        return NULL;
    lista->nodo_inicio=NULL;
    lista->nodo_fin=NULL;
    lista->cantidad=0;
    return lista;
}

int lista_insertar(lista_t* lista, void* elemento){
    if(!lista) 
        return ERROR;

    nodo_t *nuevo_nodo = malloc(sizeof(nodo_t));
    if (!nuevo_nodo)
        return ERROR;
    nuevo_nodo->elemento = elemento;
    nuevo_nodo->siguiente = NULL;
    insertar_al_final(lista, nuevo_nodo);
    lista->cantidad++;
    return 0;
}

int lista_insertar_en_posicion(lista_t* lista, void* elemento, size_t posicion){
    if(!lista)
        return ERROR;

    nodo_t *nuevo_nodo = malloc(sizeof(nodo_t));
    if (!nuevo_nodo)
        return ERROR;
    nuevo_nodo->elemento = elemento;
    if (lista->cantidad <= posicion){
        nuevo_nodo->siguiente = NULL;
        insertar_al_final(lista, nuevo_nodo);
    }else if (posicion == 0){
        nuevo_nodo->siguiente = lista->nodo_inicio;
        lista->nodo_inicio = nuevo_nodo;
    }else{
        nodo_t * reemplazado = nodo_en_posicion(lista->nodo_inicio, 0, posicion);
        nodo_t* antecesor = nodo_buscar_anterior(lista->nodo_inicio, reemplazado);
        antecesor->siguiente = nuevo_nodo;
        nuevo_nodo->siguiente = reemplazado;
    }
    lista->cantidad++;
    return 0;
}

int lista_borrar(lista_t* lista){
    if((!lista) || (lista->cantidad == 0)) 
        return ERROR;
    if(lista->cantidad == 1){
        free(lista->nodo_inicio);
        lista->nodo_inicio = NULL;
        lista->nodo_fin = NULL;
    }else{
        borrar_ultimo_elemento(lista);
    }
    lista->cantidad --;
    return 0;
}


int lista_borrar_de_posicion(lista_t* lista, size_t posicion){
    if(!lista)
        return ERROR;
    if(lista->cantidad <= posicion){
        borrar_ultimo_elemento(lista);
    }else if (posicion == 0){
        borrar_primer_elemento(lista);
    }else{
        nodo_t * borrado = nodo_en_posicion(lista->nodo_inicio, 0, posicion);
        nodo_t * antecesor = nodo_buscar_anterior(lista->nodo_inicio, borrado);
        antecesor->siguiente = borrado->siguiente;
        free(borrado);
    }
    lista->cantidad --;
    return 0;
}

void* lista_elemento_en_posicion(lista_t* lista, size_t posicion){
    if((!lista) || lista->cantidad <= posicion) 
        return NULL;
    nodo_t* nodo_buscado = nodo_en_posicion(lista->nodo_inicio, 0, posicion);     
    return nodo_buscado->elemento;
}

void* lista_ultimo(lista_t* lista){
    if (!lista)
        return NULL;
    return (lista->nodo_fin)->elemento;
}

bool lista_vacia(lista_t* lista){
    if ((!lista) || lista->cantidad != 0)
        return false;
    return true;
}

size_t lista_elementos(lista_t* lista){
    if (!lista)
        return 0;
    return lista->cantidad;
}

int lista_apilar(lista_t* lista, void* elemento){
    if (!lista)
        return ERROR;
    nodo_t *nuevo_nodo = malloc(sizeof(nodo_t));
    if (!nuevo_nodo)
        return ERROR;
    nuevo_nodo->elemento = elemento;
    nuevo_nodo->siguiente = NULL;
    insertar_al_final(lista, nuevo_nodo);
    lista->cantidad++;
    return 0;
}

int lista_desapilar(lista_t* lista){
    if ((!lista) || (lista->cantidad == 0))
        return ERROR;
    if (lista->cantidad == 1){
        free(lista->nodo_inicio);
        lista->nodo_inicio = NULL;
        lista->nodo_fin = NULL;
    }else{
        borrar_ultimo_elemento(lista);
    }
    lista->cantidad--;
    return 0;
}

void* lista_tope(lista_t* lista){
    if (!lista)
        return NULL;
    return (lista->nodo_fin)->elemento;
}

int lista_encolar(lista_t* lista, void* elemento){
    if (!lista)
        return ERROR;
    nodo_t *nuevo_nodo = malloc(sizeof(nodo_t));
    if (!nuevo_nodo)
        return ERROR;
    nuevo_nodo->elemento = elemento;
    nuevo_nodo->siguiente = NULL;
    insertar_al_final(lista, nuevo_nodo);
    lista->cantidad++;
    return 0;
}

int lista_desencolar(lista_t* lista){
    if ((!lista) || (lista->cantidad == 0))
        return ERROR;
    if (lista->cantidad == 1){
        free(lista->nodo_inicio);
        lista->nodo_inicio = NULL;
        lista->nodo_fin = NULL;
    }else{
        borrar_primer_elemento(lista);
    }
    lista->cantidad--;
    return 0;
}

void* lista_primero(lista_t* lista){
    if(!lista) 
        return NULL;
    return (lista->nodo_inicio)->elemento;
}

void lista_destruir(lista_t* lista){
    if (!lista)
        return;
    if(lista->cantidad != 0)
        nodo_destruir(lista->nodo_inicio);
    free(lista);
    lista = NULL;
}

lista_iterador_t* lista_iterador_crear(lista_t* lista){
    if(!lista) 
        return NULL;
    lista_iterador_t* iterador = malloc(sizeof(lista_iterador_t));
    if(!iterador)
        return NULL;
    iterador->corriente = lista->nodo_inicio;
    iterador->lista = lista;
    return iterador;
}

bool lista_iterador_tiene_siguiente(lista_iterador_t* iterador){
    if(!((iterador->corriente)->siguiente))
        return false;
    return true;
}

bool lista_iterador_avanzar(lista_iterador_t* iterador){
    if (!((iterador->corriente)->siguiente))
        return false;
    iterador->corriente = (iterador->corriente)->siguiente;
    return true;
}

void* lista_iterador_elemento_actual(lista_iterador_t* iterador){
    if(!(iterador->corriente))
        return NULL;
    return (iterador->corriente)->elemento;
}

void lista_iterador_destruir(lista_iterador_t* iterador){
    free(iterador);
}

size_t mover_por_nodos(nodo_t* nodo, bool (*funcion)(void *, void *), void *contexto){
    if(!(nodo->siguiente))
        return 0;
    if(!funcion(nodo, contexto))
        return 0;
    return 1 + mover_por_nodos(nodo->siguiente, funcion, contexto);
}

size_t lista_con_cada_elemento(lista_t* lista, bool (*funcion)(void*, void*), void *contexto){
    if(!lista)
        return 0;
    return mover_por_nodos(lista->nodo_inicio, funcion, contexto);
}