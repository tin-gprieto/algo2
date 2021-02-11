#include "interfaz.h"

#define FONDO "\e[44m"
#define COLOR "\e[40m"
#define VACIO ""
const size_t MARCO_ESP = 2;
const size_t INTERFAZ_LIM = 80;
const size_t INTERFAZ_ESPACIO= 10;
const size_t INTERFAZ_OPC= 10;
const size_t MARGEN_CORTO = 5;
const size_t MARGEN_MEDIO = 20;
const size_t MARGEN_MEDIO_LARGO = 22;
const size_t MARGEN_LARGO  = 30;

const size_t NOMBRE_MAX  = 17;
const size_t ESP_MIN  = 4;
const size_t ESP_MAX  = 21;

const char ESTADO_NULO = ' ';
const int INICIO = 0;
const int FIN = 1;

void imprimir_espaciado(size_t espacio){
    for(int i=0; i < espacio; i++)
            printf(" ");
}
/* 
* 
* Pre : Recibe que tipo de margen es, si INICIO o FIN del renglón
        y la longitud de dicho margen
* Post: Imprime por pantalla un margen con espacio vacío (con fondo)
*/
void imprimir_margen(int margen, size_t longitud){
    if(margen == INICIO)
        imprimir_espaciado(INTERFAZ_ESPACIO);
    for(int i=0; i < longitud; i++)
        printf(FONDO" ");
    if(margen == FIN)
        printf(RESET"\n");
}

void determinar_color(const char * color){
    if(strcmp(color, AMARILLO) == 0)
        printf(AMARILLO);
    else if(strcmp(color, ROJO) == 0)
        printf(ROJO);
    else if(strcmp(color, VERDE) == 0)
        printf(VERDE);
    else if(strcmp(color, BLANCO) == 0)
        printf(BLANCO);
    else if(strcmp(color, COLOR) == 0)
        printf(COLOR);
}

void imprimir_linea(size_t margen, const char* color, const char* linea){
    imprimir_margen(INICIO, margen);
    size_t limite;

    if(strcmp(VACIO, linea) == 0){
        limite = INTERFAZ_LIM - margen;
        imprimir_margen(FIN, limite);
        return;
    }

    determinar_color(color);
    
    printf("%s", linea);
    
    limite = INTERFAZ_LIM - margen - strlen(linea);

    imprimir_margen(FIN, limite);
    
}

/* 
* Pre : Recibe que tipo de marco es, si INICIO o FIN de la pantalla
* Post: Imprime por pantalla el marco de pantalla 
        (indica el inicio y fin la zona del juego)
*/
void imprimir_marco(int marco){
    if(marco == FIN){
        for(int i=0; i < MARCO_ESP; i++)
            imprimir_linea(MARGEN_MEDIO, VACIO,VACIO);;
    }
    for(int i=0; i < INTERFAZ_ESPACIO; i++)
        printf(" ");
    for(int i=0; i< INTERFAZ_LIM; i++){
        if(marco == FIN)
            printf(FONDO);
        printf("_");
    }
    printf(RESET"\n");
    if(marco == INICIO){
        for(int i=0; i < MARCO_ESP; i++)
            imprimir_linea(MARGEN_MEDIO, VACIO,VACIO);;
    }
}
/* 
* Pre : Recibe algún color AMARILLO, ROJO o VERDE
* Post: Devuelve por pantalla una barra, según el color,
        en el centro de la pantalla (con fondo y margen)
*/
void imprimir_barra(const char* color, int barra){
    imprimir_margen(INICIO, MARGEN_MEDIO);
    determinar_color(color);
    printf("________________________________________"RESET);
    imprimir_margen(FIN, MARGEN_MEDIO);
    if(barra==INICIO)
        imprimir_linea(MARGEN_MEDIO, VACIO,VACIO);
}

