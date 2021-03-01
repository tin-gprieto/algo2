#include "interfaz.h"

#define FONDO "\e[1;44m"
#define FONDO_2 "\e[40m"
#define SUBRAYADO "\e[4;37m"
#define AMARILLO_SUB "\e[4;33m"
#define AMARILLO_PARP "\e[5;33m"
#define LIMPIAR "clear"

#define ASCII_NUM 48

static const size_t MARCO_ESP          = 2;
static const size_t INTERFAZ_LIM       = 80;
static const size_t INTERFAZ_ESPACIO   = 10;
static const size_t MARGEN_CORTO       = 5;
static const size_t MARGEN_MEDIO       = 20;
static const size_t MARGEN_MEDIO_LARGO = 22;
static const size_t MARGEN_LARGO       = 30;

static const int ESP_1  = 21;
static const int ESP_2  = 15;
static const int ESP_3  = 4;

#define ATAQUE "ATQ"
#define DEFENSA "DEF"
#define VELOCIDAD "VEL"
#define NIVEL "NVL"

static const char INTERFAZ_INICIAL = ' ';
static const int INICIO = 0;
static const int FIN = 1;
static const size_t UNIDAD= 1;

/* 
* Imprime una serie de espacios por pantalla
* Pre : 
* Post: Espacios por pantalla
*/
void imprimir_espaciado(size_t espacio){
    for(int i=0; i < espacio; i++)
            printf(" ");
}
/* 
*  Imprime un espacio en la interfaz para alinear texto
* Pre : Recibe que tipo de margen es, si INICIO o FIN del renglón
* y la longitud de dicho margen
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
/* 
* Imprime un renglón dentro de la interfaz
* Pre : -
* Post: Un linea vacía en la interfaz
*/
void imprimir_enter(){
    imprimir_espaciado(INTERFAZ_ESPACIO);
    printf(FONDO);
    imprimir_espaciado(INTERFAZ_LIM);
    printf(RESET"\n");
}
/* 
* Dado string identificado de color (constantes) 
* imprime por pantalla dicho color
* Pre : Color válido entre las opciones
* Post: Color próximo para un printf
*/
void determinar_color(const char * color){
    if(strcmp(color, AMARILLO) == 0)
        printf(AMARILLO);
    else if(strcmp(color, AMARILLO_SUB) == 0)
        printf(AMARILLO_SUB);
    else if(strcmp(color, AMARILLO_PARP) == 0)
        printf(AMARILLO_PARP);
    else if(strcmp(color, ROJO) == 0)
        printf(ROJO);
    else if(strcmp(color, VERDE) == 0)
        printf(VERDE);
    else if(strcmp(color, BLANCO) == 0)
        printf(BLANCO);
    else if(strcmp(color, FONDO_2) == 0)
        printf(FONDO_2);
    else if(strcmp(color, SUBRAYADO) == 0)
        printf(SUBRAYADO);
}
/* 
* Imprime una linea completa de interfaz dado un contenido
* Pre : margen y extensión del string menor al limite, color válido entre las opciones
* Post: Un linea de texto alineada en la interfaz
*/
void imprimir_linea(size_t margen, const char* color, const char* linea){
    imprimir_margen(INICIO, margen);
    determinar_color(color);
    printf("%s", linea);
    printf(RESET);
    size_t limite = INTERFAZ_LIM - margen - strlen(linea);
    imprimir_margen(FIN, limite);
}
/* 
* Imprime sobre una misma linea dos strings con eleccion de color por separado
* Pre : margen y extensión de los strings menor al limite, 
* colores válidos entre las opciones
* Post: Un linea de texto alineada en la interfaz
*/
void imprimir_linea_partida(size_t margen, const char* color_1, const char* linea_1, const char* color_2, const char* linea_2){
    imprimir_margen(INICIO, margen);
    size_t limite;

    determinar_color(color_1);
    printf("%s", linea_1);
    printf(RESET FONDO);
    determinar_color(color_2);
    printf("%s", linea_2);
    printf(RESET);
    limite = INTERFAZ_LIM - margen - strlen(linea_1) - strlen(linea_2);

    imprimir_margen(FIN, limite);
    
}
/* 
* Pre : Recibe que tipo de marco es, si INICIO o FIN de la pantalla
* Post: Imprime por pantalla el marco de pantalla 
* (indica el inicio y fin la interfaz)
*/
void imprimir_marco(int marco){
    if(marco == FIN){
        for(int i=0; i < MARCO_ESP; i++)
            imprimir_enter();
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
           imprimir_enter();
    }
}
/* 
* Pre : Recibe algún color AMARILLO, ROJO o VERDE
* Post: Devuelve por pantalla una barra, según el color,
* en el centro de la pantalla (con fondo y margen)
*/
void imprimir_barra(const char* color, int barra){
    imprimir_margen(INICIO, MARGEN_MEDIO);
    determinar_color(color);
    printf("________________________________________"RESET);
    imprimir_margen(FIN, MARGEN_MEDIO);
    if(barra==INICIO)
        imprimir_enter();
}
/* 
* Muestra por pantalla un adverticia después de una entrada de datos
* Pre : -
* Post: Informacion por pantalla
*/
void mostrar_advertencia(){
    imprimir_espaciado(INTERFAZ_ESPACIO);
    printf(ROJO "%s - Se ingresó una opción INVÁLIDA \n" RESET, CRUZ);
    imprimir_espaciado(INTERFAZ_ESPACIO);
    printf("Ingrese nuevamente la opción :");
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
    imprimir_espaciado(INTERFAZ_ESPACIO);
    printf("Ingrese alguna opción : ");
    char clave = (char)getc(stdin);
    while(!clave_valida((char)clave, opciones, cantidad)){
        getc(stdin);
        mostrar_advertencia();
        clave = (char)getc(stdin);
    }
    getc(stdin);
    return clave;
}
/* 
* Dada un posicion evalua si es válida para un conjunto
* Pre : tope como máximo del conjunto
* Post: verdadero si la posicion es válida
*/
bool pos_valida(size_t pos, size_t tope){
    return pos <= tope;
}
/* 
* Dado el máximo de un conjunto, 
* pide al usuario una posicion válida para el mismo
* Pre : máximo del conjunto (última posicion válida)
* Post: Una posición elegida por el usuario 
*/
size_t pedir_pos(size_t maximo){
    imprimir_espaciado(INTERFAZ_ESPACIO);
    printf("Ingrese el n° del pokemón que desea : ");
    size_t numero = (size_t)getc(stdin);
    numero -= ASCII_NUM;
    while(!pos_valida(numero, maximo)){
        getc(stdin);
        mostrar_advertencia();
        numero = (size_t)getc(stdin);
        numero -= ASCII_NUM;
    }
    getc(stdin);
    return numero - 1;
}
/* 
* Imprime la opción de un menu
* Pre : Recibe la clave y la descripción de una opción
* Post: Imprime la información alineada a la interfaz 
*/
void imprimir_opcion(char clave, const char* descripcion){
    char linea_1[INTERFAZ_LIM];            
    char linea_2[INTERFAZ_LIM];
    sprintf(linea_1," >> ( %c )  ", clave);             
    sprintf(linea_2,"-  %s", descripcion);             
    imprimir_linea_partida(MARGEN_MEDIO, AMARILLO, linea_1, BLANCO, linea_2);
    
}
/* 
* Muestra por pantalla todas las opciones de un menu
* Pre : tipo válido dentro los menus de interfaz, interfaz no nula
* Post: Opciones del menu en pantalla
*/
void mostrar_opciones(interfaz_t* interfaz, int tipo){
    for (size_t i = 0; i < interfaz->menus[tipo].cant_opciones; i++){
        imprimir_enter();
        imprimir_opcion(interfaz->menus[tipo].opciones[i], interfaz->menus[tipo].descripciones[i]);
        imprimir_enter();
    }
    imprimir_marco(FIN);
    interfaz->estado = pedir_clave(interfaz->menus[tipo].opciones, interfaz->menus[tipo].cant_opciones);
}
/*
* Muestra por pantalla la opción de avanzar y pide al usuario 
* que la ingrese para continuar con la ejecución 
* Pre : -
* Post: Información por pantalla y pedido al usuario de un input
*/
void pedir_opcion_avanzar(){
    imprimir_enter();
    imprimir_opcion(OPCION_AVANZAR, "Avanzar");
    imprimir_marco(FIN);
    char opciones[2];
    sprintf(opciones, "%c", OPCION_AVANZAR);
    pedir_clave(opciones, UNIDAD);
}
/* 
* Muestra por pantalla un dibujo para el inicio
* Pre : -
* Post: Dibujo por pantalla
*/
void dibujo_inicio(){
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
/* 
* Imprime por pantalla el encabezado del gimnasio
* Pre : nombre del gimnasio
* Post: Título impreso por pantalla
*/
void encabezado_gimnasio(const char* gimnasio){
    imprimir_marco(INICIO);
    imprimir_barra(AMARILLO, INICIO);
    imprimir_linea_partida(MARGEN_MEDIO, AMARILLO, " GIMNASIO:  ", BLANCO, gimnasio);
    imprimir_barra(AMARILLO, FIN); 
}
/* 
* Carga un string con espacios dada una longitud
* Pre : longitud mayor a 0, separacion vacio
* Post: separacion de la longitud pasada por parametro con espacios
*/
void cargar_separacion(char separcion[INTERFAZ_LIM], int longitud){
    if(longitud < 0) return;
    strcpy(separcion,"");
    for(int i = 0; i < longitud; i++){
        strcat(separcion, " ");
    }
}
/* 
* Carga un string con espacios dada una longitud y un número
  (según si es un número de dos o una cifra)
* Pre : longitud mayor a 0, string vacio
* Post: separacion con espacios según el número y la longitud
*/
void cargar_separacion_magnitud(char separcion[INTERFAZ_LIM], int longitud, int magnitud){
    if(magnitud < 10)
        longitud++;
    if(longitud < 0) return;
    strcpy(separcion,"");
    for(int i = 0; i < longitud; i++){
        strcat(separcion, " ");
    }
}
/* 
* Dadas dos magnitudes, las imprime en una linea con una separacion fija
* Pre : dos números mayores a 0 y un string que indique su tipo
* Post: Información por pantalla
*/
void imprimir_magnitud_batalla(int magnitud_1, int magnitud_2, const char* id){
    char string[INTERFAZ_LIM];
    char separcion[INTERFAZ_LIM];
    cargar_separacion_magnitud(separcion, ESP_2, magnitud_1);
    
    if(magnitud_1 == 0)
        sprintf(string, "%s: -%s%s: %i", id, separcion, id, magnitud_2);
    else if(magnitud_2 == 0)
        sprintf(string, "%s: %i%s%s: -", id, magnitud_1, separcion, id);
    else
        sprintf(string, "%s: %i%s%s: %i", id, magnitud_1, separcion, id, magnitud_2);


    imprimir_linea(MARGEN_MEDIO_LARGO, BLANCO, string);
}
/* 
* Dados dos nombres, los imprime en una linea con separcion fija
* Pre : dos strings de longitud menor al límite de la interfaz
* Post: Información ṕor pantalla
*/
void imprimir_nombre_batalla(const char * nombre_1, const char * nombre_2){
    char string[INTERFAZ_LIM];
    char separcion[INTERFAZ_LIM];
    cargar_separacion(separcion, ESP_1 - (int) strlen(nombre_1));
    sprintf(string, "%s%s%s", nombre_1, separcion, nombre_2);
    imprimir_linea(MARGEN_MEDIO_LARGO, AMARILLO, string);
}
/* 
* Muestra por pantalla las caracteristicas de dos pokemones
* Pre : pokemones previamente cargados
* Post: Información por pantalla
*/
void mostrar_pokemones_batalla(pokemon_t* pkm_1, pokemon_t* pkm_2){
    imprimir_enter();
    imprimir_nombre_batalla(pkm_1->nombre, pkm_2->nombre);
    imprimir_magnitud_batalla(pkm_1->nivel, pkm_2->nivel, NIVEL);
    imprimir_magnitud_batalla(pkm_1->ataque, pkm_2->ataque, ATAQUE);
    imprimir_magnitud_batalla(pkm_1->defensa, pkm_2->defensa, DEFENSA);
    imprimir_magnitud_batalla(pkm_1->velocidad, pkm_2->velocidad, VELOCIDAD);
    imprimir_enter();
}
/* 
* Imprime por pantalla la información de una batalla
* Pre : estado DERROTA o VICTORIA, pokemones cargados
* Post: Información por pantalla
*/
void informacion_batalla(pokemon_t* pkm_propio, pokemon_t* pkm_rival, int estado){
    imprimir_marco(INICIO);
    imprimir_enter();
    imprimir_linea(MARGEN_MEDIO, AMARILLO_SUB, "BATALLA");
    imprimir_enter();
    
    if(estado == BATALLA_DERROTA){
        imprimir_barra(ROJO, INICIO);
        imprimir_linea(MARGEN_LARGO, ROJO, "      DERROTA");
        imprimir_barra(ROJO, INICIO);
    }
    if(estado == BATALLA_VICTORIA){
        imprimir_barra(VERDE, INICIO);
        imprimir_linea(MARGEN_LARGO, VERDE,"    VICTORIA");
        imprimir_barra(VERDE, INICIO);
    }
    imprimir_enter();
   
    imprimir_linea(MARGEN_MEDIO, FONDO_2, "       PROPIO       ||       RIVAL       "); 
    mostrar_pokemones_batalla(pkm_propio, pkm_rival);
}
/* 
* Imprime por pantalla el encabezado de victoria
* Pre : -
* Post: Información por pantalla
*/
void encabezado_victoria(){
    imprimir_marco(INICIO);
    imprimir_barra(VERDE, INICIO);
    imprimir_linea(MARGEN_LARGO, VERDE," GIMNASIO SUPERADO ");
    imprimir_barra(VERDE, FIN);
}
/* 
* Imprime por pantalla el encabezado de victoria 
* y el nombre del último gimnasio
* Pre : nombre del gimnasio
* Post: Información por pantalla
*/
void encabezado_derrota(gimnasio_t* gimnasio){ 
    imprimir_marco(INICIO);
    imprimir_barra(ROJO, INICIO);
    imprimir_linea(MARGEN_LARGO, ROJO, " HAS PERDIDO ");
    imprimir_barra(ROJO, FIN);
    imprimir_enter();
    imprimir_linea_partida(MARGEN_MEDIO, SUBRAYADO,"ULTIMO GIMNASIO:",BLANCO, gimnasio->nombre);
    entrenador_t* entrenador = (entrenador_t*) pila_tope(gimnasio->entrenadores);
    if(entrenador){
        imprimir_enter();
        imprimir_linea_partida(MARGEN_MEDIO, SUBRAYADO, "ENTRENADOR:", BLANCO, entrenador->nombre);
        imprimir_enter();
    }
}
/* 
* Dada un letra, lo busca en un vector de letras
* Pre : cantidad de opciones
* Post: Devuelve la posicion de la letra dentro del vector
*/
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
/* 
* Swapea dos letras
* Pre : posicion de la letra a eliminar
* Post: letra a eliminar al final del vector
*/
void eliminar_letra(char opciones[], int pos, size_t tope){
    char aux = opciones[pos];
    opciones[pos] = opciones[tope - 1];
    opciones[tope - 1] = aux;
}
/* 
* Swapea dos strings
* Pre : posicion del string a eliminar
* Post: string a eliminar al final del vector
*/
void eliminar_descripcion(char descripciones[MAX_OPCIONES][MAX_STRING], int pos, size_t tope){
    char aux[MAX_STRING];
    strcpy(aux, descripciones[pos]);
    strcpy(descripciones[pos], descripciones[tope - 1]);
    strcpy(descripciones[tope - 1], aux);
}
/*
* Dado un string, la posicion del pokemon, en qué lista se encuentra y si está elegido
* Agrega al string dicha posicion según corresponda
* Pre : Linea vacia, int lista válido según constantes
* Post: Linea cargada con la posicion según corresponda
*/
void cargar_posicion_a_linea(char linea[], int pos, int lista, bool elegido){
    if(elegido && lista == LISTA_CAJA)
        if (pos > 9)
            sprintf(linea,"* %i", pos);
        else
            sprintf(linea,"* %i ", pos);
    else
        if (pos > 9)
            sprintf(linea,"  %i", pos);
        else
            sprintf(linea,"  %i ", pos);
}
/*
*
* Pre :
* Post:
*/
void cargar_nombre_a_linea(char linea[], char nombre[]){
    char separador[INTERFAZ_LIM];
    cargar_separacion(separador, ESP_2 - (int) strlen(nombre));
    sprintf(linea, " -  %s%s", nombre, separador);
}
/*
*
* Pre :
* Post:
*/
void cargar_magnitud_a_linea(char linea[], int magnitud, const char * id){
    char separador[INTERFAZ_LIM];
    cargar_separacion_magnitud(separador, ESP_3, magnitud);
    char info[INTERFAZ_LIM];
    if(magnitud == 0)
        sprintf(info, "%s:  -%s", id, separador);
    else
        sprintf(info, "%s:  %i%s", id, magnitud, separador);
    strcat(linea, info);
}
/* 
* Muestra la posicion completa del pokemón en una línea
* Pre : tipo de lista (PARTY, CAJA, o ENTRENADOR), pokemón cargado, 
* posicion de dicho pokemón en la lista + 1 
* Post: Información por pantalla en una linea dentro de la interfaz
*/
void mostrar_pokemon(int pos, int lista, pokemon_t* pkm){
    char linea_1[INTERFAZ_LIM];
    cargar_posicion_a_linea(linea_1, pos, lista, pkm->elegido);
    char linea_2[INTERFAZ_LIM];
    cargar_nombre_a_linea(linea_2, pkm->nombre);
    cargar_magnitud_a_linea(linea_2, pkm->nivel, NIVEL);
    cargar_magnitud_a_linea(linea_2, pkm->ataque, ATAQUE);
    cargar_magnitud_a_linea(linea_2, pkm->defensa, DEFENSA);
    cargar_magnitud_a_linea(linea_2, pkm->velocidad, VELOCIDAD);

    if(pkm->elegido && lista == LISTA_CAJA)
        imprimir_linea_partida(MARGEN_CORTO, AMARILLO, linea_1, BLANCO, linea_2);
    else
        imprimir_linea_partida(MARGEN_CORTO, BLANCO, linea_1, BLANCO, linea_2);
}
/* 
* Según el tipo de lista imprime un título identificador
* Pre : tipo de lista (PARTY, CAJA, o ENTRENADOR)
* Post: Título por pantalla
*/
void imprimir_titulo_pokemones(int lista){
    if(lista == LISTA_CAJA){
        imprimir_linea(MARGEN_CORTO, AMARILLO_SUB, "POKEMONES");
    }else if(lista == LISTA_COMBATE){
        imprimir_linea(MARGEN_CORTO, AMARILLO_SUB, "CONJUNTO DE COMBATE");
    }else if(lista == LISTA_ENTRENADOR){
        imprimir_linea(MARGEN_CORTO, AMARILLO_SUB, "POKEMONES DEL RIVAL");
    }
}
/* 
* Muestra todos los pokemones de una lista
* Pre : tipo de lista (PARTY, CAJA, o ENTRENADOR), lista no vacía
* Post: Información por pantalla
*/
void listar_pokemones(lista_t* pokemones, int lista){
    imprimir_titulo_pokemones(lista);
    imprimir_enter();
    lista_iterador_t* iterador = lista_iterador_crear(pokemones);
    int pos = 1;
    while(lista_iterador_tiene_siguiente(iterador)){
        pokemon_t* pkm_actual = (pokemon_t*)lista_iterador_elemento_actual(iterador);
        mostrar_pokemon(pos, lista, pkm_actual);
        lista_iterador_avanzar(iterador);
        pos++;
    }
    lista_iterador_destruir(iterador);
}
/* 
* Dada una interfaz, carga una letra y su descripcion para el menú
* Pre : interfaz creada, menú dentro del rango posible
* Post: Opcion y descripción cargados al final del menu
*/
void cargar_opcion(interfaz_t* interfaz, size_t menu, char opcion, const char* descripcion){
    size_t tope = interfaz->menus[menu].cant_opciones;
    interfaz->menus[menu].opciones[tope] = opcion;
    strcpy(interfaz->menus[menu].descripciones[tope], descripcion);
    interfaz->menus[menu].cant_opciones ++;
}   
/*
* Imprime por pantalla la cantidad de medallas
* Pre : Cantidad de medallas del entrenador principal
* Post: Información por pantalla
*/
void imprimir_medallero(int medallas){
    char str_medallas[INTERFAZ_LIM];
    if(medallas == 0)
        strcpy(str_medallas, " - ");
    else{
        for(int i=0; i < medallas;i++)
            strcat(str_medallas, " -o- ");
    }

    imprimir_linea_partida(MARGEN_CORTO, AMARILLO, "MEDALLAS:  ", AMARILLO, str_medallas);
}
/* 
* Inicializa el menu inicio con sus opciones y descripciones
* Pre : Interfaz creada
* Post: Menú funcional para la interfaz
*/
void inicializar_inicio(interfaz_t* interfaz){
    cargar_opcion(interfaz, MENU_INICIO, OPCION_PERSONAJE, "Ingresar personaje" );
    cargar_opcion(interfaz, MENU_INICIO, OPCION_AGREGAR_GYM, "Agregar gimnasio" );
    cargar_opcion(interfaz, MENU_INICIO, OPCION_INICIAR, "Iniciar partida" );
    cargar_opcion(interfaz, MENU_INICIO, OPCION_SIMULAR, "Simular partida" );
}
/* 
* Inicializa el menu gimnasio con sus opciones y descripciones
* Pre : Interfaz creada
* Post: Menú funcional para la interfaz
*/
void inicializar_gimnasio(interfaz_t* interfaz){
    cargar_opcion(interfaz, MENU_GYM, OPCION_PERSONAJE, "Informacion del personaje" );
    cargar_opcion(interfaz, MENU_GYM, OPCION_GIMNASIO, "Informacion del gimnasio" );
    cargar_opcion(interfaz, MENU_GYM, OPCION_CAMBIAR, "Cambiar pokemones de combate" );
    cargar_opcion(interfaz, MENU_GYM, OPCION_BATALLA, "Luchar primer batalla" );
}
/* 
* Inicializa el menu victoria con sus opciones y descripciones
* Pre : Interfaz creada
* Post: Menú funcional para la interfaz
*/
void inicializar_victoria(interfaz_t* interfaz){
    cargar_opcion(interfaz, MENU_VICTORIA, OPCION_TOMAR_PKM, "Tomar prestado un pokemon" );
    cargar_opcion(interfaz, MENU_VICTORIA, OPCION_CAMBIAR, "Cambiar pokemones de combate" );
    cargar_opcion(interfaz, MENU_VICTORIA, OPCION_AVANZAR, "Siguiente gimnasio" );
}
/* 
* Inicializa el menu derrota con sus opciones y descripciones
* Pre : Interfaz creada
* Post: Menú funcional para la interfaz
*/
void inicializar_derrota(interfaz_t* interfaz){
    cargar_opcion(interfaz, MENU_DERROTA, OPCION_CAMBIAR, "Cambiar pokemones de combate" );
    cargar_opcion(interfaz, MENU_DERROTA, OPCION_REPETIR, "Repetir batalla / simulacion" );
    cargar_opcion(interfaz, MENU_DERROTA, OPCION_SALIR, "Finalizar partida" );
}
/* 
* Inicializa todos los menus con sus opciones y descripciones
* Pre : Interfaz creada
* Post: Interfaz funcional para utilizar las funciones menu
*/
void inicializar_interfaz(interfaz_t* interfaz){
    inicializar_inicio(interfaz);
    inicializar_gimnasio(interfaz);
    inicializar_victoria(interfaz);
    inicializar_derrota(interfaz);
}

//FUNCIONES INTERFAZ.H

void gimnasio_informacion(gimnasio_t* gimnasio){
    if(!gimnasio){
        warning("el gimnasio");
        return;
    }
    system(LIMPIAR);
    imprimir_marco(INICIO);
    imprimir_linea(MARGEN_MEDIO_LARGO+4, SUBRAYADO, "INFORMACION DEL GIMNASIO");
    imprimir_enter();
    imprimir_linea_partida(MARGEN_CORTO, AMARILLO, "NOMBRE:        ", BLANCO, gimnasio->nombre);
    imprimir_enter();
    char dificultad[MAX_STRING];
    sprintf(dificultad, "NVL  %i", gimnasio->dificultad);
    imprimir_linea_partida(MARGEN_CORTO, AMARILLO, "DIFICULTAD:    ", BLANCO, dificultad);
    imprimir_enter();
    char entrenadores[MAX_STRING];
    sprintf(entrenadores, "%li", pila_elementos(gimnasio->entrenadores));
    imprimir_linea_partida(MARGEN_CORTO, AMARILLO, "ENTRENADORES RESTANTES:    ", BLANCO, entrenadores);
    entrenador_t aux = * (entrenador_t*) pila_tope(gimnasio->entrenadores);
    imprimir_enter();
    imprimir_linea_partida(MARGEN_CORTO, AMARILLO, "PROXIMO RIVAL: ", BLANCO, aux.nombre);
    listar_pokemones(aux.pokemones, LISTA_ENTRENADOR);
    imprimir_enter();
    pedir_opcion_avanzar();    
}

void personaje_informacion(personaje_t* personaje){
    if(!personaje){
        warning("el personaje principal");
        return;
    }
    system(LIMPIAR);
    imprimir_marco(INICIO);
    imprimir_linea(MARGEN_MEDIO_LARGO+4, SUBRAYADO, "INFORMACION DEL PERSONAJE");
    imprimir_enter();
    imprimir_linea_partida(MARGEN_CORTO, AMARILLO, "NOMBRE:     ", BLANCO, personaje->nombre);
    imprimir_enter();
    imprimir_medallero(personaje->medallas);
    imprimir_enter();
    listar_pokemones(personaje->caja, LISTA_CAJA);
    imprimir_enter();
    listar_pokemones(personaje->party, LISTA_COMBATE);
    imprimir_enter();
    pedir_opcion_avanzar();
}

void pedir_archivo(char ruta_archivo[MAX_STRING]){
    FILE* archivo;
    imprimir_espaciado(INTERFAZ_ESPACIO);
    printf("Ingrese la ruta del archivo:");
    scanf("%100[^\n]", ruta_archivo);
    archivo = fopen(ruta_archivo, LECTURA);
    while(!archivo){
        mostrar_advertencia();
        scanf("%100[^\n]", ruta_archivo);
        archivo = fopen(ruta_archivo, LECTURA);
    }
    fclose(archivo);
}

size_t pedir_pokemon(lista_t* pokemones, int lista){
    if(!pokemones){
        warning("la lista de pokemones");
        return lista_elementos(pokemones);
    }
    system(LIMPIAR);
    imprimir_marco(INICIO);
    listar_pokemones(pokemones, lista);
    imprimir_marco(FIN);
    return pedir_pos(lista_elementos(pokemones));
}

void eliminar_opcion(interfaz_t* interfaz, size_t menu, char opcion){
    if(!interfaz)
        return;
    size_t cantidad = interfaz->menus[menu].cant_opciones;
    int pos = buscar_opcion(interfaz->menus[menu].opciones,cantidad, opcion);
    if(pos == ERROR)
        return;
    eliminar_letra(interfaz->menus[menu].opciones, pos, cantidad);
    eliminar_descripcion(interfaz->menus[menu].descripciones, pos, cantidad);
    interfaz->menus[menu].cant_opciones --;
}

void reiniciar_menu_victoria(interfaz_t* interfaz){
    if(!interfaz)
        return;
    cargar_opcion(interfaz, MENU_VICTORIA, OPCION_TOMAR_PKM, "Tomar prestado un pokemon" );
    size_t cantidad = interfaz->menus[MENU_VICTORIA].cant_opciones;
    eliminar_letra(interfaz->menus[MENU_VICTORIA].opciones, 0, cantidad);
    eliminar_descripcion(interfaz->menus[MENU_VICTORIA].descripciones, 0, cantidad);
}

void menu_maestro_pokemon(){
    system(LIMPIAR);
    imprimir_marco(INICIO);
    imprimir_enter();;
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
    imprimir_linea(MARGEN_MEDIO, AMARILLO_PARP,"   TE HAS CONSAGRADO MAESTRO POKEMON!");
    imprimir_barra(AMARILLO, FIN);
    imprimir_enter();;
    imprimir_marco(FIN);
}

void menu_derrota(interfaz_t* interfaz, gimnasio_t* gimnasio){
    if(!interfaz){
        warning("la interfaz");
        return;
    }
    if(!gimnasio){
         warning("el gimnasio");
        return;
    }
    system(LIMPIAR);
    encabezado_derrota(gimnasio);
    mostrar_opciones(interfaz, MENU_DERROTA);
}

void menu_victoria(interfaz_t* interfaz){
    if(!interfaz){
        warning("la interfaz");
        return;
    }
    system(LIMPIAR);
    encabezado_victoria();
    mostrar_opciones(interfaz, MENU_VICTORIA);
}

void menu_batalla(pokemon_t* pkm_propio, pokemon_t* pkm_rival, int estado){
    if(!pkm_propio || !pkm_rival){
        warning("los pokemones de la batalla");
        return;
    }
    system(LIMPIAR);
    informacion_batalla(pkm_propio, pkm_rival, estado);
    pedir_opcion_avanzar();
}

void menu_gimnasio(interfaz_t* interfaz, gimnasio_t* gimnasio){
    if(!interfaz){
        warning(" la interfaz");
        return;
    }
    if(!gimnasio){
         warning("el gimnasio");
        return;
    }
    system(LIMPIAR);
    encabezado_gimnasio(gimnasio->nombre);
    mostrar_opciones(interfaz, MENU_GYM);
}

void menu_inicio(interfaz_t* interfaz){
    if(!interfaz){
        warning(" la interfaz");
        return;
    }
    system(LIMPIAR);
    dibujo_inicio();
    mostrar_opciones(interfaz, MENU_INICIO);
}

bool interfaz_estado(interfaz_t* interfaz, char estado){
    return interfaz->estado == estado;
}

void interfaz_destruir(interfaz_t* interfaz){
    if(!interfaz) return;
    free(interfaz->menus);
    free(interfaz);
}

interfaz_t* interfaz_crear(){
    interfaz_t* inter_aux = malloc(sizeof(interfaz_t));
    if(!inter_aux) return NULL;
    inter_aux->estado = INTERFAZ_INICIAL;
    menu_t* menus_aux = calloc(MAX_MENU, sizeof(menu_t));
    if(!menus_aux)return NULL;
    inter_aux->menus = menus_aux;
    for(int i = 0; i < MAX_MENU; i++)
        inter_aux->menus[i].cant_opciones = 0;
    inicializar_interfaz(inter_aux);
    return inter_aux;
}
