#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "pa2mm.h"
#include "lista.h"

#define ERROR -1
void imprimir_separador(){
    printf("------------------------------------------------------\n");
}
void probar_operaciones_comunes(){
    pa2m_nuevo_grupo("OPERACIONES DE CREACIÓN");
    lista_t * lista= lista_crear();
    pa2m_afirmar(lista != NULL, "Se crea una lista");
    pa2m_afirmar(lista_vacia(lista), "La lista está vacia");
    pa2m_afirmar(lista_elementos(lista) == 0, "Tiene 0 elementos");
    lista_destruir(lista);
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

void probar_operaciones_lista(){
    pa2m_nuevo_grupo("OPERACIONES EN LISTA");
    lista_t *lista = lista_crear();
    int primer_elemento=1;
    pa2m_afirmar((lista_insertar(lista, &primer_elemento) == 0), "Se agrega el primer elemento");
    pa2m_afirmar(lista_primero(lista) == &primer_elemento, "Es el primer elemento de la lista");
    pa2m_afirmar(lista_ultimo(lista) == &primer_elemento, "Es el ultimo elemento de la lista")
    pa2m_afirmar(lista_elementos(lista) == 1, "Tiene 1 elemento");
    
    int segundo_elemento = 2;
    pa2m_afirmar((lista_insertar(lista, &segundo_elemento) == 0), "Se agrega otro elemento");
    pa2m_afirmar(lista_ultimo(lista) == &segundo_elemento, "Es el ultimo elemento de la lista")
    pa2m_afirmar(lista_elementos(lista) == 2, "Tiene 2 elementos");

    pa2m_afirmar((lista_elemento_en_posicion(lista, 0) == &primer_elemento), "Elemento en posicio 0 es el primero")
    pa2m_afirmar((lista_elemento_en_posicion(lista, 1) == &segundo_elemento), "Elemento en posicio 1 es el segundo")

    imprimir_separador();

    pa2m_afirmar((lista_borrar(lista) == 0), "Se borra el último elemento");
    pa2m_afirmar(lista_elementos(lista) == 1, "Tiene 1 elemento");
    pa2m_afirmar(lista_primero(lista)==lista_ultimo(lista), "El último elemento también es el primero");

    pa2m_afirmar((lista_borrar(lista) == 0), "Se borra el único elemento");
    pa2m_afirmar(lista_vacia(lista), "La lista está vacia");
    pa2m_afirmar((lista_borrar(lista) == ERROR), "No se puede borrar algo de una lista vacia");

    pa2m_nuevo_grupo("OPERACIONES AVANZADAS EN LISTA");

    size_t cant_insertar = 6;
    int elementos[] = {1,2,3,4,5,6};
    size_t i = 0;
    int estado = 0;
    while ((i < cant_insertar) && (estado == 0)){
        estado = lista_insertar(lista, elementos+i);
        i++;
    }

    pa2m_afirmar(estado == 0, "Se insertan varios elementos");
    pa2m_afirmar((lista_elementos(lista) == cant_insertar), "Se insertó la cantidad adecuada");
    bool insercion = se_inserto_bien(lista, elementos, cant_insertar);
    pa2m_afirmar((int) insercion, "Se insertaron en orden correcto");

    imprimir_separador();

    float elemento_extra = 3.5;
    pa2m_afirmar((lista_insertar_en_posicion(lista, &elemento_extra, 4) == 0), "Se inserta un elemento en la posicion 4");
    pa2m_afirmar((lista_elementos(lista) == (cant_insertar+1)), "Tiene la cantidad adecuada");
    pa2m_afirmar((lista_borrar_de_posicion(lista, 4) == 0), "Se borra el elemento de la posicion 4");
    pa2m_afirmar((lista_elementos(lista) == cant_insertar), "Tiene la cantidad adecuada");
    pa2m_afirmar((lista_elemento_en_posicion(lista, 4) != &elemento_extra), "El elemento borrado no está más");
    insercion = se_inserto_bien(lista, elementos, cant_insertar);
    pa2m_afirmar((int)insercion, "La lista volvió al orden anterior de la inserción");

    imprimir_separador();

    pa2m_afirmar((lista_insertar_en_posicion(lista, &elemento_extra, 0) == 0), "Se inserta un elemento en la posicion 0");
    pa2m_afirmar((lista_elementos(lista) == (cant_insertar + 1)), "Tiene la cantidad adecuada");
    pa2m_afirmar((lista_borrar_de_posicion(lista, 0) == 0), "Se borra el elemento de la posicion 0");
    pa2m_afirmar((lista_elementos(lista) == cant_insertar), "Tiene la cantidad adecuada");
    pa2m_afirmar((lista_elemento_en_posicion(lista, 0) != &elemento_extra), "El elemento borrado no está más");
    insercion = se_inserto_bien(lista, elementos, cant_insertar);
    pa2m_afirmar((int)insercion, "La lista volvió al orden anterior de la inserción");

    pa2m_nuevo_grupo("OPERACIONES LIMITES EN LISTA");

    pa2m_afirmar((lista_insertar_en_posicion(lista, &elemento_extra, 500) == 0), "Se inserta un elemento en la posicion 500");
    pa2m_afirmar((lista_elementos(lista) == (cant_insertar + 1)), "Tiene la cantidad adecuada");
    pa2m_afirmar((lista_ultimo(lista) == &elemento_extra), "El elemento se encuentra al final");
    pa2m_afirmar((lista_elemento_en_posicion(lista, 500) == NULL), "No existe la posicion 500");
    lista_borrar(lista);
    pa2m_afirmar((lista_ultimo(lista) != &elemento_extra), "Se borra el nuevo elemento y no está en el final")
    pa2m_afirmar((lista_elementos(lista) == cant_insertar), "Tiene la cantidad adecuada");

    //insertar 1000 elementos
    
    lista_destruir(lista);
}

void probar_operaciones_cola(){
    pa2m_nuevo_grupo("OPERACIONES EN COLA");
}

void probar_operaciones_pila(){     
    pa2m_nuevo_grupo("OPERACIONES EN PILA");
}

void probar_operaciones_iterador(){
    pa2m_nuevo_grupo("OPERACIONES CON ITERADOR EXTERNO");

    pa2m_nuevo_grupo("OPERACIONES CON ITERADOR INTERNO");
}

int main(){
    probar_operaciones_comunes();
    probar_operaciones_lista();
    //probar_operaciones_cola();
    //probar_operaciones_pila();
    //probar_operaciones_iterador();
    pa2m_mostrar_reporte();
    return 0;
}