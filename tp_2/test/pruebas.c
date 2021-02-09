#include "../code/juego.h"
#include "../code/interfaz.h"

int main(){
    interfaz_t menus[MAX_MENU];
    inicializar_menus(menus);
    char clave = mostrar_menu(menus, MENU_INICIO, NULL);
    printf("    Opción elegida : %c \n", clave);

    
    return 0;
}