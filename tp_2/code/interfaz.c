#include "interfaz.h"

#define FONDO "\e[44m"

const size_t LIMITE_INTERFAZ = 80;
const size_t MARCO_INICIO = 20;
const size_t MARCO_FIN = 19;
const size_t INTERFAZ_DESCRP= 30;
const size_t INTERFAZ_TITULO= 25;
const int INICIO = 0;
const int FIN = 1;
const int LIM_MARCO = 2;


/* 
* 
* Pre:
* Post:
*/
void imprimir_espaciado(){
    printf("     " FONDO);
    for(int i=0; i < LIMITE_INTERFAZ; i++)
        printf(" ");
    printf("\n" RESET);
}
/* 
* 
* Pre:
* Post:
*/
void imprimir_margen(int margen, size_t longitud){
    if(margen == INICIO)
        printf("     ");
    printf(FONDO);
    for(int i=0; i < longitud; i++)
        printf(" ");
    if(margen == FIN)
        printf("\n" RESET);
}
/* 
* 
* Pre:
* Post:
*/
void imprimir_marco(int marco){
    if(marco == FIN){
        for(int i=0; i < LIM_MARCO; i++)
            imprimir_espaciado();
    }
    printf("     ");
    for(int i=0; i< LIMITE_INTERFAZ; i++)
        printf("_");
    printf("\n");
    if(marco == INICIO){
        for(int i=0; i < LIM_MARCO; i++)
            imprimir_espaciado();
    }
}
void titulo_gimnasio(const char* titulo){
    printf("     "AMARILLO FONDO"                     ____________________________________                       "RESET"\n");
    imprimir_espaciado();
    printf("     "BLANCO FONDO  "                      ߷  GIMNASIO: %s " RESET, titulo);
    if(strlen(titulo)< INTERFAZ_TITULO){
        for (int i = 0; i < INTERFAZ_TITULO-strlen(titulo); i++)
            printf(FONDO" ");
    }
    imprimir_margen(FIN, MARCO_FIN);
    printf("     "AMARILLO FONDO"                     ____________________________________                       "RESET"\n");
}

void titulo_batalla(const char* titulo){
    printf("     "AMARILLO FONDO"                       ____________________________________                     "RESET"\n");
    imprimir_espaciado();
    printf("     "VERDE FONDO   "                       %s VICTORIA:" BLANCO " %s " RESET, TILDE, titulo);
     if(strlen(titulo)< INTERFAZ_TITULO){
        for (int i = 0; i < INTERFAZ_TITULO-strlen(titulo); i++)
            printf(FONDO" ");
    }
    imprimir_margen(FIN, MARCO_FIN);
    printf("     "AMARILLO FONDO"                       ____________________________________                     "RESET"\n");
}

void titulo_victoria(){
    printf("     "VERDE FONDO"                       ____________________________________                     "RESET"\n");
    imprimir_espaciado();
    printf("     "VERDE FONDO"                             %s GIMANSIO SUPERADO %s                              "RESET"\n", TILDE, TILDE);
    printf("     "VERDE FONDO"                       ____________________________________                     "RESET"\n");
}

void titulo_derrota(){ 
    printf("     "ROJO FONDO"                      ____________________________________                      "RESET"\n");
    imprimir_espaciado(); 
    printf("     "ROJO FONDO"                               %s HAS PERDIDO %s                                  "RESET"\n", CRUZ, CRUZ);
    printf("     "ROJO FONDO"                      ____________________________________                      "RESET"\n");
}

