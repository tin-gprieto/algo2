#ifndef __HEAP_H__
#define __HEAP_H__

#include <stdbool.h>
#include <stdlib.h>

#define ERROR -1
#define EXITO 0


/*
 * Condicion del heap. Recibe dos elementos del heap y devuelve
 * verdadero si el primer elemento es menor que el segundo en un heap
 * minimal o si es mayor en un heap maximal. (Relacion padre - hijo)
 */
typedef bool (*heap_condicion)(void*, void*);

/*
 * Destructor de elementos. Cada vez que un elemento deja el heap
 * se invoca al destructor pasandole el elemento.
 */
typedef void (*heap_destructor)(void*);

typedef struct heap{
    void** vector;
    size_t tope;
    heap_condicion condicion;
    heap_destructor destructor;
}heap_t;

heap_t* heap_crear(heap_condicion condicion, heap_destructor destructor);

void heap_destruir(heap_t* heap);

void* heap_raiz(heap_t* heap);

bool heap_vacio(heap_t* heap);

size_t heap_elementos(heap_t* heap);

int heap_insertar(heap_t* heap, void* elemento);

int heap_borrar(heap_t* heap);



#endif /* __HEAP_H__ */