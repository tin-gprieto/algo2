#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "test.h"
#include "abb.h"

#define ERROR -1

#define MAX_VECTOR 10

int comparador_int(void* elemento_1, void* elemento_2){
    int primer_numero = *(int*) elemento_1;
    int segundo_numero = *(int*) elemento_2;
    if(primer_numero > segundo_numero)
        return 1;
    if(primer_numero < segundo_numero)
        return -1;
    return 0;
}

void destructor_dinamico(void* elemento){
    free(elemento);
}

int cargar_arbol(abb_t* arbol, int elementos[], int tope){
    int i = 0;
    int insercion = 0;
    while ((insercion == 0) && (i < tope)){
        insercion = arbol_insertar(arbol, (void *)&elementos[i]);
        i++;
    }
    return insercion;
}

/*
*Compara 
*/
bool comparar_vectores(int vector_1[], int recorrido[], int tamanio){
    int i=0;
    bool coincide=true;
    while (coincide && i<tamanio){
        if (vector_1[i] != recorrido[i])
            coincide=false;
        i++;
    }
    return coincide;
}

void probar_iterador(){
    test_nuevo_grupo("Pruebas con iterador interno");
    //completo
    //en parte
    //ninguno
}

void probar_recorridos(){
    abb_t* arbol = arbol_crear(comparador_int, NULL);
    int elementos[] = {5, 3, 4, 7, 6, 9, 12};
    int tope = 7;
    cargar_arbol(arbol, elementos, tope);
    
    int* elementos_recorridos;
    int** recorrido = &elementos_recorridos;
    size_t tamanio_recorrido = 0;
    size_t cant_recorrido = 0;
    bool orden_adecuado = true;

    test_nuevo_grupo("Recorrido Inorden");
    int inorden[]={3, 4, 5, 6, 7, 9, 12};
    tamanio_recorrido = 10;
    cant_recorrido = arbol_recorrido_inorden(arbol, (void**) recorrido, tamanio_recorrido);
    test_afirmar(cant_recorrido == tope, "Se recorrió la cantidad adecuada");
    orden_adecuado = comparar_vectores(inorden, elementos_recorridos, tope);
    test_afirmar(orden_adecuado, "Se recorrió en el orden correcto");

    test_nuevo_grupo("Recorrido Preorden");
    int preorden[] = {5, 3, 4, 7, 6, 9, 12};
    tamanio_recorrido = 10;
    cant_recorrido = arbol_recorrido_preorden(arbol, (void**) recorrido, tamanio_recorrido);
    test_afirmar(cant_recorrido == tope, "Se recorrió la cantidad adecuada");
    orden_adecuado = comparar_vectores(preorden, elementos_recorridos, tope);
    test_afirmar(orden_adecuado, "Se recorrió en el orden correcto");

    test_nuevo_grupo("Recorrido Inorden");
    int postorden[] = {12, 9, 7, 6, 5, 4, 3};
    tamanio_recorrido = 10;
    cant_recorrido = arbol_recorrido_postorden(arbol, (void**) recorrido, tamanio_recorrido);
    test_afirmar(cant_recorrido == tope, "Se recorrió la cantidad adecuada");
    orden_adecuado = comparar_vectores(postorden, elementos_recorridos, tope);
    test_afirmar(orden_adecuado, "Se recorrió en el orden correcto");

    arbol_destruir(arbol);
}


