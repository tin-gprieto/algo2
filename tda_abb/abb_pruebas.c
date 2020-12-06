#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "test.h"
#include "abb.h"

#define ERROR -1

#define MAX_VECTOR 10

typedef struct contador{
    size_t contador;
    size_t tope;
} contador_t;

typedef struct array{
    void** vector;
    size_t tamanio;
    size_t posicion;
} array_t;

bool array_sin_espacio(array_t array){
    return (array.posicion > (array.tamanio - 1));
}

bool cargar_array_arbol(void* elemento, void* array){
    if(array_sin_espacio(*(array_t*)array)) return false;
    ((array_t*)array)->vector[((array_t*)array)->posicion] = elemento;
    (((array_t*)array)->posicion)++;
    return true;
}

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

int cargar_arbol(abb_t* arbol, int elementos[], size_t tope){
    int i = 0;
    int insercion = 0;
    while ((insercion == 0) && (i < tope)){
        insercion = arbol_insertar(arbol, (void *)&elementos[i]);
        i++;
    }
    return insercion;
}

bool buscar_elementos(abb_t* arbol, int elementos[], int tope){
    bool encuentra = true;
    int i = 0;
    while(encuentra && i<tope){
        encuentra = (arbol_buscar(arbol, &elementos[i]) != NULL);
        i++;
    }
    return encuentra;
}

void print_array(int* array, size_t tope){
    printf("[");
    for(size_t i = 0; i < tope; i++){
        printf(" %i ", array[i]);
    }
    printf("] \n");
}
bool no_imprimir(void* elemento, void* extra){
    return false;
}

bool imprimir_arbol(void* elemento, void* contador){
    contador_t aux = *(contador_t*)contador;
    if(aux.contador > aux.tope) return false;
    if(aux.contador == 0) printf("[");
    printf(" %i ", *(int*) elemento);
    if(aux.contador == aux.tope -1) printf("]\n");
    ((contador_t*)contador)->contador ++;
    return true;
}

bool imprimir_impares(void* elemento, void* contador){
    contador_t aux = *(contador_t*)contador;
    if(aux.contador > aux.tope) return false;
    if(aux.contador == 0) printf("[");
    if((*(int*)elemento)%2 != 0)
        printf(" %i ", *(int*) elemento);
    
    ((contador_t*)contador)->contador ++;
    if(aux.contador == aux.tope - 1) printf("]\n");
    return true;
}

/*
*Compara dos vectores del mismo tamaño
*/
bool comparar_vectores(int vector_1[], int recorrido[], size_t tamanio){
    size_t i=0;
    bool coincide=true;
    while (coincide && i<tamanio){
        if (vector_1[i] != recorrido[i])
            coincide=false;
        i++;
    }
    return coincide;
}

void probar_iterador(){
    int elementos[] = {9, 5, 3, 2, 4, 7, 6, 8, 13, 11, 10, 12, 15, 14, 16};
    size_t tope = 15;
    abb_t* arbol = arbol_crear(comparador_int, NULL);
    cargar_arbol(arbol, elementos, tope);

    contador_t contador;
    contador.contador = 0;
    contador.tope = tope;
    size_t iteracion = 0;
    test_nuevo_grupo("Pruebas con iterador interno");

    test_nuevo_sub_grupo("Iteracion completa");
    contador.contador = 0;
    iteracion = abb_con_cada_elemento(arbol, ABB_RECORRER_INORDEN,imprimir_arbol, &contador);
    test_afirmar(iteracion == tope, "Se itera completamente INorden");
    contador.contador = 0;
    iteracion = abb_con_cada_elemento(arbol, ABB_RECORRER_PREORDEN,imprimir_arbol, &contador);
    test_afirmar(iteracion == tope, "Se itera completamente PREorden");
    contador.contador = 0;
    iteracion = abb_con_cada_elemento(arbol, ABB_RECORRER_POSTORDEN,imprimir_arbol, &contador);
    test_afirmar(iteracion == tope, "Se itera completamente POSTorden");

    test_nuevo_sub_grupo("Iteracion restringida");
    contador.contador = 0;
    iteracion = abb_con_cada_elemento(arbol, ABB_RECORRER_INORDEN, imprimir_impares, &contador);
    test_afirmar(iteracion == tope, "Se itera en todos los elementos INorden");
    contador.contador = 0;
    iteracion = abb_con_cada_elemento(arbol, ABB_RECORRER_PREORDEN,imprimir_impares, &contador);
    test_afirmar(iteracion == tope, "Se itera en todos los elementos PREorden");
    contador.contador = 0;
    iteracion = abb_con_cada_elemento(arbol, ABB_RECORRER_POSTORDEN,imprimir_impares, &contador);
    test_afirmar(iteracion == tope, "Se itera en todos los elementos POSTorden");

    test_nuevo_sub_grupo("Pruebas de fallo");
    iteracion = abb_con_cada_elemento(arbol, ABB_RECORRER_INORDEN, NULL, NULL);
    test_afirmar(iteracion == 0, "No itera si la funcion es NULL");
    iteracion = abb_con_cada_elemento(arbol, ABB_RECORRER_INORDEN, no_imprimir, NULL);
    test_afirmar(iteracion == 0, "No itera si la funcion es siempre falsa");
    int recorrido_invalido = 5;
    contador.contador = 0;
    iteracion = abb_con_cada_elemento(arbol, recorrido_invalido, imprimir_arbol, &contador);
    test_afirmar(iteracion == 0, "No itera si el recorrido es inválido");

    arbol_destruir(arbol);
}

