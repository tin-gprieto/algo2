#include "../code/juego.h"
#include "../code/interfaz.h"

int main(){
    system("clear");
    interfaz_t menus[MAX_MENU];
    inicializar_menus(menus);
    char clave =  mostrar_menu(menus, MENU_INICIO, NULL);
    system("clear");
    printf("    Opción elegida : %c \n", clave); 
    clave =  mostrar_menu(menus, MENU_GYM, "CAPO");
    system("clear");
    printf("    Opción elegida : %c \n", clave);
    clave = mostrar_menu(menus, MENU_BATALLA, "GENIO");
    system("clear");
    printf("    Opción elegida : %c \n", clave);
    clave = mostrar_menu(menus, MENU_VICTORIA, NULL);
    system("clear");
    printf("    Opción elegida : %c \n", clave);
    clave = mostrar_menu(menus, MENU_DERROTA, NULL);
    system("clear");
    printf("    Opción elegida : %c \n", clave);
    return 0;
}