void probar_borrado(){
    abb_t *arbol = arbol_crear(comparador_int, NULL);
    int elementos[] = {5, 3, 4, 7, 6, 9, 12};
    int tope = 7;
    cargar_arbol(arbol, elementos, tope);

    int *elementos_encontrados;
    int **recorrido = &elementos_encontrados;
    size_t tamanio_recorrido = 0;
    size_t cant_recorrido = 0;
    tamanio_recorrido = 10;
    bool orden_adecuado = false;

    test_nuevo_grupo("Pruebas con Borrar");

    test_nuevo_sub_grupo("Con Predecesor inorden");
    test_afirmar(arbol_borrar(arbol, &elementos[0]) == 0, "Se elimina el elemento");
    test_afirmar(arbol_buscar(arbol, &elementos[0]) == NULL, "El elemento no se encuentra en el árbol");
    int borrado_1_esperado[] = {4, 3, 7, 6, 9, 12};
    cant_recorrido = arbol_recorrido_preorden(arbol, (void **)recorrido, tamanio_recorrido);
    test_afirmar(cant_recorrido == tope - 1, "El árbol se encuentra con la cantidad de elementos adecuada");
    orden_adecuado = comparar_vectores(borrado_1_esperado, elementos_encontrados, tope - 1);
    test_afirmar(orden_adecuado, "Se recorrió en el orden correcto");

    test_nuevo_sub_grupo("No tiene sub-árbol menor");
    test_afirmar(arbol_borrar(arbol, &elementos[5]) == 0, "Se elimina el elemento");
    test_afirmar(arbol_buscar(arbol, &elementos[5]) == NULL, "El elemento no se encuentra en el árbol");
    int borrado_2_esperado[] = {4, 3, 7, 6, 9, 12};
    cant_recorrido = arbol_recorrido_preorden(arbol, (void **)recorrido, tamanio_recorrido);
    test_afirmar(cant_recorrido == tope - 2, "El árbol se encuentra con la cantidad de elementos adecuada");
    orden_adecuado = comparar_vectores(borrado_2_esperado, elementos_encontrados, tope - 2);
    test_afirmar(orden_adecuado, "Se recorrió en el orden correcto");

    test_nuevo_sub_grupo("El hijo menor es hoja");
    test_afirmar(arbol_borrar(arbol, &elementos[3]) == 0, "Se elimina el elemento");
    test_afirmar(arbol_buscar(arbol, &elementos[3]) == NULL, "El elemento no se encuentra en el árbol");
    int borrado_3_esperado[] = {4, 3, 7, 6, 9, 12};
    cant_recorrido = arbol_recorrido_preorden(arbol, (void **)recorrido, tamanio_recorrido);
    test_afirmar(cant_recorrido == tope - 3, "El árbol se encuentra con la cantidad de elementos adecuada");
    orden_adecuado = comparar_vectores(borrado_3_esperado, elementos_encontrados, tope - 3);
    test_afirmar(orden_adecuado, "Se recorrió en el orden correcto");

    test_nuevo_sub_grupo("No tiene hijos");
    test_afirmar(arbol_borrar(arbol, &elementos[6]) == 0, "Se elimina el elemento");
    test_afirmar(arbol_buscar(arbol, &elementos[6]) == NULL, "El elemento no se encuentra en el árbol");
    int borrado_4_esperado[] = {4, 3, 7, 6, 9, 12};
    cant_recorrido = arbol_recorrido_preorden(arbol, (void **)recorrido, tamanio_recorrido);
    test_afirmar(cant_recorrido == tope - 4, "El árbol se encuentra con la cantidad de elementos adecuada");
    orden_adecuado = comparar_vectores(borrado_4_esperado, elementos_encontrados, tope - 4);
    test_afirmar(orden_adecuado, "Se recorrió en el orden correcto");

    arbol_destruir(arbol);
}


void probar_busqueda(){
    test_nuevo_grupo("Pruebas con Buscar");
    abb_t *arbol = arbol_crear(comparador_int, NULL);

    int numero_insertado = 5;
    int *elemento_insertado = &numero_insertado;
    arbol_insertar(arbol, (void *)elemento_insertado);
    test_afirmar((int *)arbol_buscar(arbol, (void*) elemento_insertado) == elemento_insertado, "Se encuentra el único elemento del árbol");
    test_afirmar(*(int*)arbol_buscar(arbol, (void*) elemento_insertado) == numero_insertado, "Coinciden los valores de ambos elementos");

    int elementos[] = {5, 3, 4, 7, 6, 9, 12};
    int tope = 7;
    cargar_arbol(arbol, elementos, tope);

    int j = 0;
    bool se_encuentra = true;
    while ((se_encuentra) && (j<tope)){
        if(*(int *)arbol_buscar(arbol, (void *)&elementos[j]) != elementos[j])
           se_encuentra = false;
        j++;
    }
    
    test_afirmar(se_encuentra, "Se encuentra todos los elemento en un árbol con varias inserciones");

    int numero_fuera = 10;
    int *elemento_fuera = &numero_fuera;
    test_afirmar(arbol_buscar(arbol, (void*) elemento_fuera) == NULL, "No se encuentra un elemento no insertado");

    test_afirmar(arbol_buscar(arbol, NULL) == NULL, "No se encuentra un elemento nulo");

    arbol_destruir(arbol);
}