/* 
* Valida la clave ingresada por el usuario
* Pre : Recibe una clave y las opciones que tiene para ser válida
* Post: Devuelve verdader si la clave cumple con alguna de las opciones
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
* Pide alguna de las opciones y devuelve la letra que ingrese el usuario
* Pre : Recibe todas las opciones posibles y la cantidad de las mismas
* Post: Devuelve un letra ingresada y válida dentro de las opciones
*/
char pedir_clave(char opciones[], size_t cantidad){
    imprimir_margen(INICIO, 0);
    printf("Ingrese alguna opción : ");
    char clave = (char)getc(stdin);
    while(!clave_valida((char)clave, opciones, cantidad)){
        getc(stdin);
        imprimir_espaciado(INTERFAZ_ESPACIO);
        printf(ROJO "%s - Se ingresó una opción INVÁLIDA \n" RESET, CRUZ);
        imprimir_espaciado(INTERFAZ_ESPACIO);
        printf("Ingrese nuevamente la opción :");
        clave = (char)getc(stdin);
    }
    getc(stdin);
    return clave;
}

/* 
* 
* Pre : Recibe la clave y la descripción de una opción
* Post: Imprime en el centro de la pantalla la información 
        (con fondo y margen)
*/
void imprimir_opcion(char clave, const char* descripcion){
    imprimir_margen(INICIO, MARGEN_MEDIO);               
    printf(AMARILLO "༄ ( %c )" BLANCO " - %s", clave, descripcion);
    size_t ocupado =  INTERFAZ_OPC + strlen(descripcion); 
    imprimir_margen(FIN, INTERFAZ_LIM - ocupado - MARGEN_MEDIO);
}

void mostrar_opciones(interfaz_t* interfaz, int tipo){
    for (size_t i = 0; i < interfaz->menus[tipo].cant_opciones; i++){
        imprimir_linea(MARGEN_MEDIO, VACIO,VACIO);
        imprimir_opcion(interfaz->menus[tipo].opciones[i], interfaz->menus[tipo].descripciones[i]);
        imprimir_linea(MARGEN_MEDIO, VACIO,VACIO);
    }
    imprimir_marco(FIN);
    interfaz->estado = pedir_clave(interfaz->menus[tipo].opciones, interfaz->menus[tipo].cant_opciones);
}

void titulo_inicio(){
    imprimir_marco(INICIO);
    imprimir_margen(INICIO, MARGEN_CORTO);
    printf(AMARILLO FONDO"                                     .::.                             " RESET);
    imprimir_margen(FIN, MARGEN_CORTO);
    imprimir_margen(INICIO, MARGEN_CORTO);
    printf(AMARILLO FONDO"                                   .;:**'                             " RESET);
    imprimir_margen(FIN, MARGEN_CORTO);
    imprimir_margen(INICIO, MARGEN_CORTO);
    printf(AMARILLO FONDO"     .:XHHHHk.              db.   .;;.     dH  MX                     " RESET ); 
    imprimir_margen(FIN, MARGEN_CORTO);
    imprimir_margen(INICIO, MARGEN_CORTO);
    printf(AMARILLO FONDO"   oMMMMMMMMMMM       ~MM  dMMP :MMMMMR   MMM  MR      ~MRMN          " RESET );
    imprimir_margen(FIN, MARGEN_CORTO);
    imprimir_margen(INICIO, MARGEN_CORTO);
    printf(AMARILLO FONDO"   QMMMMMb   MMX       MMMMMMP !MX' :M~   MMM MMM  .oo. XMMM 'MMM     " RESET );
    imprimir_margen(FIN, MARGEN_CORTO);
    imprimir_margen(INICIO, MARGEN_CORTO);
    printf(AMARILLO FONDO"     `MMMM.  )M> :X!Hk. MMMM   XMM.o:     MMMMMMM X?XMMM MMM>!MMP     " RESET );
    imprimir_margen(FIN, MARGEN_CORTO);
    imprimir_margen(INICIO, MARGEN_CORTO);
    printf(AMARILLO FONDO"      'MMMb.dM! XM M'?M MMMMMX.`MMMMMMMM~ MM MMM XM   MX MMXXMM       " RESET );
    imprimir_margen(FIN, MARGEN_CORTO);
    imprimir_margen(INICIO, MARGEN_CORTO);
    printf(AMARILLO FONDO"       ~MMMMM~ XMM. .XM XM` MMMb.~*?**~ .MMX M t MMbooMM XMMMMMP      " RESET );
    imprimir_margen(FIN, MARGEN_CORTO);
    imprimir_margen(INICIO, MARGEN_CORTO);
    printf(AMARILLO FONDO"        ?MMM>  YMMMMMM! MM   `?MMRb.    `'''   !L:MMMMM XM IMMM       " RESET );
    imprimir_margen(FIN, MARGEN_CORTO);
    imprimir_margen(INICIO, MARGEN_CORTO);
    printf(AMARILLO FONDO"         MMMX    MMMM   MM       ~:            !Mh.    dMI IMMP       " RESET );
    imprimir_margen(FIN, MARGEN_CORTO);
    imprimir_margen(INICIO, MARGEN_CORTO);
    printf(AMARILLO FONDO"         'MMM.                                             IMX        " RESET );
    imprimir_margen(FIN, MARGEN_CORTO);
    imprimir_margen(INICIO, MARGEN_CORTO);
    printf(AMARILLO FONDO"          ~M!M                                             IMP        " RESET );
    imprimir_margen(FIN, MARGEN_CORTO);
}

