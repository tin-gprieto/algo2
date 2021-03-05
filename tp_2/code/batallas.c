#include "batallas.h"

int golpe(int magnitud, int resistencia){
    return magnitud - (resistencia / 2);
}

int golpe_debil(int magnitud, int resistencia){
    return magnitud - resistencia;
}

int determinar_ganador(int pkm_1, int pkm_2){
    if(pkm_1 >= pkm_2)
        return GANO_PRIMERO;
    return GANO_SEGUNDO;
}
/*
* Golpes con ataque
* Pre : pokemones existentes e inicializados
* Post: Ganador de la batalla
*/
int golpes_basicos(pokemon_t pkm_1, pokemon_t pkm_2){
    int golpe_pkm_1 = golpe(pkm_1.ataque, pkm_2.defensa);
    int golpe_pkm_2 = golpe(pkm_2.ataque, pkm_1.defensa);
    return determinar_ganador(golpe_pkm_1, golpe_pkm_2);
}
/*
* Golpes con ataque y velocidad
* Pre : pokemones existentes e inicializados
* Post: Ganador de la batalla
*/
int golpes_veloces(pokemon_t pkm_1, pokemon_t pkm_2){
    int golpe_pkm_1 = golpe(pkm_1.ataque * pkm_1.velocidad, pkm_2.defensa);
    int golpe_pkm_2 = golpe(pkm_2.ataque * pkm_2.velocidad, pkm_1.defensa);
    return determinar_ganador(golpe_pkm_1, golpe_pkm_2);
}
/*
* Golpes con ataque y altamente defendidos
* Pre : pokemones existentes e inicializados
* Post: Ganador de la batalla
*/
int golpes_defendidos(pokemon_t pkm_1, pokemon_t pkm_2){
    int golpe_pkm_1 = golpe_debil(pkm_1.ataque, pkm_2.defensa);
    int golpe_pkm_2 = golpe_debil(pkm_2.ataque, pkm_1.defensa);
    return determinar_ganador(golpe_pkm_1, golpe_pkm_2);
}
/*
* Golpes esquivados por velocidad
* Pre : pokemones existentes e inicializados
* Post: Ganador de la batalla
*/
int golpes_esquivados(pokemon_t pkm_1, pokemon_t pkm_2){
    int golpe_pkm_1 = golpe(pkm_1.ataque , pkm_2.defensa + pkm_2.velocidad);
    int golpe_pkm_2 = golpe(pkm_2.ataque , pkm_1.defensa + pkm_1.velocidad);
    return determinar_ganador(golpe_pkm_1, golpe_pkm_2);
}
/*
* Golpes con ataque y velocidad y altamente defendidos
* Pre : pokemones existentes e inicializados
* Post: Ganador de la batalla
*/
int golpes_mixtos(pokemon_t pkm_1, pokemon_t pkm_2){
    int golpe_pkm_1 = golpe_debil(pkm_1.ataque * pkm_1.velocidad, pkm_2.defensa);
    int golpe_pkm_2 = golpe_debil(pkm_2.ataque * pkm_2.velocidad, pkm_1.defensa);
    return determinar_ganador(golpe_pkm_1, golpe_pkm_2);
}

int funcion_batalla_1(void* pkm_1, void* pkm_2){
    pokemon_t pokemon_1 = *(pokemon_t*)pkm_1;
    pokemon_t pokemon_2 = *(pokemon_t*)pkm_2;
    return golpes_basicos(pokemon_1, pokemon_2);
}

int funcion_batalla_2(void* pkm_1, void* pkm_2){
    pokemon_t pokemon_1 = *(pokemon_t*)pkm_1;
    pokemon_t pokemon_2 = *(pokemon_t*)pkm_2;
    return golpes_veloces(pokemon_1, pokemon_2);
}

int funcion_batalla_3(void* pkm_1, void* pkm_2){
    pokemon_t pokemon_1 = *(pokemon_t*)pkm_1;
    pokemon_t pokemon_2 = *(pokemon_t*)pkm_2;
    return golpes_defendidos(pokemon_1, pokemon_2);
}

int funcion_batalla_4(void* pkm_1, void* pkm_2){
    pokemon_t pokemon_1 = *(pokemon_t*)pkm_1;
    pokemon_t pokemon_2 = *(pokemon_t*)pkm_2;
    return golpes_esquivados(pokemon_1, pokemon_2);
}

int funcion_batalla_5(void* pkm_1, void* pkm_2){
    pokemon_t pokemon_1 = *(pokemon_t*)pkm_1;
    pokemon_t pokemon_2 = *(pokemon_t*)pkm_2;
    return golpes_mixtos(pokemon_1, pokemon_2);
}