void menu_maestro(){
    imprimir_espaciado();
    imprimir_espaciado();
    printf("     "FONDO BLANCO"                               ▄███████████▄                                    "RESET"\n");        
    printf("     "FONDO BLANCO"                            ▄██"ROJO"░░░░░░░░░░░░░"BLANCO"██▄                                 "RESET"\n");
    printf("     "FONDO BLANCO"                           ██"ROJO"░░░░░░░░░░░░░░░░░"BLANCO"███                               "RESET"\n");
    printf("     "FONDO BLANCO"                         ██"ROJO"░░░░░░░░░░░░░░░░░░░░░"BLANCO"██                              "RESET"\n");
    printf("     "FONDO BLANCO"                        █"ROJO"░░░░░░░░░"BLANCO"███████"ROJO"░░░░░░░░░"BLANCO"█                             "RESET"\n");
    printf("     "FONDO BLANCO"                        █"ROJO"░░░░░░░"BLANCO"██"ROJO"░░░░░░░"BLANCO"██"ROJO"░░░░░░░"BLANCO"█                             "RESET"\n");
    printf("     "FONDO BLANCO"                        ██████████"ROJO"░░░"BLANCO"█"ROJO"░░░"BLANCO"██████████                             "RESET"\n");
    printf("     "FONDO BLANCO"                        █▓▓▓▓▓▓▓██"ROJO"░░░░░░░"BLANCO"██▓▓▓▓▓▓▓█                             "RESET"\n");
    printf("     "FONDO BLANCO"                        █▓▓▓▓▓▓▓▓▓███████▓▓▓▓▓▓▓▓▓█                             "RESET"\n");
    printf("     "FONDO BLANCO"                         ██▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓██                              "RESET"\n");
    printf("     "FONDO BLANCO"                          ██▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓██                               "RESET"\n");
    printf("     "FONDO BLANCO"                           ▀██▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓██▀                                "RESET"\n");
    printf("     "FONDO BLANCO"                              ▀█████████████▀                                   "RESET"\n");
    imprimir_espaciado();
    printf("     "AMARILLO FONDO"                   ____________________________________                         "RESET"\n");
    imprimir_espaciado();
    printf("     "AMARILLO FONDO"                     TE HAS CONSAGRADO MAESTRO POKEMÓN                          "RESET"\n");
    printf("     "AMARILLO FONDO"                   _____________________________________                        "RESET"\n");
    imprimir_espaciado();
    imprimir_espaciado();
}

void titulo_inicio(){
    printf("     "AMARILLO FONDO);
    printf("                                          .::.                                  " RESET "\n     "AMARILLO FONDO);
    printf("                                        .;:**'                                  " RESET "\n");
    imprimir_espaciado();
    printf("     "AMARILLO FONDO);                                                    
    printf("          .:XHHHHk.              db.   .;;.     dH  MX                          " RESET "\n     "AMARILLO FONDO);  
    printf("        oMMMMMMMMMMM       ~MM  dMMP :MMMMMR   MMM  MR      ~MRMN               " RESET "\n     "AMARILLO FONDO);
    printf("        QMMMMMb   MMX       MMMMMMP !MX' :M~   MMM MMM  .oo. XMMM 'MMM          " RESET "\n     "AMARILLO FONDO);
    printf("          `MMMM.  )M> :X!Hk. MMMM   XMM.o:     MMMMMMM X?XMMM MMM>!MMP          " RESET "\n     "AMARILLO FONDO);
    printf("           'MMMb.dM! XM M'?M MMMMMX.`MMMMMMMM~ MM MMM XM   MX MMXXMM            " RESET "\n     "AMARILLO FONDO);
    printf("            ~MMMMM~ XMM. .XM XM` MMMb.~*?**~ .MMX M t MMbooMM XMMMMMP           " RESET "\n     "AMARILLO FONDO);
    printf("             ?MMM>  YMMMMMM! MM   `?MMRb.    `'''   !L:MMMMM XM IMMM            " RESET "\n     "AMARILLO FONDO);
    printf("              MMMX    MMMM   MM       ~:            !Mh.    dMI IMMP            " RESET "\n     "AMARILLO FONDO);
    printf("              'MMM.                                             IMX             " RESET "\n     "AMARILLO FONDO);
    printf("               ~M!M                                             IMP             " RESET "\n");
}

/* 
* 
* Pre:
* Post:
*/
bool clave_valida(char clave, char opciones[], size_t cantidad){
    bool validez = false;
    int i = 0;
    while(i < cantidad && !validez){
        if(opciones[i] == clave)
            validez = true;
        i++;
    }
    return validez;
}

/* 
* 
* Pre:
* Post:
*/
char pedir_clave(char opciones[], size_t cantidad){
    printf("    Ingrese alguna opción : ");
    char clave = (char)getc(stdin);
    while(!clave_valida((char)clave, opciones, cantidad)){
        getc(stdin);
        printf(ROJO "    %s - Se ingresó una opción INVÁLIDA \n" RESET, CRUZ);
        printf("    Ingrese nuevamente la opción :");
        clave = (char)getc(stdin);
    }
    getc(stdin);
    return clave;
}

