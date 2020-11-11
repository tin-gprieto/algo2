#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "pa2mm.h"
#include "lista.h"

#define ERROR -1

#define COLOR_CLARO "\x1b[1;33m"
#define RESET "\x1b[0m"

void pa2m_nuevo_sub_grupo(char* descripcion){
    printf(COLOR_CLARO "%s" RESET "\n", descripcion);
}

void imprimir_separador(){
    printf("---------------------------------------------------------\n");
}

int inicializar_con_varios_elementos(lista_t *lista, int (*insercion)(lista_t *, void *), int* elementos, size_t cantidad){
    size_t i = 0;
    int estado = 0;
    while ((i < cantidad) && (estado == 0)){
        estado = insercion(lista, (void *)(elementos + i));
        i++;
    }
    return estado;
}

bool se_inserto_bien(lista_t *lista, int elementos[], size_t cantidad){
    bool son_iguales = true;
    size_t i = (lista->cantidad) - cantidad;
    int* lista_elemento;

    while(son_iguales && (i<cantidad)){
        lista_elemento = (int*) lista_elemento_en_posicion(lista, i);
        if(lista_elemento != (elementos+i))
            son_iguales = false;
        i++;   
    }
    return son_iguales;

}

bool existe_elemento(lista_t *lista, void* elemento){
    lista_iterador_t *iterador = lista_iterador_crear(lista);
    bool encuentra = false;
    while (lista_iterador_tiene_siguiente(iterador) && !encuentra){
        if(lista_iterador_elemento_actual(iterador) == elemento)
            encuentra = true;
        lista_iterador_avanzar(iterador);
    }
    lista_iterador_destruir(iterador);
    return encuentra;
}

bool vaciar_y_mostrar(lista_t *lista, void *(*elemento)(lista_t *), int (*borrar)(lista_t *), char *descripcion){
    int elimina = 0;
    printf("%s: ", descripcion);
    while ((elimina == 0) && (lista->cantidad > 0)){
        int* corriente = (int*)(elemento(lista));
        printf(" %i ", *corriente);
        elimina = borrar(lista);
    }
    printf("\n");
    return lista_vacia(lista);
}

void probar_operaciones_pila(){
    int elementos[] = {1, 2, 3, 4, 5, 6};
    size_t cant_elementos = 6;
    lista_t *pila = lista_crear();
    int estado_pila = inicializar_con_varios_elementos(pila, lista_apilar, elementos, cant_elementos);
    pa2m_afirmar(estado_pila == 0, "Se apiló varios elementos");
    pa2m_afirmar((lista_elementos(pila) == cant_elementos), "Se insertó la cantidad adecuada");
    int * ultimo_elemento = (int *) lista_ultimo(pila);
    pa2m_afirmar(lista_desapilar(pila) == 0,  "Se desapila un elemento");
    pa2m_afirmar(!existe_elemento(pila, ultimo_elemento), "Se desapiló el último elemento");
    bool se_vacia = vaciar_y_mostrar(pila, lista_ultimo, lista_desapilar, "Pila");
    pa2m_afirmar(se_vacia, "La pila se desapila por completo y queda vacia");
    pa2m_afirmar(lista_desapilar(pila) == ERROR, "No se puede desapilar una pila vacia");
    lista_destruir(pila);
}

void probar_operaciones_cola(){
    int elementos[] = {1, 2, 3, 4, 5, 6};
    size_t cant_elementos = 6;
    lista_t *cola = lista_crear();
    int estado_cola = inicializar_con_varios_elementos(cola, lista_encolar, elementos, cant_elementos);
    pa2m_afirmar(estado_cola == 0, "Se encoló varios elementos");
    pa2m_afirmar((lista_elementos(cola) == cant_elementos), "Se insertó la cantidad adecuada");
    int * primer_elemento = (int*) lista_primero(cola);
    pa2m_afirmar(lista_desencolar(cola) == 0, "Se desencola un elemento");
    pa2m_afirmar(!existe_elemento(cola, primer_elemento), "Se desencoló el primer elemento");
    bool se_vacia = vaciar_y_mostrar(cola, lista_primero, lista_desencolar, "Cola");
    pa2m_afirmar(se_vacia, "La cola se desencola por completo y queda vacia");
    pa2m_afirmar(lista_desencolar(cola) == ERROR, "No se puede desencolar una cola vacia");
    lista_destruir(cola);
}