void probar_insercion(){
    test_nuevo_grupo("Pruebas básicas con Insertar");

    test_nuevo_sub_grupo("Inserción de raiz");
    abb_t* arbol = arbol_crear(comparador_int, NULL);
    int numero_1 = 5;
    int* elemento_1 = &numero_1;
    test_afirmar(arbol_insertar(arbol, (void*)elemento_1) != ERROR,"Se inserta un primer elemento correctamente");
    test_afirmar((int*) arbol_raiz(arbol) == elemento_1, "El primer elemento es la raíz");
    test_afirmar(*(int*) arbol_raiz(arbol) == numero_1, "El elemento corresponde con el ingresado");

    test_nuevo_sub_grupo("Inserción de un elemento mayor");
    int numero_2 = 3;
    int* elemento_2 = &numero_2;
    arbol_insertar(arbol, (void*) elemento_2);
    test_afirmar(arbol->nodo_raiz->izquierda->elemento == elemento_2, "Se encuentra a la izquierda de la raíz");
    test_afirmar(*(int *)(arbol->nodo_raiz->izquierda->elemento) == numero_2, "El elemento corresponde con el ingresado");
    test_afirmar((int *)arbol_raiz(arbol) == elemento_1, "La raíz sigue siendo la misma");

    test_nuevo_sub_grupo("Inserción de un elemento menor");
    int numero_3 = 7;
    int *elemento_3 = &numero_3;
    test_afirmar(arbol_insertar(arbol, (void *)elemento_3) != ERROR, "Se inserta un elemento mayor correctamente");
    test_afirmar(arbol->nodo_raiz->derecha->elemento == elemento_3, "Se encuentra a la derecha de la raíz");
    test_afirmar(*(int *)(arbol->nodo_raiz->derecha->elemento) == numero_3, "El elemento corresponde con el ingresado");
    test_afirmar((int *)arbol_raiz(arbol) == elemento_1, "La raíz sigue siendo la misma");
    
    test_nuevo_sub_grupo("Inserción de un elemento repetido");
    int numero_4 = 5;
    int *elemento_4 = &numero_4;
    test_afirmar(arbol_insertar(arbol, (void *)elemento_4) != ERROR, "Se inserta un elemento igual a la raíz");
    test_afirmar(arbol->nodo_raiz->derecha->izquierda->elemento == elemento_4, "Se encuentra a la izquierda del mayor");
    test_afirmar(*(int *)(arbol->nodo_raiz->derecha->izquierda->elemento) == numero_4, "El elemento corresponde con el ingresado");
    test_afirmar((int *)arbol_raiz(arbol) == elemento_1, "La raíz sigue siendo la misma");

    arbol_destruir(arbol);

    test_nuevo_sub_grupo("Insertar varios elementos");

    abb_t* arbol_2 = arbol_crear(comparador_int, NULL);

    int elementos[]={5,3,4,7,6,9,12};
    int tope = 7;
    int insercion = cargar_arbol(arbol_2, elementos, tope);

    test_afirmar(insercion == 0, "Se insertaron correctamente varios elementos");
    test_afirmar(arbol_insertar(arbol_2, NULL) == ERROR, "No se inserta un elemento nulo");

    arbol_destruir(arbol_2);
}

void probar_basicas(){
    test_nuevo_grupo("Pruebas básicas");

    test_nuevo_sub_grupo("Creación del árbol");
    abb_t* arbol = arbol_crear(comparador_int, destructor_dinamico);
    test_afirmar(arbol != NULL, "Se crea un árbol");
    test_afirmar(arbol_vacio(arbol), "El árbol creado está vacio");
    test_afirmar(arbol_raiz(arbol) == NULL, "El árbol no tiene raíz");
    arbol_destruir(arbol);

    test_nuevo_sub_grupo("Pruebas con NULL");
    arbol = arbol_crear(comparador_int, NULL);
    test_afirmar(arbol != NULL, "Se crea un árbol sin destructor");
    arbol_destruir(arbol);
    arbol = arbol_crear(NULL, destructor_dinamico);
    test_afirmar(arbol == NULL, "No se crea un árbol sin comparador");
    test_afirmar(arbol_vacio(arbol), "Un árbol nulo está vacío");
    test_afirmar(arbol_raiz(arbol) == NULL, "Un árbol nulo no tiene raíz");

}

int main(){
   
    probar_basicas(); //Crear, Vacio, Destruir, Raiz   
    probar_insercion(); //Insertar, Raiz
    probar_busqueda(); 
    probar_borrado(); 
    probar_recorridos();
    probar_iterador();
    test_mostrar_reporte();
    return 0;
}