void menu_inicio(interfaz_t* interfaz){
    titulo_inicio();
    mostrar_opciones(interfaz, MENU_INICIO);
}

void titulo_gimnasio(const char* gimnasio){
    imprimir_marco(INICIO);
    imprimir_barra(AMARILLO, INICIO);
    char string[INTERFAZ_LIM];
    sprintf(string, " * GIMNASIO: %s *", gimnasio);
    imprimir_linea(MARGEN_MEDIO, BLANCO, string);
    imprimir_barra(AMARILLO, FIN);
}

void menu_gimnasio(interfaz_t* interfaz, const char* gimansio){
    titulo_gimnasio(gimansio);
    mostrar_opciones(interfaz, MENU_GYM);
}
void calcular_separacion(){

}
void imprimir_magnitud(int magnitud_1, int magnitud_2, const char* id){
    char string[INTERFAZ_LIM - MARGEN_MEDIO_LARGO];

    if(magnitud_1 < 9)
        sprintf(string, "%s: %i               %s: %i", id, magnitud_1, id, magnitud_2);
    else
        sprintf(string, "%s: %i              %s: %i", id, magnitud_1, id, magnitud_2);

    imprimir_linea(MARGEN_MEDIO_LARGO, BLANCO, string);
}

void imprimir_nombre(const char * nombre_1, const char * nombre_2){
    char string[INTERFAZ_LIM - MARGEN_MEDIO_LARGO];
    char separcion[MAX_STR];
    strcpy(separcion,"");
    for(int i = 0; i< ESP_MAX - strlen(nombre_1); i++){
        strcat(separcion, " ");
    }
    sprintf(string, "%s%s%s", nombre_1, separcion, nombre_2);
    imprimir_linea(MARGEN_MEDIO_LARGO, AMARILLO, string);
}

void titulo_batalla_pokemon(pokemon_t* pkm_1, pokemon_t* pkm_2){
    imprimir_linea(MARGEN_MEDIO, VACIO,VACIO);
    
    imprimir_nombre(pkm_1->nombre, pkm_2->nombre);
    imprimir_magnitud(pkm_1->ataque, pkm_2->ataque, "ATQ");
    imprimir_magnitud(pkm_1->defensa, pkm_2->defensa, "DEF");
    imprimir_magnitud(pkm_1->velocidad, pkm_2->velocidad, "VEL");
    
    imprimir_linea(MARGEN_MEDIO, VACIO,VACIO);
}

