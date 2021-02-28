#include "../code/juego.h"
#include "../code/estructuras.h"

#define DESCRIPCION_MAX 80

void personaje_creado(char * ruta_archivo, size_t caja, size_t party){
    personaje_t* personaje = personaje_cargar(ruta_archivo);
    test_afirmar(personaje != NULL, "Se crea correctamente el personaje");
    if(personaje){
        test_afirmar(lista_elementos(personaje->caja) == caja, "La caja tiene la cantidad de pokemones correcta");
        //pedir_pokemon(personaje->caja, LISTA_CAJA);
        test_afirmar(lista_elementos(personaje->party) == party, "El party tiene la cantidad de pokemones correcta");
        //pedir_pokemon(personaje->party, LISTA_COMBATE);
    }
    personaje_destruir(personaje);
}

void personaje_no_creado(char * ruta_archivo){
    personaje_t* personaje = personaje_cargar(ruta_archivo);
    test_afirmar(personaje == NULL, "No se crea el personaje, archivo erróneo");
}

void pruebas_cargar_personaje(){
    test_nuevo_grupo("1 - Pruebas cargar personaje");
    test_nuevo_sub_grupo("1.1.Archivo correcto, menos de 6 pokemones");
    personaje_creado("test/txt/personaje/pocos_pokemones.txt", 3, 3);
    test_nuevo_sub_grupo("1.2.Archivo correcto, más de 6 pokemones");
    personaje_creado("test/txt/personaje/muchos_pokemones.txt", 12, 6);
    test_nuevo_sub_grupo("1.3.Dos personajes");
    personaje_no_creado("test/txt/personaje/personaje_doble.txt");
    test_nuevo_sub_grupo("1.4.Personaje sin pokemon");
    personaje_no_creado("test/txt/personaje/personaje_vacio.txt");
    test_nuevo_sub_grupo("1.5.Personaje con mal formato");
    personaje_no_creado("test/txt/personaje/personaje_incorrecto.txt");
    test_nuevo_sub_grupo("1.6.Pokemón con mal formato");
    personaje_no_creado("test/txt/personaje/pokemon_incorrecto.txt");
    test_nuevo_sub_grupo("1.7.Pokemón sin personaje");
    personaje_no_creado("test/txt/personaje/pokemon_sin_dueño.txt");
    test_nuevo_sub_grupo("1.8.Linea conocida pero inválida");
    personaje_no_creado("test/txt/personaje/linea_intrusa.txt");
    test_nuevo_sub_grupo("1.9.Linea desconocida");
    personaje_no_creado("test/txt/personaje/linea_ilegible.txt");
    test_nuevo_sub_grupo("1.10.Archivo vacio");
    personaje_no_creado("test/txt/archivo_vacio.txt");
    test_nuevo_sub_grupo("1.11.Sobrecarga en la lectura");
    personaje_no_creado("test/txt/overflow.txt");
}

bool verificar_orden(heap_t * heap){
    bool cumple_condicion = true;
    int anterior = ((gimnasio_t*)heap_raiz(heap))->dificultad;
    heap_borrar(heap);
    while(cumple_condicion && !heap_vacio(heap)){
        int proximo = ((gimnasio_t*)heap_raiz(heap))->dificultad;
        if(anterior < proximo){
            heap_borrar(heap);
            anterior = proximo;
        }else{
            cumple_condicion = false;
        }
    }
    return cumple_condicion;
}

void gimnasio_creado(char * ruta_archivo, size_t cant_gimnasios){
    heap_t* gimnasios = gimnasios_cargar(ruta_archivo);
    test_afirmar(gimnasios != NULL, "Se crean correctamente los gimnasios");
    if(gimnasios){
        size_t tamanio_heap = heap_elementos(gimnasios);
        test_afirmar(tamanio_heap == cant_gimnasios, "Se cargó la cantidad adecuada de gimnasios");
        if(tamanio_heap > 1)
            test_afirmar(verificar_orden(gimnasios),"El heap creado se encuentra en orden adecuado");
    }
    heap_destruir(gimnasios);
}

void gimnasio_no_creado(char * ruta_archivo){
    heap_t* gimnasios = gimnasios_cargar(ruta_archivo);
    test_afirmar(gimnasios == NULL, "No se crea ningún gimnasio, archivo erróneo");
}

void pruebas_cargar_gimnasio(){
    test_nuevo_grupo("2 - Pruebas cargar gimnasio");
    test_nuevo_sub_grupo("1.1. Archivo correcto, varios gimnasios");
    gimnasio_creado("test/txt/gimnasio/completo.txt", 3);
    test_nuevo_sub_grupo("1.2. Gimnasio correcto, gimnasio minimo");
    gimnasio_creado("test/txt/gimnasio/minimo.txt", 1);
    test_nuevo_sub_grupo("1.3. Gimnasio sin lider");
    gimnasio_no_creado("test/txt/gimnasio/sin_lider.txt");
    test_nuevo_sub_grupo("1.4. Gimnasio sin entrenador");
    gimnasio_no_creado("test/txt/gimnasio/sin_entrenador.txt");
    test_nuevo_sub_grupo("1.5. Gimnasio con dos líderes");
    gimnasio_no_creado("test/txt/gimnasio/sin_entrenador.txt");
    test_nuevo_sub_grupo("1.6. Lider sin pokemones");
    gimnasio_no_creado("test/txt/gimnasio/lider_vacio.txt");
    test_nuevo_sub_grupo("1.7. Entrenador sin pokemones");
    gimnasio_no_creado("test/txt/gimnasio/entrenador_vacio.txt");
    test_nuevo_sub_grupo("1.8. Lider com más de 6 pokemones");
    gimnasio_no_creado("test/txt/gimnasio/lider_max_pkm.txt");
    test_nuevo_sub_grupo("1.9. Entrenador com más de 6 pokemones");
    gimnasio_no_creado("test/txt/gimnasio/entrenador_max_pkm.txt");
    test_nuevo_sub_grupo("1.10. Gimnasio vacío");
    gimnasio_no_creado("test/txt/gimnasio/gimnasio_vacio.txt");
    test_nuevo_sub_grupo("1.11. Línea desconocida");
    gimnasio_no_creado("test/txt/gimnasio/linea_desconocida.txt");
    test_nuevo_sub_grupo("1.12. Orden incorrecto de las lineas");
    gimnasio_no_creado("test/txt/gimnasio/orden_incorrecto.txt");
    test_nuevo_sub_grupo("1.13.Archivo vacio");
    gimnasio_no_creado("test/txt/archivo_vacio.txt");
    test_nuevo_sub_grupo("1.14.Sobrecarga en la lectura");
    gimnasio_no_creado("test/txt/overflow.txt");    
}

int main(){
    pruebas_cargar_personaje();
    pruebas_cargar_gimnasio();
    test_mostrar_reporte();
    return EXITO;
}