#include "abb.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#define ERROR -1

abb_t *arbol_crear(abb_comparador comparador, abb_liberar_elemento destructor){

}
int arbol_insertar(abb_t *arbol, void *elemento){

}
int arbol_borrar(abb_t *arbol, void *elemento){

}
void *arbol_buscar(abb_t *arbol, void *elemento){

}
void *arbol_raiz(abb_t *arbol){

}
bool arbol_vacio(abb_t *arbol){

}
size_t arbol_recorrido_inorden(abb_t *arbol, void **array, size_t tamanio_array){

}
size_t arbol_recorrido_preorden(abb_t *arbol, void **array, size_t tamanio_array){

}
size_t arbol_recorrido_postorden(abb_t *arbol, void **array, size_t tamanio_array){

}
void arbol_destruir(abb_t *arbol){

}
size_t abb_con_cada_elemento(abb_t *arbol, int recorrido, bool (*funcion)(void *, void *), void *extra){

}