void insertar_y_borrar_fuera_de_lista(lista_t *lista, void *elemento, size_t posicion, size_t cantidad_en_lista){
    pa2m_nuevo_sub_grupo("Insertar y borrar fuera de lista");
    pa2m_afirmar((lista_insertar_en_posicion(lista, elemento, posicion) == 0), "Se inserta un elemento en una posicion fuera de lista");
    pa2m_afirmar((lista_elementos(lista) == (cantidad_en_lista + 1)), "Tiene la cantidad adecuada");
    pa2m_afirmar((lista_ultimo(lista) == elemento), "El elemento se encuentra al final");
    pa2m_afirmar((lista_elemento_en_posicion(lista, posicion) == NULL), "No existe elemento en la posicion fuera de la lista");
    lista_borrar(lista);
    pa2m_afirmar((lista_ultimo(lista) != elemento), "Se borra el nuevo elemento y no está en el final");
}

void probar_operaciones_limite(){
    float elemento_extra = 3.5;
    int elementos[] = {1, 2, 3, 4, 5, 6};
    size_t cant_elementos = 6;
    lista_t *lista = lista_crear();
    inicializar_con_varios_elementos(lista, lista_insertar, elementos, cant_elementos);

    size_t posicion_fuera = 500;
    insertar_y_borrar_fuera_de_lista(&(*lista), &elemento_extra, posicion_fuera, lista_elementos(lista));
    pa2m_afirmar((lista_elementos(lista) == cant_elementos), "Tiene la cantidad adecuada");

    imprimir_separador();

    //insertar 1000 elementos

    lista_destruir(lista);
}

bool mostrar_elemento(void *elemento, void *contexto){
    if (elemento)
        printf(" %i ", *(int *)elemento);
    return true;
}

bool mostrar_primeros_3_elementos(void *elemento, void *contador){
    if ((*(int *)contador) > 2)
        return false;
    if (elemento && contador){
        printf(" %i ", *(int *)elemento);
        (*(int *)contador)++;
    }
    return true;
}

bool no_mostrar_nada(void *elemento, void *context){
    printf(" -");
    return false;
}

void probar_operaciones_it_interno(){

    int elementos[] = {1, 2, 3, 4, 5, 6};
    size_t cant_elementos = 6;
    lista_t *lista = lista_crear();
    inicializar_con_varios_elementos(lista, lista_insertar, elementos, cant_elementos);

    size_t elementos_recorridos = 0;
    printf("Lista");
    elementos_recorridos = lista_con_cada_elemento(lista, mostrar_elemento, NULL);
    printf("\n");
    pa2m_afirmar((elementos_recorridos == lista_elementos(lista)), "Se recorrió todos los elementos de la lista");
    
    int contador = 0;
    printf("Lista");
    elementos_recorridos = lista_con_cada_elemento(lista, mostrar_primeros_3_elementos, (void *)&contador);
    printf("\n");
    pa2m_afirmar((elementos_recorridos == 3), "Se recorrió los primeros 3 elementos de la lista");

    lista_destruir(lista);
}

void imprimir_con_it_externo(lista_t *lista, lista_iterador_t *iterador){
    size_t elementos_recorridos = 0;
    printf("Lista");
    while (lista_iterador_tiene_siguiente(iterador)){
        printf(" %i ", *(int *)lista_iterador_elemento_actual(iterador));
        lista_iterador_avanzar(iterador);
        elementos_recorridos++;
    }
    printf("\n");
    pa2m_afirmar((elementos_recorridos == lista_elementos(lista)), "Se recorrió todos los elementos de la lista");
}