void titulo_batalla(pokemon_t* pkm_1, pokemon_t* pkm_2, int estado){
    imprimir_marco(INICIO);
    imprimir_linea(MARGEN_MEDIO, VACIO,VACIO);
    imprimir_linea(MARGEN_MEDIO, AMARILLO, "BATALLA");
    imprimir_linea(MARGEN_MEDIO, VACIO,VACIO);
    imprimir_linea(MARGEN_MEDIO, COLOR, "       PROPIO       ||       RIVAL       ");
    
    titulo_batalla_pokemon(pkm_1, pkm_2);
    
    if(estado == DERROTA){
        imprimir_barra(ROJO, INICIO);
        imprimir_linea(MARGEN_LARGO, ROJO, "      DERROTA");
        imprimir_barra(ROJO, INICIO);
    }
    if(estado == VICTORIA){
        imprimir_barra(VERDE, INICIO);
        imprimir_linea(MARGEN_LARGO, VERDE,"    VICTORIA");
        imprimir_barra(VERDE, INICIO);
    }

    imprimir_linea(MARGEN_MEDIO, VACIO,VACIO);
}

void menu_batalla(interfaz_t* interfaz, pokemon_t* pkm_1, pokemon_t* pkm_2, int estado){
    titulo_batalla(pkm_1, pkm_2, estado);
    mostrar_opciones(interfaz, MENU_BATALLA);
}

void titulo_victoria(){
    imprimir_marco(INICIO);
    imprimir_barra(VERDE, INICIO);
    imprimir_linea(MARGEN_LARGO, VERDE," GIMANSIO SUPERADO ");
    imprimir_barra(VERDE, FIN);
}

void menu_victoria(interfaz_t* interfaz){
    titulo_victoria();
    mostrar_opciones(interfaz, MENU_VICTORIA);
}

void titulo_derrota(const char* gimansio){ 
    imprimir_marco(INICIO);
    imprimir_barra(ROJO, INICIO);
    imprimir_linea(MARGEN_LARGO, ROJO, " HAS PERDIDO ");
    imprimir_barra(ROJO, FIN);
    imprimir_linea(MARGEN_MEDIO, VACIO,VACIO);
    char string_2[INTERFAZ_LIM];
    sprintf(string_2,"ULTIMO GIMNASIO: %s ", gimansio);
    imprimir_linea(MARGEN_MEDIO, AMARILLO, string_2);
}

void menu_derrota(interfaz_t* interfaz, const char* gimnasio){
    titulo_derrota(gimnasio);
    mostrar_opciones(interfaz, MENU_DERROTA);
}

