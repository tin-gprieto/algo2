#include "../code/juego.h"
#include "../code/interfaz.h"

int main(){
    interfaz_t* interfaz = interfaz_crear(MAX_MENU);
    if(!interfaz) return ERROR;
    pokemon_t pkm_1;
    strcpy(pkm_1.nombre, "Pikachu");
    pkm_1.ataque = 1;
    pkm_1.defensa = 5;
    pkm_1.velocidad = 6;
    pkm_1.elegido = false;
    pokemon_t pkm_2;
    strcpy(pkm_2.nombre, "Charizard");
    pkm_2.ataque = 50;
    pkm_2.defensa = 32;
    pkm_2.velocidad = 4;
    pkm_2.elegido = true;
    pokemon_t pkm_3;
    strcpy(pkm_3.nombre, "Charmilion");
    pkm_3.ataque = 30;
    pkm_3.defensa = 9;
    pkm_3.velocidad = 12;
    pkm_3.elegido = true;

    personaje_t personaje;
    strcpy(personaje.nombre, "Martin Gonzalez");

    personaje.caja = lista_crear();
    lista_insertar(personaje.caja, (void*)&pkm_2);
    lista_insertar(personaje.caja, (void*)&pkm_3);
    lista_insertar(personaje.caja, (void*)&pkm_1);

    personaje.party = lista_crear();
    lista_insertar(personaje.party, (void*)&pkm_2);
    lista_insertar(personaje.party, (void*)&pkm_3);

    informacion_personaje(&personaje);

    entrenador_t entrenador;

    strcpy(entrenador.nombre, "Martin Gonzalez");

    entrenador.pokemones = lista_crear();
    lista_insertar(entrenador.pokemones, (void*)&pkm_2);
    lista_insertar(entrenador.pokemones, (void*)&pkm_3);
    lista_insertar(entrenador.pokemones, (void*)&pkm_1);

    gimnasio_t gimnasio;

    strcpy(gimnasio.nombre, "Ciudad Paleta");
    gimnasio.dificultad = 15;
    gimnasio.cant_entrenadores = 8;
    gimnasio.entrenadores = pila_crear();
    pila_apilar(gimnasio.entrenadores, (void*) &entrenador);
    
    informacion_gimnasio(&gimnasio);

    /*
    size_t posicion = pedir_pokemon(personaje.caja, ENTRENADOR, personaje.nombre);
    pokemon_t* seleccionado = lista_elemento_en_posicion(personaje.caja, posicion);
    printf("          %s ", seleccionado->nombre);
    printf("        ATQ: %i ", seleccionado->ataque);
    printf("        DEF: %i ", seleccionado->defensa);
    printf("        VEL: %i \n", seleccionado->velocidad);
    */
    interfaz_destruir(interfaz);
    lista_destruir(personaje.caja);
    lista_destruir(personaje.party);
    lista_destruir(entrenador.pokemones);
    pila_destruir(gimnasio.entrenadores);
    return EXITO;
}