/* 
* 
* Pre:
* Post:
*/
void imprimir_descripcion(char opcion, const char* descripcion){
    imprimir_espaciado();
    imprimir_margen(INICIO, MARCO_INICIO);
    printf(AMARILLO " ༄ ( %c )"  RESET FONDO " - %s"  , opcion, descripcion);
    if(strlen(descripcion)< INTERFAZ_DESCRP){
        for (int i = 0; i < INTERFAZ_DESCRP-strlen(descripcion); i++)
            printf(FONDO" ");
    }
    imprimir_margen(FIN, MARCO_FIN);
    imprimir_espaciado();
}

char mostrar_menu(interfaz_t* menu, int tipo, const char* extra){
    imprimir_marco(INICIO);
    if(tipo == MENU_INICIO)
        titulo_inicio();
    if(tipo == MENU_GYM)
        titulo_gimnasio(extra);
    if(tipo == MENU_BATALLA)
        titulo_batalla(extra);
    if(tipo == MENU_VICTORIA)
        titulo_victoria();
    if(tipo == MENU_DERROTA)
        titulo_derrota();

    for (size_t i = 0; i < menu[tipo].cant_opciones; i++)
        imprimir_descripcion(menu[tipo].opciones[i], menu[tipo].descripciones[i]);
    
    imprimir_marco(FIN);
    return pedir_clave(menu[tipo].opciones, menu[tipo].cant_opciones);
}

void inicializar_inicio(interfaz_t* menu){
    menu->opciones[0]= PERSONAJE;
    strcpy(menu->descripciones[0], "Ingresar personaje");
    menu->opciones[1]= AGREGAR_GYM;
    strcpy(menu->descripciones[1], "Agregar gimnasio");
    menu->opciones[2]= INICIAR;
    strcpy(menu->descripciones[2], "Iniciar partida");
    menu->opciones[3]= SIMULAR;
    strcpy(menu->descripciones[3], "Simular partida");
    menu->cant_opciones = 4;
}

void inicializar_gimnasio(interfaz_t* menu){
    menu->opciones[0]= PERSONAJE;
    strcpy(menu->descripciones[0], "Informacion del personaje");
    menu->opciones[1]= GIMNASIO;
    strcpy(menu->descripciones[1], "Informacion del gimnasio");
    menu->opciones[2]= CAMBIAR;
    strcpy(menu->descripciones[2], "Cambiar pokemones de combate");
    menu->opciones[3]= BATALLA;
    strcpy(menu->descripciones[3], "Luchar primer batalla");
    menu->cant_opciones = 4;
}

void inicializar_batalla(interfaz_t* menu){
    menu->opciones[0]= AVANZAR;
    strcpy(menu->descripciones[0], "Siguiente batalla");
    menu->cant_opciones = 1;
}

void inicializar_victoria(interfaz_t* menu){
    menu->opciones[0]= TOMAR_PKM;
    strcpy(menu->descripciones[0], "Tomar prestado un pokemon");
    menu->opciones[1]= CAMBIAR;
    strcpy(menu->descripciones[1], "Cambiar pokemones de combate");
    menu->opciones[2]= AVANZAR;
    strcpy(menu->descripciones[2], "Siguiente gimnasio");

    menu->cant_opciones = 3;
}

void inicializar_derrota(interfaz_t* menu){
    menu->opciones[0]= CAMBIAR;
    strcpy(menu->descripciones[0], "Cambiar pokemones de combate");
    menu->opciones[1]= REPETIR;
    strcpy(menu->descripciones[1], "Repetir batalla");
    menu->opciones[2]= SALIR;
    strcpy(menu->descripciones[2], "Finalizar partida");
    menu->cant_opciones = 3;
}

void inicializar_menus(interfaz_t* menus){
    inicializar_inicio(&(menus[MENU_INICIO]));
    inicializar_gimnasio(&(menus[MENU_GYM]));
    inicializar_batalla(&(menus[MENU_BATALLA]));
    inicializar_victoria(&(menus[MENU_VICTORIA]));
    inicializar_derrota(&(menus[MENU_DERROTA]));
}