void menu_maestro(){
    imprimir_marco(INICIO);
    imprimir_linea(MARGEN_MEDIO, VACIO,VACIO);;
    imprimir_margen(INICIO, MARGEN_MEDIO);
    printf(FONDO BLANCO"            ▄█████████████▄             "RESET);        
    imprimir_margen(FIN, MARGEN_MEDIO);
    imprimir_margen(INICIO, MARGEN_MEDIO);
    printf(FONDO BLANCO"         ▄██"ROJO"░░░░░░░░░░░░░░░"BLANCO"██▄          "RESET);
    imprimir_margen(FIN, MARGEN_MEDIO);
    imprimir_margen(INICIO, MARGEN_MEDIO);
    printf(FONDO BLANCO"        ██"ROJO"░░░░░░░░░░░░░░░░░░░"BLANCO"██         "RESET);
    imprimir_margen(FIN, MARGEN_MEDIO);
    imprimir_margen(INICIO, MARGEN_MEDIO);
    printf(FONDO BLANCO"       ██"ROJO"░░░░░░░░░░░░░░░░░░░░░"BLANCO"██        "RESET);
    imprimir_margen(FIN, MARGEN_MEDIO);
    imprimir_margen(INICIO, MARGEN_MEDIO);
    printf(FONDO BLANCO"      █"ROJO"░░░░░░░░░"BLANCO"███████"ROJO"░░░░░░░░░"BLANCO"█       "RESET);
    imprimir_margen(FIN, MARGEN_MEDIO);
    imprimir_margen(INICIO, MARGEN_MEDIO);
    printf(FONDO BLANCO"      █"ROJO"░░░░░░░"BLANCO"██"ROJO"░░░░░░░"BLANCO"██"ROJO"░░░░░░░"BLANCO"█       "RESET);
    imprimir_margen(FIN, MARGEN_MEDIO);
    imprimir_margen(INICIO, MARGEN_MEDIO);
    printf(FONDO BLANCO"      ██████████"ROJO"░░░"BLANCO"█"ROJO"░░░"BLANCO"██████████       "RESET);
    imprimir_margen(FIN, MARGEN_MEDIO);
    imprimir_margen(INICIO, MARGEN_MEDIO);
    printf(FONDO BLANCO"      █▓▓▓▓▓▓▓██"ROJO"░░░░░░░"BLANCO"██▓▓▓▓▓▓▓█       "RESET);
    imprimir_margen(FIN, MARGEN_MEDIO);
    imprimir_margen(INICIO, MARGEN_MEDIO);
    printf(FONDO BLANCO"      █▓▓▓▓▓▓▓▓▓███████▓▓▓▓▓▓▓▓▓█       "RESET);
    imprimir_margen(FIN, MARGEN_MEDIO);
    imprimir_margen(INICIO, MARGEN_MEDIO);
    printf(FONDO BLANCO"       ██▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓██        "RESET);
    imprimir_margen(FIN, MARGEN_MEDIO);
    imprimir_margen(INICIO, MARGEN_MEDIO);
    printf(FONDO BLANCO"        ██▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓██         "RESET);
    imprimir_margen(FIN, MARGEN_MEDIO);
    imprimir_margen(INICIO, MARGEN_MEDIO);
    printf(FONDO BLANCO"         ▀██▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓██▀          "RESET);
    imprimir_margen(FIN, MARGEN_MEDIO);
    imprimir_margen(INICIO, MARGEN_MEDIO);
    printf(FONDO BLANCO"            ▀█████████████▀             "RESET);
    imprimir_margen(FIN, MARGEN_MEDIO);
    imprimir_barra(AMARILLO, INICIO);
    imprimir_linea(MARGEN_MEDIO, AMARILLO,"   TE HAS CONSAGRADO MAESTRO POKEMON!");
    imprimir_barra(AMARILLO, FIN);
    imprimir_linea(MARGEN_MEDIO, VACIO,VACIO);;
    imprimir_marco(FIN);
}

int buscar_opcion(char opciones[], size_t tope, char opcion){
    bool encontro = false;
    int pos = 0;
    while( (pos < tope) && (!encontro)){
        if(opciones[pos]  == opcion)
            encontro = true;
        else
            pos++;
    }
    if(!encontro)
        return ERROR;
    return pos;
}

void eliminar_letra(char opciones[], int pos, size_t tope){
    char aux = opciones[pos];
    opciones[pos] = opciones[tope - 1];
    opciones[tope - 1] = aux;
}

void eliminar_descripcion(char descripciones[MAX_OPC][MAX_STR], int pos, size_t tope){
    char aux[MAX_STR];
    strcpy(aux, descripciones[pos]);
    strcpy(descripciones[pos], descripciones[tope - 1]);
    strcpy(descripciones[tope - 1], aux);
}

void eliminar_opcion(interfaz_t* interfaz, size_t menu, char opcion){
    size_t cantidad = interfaz->menus[menu].cant_opciones;
    int pos = buscar_opcion(interfaz->menus[menu].opciones,cantidad, opcion);
    if(pos == ERROR)
        return;
    eliminar_letra(interfaz->menus[menu].opciones, pos, cantidad);
    eliminar_descripcion(interfaz->menus[menu].descripciones, pos, cantidad);
    interfaz->menus[menu].cant_opciones --;
}