void probar_operaciones_it_externo(){
    int elementos[] = {1, 2, 3, 4, 5, 6};
    size_t cant_elementos = 6;
    lista_t *lista = lista_crear();
    inicializar_con_varios_elementos(lista, lista_insertar, elementos, cant_elementos);

    lista_iterador_t *iterador = lista_iterador_crear(lista);
    pa2m_afirmar((iterador != NULL), "Se crea un iterador correctamente")
    pa2m_afirmar(((iterador->corriente) == (lista->nodo_inicio)), "El iterador comienza apuntando al primer elemento");
    pa2m_afirmar(((iterador->lista) == lista), "El iterador contiene a la lista");
    imprimir_con_it_externo(&(*lista), &(*iterador));
    lista_iterador_destruir(iterador);
    lista_destruir(lista);

    lista_t* lista2 = lista_crear();
    int elemento = 23;
    int insercion = lista_insertar(lista2, &elemento);
    pa2m_afirmar(insercion == 0, "Se crear una lista con un elemento");
    lista_iterador_t *iterador2 = lista_iterador_crear(lista2);
    imprimir_con_it_externo(&(*lista2), &(*iterador2));

    lista_iterador_destruir(iterador2);
    lista_destruir(lista2);
}

void insertar_y_borrar_al_principio(lista_t *lista, void *elemento, size_t cantidad_en_lista){
    pa2m_nuevo_sub_grupo("Insertar y borrar en la primera posicion");
    pa2m_afirmar((lista_insertar_en_posicion(lista, elemento, 0) == 0), "Se inserta un elemento en la posicion 0");
    pa2m_afirmar((lista_elementos(lista) == (cantidad_en_lista + 1)), "Tiene la cantidad adecuada");
    pa2m_afirmar((lista_borrar_de_posicion(lista, 0) == 0), "Se borra el elemento de la posicion 0");
    pa2m_afirmar((lista_elementos(lista) == cantidad_en_lista), "Tiene la cantidad adecuada");
    pa2m_afirmar((lista_elemento_en_posicion(lista, 0) != elemento), "El elemento borrado no está más");
}

void insertar_y_borrar_en_posicion(lista_t *lista, void *elemento, size_t posicion, size_t cantidad_en_lista){
    pa2m_nuevo_sub_grupo("Insertar y borrar en posicion");
    pa2m_afirmar((lista_insertar_en_posicion(lista, elemento, posicion) == 0), "Se inserta un elemento en una posicion de la lista");
    pa2m_afirmar((lista_elementos(lista) == (cantidad_en_lista + 1)), "Tiene la cantidad adecuada");
    pa2m_afirmar((lista_borrar_de_posicion(lista, posicion) == 0), "Se borra el elemento insertado anteriormente");
    pa2m_afirmar((lista_elementos(lista) == cantidad_en_lista), "Tiene la cantidad adecuada");
    pa2m_afirmar((lista_elemento_en_posicion(lista, posicion) != elemento), "El elemento borrado no está más");
}

void probar_operaciones_avanzadas(){
    float elemento_extra = 3.5;
    int elementos[] = {1, 2, 3, 4, 5, 6};
    size_t cant_elementos = 6;
    lista_t *lista = lista_crear();

    pa2m_nuevo_sub_grupo("Insertar varios elementos");
    int estado = inicializar_con_varios_elementos(lista, lista_insertar, elementos, cant_elementos);
    pa2m_afirmar(estado == 0, "Se insertan varios elementos");
    pa2m_afirmar((lista_elementos(lista) == cant_elementos), "Se insertó la cantidad adecuada");
    bool insercion = se_inserto_bien(lista, elementos, cant_elementos);
    pa2m_afirmar((int)insercion, "Se insertaron en orden correcto");

    imprimir_separador();

    size_t posicion = 4;
    insertar_y_borrar_en_posicion(&(*lista), &elemento_extra, posicion, lista_elementos(lista));
    insercion = se_inserto_bien(lista, elementos, cant_elementos);
    pa2m_afirmar((int)insercion, "La lista volvió al orden anterior de la inserción");

    imprimir_separador();

    insertar_y_borrar_al_principio(&(*lista), &elemento_extra, lista_elementos(lista));
    insercion = se_inserto_bien(lista, elementos, cant_elementos);
    pa2m_afirmar((int)insercion, "La lista volvió al orden anterior de la inserción");

    lista_destruir(lista);
}

