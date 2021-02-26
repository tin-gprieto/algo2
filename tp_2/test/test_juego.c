#include "../code/juego.h"

#define DESCRIPCION_MAX 80

void personaje_creado(char * ruta_archivo, size_t caja, size_t party){
    personaje_t* personaje = personaje_cargar(ruta_archivo);
    test_afirmar(personaje != NULL, "Se crea correctamente el personaje");
    if(personaje){
        test_afirmar(lista_elementos(personaje->caja) == caja, "La caja tiene la cantidad de pokemones correcta");
        test_afirmar(lista_elementos(personaje->party) == party, "El party tiene la cantidad de pokemones correcta");
    }
    personaje_destruir(personaje);
}

void personaje_no_creado(char * ruta_archivo){
    personaje_t* personaje = personaje_cargar(ruta_archivo);
    test_afirmar(personaje == NULL, "No se crea el personaje");
}

void pruebas_cargar_personaje(){
    test_nuevo_grupo("1 - Pruebas cargar personaje");
    test_nuevo_sub_grupo("1.1.Archivo correcto, menos de 6 pokemones");
    personaje_creado("test/txt/personaje/pocos_pokemones.csv", 3, 3);
    test_nuevo_sub_grupo("1.2.Archivo correcto, más de 6 pokemones");
    personaje_creado("test/txt/personaje/muchos_pokemones.csv", 12, 6);
    test_nuevo_sub_grupo("1.3.Archivo vacio");
    personaje_no_creado("test/txt/personaje/archivo_vacio.csv");
    test_nuevo_sub_grupo("1.4.Dos personajes");
    personaje_no_creado("test/txt/personaje/personaje_doble.csv");
    test_nuevo_sub_grupo("1.5.Personaje sin pokemon");
    personaje_no_creado("test/txt/personaje/personaje_vacio.csv");
    test_nuevo_sub_grupo("1.6.Personaje con mal formato");
    personaje_no_creado("test/txt/personaje/personaje_incorrecto.csv");
    test_nuevo_sub_grupo("1.7.Pokemón con mal formato");
    personaje_no_creado("test/txt/personaje/pokemon_incorrecto.csv");
    test_nuevo_sub_grupo("1.8.Pokemón sin personaje");
    personaje_no_creado("test/txt/personaje/pokemon_sin_dueño.csv");
    test_nuevo_sub_grupo("1.9.Linea conocida pero inválida");
    personaje_no_creado("test/txt/personaje/linea_intrusa.csv");
    test_nuevo_sub_grupo("1.10.Linea desconocida");
    personaje_no_creado("test/txt/personaje/linea_ilegible.csv");
}

int main(){
    pruebas_cargar_personaje();
    test_mostrar_reporte();
    return EXITO;
}