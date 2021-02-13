#ifndef __LISTA_H__
#define __LISTA_H__

#include <stdbool.h>
#include <stddef.h>

typedef struct nodo{
    void* elemento;
    struct nodo* siguiente;
}nodo_t;

typedef struct lista{
    nodo_t* nodo_inicio;
    nodo_t* nodo_fin;
    size_t cantidad;
}lista_t;

typedef struct cola{
    nodo_t* nodo_inicio;
    nodo_t* nodo_fin;
    size_t cantidad;
}cola_t;

typedef struct pila{
    nodo_t* nodo_inicio;
    nodo_t* nodo_fin;
    size_t cantidad;
}pila_t;

typedef struct lista_iterador{
    nodo_t* corriente;
    lista_t* lista;
}lista_iterador_t;

/*
 * Crea la lista reservando la memoria necesaria.
 * Devuelve un puntero a la lista creada o NULL en caso de error.
 */
lista_t* lista_crear();

/*
 * Inserta un elemento al final de la lista.
 * Devuelve 0 si pudo insertar o -1 si no pudo.
 */
int lista_insertar(lista_t* lista, void* elemento);

/*
 * Inserta un elemento en la posicion indicada, donde 0 es insertar
 * como primer elemento y 1 es insertar luego del primer elemento.  
 * En caso de no existir la posicion indicada, lo inserta al final.
 * Devuelve 0 si pudo insertar o -1 si no pudo.
 */
int lista_insertar_en_posicion(lista_t* lista, void* elemento, size_t posicion);

/*
 * Quita de la lista el elemento que se encuentra en la ultima posición.
 * Devuelve 0 si pudo eliminar o -1 si no pudo.
 */
int lista_borrar(lista_t* lista);

/*
 * Quita de la lista el elemento que se encuentra en la posición
 * indicada, donde 0 es el primer elemento.  
 * En caso de no existir esa posición se intentará borrar el último
 * elemento.  
 * Devuelve 0 si pudo eliminar o -1 si no pudo.
 */
int lista_borrar_de_posicion(lista_t* lista, size_t posicion);

/*
 * Devuelve el elemento en la posicion indicada, donde 0 es el primer
 * elemento.
 *
 * Si no existe dicha posicion devuelve NULL.
 */
void* lista_elemento_en_posicion(lista_t* lista, size_t posicion);

/* 
 * Devuelve el último elemento de la lista o NULL si la lista se
 * encuentra vacía.
 */
void* lista_ultimo(lista_t* lista);

/* 
 * Devuelve true si la lista está vacía o false en caso contrario.
 */
bool lista_vacia(lista_t* lista);

/*
 * Devuelve la cantidad de elementos almacenados en la lista.
 */
size_t lista_elementos(lista_t* lista);

/*
 * Libera la memoria reservada por la lista.
 */
void lista_destruir(lista_t* lista);

/*
 * Crea un iterador para una lista. El iterador creado es válido desde
 * el momento de su creación hasta que no haya mas elementos por
 * recorrer o se modifique la lista iterada (agregando o quitando
 * elementos de la lista). 
 *
 * Al momento de la creación, el iterador queda listo para devolver el
 * primer elemento utilizando lista_iterador_elemento_actual.
 *
 * Devuelve el puntero al iterador creado o NULL en caso de error.
 */
lista_iterador_t* lista_iterador_crear(lista_t* lista);

/*
 * Devuelve true si hay mas elementos sobre los cuales iterar o false
 * si no hay mas.
 */
bool lista_iterador_tiene_siguiente(lista_iterador_t* iterador);

/*
 * Avanza el iterador al siguiente elemento.
 * Devuelve true si pudo avanzar el iterador o false en caso de
 * que no queden elementos o en caso de error.
 *
 * Una vez llegado al último elemento, si se invoca a
 * lista_iterador_elemento_actual, el resultado siempre será NULL.
 */
bool lista_iterador_avanzar(lista_iterador_t* iterador);

/*
 * Devuelve el elemento actual del iterador o NULL en caso de que no
 * exista dicho elemento o en caso de error.
 */
void* lista_iterador_elemento_actual(lista_iterador_t* iterador);

/*
 * Libera la memoria reservada por el iterador.
 */
void lista_iterador_destruir(lista_iterador_t* iterador);

/*
 * Iterador interno. Recorre la lista e invoca la funcion con cada elemento de
 * la misma. Dicha función puede devolver true si se deben seguir recorriendo
 * elementos o false si se debe dejar de iterar elementos.
 *
 * La función retorna la cantidad de elementos iterados o 0 en caso de error.
 */
size_t lista_con_cada_elemento(lista_t* lista, bool (*funcion)(void*, void*), void *contexto);

/*
 * Crea una pila reservando la memoria necesaria.
 * Devuelve un puntero a la pila creada o NULL en caso de error.
 */
pila_t* pila_crear();

/* 
 * Apila un elemento.
 * Devuelve 0 si pudo o -1 en caso contrario.
 */
int pila_apilar(pila_t* pila, void* elemento);

/* 
 * Desapila un elemento.
 * Devuelve 0 si pudo desapilar o -1 si no pudo.
 */
int pila_desapilar(pila_t* pila);

/*
 * Devuelve el elemento en el tope de la pila o NULL
 * en caso de estar vacía.
 */
void* pila_tope(pila_t* pila);

/* 
 * Devuelve true si la pila está vacía o false en caso contrario.
 */
bool pila_vacia(pila_t* pila);

/*
 * Devuelve la cantidad de elementos almacenados en la pila.
 */
size_t pila_elementos(pila_t* pila);

/*
 * Libera la memoria reservada por la pila.
 */
void pila_destruir(pila_t* pila);

/*
 * Crea una cola reservando la memoria necesaria.
 * Devuelve un puntero a una cola creada o NULL en caso de error.
 */
cola_t* cola_crear();

/* 
 * Encola un elemento.
 * Devuelve 0 si pudo encolar o -1 si no pudo.
 */
int cola_encolar(cola_t* cola, void* elemento);

/* 
 * Desencola un elemento.
 * Devuelve 0 si pudo desencolar o -1 si no pudo.
 */
int cola_desencolar(cola_t* cola);

/*
 * Devuelve el primer elemento de la cola o NULL en caso de estar
 * vacía.
 */
void* cola_primero(cola_t* cola);

/* 
 * Devuelve true si la cola está vacía o false en caso contrario.
 */
bool cola_vacia(cola_t* cola);

/*
 * Devuelve la cantidad de elementos almacenados en la cola.
 */
size_t cola_elementos(cola_t* cola);

/*
 * Libera la memoria reservada por la cola.
 */
void cola_destruir(cola_t* cola);

#endif /* __LISTA_H__ */