void probar_operaciones_basicas(){

    int segundo_elemento = 2;
    int primer_elemento = 1;
    lista_t *lista = lista_crear();

    pa2m_nuevo_sub_grupo("Insertar el primer elemento");
    pa2m_afirmar((lista_insertar(lista, &primer_elemento) == 0), "Se agrega el primer elemento");
    pa2m_afirmar(lista_primero(lista) == lista_ultimo(lista), "El primer elemento también es el último");
    pa2m_afirmar(lista_elementos(lista) == 1, "Tiene 1 elemento");
    pa2m_afirmar((lista_elemento_en_posicion(lista, 0) == &primer_elemento), "El elemento se encuentra en posicion 0 ")
    nodo_t* siguiente = (lista->nodo_inicio)->siguiente;  
    pa2m_afirmar(siguiente == NULL, "El siguiente nodo es NULL");
    pa2m_nuevo_sub_grupo("Insertar un segundo elemento");
    pa2m_afirmar(lista_insertar(lista, &segundo_elemento) == 0, "Se agrega otro elemento");
    pa2m_afirmar(lista_ultimo(lista) == &segundo_elemento, "Es el ultimo elemento de la lista");
    pa2m_afirmar(lista_elementos(lista) == 2, "Tiene 2 elementos");
    pa2m_afirmar((lista_elemento_en_posicion(lista, 1) == &segundo_elemento), "El elemento se encuentra en posicion 1")

    imprimir_separador();

    pa2m_nuevo_sub_grupo("Borrar los dos elementos");
    pa2m_afirmar((lista_borrar(lista) == 0), "Se borra el último elemento");
    pa2m_afirmar(lista->cantidad == 1, "Tiene 1 elemento");
    pa2m_afirmar(lista_primero(lista) == lista_ultimo(lista), "El último elemento también es el primero");
    pa2m_afirmar(lista_elementos(lista) == lista->cantidad, "La cantidad coincide con lista_elementos");
    pa2m_afirmar((lista_borrar(lista) == 0), "Se borra el único elemento");
    pa2m_afirmar(lista_vacia(lista), "La lista está vacia");
    pa2m_afirmar((lista_borrar(lista) == ERROR), "No se puede borrar algo de una lista vacia");

    lista_destruir(lista);
}

void probar_operaciones_comunes(){
    lista_t * lista= lista_crear();
    pa2m_afirmar(lista != NULL, "Se crea una lista");
    pa2m_afirmar(lista_vacia(lista), "La lista está vacia");
    pa2m_afirmar(lista_elementos(lista) == 0, "Tiene 0 elementos");
    lista_destruir(lista);
}

int main(){
    pa2m_nuevo_grupo("OPERACIONES DE CREACIÓN");
    probar_operaciones_comunes();
    pa2m_nuevo_grupo("OPERACIONES DE LISTA");
    probar_operaciones_basicas();
    pa2m_nuevo_grupo("OPERACIONES AVANZADAS DE LISTA");
    probar_operaciones_avanzadas();
    pa2m_nuevo_grupo("OPERACIONES CON ITERADOR EXTERNO");
    probar_operaciones_it_externo();
    pa2m_nuevo_grupo("OPERACIONES CON ITERADOR INTERNO");
    probar_operaciones_it_interno();
    pa2m_nuevo_grupo("OPERACIONES LIMITES DE LISTA");
    probar_operaciones_limite();
    pa2m_nuevo_grupo("OPERACIONES DE COLA");
    probar_operaciones_cola();
    pa2m_nuevo_grupo("OPERACIONES DE PILA");
    probar_operaciones_pila();
    pa2m_mostrar_reporte();
    return 0;
}

