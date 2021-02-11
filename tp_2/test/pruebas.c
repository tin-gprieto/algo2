#include "../code/juego.h"
#include "../code/interfaz.h"

int main(){
    interfaz_t* interfaz = interfaz_crear(MAX_MENU);
    if(!interfaz) return ERROR;
    inicializar_interfaz(interfaz);
    pokemon_t pkm_1;
    strcpy(pkm_1.nombre, "Pikachu");
    pkm_1.ataque = 1;
    pkm_1.defensa = 5;
    pkm_1.velocidad = 6;
    pokemon_t pkm_2;
    strcpy(pkm_2.nombre, "Charizard");
    pkm_2.ataque = 50;
    pkm_2.defensa = 32;
    pkm_2.velocidad = 4;
    interfaz_destruir(interfaz);
    return EXITO;
}