void trasformar_generico_a_int(void** array, size_t tope, int array_int[]){
    for(int i = 0; i < tope; i++)
        array_int[i] = *(int*)array[i];
}

void pruebas_recorrido_completas(size_t (*recorrido)(abb_t*, void**, size_t), int orden_completo[], int orden_incompleto[], int orden_insuficiente[]){
    int completo[] = {9, 5, 3, 2, 4, 7, 6, 8, 13, 11, 10, 12, 15, 14, 16};
    size_t tope_completo = 15;
    int incompleto[] = {9, 5, 3, 2, 4, 13, 15, 14, 16};
    size_t tope_incompleto = 9;
    size_t tope_insuficiente =  9;  


    test_nuevo_sub_grupo("Árbol Completo");
    abb_t* arbol_completo = arbol_crear(comparador_int, NULL);
    cargar_arbol(arbol_completo, completo, tope_completo);
    
    void* array_completo[tope_completo];
    size_t cant_recorrido = 0;
    bool orden_adecuado = true;

    cant_recorrido = recorrido(arbol_completo, array_completo , tope_completo);
    test_afirmar(cant_recorrido == tope_completo, "Se recorrió la cantidad adecuada");
    int recorrido_completo[cant_recorrido];
    trasformar_generico_a_int(array_completo, cant_recorrido, recorrido_completo);
    orden_adecuado = comparar_vectores(orden_completo, recorrido_completo, cant_recorrido);
    test_afirmar(orden_adecuado, "Se recorrió en el orden correcto");
     
    arbol_destruir(arbol_completo);
    
    test_nuevo_sub_grupo("Árbol Incompleto");
    
    abb_t* arbol_incompleto = arbol_crear(comparador_int, NULL);
    cargar_arbol(arbol_incompleto, incompleto, tope_incompleto);
    
    void* array_incompleto[tope_incompleto];
    cant_recorrido = 0;
    orden_adecuado = true;

    cant_recorrido = recorrido(arbol_incompleto, array_incompleto , tope_incompleto);
    test_afirmar(cant_recorrido == tope_incompleto, "Se recorrió la cantidad adecuada");
    int recorrido_incompleto[cant_recorrido];
    trasformar_generico_a_int(array_incompleto, cant_recorrido, recorrido_incompleto);
    orden_adecuado = comparar_vectores(orden_incompleto, recorrido_incompleto, cant_recorrido);
    test_afirmar(orden_adecuado, "Se recorrió en el orden correcto");
     
    arbol_destruir(arbol_incompleto);

    test_nuevo_sub_grupo("Array sin capacidad suficiente");

    abb_t* arbol_insuficiente = arbol_crear(comparador_int, NULL);
    cargar_arbol(arbol_insuficiente, completo, tope_completo);
    
    void* array_insuficiente[tope_incompleto];
    cant_recorrido = 0;
    orden_adecuado = true;

    cant_recorrido = recorrido(arbol_insuficiente, array_insuficiente , tope_insuficiente);
    test_afirmar(cant_recorrido == tope_insuficiente, "Se recorrió la cantidad adecuada");
    int recorrido_insuficiente[cant_recorrido];
    trasformar_generico_a_int(array_insuficiente, tope_insuficiente, recorrido_insuficiente);
    orden_adecuado = comparar_vectores(orden_insuficiente, recorrido_insuficiente, tope_insuficiente);
    test_afirmar(orden_adecuado, "Se recorrió en el orden correcto");
     
    arbol_destruir(arbol_insuficiente);
}