void listar_pokemones(){
    imprimir_marco(INICIO);

    imprimir_marco(FIN);
}

size_t pedir_numero(size_t maximo){
    size_t numero = 0;

    return numero;
}

void* pedir_pokemon(lista_t* pokemones){
    listar_pokemones(pokemones);
    size_t lim = lista_elementos(pokemones) + 1;
    size_t opcion = pedir_numero(lim);
    if(opcion == lim)
        return NULL;
    return lista_elemento_en_posicion(pokemones, opcion);
}

void cargar_opcion(interfaz_t* interfaz, size_t menu, char opcion, const char* descripcion){
    size_t tope = interfaz->menus[menu].cant_opciones;
    interfaz->menus[menu].opciones[tope] = opcion;
    strcpy(interfaz->menus[menu].descripciones[tope], descripcion);
    interfaz->menus[menu].cant_opciones ++;
}   

char interfaz_estado(interfaz_t* interfaz){
    return interfaz->estado;
}

interfaz_t* interfaz_crear(size_t cant_menus){
    interfaz_t* inter_aux = malloc(sizeof(interfaz_t));
    if(!inter_aux) return NULL;
    inter_aux->cant_menus = cant_menus;
    inter_aux->estado = ESTADO_NULO;
    menu_t* menus_aux = calloc(cant_menus, sizeof(menu_t));
    if(!menus_aux)return NULL;
    inter_aux->menus = menus_aux;
    for(int i = 0; i < cant_menus; i++)
        inter_aux->menus[i].cant_opciones = 0;
    return inter_aux;
}

void interfaz_destruir(interfaz_t* interfaz){
    free(interfaz->menus);
    free(interfaz);
}

void inicializar_inicio(interfaz_t* interfaz){
    cargar_opcion(interfaz, MENU_INICIO, PERSONAJE, "Ingresar personaje" );
    cargar_opcion(interfaz, MENU_INICIO, AGREGAR_GYM, "Agregar gimnasio" );
    cargar_opcion(interfaz, MENU_INICIO, INICIAR, "Iniciar partida" );
    cargar_opcion(interfaz, MENU_INICIO, SIMULAR, "Simular partida" );
}
void inicializar_gimnasio(interfaz_t* interfaz){
    cargar_opcion(interfaz, MENU_GYM, PERSONAJE, "Informacion del personaje" );
    cargar_opcion(interfaz, MENU_GYM, GIMNASIO, "Informacion del gimnasio" );
    cargar_opcion(interfaz, MENU_GYM, CAMBIAR, "Cambiar pokemones de combate" );
    cargar_opcion(interfaz, MENU_GYM, BATALLA, "Luchar primer batalla" );
}
void inicializar_batalla(interfaz_t* interfaz){
    cargar_opcion(interfaz, MENU_BATALLA, AVANZAR, "Siguiente batalla" );
}
void inicializar_victoria(interfaz_t* interfaz){
    cargar_opcion(interfaz, MENU_VICTORIA, TOMAR_PKM, "Tomar prestado un pokemon" );
    cargar_opcion(interfaz, MENU_VICTORIA, CAMBIAR, "Cambiar pokemones de combate" );
    cargar_opcion(interfaz, MENU_VICTORIA, AVANZAR, "Siguiente gimnasio" );
}
void inicializar_derrota(interfaz_t* interfaz){
    cargar_opcion(interfaz, MENU_DERROTA, CAMBIAR, "Cambiar pokemones de combate" );
    cargar_opcion(interfaz, MENU_DERROTA, REPETIR, "Repetir batalla o simulacion" );
    cargar_opcion(interfaz, MENU_DERROTA, SALIR, "Finalizar partida" );
}

void inicializar_interfaz(interfaz_t* interfaz){
    inicializar_inicio(interfaz);
    inicializar_gimnasio(interfaz);
    inicializar_batalla(interfaz);
    inicializar_victoria(interfaz);
    inicializar_derrota(interfaz);
}
