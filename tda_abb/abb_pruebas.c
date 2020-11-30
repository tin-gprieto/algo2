#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "test.h"
#include "abb.h"

#define ERROR -1

int comparador_int(void* elemento_1, void* elemento_2){
    int primer_numero = *(int*) elemento_1;
    int segundo_numero = *(int*) elemento_2;
    if(primer_numero > segundo_numero)
        return 1;
    if(primer_numero < segundo_numero)
        return -1;
    return 0;
}

void destructor_heap(void* elemento){
    free(elemento);
}

void probar_iterador(){

}

void probar_postorden(){

}

void probar_preorden(){

}

void  probar_inorden(){

}

void probar_busqueda(){

}

void probar_borrado(){

}

void probar_insercion(){
    test_nuevo_sub_grupo("Inserciones básicas");
    abb_t* arbol = arbol_crear(comparador_int, NULL);
    int numero_1 = 5;
    int* elemento_1 = &numero_1;
    test_afirmar(arbol_insertar(arbol, (void*)elemento_1) != ERROR,"Se inserta un primer elemento correctamente");
    test_afirmar((int*) arbol_raiz(arbol) == elemento_1, "El primer elemento es la raíz");

    int numero_2 = 3;
    int* elemento_2 = &numero_2;
    arbol_insertar(arbol, (void*) elemento_2);
    test_afirmar(arbol->nodo_raiz->izquierda->elemento == elemento_2, "Se encuentra a la izquierda de la raíz");
    test_afirmar((int *)arbol_raiz(arbol) == elemento_1, "La raíz sigue siendo la misma");

    int numero_3 = 7;
    int *elemento_3 = &numero_3;
    test_afirmar(arbol_insertar(arbol, (void *)elemento_3) != ERROR, "Se inserta un elemento mayor correctamente");
    test_afirmar(arbol->nodo_raiz->derecha->elemento == elemento_3, "Se encuentra a la derecha de la raíz");
    test_afirmar((int *)arbol_raiz(arbol) == elemento_1, "La raíz sigue siendo la misma");

    arbol_destruir(arbol);
}

void probar_basicas(){
    test_nuevo_sub_grupo("Creación del árbol");
    abb_t* arbol = arbol_crear(comparador_int, destructor_heap);
    test_afirmar(arbol != NULL, "Se crea un árbol");
    test_afirmar(arbol_vacio(arbol), "El árbol creado está vacio");
    test_afirmar(arbol_raiz(arbol) == NULL, "El árbol no tiene raíz");
    arbol_destruir(arbol);

    test_nuevo_sub_grupo("Pruebas con NULL");
    arbol = arbol_crear(comparador_int, NULL);
    test_afirmar(arbol != NULL, "Se crea un árbol sin destructor");
    arbol_destruir(arbol);
    arbol = arbol_crear(NULL, destructor_heap);
    test_afirmar(arbol == NULL, "No se crea un árbol sin comparador");
    test_afirmar(arbol_vacio(arbol), "Un árbol nulo está vacío");
    test_afirmar(arbol_raiz(arbol) == NULL, "Un árbol nulo no tiene raíz");

}

int main(){
    test_nuevo_grupo("Pruebas básicas");
    probar_basicas(); //Crear, Vacio, Destruir, Raiz
    test_nuevo_grupo("Pruebas con Insertar");
    probar_insercion(); //Insertar, Raiz
    test_nuevo_grupo("Pruebas con Borrar");
    probar_borrado(); 
    test_nuevo_grupo("Pruebas con Buscar");
    probar_busqueda(); 
    test_nuevo_grupo("Recorrido Inorden");
    probar_inorden();
    test_nuevo_grupo("Recorrido Preorden");
    probar_preorden();
    test_nuevo_grupo("Recorrido Postorden");
    probar_postorden();
    test_nuevo_grupo("Pruebas con Iterador interno");
    probar_iterador();
    test_mostrar_reporte();
    return 0;
}