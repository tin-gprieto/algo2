#include "../code/interfaz.h"

#define MAX_PKM 3

lista_t* crear_caja(pokemon_t pokemones[], size_t cantidad){
    lista_t* lista = lista_crear();
    if(!lista) return NULL;
    for(int i=0; i < cantidad; i++){
        lista_insertar(lista, &pokemones[i]);
    }
    return lista;
}

lista_t* crear_party(pokemon_t pokemones[], size_t cantidad){
    lista_t* lista = lista_crear();
    if(!lista) return NULL;
    for(int i=0; i < cantidad; i++){
        if(pokemones[i].elegido)
            lista_insertar(lista, &pokemones[i]);
    }
    return lista;
}

void inicializar_estructuras(gimnasio_t* gimnasio, personaje_t* personaje, entrenador_t* entrenador, pokemon_t pokemones[], size_t cant_pkm){
  
    strcpy(personaje->nombre, "Ash Ketchup");
    personaje->caja = crear_caja(pokemones, cant_pkm);

    personaje->party =  crear_party(pokemones, cant_pkm);
    strcpy(entrenador->nombre, "Brock");

    personaje->medallas = 5;

    entrenador->pokemones = crear_caja(pokemones, cant_pkm);

    strcpy(gimnasio->nombre, "Ciudad Paleta");
    gimnasio->dificultad = 15;
    gimnasio->cant_entrenadores = 8;
    gimnasio->entrenadores = pila_crear();
    pila_apilar(gimnasio->entrenadores, (void*) entrenador);
}

void crear_pokemones(pokemon_t pokemones[], size_t* cantidad){
    pokemon_t pkm_1;
    strcpy(pkm_1.nombre, "Pikachu");
    pkm_1.ataque = 1;
    pkm_1.defensa = 5;
    pkm_1.velocidad = 6;
    pkm_1.elegido = false;
    pkm_1.nivel = 0;
    pokemon_t pkm_2;
    strcpy(pkm_2.nombre, "Charizard");
    pkm_2.ataque = 50;
    pkm_2.defensa = 32;
    pkm_2.velocidad = 4;
    pkm_2.elegido = true;
    pkm_2.nivel = 17;
    pokemon_t pkm_3;
    strcpy(pkm_3.nombre, "Charmilion");
    pkm_3.ataque = 30;
    pkm_3.defensa = 9;
    pkm_3.velocidad = 12;
    pkm_3.elegido = true;
    pkm_3.nivel = 8;

    pokemones[0]=pkm_1;
    pokemones[1]=pkm_2;
    pokemones[2]=pkm_3;
    (*cantidad) = MAX_PKM;
}

int main(){
    interfaz_t* interfaz = interfaz_crear(MAX_MENU);
    if(!interfaz) return ERROR;
    
    pokemon_t pokemones[MAX_PKM];
    size_t cant_pkm = 0;

    crear_pokemones(pokemones, &cant_pkm);

    personaje_t personaje;
    entrenador_t entrenador;
    gimnasio_t gimnasio;

    inicializar_estructuras(&gimnasio, &personaje, &entrenador, pokemones, cant_pkm);

    menu_inicio(interfaz);
    menu_gimnasio(interfaz, &gimnasio);
    personaje_informacion(&personaje);
    gimnasio_informacion(&gimnasio);
    menu_batalla(&pokemones[0], &pokemones[2], DERROTA);
    menu_batalla(&pokemones[1], &pokemones[0], VICTORIA);
    pedir_pokemon(personaje.party, COMBATE);
    pedir_pokemon(personaje.caja, CAJA);
    pedir_pokemon(entrenador.pokemones, ENTRENADOR);

    interfaz_destruir(interfaz);
    lista_destruir(personaje.caja);
    lista_destruir(personaje.party);
    lista_destruir(entrenador.pokemones);
    pila_destruir(gimnasio.entrenadores);
    return EXITO;
}