void probar_recorridos(){

    test_nuevo_grupo("Recorrido Inorden");
    int inorden_completo[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    int inorden_incompleto[] = {2, 3, 4, 5, 9, 13, 14, 15, 16};
    int inorden_insuficiente[] = {2, 3, 4, 5, 6, 7, 8, 9, 10};
    pruebas_recorrido_completas(arbol_recorrido_inorden, inorden_completo, inorden_incompleto, inorden_insuficiente);

    test_nuevo_grupo("Recorrido Preorden");

    int preorden_completo[] = {9, 5, 3, 2, 4, 7, 6, 8, 13, 11, 10, 12, 15, 14, 16};
    int preorden_incompleto[] = {9, 5, 3, 2, 4, 13, 15, 14, 16};
    int preorden_insuficiente[] = {9, 5, 3, 2, 4, 7, 6, 8, 13};
    pruebas_recorrido_completas(arbol_recorrido_preorden, preorden_completo, preorden_incompleto, preorden_insuficiente);

    test_nuevo_grupo("Recorrido Postorden");

    int postorden_completo[] = {2, 4, 3, 6, 8, 7, 5, 10, 12, 11, 14, 16, 15, 13, 9};
    int postorden_incompleto[] = {2, 4, 3, 5, 14, 16, 15, 13, 9};
    int postorden_insuficiente[] = {2, 4, 3, 6, 8, 7, 5, 10, 12};
    pruebas_recorrido_completas(arbol_recorrido_postorden, postorden_completo, postorden_incompleto, postorden_insuficiente);

}

void prueba_borrado_generica(abb_t* arbol, int* elemento_borrado, size_t cant_inicial, int borrado_esperado[]){
    size_t tamanio_recorrido = cant_inicial;
    void* recorrido[tamanio_recorrido] ;
    size_t cant_recorrido = 0;
    bool orden_adecuado = false;
    test_afirmar(arbol_borrar(arbol, (void*) elemento_borrado) == 0, "Se elimina el elemento");
    test_afirmar(arbol_buscar(arbol, (void*) elemento_borrado) == NULL, "El elemento no se encuentra en el árbol");
    int elementos_borrados[tamanio_recorrido];
    cant_recorrido = arbol_recorrido_preorden(arbol, recorrido, tamanio_recorrido);
    test_afirmar(cant_recorrido == cant_inicial - 1, "El árbol se encuentra con la cantidad de elementos adecuada");
    trasformar_generico_a_int(recorrido, cant_recorrido, elementos_borrados);
    orden_adecuado = comparar_vectores(borrado_esperado, elementos_borrados, cant_recorrido);
    test_afirmar(orden_adecuado, "Se recorrió en el orden correcto");
    print_array(elementos_borrados, cant_recorrido);

}
 
void probar_borrado(){
    abb_t *arbol = arbol_crear(comparador_int, NULL);
    int elementos[] = {5, 3, 4, 7, 6, 9, 12};
    size_t tope = 7;
    cargar_arbol(arbol, elementos, tope);

    test_nuevo_grupo("Pruebas con Borrar");

    printf("Árbol(preorden): ");
    print_array(elementos, tope);

    test_nuevo_sub_grupo("Raíz con Predecesor inorden");
    int borrado_1_esperado[] = {4, 3, 7, 6, 9, 12};
    printf("Borra el elemento : %i : %p \n", elementos[0], (void*) &elementos[0]);
    prueba_borrado_generica(arbol, &elementos[0], tope, borrado_1_esperado);
    tope --;

    test_nuevo_sub_grupo("No tiene sub-árbol menor");
    int borrado_2_esperado[] = {4, 3, 7, 6, 12};
    printf("Borra el elemento : %i : %p \n", elementos[5], (void*) &elementos[5]);
    prueba_borrado_generica(arbol, &elementos[5], tope, borrado_2_esperado);
    tope --;
    
    test_nuevo_sub_grupo("El hijo menor es hoja");
    int borrado_3_esperado[] = {4, 3, 6, 12};
    printf("Borra el elemento : %i : %p \n", elementos[3], (void*) &elementos[3]);
    prueba_borrado_generica(arbol, &elementos[3], tope, borrado_3_esperado);
    tope --;
    
    test_nuevo_sub_grupo("No tiene hijos");
    int borrado_4_esperado[] = {4, 3, 6};
    printf("Borra el elemento : %i : %p \n", elementos[6], (void*) &elementos[6]);
    prueba_borrado_generica(arbol, &elementos[6], tope, borrado_4_esperado);
    tope --;
    
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
    size_t tope = 7;
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
    size_t tope = 7;
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
    probar_recorridos();
    probar_iterador();
    probar_borrado();
    test_mostrar_reporte();
    return 0;
}