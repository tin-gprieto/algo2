#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "evento_pesca.h"

#define MAX_RUTA 100
#define MAX_FUNCIONES 10
#define MAX_FIRMA 100
#define MAX_COLORES 15

#define RESET "\e[0m"
#define ROJO "\e[31m"
#define VERDE "\e[32m"
#define AMARILLO "\e[33m"
#define AZUL "\e[34m"
#define ROSA "\e[35m"

const char AYUDA[MAX_RUTA] = "--help";
const char SI = 's';
const char NO = 'n';
const char LETRA_1 = 'y';
const char LETRA_2 = 'k';
const char LETRA_3 = 'w';
const char LETRA_4 = 'q';
const char LETRA_MAYUS_1 = 'Y';
const char LETRA_MAYUS_2 = 'K';
const char LETRA_MAYUS_3= 'W';
const char LETRA_MAYUS_4= 'Q';

const int ERROR = -1;
const int MAX_LIVIANO = 10;
const int MIN_PESADO = 20;
const int MAX_LENTO = 10;
const int MIN_RAPIDO = 15;
const int CANT_COLORES_RAROS = 4;
const int CANT_COLORES_COMUNES = 3;

typedef struct funciones_t{
  bool (*seleccionar[MAX_FUNCIONES])(pokemon_t*);
  char firma_seleccionar[MAX_FUNCIONES][MAX_FIRMA];
  int tope_seleccionar;
  void (*mostrar[MAX_FUNCIONES])(pokemon_t*);
  char firma_mostrar[MAX_FUNCIONES][MAX_FIRMA];
  int tope_mostrar;
} funciones_t;

/*
Pre: Pokemon propio de la funcion de seleccionar, array de colores
*con el cual comparar el color, cantidad de colores que hay en el array
Post: Verdadero si cumple con alguno de los colores
*/
bool es_color_especial(pokemon_t* pokemon, char* colores[MAX_COLORES], int tope_colores){
  bool cumple_color=false;
  int i=0;
  while ((i<tope_colores) && (!cumple_color)){
    if (strcmp((*pokemon).color, colores[i]) == 0){
      cumple_color=true;
    }
    i++;
  }
  return cumple_color;
}
/*
*Post: Cualquier letra que pertenezca a la especie del pokemon
*Pre: Verdadero si es alguna de las siguiente letras (por constantes) 
*/
bool es_letra_rara(char letra){
  if (((letra == LETRA_1) || (letra == LETRA_2) || (letra == LETRA_3) || (letra == LETRA_4))){
    return true;
  }else if(((letra == LETRA_MAYUS_1) || (letra == LETRA_MAYUS_2) || (letra == LETRA_MAYUS_3) || (letra == LETRA_MAYUS_4))){
    return true;
  }else{
    return false;
  }  
}
/*
*Análisis: Compara el peso del pokemon con un peso máximo (incluyendolo) que determina si es liviano
*/
bool seleccionar_livianos(pokemon_t* pokemon){
  return ((*pokemon).peso<MAX_LIVIANO);
}
/*
*Análisis: Compara el peso del pokemon con un peso mínimo que determina si es pesado
*/
bool seleccionar_pesados(pokemon_t* pokemon){
  return ((*pokemon).peso>MIN_PESADO);
}
/*
*Análisis: Compara la velocidad del pokemon con una velocidad mínima (incluyendola) que determina si es rápido
*/
bool seleccionar_rapidos(pokemon_t* pokemon){
  return ((*pokemon).velocidad>=MIN_RAPIDO);
}
/*
*Análisis: Compara la velocidad del pokemon con una velocidad máxima que determina si es lento
*/
bool seleccionar_lentos(pokemon_t* pokemon){
  return ((*pokemon).velocidad<MAX_LENTO);
}
/*
*Análisis: Según un array de colores compara si el color del pokemon cumple con alguno de estos
*/
bool seleccionar_colores_raros(pokemon_t* pokemon){
  char* colores_raros[MAX_COLORES] = {"gris", "blanco", "rosa", "marron"};
  int tope_colores= CANT_COLORES_RAROS;
  return es_color_especial(pokemon, colores_raros, tope_colores);
}
/*
*Análisis: Según un array de colores compara si el color del pokemon cumple con alguno de estos
*/
bool seleccionar_colores_comunes(pokemon_t* pokemon){
  char* colores_comunes[MAX_COLORES] = {"celeste", "azul", "naranja"};
  int tope_colores= CANT_COLORES_COMUNES;
  return es_color_especial(pokemon, colores_comunes, tope_colores);
}
/*
*Análisis: Si el nombre de la especie tiene alguna letra en particular (por constante) devuelve verdadero  
*/
bool seleccionar_nombres_raros(pokemon_t* pokemon){
  size_t largo = strlen((*pokemon).especie);
  bool es_raro=false;
  int i=0;
  while ((i<largo) && (!es_raro)){
    if (es_letra_rara((*pokemon).especie[i])){
      es_raro=true;
    }
    i++;
  }
  return es_raro;
}
/*
*Análisis: Muestra cada caracteristica con unidad o nombre 
*/
void mostrar_detallado(pokemon_t* pokemon){
  printf(" %s ; %i km/h ; %i kg ; Color: %s \n", (*pokemon).especie,
                                                 (*pokemon).velocidad,
                                                 (*pokemon).peso,
                                                 (*pokemon).color);
}
/*
*Análisis: Muestra en formato csv
*/
void mostrar_sensillo(pokemon_t* pokemon){
  printf(" %s ; %i ; %i ; %s \n", (*pokemon).especie,
                                  (*pokemon).velocidad,
                                  (*pokemon).peso,
                                  (*pokemon).color);
}
/*
*Análisis: Muestra la especie y su velocidad
*/
void mostrar_velocidad(pokemon_t* pokemon){
  printf(" %s | %i  km/h \n", (*pokemon).especie, (*pokemon).velocidad);
}
/*
*Análisis: Muestra la especie y su peso
*/
void mostrar_peso(pokemon_t* pokemon){
  printf(" %s | %i  kg \n", (*pokemon).especie, (*pokemon).peso);
}
/*
*Análisis: Muestra la especie y su color
*/
void mostrar_color(pokemon_t* pokemon){
  printf(" %s | %s \n", (*pokemon).especie, (*pokemon).color);
}
/*
*Análisis: Muestra solo el nombre de la especie 
*/
void mostrar_especie(pokemon_t* pokemon){
  printf(" %s |\n", (*pokemon).especie);
}
/*
*Análisis: Crea los punteros de arrecife y acuario con su espacio asignado a la memoria dinamica
*Pre: Arrecife y acuarios como punteros creado, ruta de archivo válida para un archivo del formato indicado
*Post: Devuelve error si no puede crear alguno y avisa cual es el problema de ser así
*/
int crear_simulacion( arrecife_t** arrecife, acuario_t** acuario, char ruta_arrecife[]){
  *arrecife = crear_arrecife(ruta_arrecife);
  if(*arrecife == NULL){
    printf( ROJO "El programa falló al crear la simulación del" AMARILLO " arrecife" RESET "\n");
    return ERROR;
  }

  *acuario = crear_acuario();
  if(*acuario == NULL){
    liberar_arrecife(*arrecife);
    printf( ROJO "El programa falló al crear la simulación del" AMARILLO " acuario" RESET "\n");
    return ERROR;
  }

  return 0;
}
/*
*Análisis: Informa al usuario la forma de utilizar el programa
*Pre: El usuario deberia haber usado el comando "--help"
*Post: Información por pantalla
*/
void imprimir_ayuda(){
  printf("El programa debe ejecutarse de la siguiente manera:\n");
  printf( AMARILLO "  ./evento_pesca <archivo del arrecife> <nombre para guardar el acuario>" RESET "\n");
  printf("Si desea utilizar" AZUL " arrecife.txt" RESET " y guardar en" AZUL " acuario.txt" RESET " utilice (Makefile necesario):\n");
  printf( AMARILLO "   make exe" RESET "\n");
}

/*
*Análisis: Carga una funcion seleccionar en un struct de funciones junto con su firma 
*(caracteristica para que muestre por pantalla)
*Pre: Tope inicializado, funcion seleccionar como funcion bool y previamente creada
*Post: Funcion nueva cargada a la última posicion de su vector dentro de funciones
*/
void cargar_seleccionar(funciones_t* funciones, bool (*funcion_nueva)(pokemon_t*), char nueva_firma[]){
  (*funciones).seleccionar[(*funciones).tope_seleccionar]=*funcion_nueva;
  strcpy(((*funciones).firma_seleccionar[(*funciones).tope_seleccionar]), nueva_firma);
  (*funciones).tope_seleccionar++;
}
/*
*Análisis: Carga una funcion mostrar en un struct de funciones junto con su firma 
*(caracteristica para que muestre por pantalla)
*Pre: Tope inicializado, funcion mostrar como funcion void y previamente creada
*Post: Funcion nueva cargada a la última posicion de su vector dentro de funciones
*/
void cargar_mostrar(funciones_t* funciones, void (*funcion_nueva)(pokemon_t*), const char nueva_firma[]){
  (*funciones).mostrar[(*funciones).tope_mostrar]=*funcion_nueva;
  strcpy((*funciones).firma_mostrar[(*funciones).tope_mostrar] , nueva_firma);
  (*funciones).tope_mostrar++;
}
/*
*Análisis: Carga todas las funciones que se desee un estruct funciones_t y lo devuelve
*Pre: -
*Post: Devuelve el struct funciones cargado con las funciones
*/
funciones_t cargar_funciones(){
  funciones_t funciones;
  funciones.tope_mostrar=0;
  funciones.tope_seleccionar=0;
  cargar_seleccionar(&funciones, seleccionar_livianos, "Livianos (peso menor a 10kg)");
  cargar_seleccionar(&funciones, seleccionar_pesados, "Pesados (peso mayor a 20kg)");
  cargar_seleccionar(&funciones, seleccionar_rapidos, "Rápidos (velocidad mayor o igual a 15 km/h)");
  cargar_seleccionar(&funciones, seleccionar_lentos, "Lentos (velocidad menor a 10 km/h)");
  cargar_seleccionar(&funciones, seleccionar_colores_raros, "Colores raros (blanco, gris, rosa o marron)");
  cargar_seleccionar(&funciones, seleccionar_colores_comunes, "Colores comunes (celeste, azul o naranja)");
  cargar_seleccionar(&funciones, seleccionar_nombres_raros, "Especies con nombres raros (contienen 'y', 'k', 'w' o 'q' )");
  cargar_mostrar(&funciones, mostrar_detallado, "Detallado");
  cargar_mostrar(&funciones, mostrar_sensillo, "Sencillo");
  cargar_mostrar(&funciones, mostrar_especie, "Solo especie");
  cargar_mostrar(&funciones, mostrar_velocidad, "Solo velocidad");
  cargar_mostrar(&funciones, mostrar_peso, "Solo peso");
  cargar_mostrar(&funciones, mostrar_color, "Solo color");
  return funciones;
}
/*
*Análisis: Muestra todas las funciones cargadas según el tipo (seleccionar o mostrar)
*Pre: Funciones previamente cargadas
*Post: Información por pantalla
*/
void mostrar_funciones_por_tipo(const char* tipo, int tope_funcion, char firma_funciones[MAX_FUNCIONES][MAX_FIRMA]){
  printf( ROSA "------------------------------------" RESET "\n");
  printf( AMARILLO "Funciones para %s los pokemones" RESET "\n", tipo);
  for(int i=0; i<tope_funcion; i++){
    printf(VERDE "=> %i:" RESET " %s \n", i, firma_funciones[i]);
  }
  printf( ROSA "------------------------------------" RESET "\n");
}
/*
*Análisis: Muestra todas las funciones
*Pre: Funciones cargadas
*Post: Información por pantalla
*/
void mostrar_funciones(funciones_t funciones){
  mostrar_funciones_por_tipo("SELECCIONAR", funciones.tope_seleccionar, funciones.firma_seleccionar);
  mostrar_funciones_por_tipo("MOSTRAR", funciones.tope_mostrar, funciones.firma_mostrar);
}
/*
*Análisis: Pregunta al usuario si traslada (con SI o NO)
*Pre: Simulacion inicializada y lista para un traslado
*Post: Verdadero si quiere trasladar, falso si no quiere
*/
bool preguntar_si_traslada(){
  char decision;
  printf("Desea hacer un traslado de pokemones?(%c/%c):", SI, NO);
  scanf(" %c", &decision);
  while((decision != NO) && (decision != SI)){
    printf( ROJO "Selecciona una respuesta correcta... \n" RESET);
    printf("Desea hacer un traslado?(%c/%c):", SI, NO);
    scanf(" %c", &decision);
  }
  if(decision == SI)
    return true;
  return false;
}
/*
*Análisis: Pregunta un número mayor que 0 y menor a max
*Pre: El maximo y la consigna se deben corresponder según el uso
*Post: Devuelve el número que ingresa el usuario
*/
int preguntar_un_numero(int max, const char* consigna){
  int eleccion;
  int min=0;
  printf("%s", consigna);
  scanf("%i", &eleccion);
  while ((eleccion > max) || (eleccion < min)){
    printf(ROJO "El número ingresado es erróneo... \n" RESET);
    printf("%s", consigna);
    scanf("%i", &eleccion);
  }
  return eleccion;
}
/*
*Análisis: Pregunta todo lo necesario para saber que funciones usar y como
*Pre: Funciones cargadas y quiere hacer un traslado
*Post: Ubicacion de las funciones y cantidad de pokemones a elección
*/
void preguntar_elecciones(funciones_t funciones, arrecife_t* arrecife, int* n_seleccion, int* cant_seleccion, int* n_mostrar){
  *n_seleccion = preguntar_un_numero((funciones.tope_seleccionar-1), "Elige el n° de funcion para seleccionar:");
  *cant_seleccion = preguntar_un_numero((*arrecife).cantidad_pokemon, "Elige la cantidad máxima de pokemones a trasladar:");
  *n_mostrar = preguntar_un_numero((funciones.tope_mostrar-1),"Elige el n° de funcion para mostrar:");
  system("clear");
  printf("SELECCIONAR CON: %s ; CANTIDAD: %i ; MOSTRAR CON: %s \n", funciones.firma_seleccionar[*n_seleccion],
                                                                    *cant_seleccion,
                                                                    funciones.firma_mostrar[*n_mostrar]);
}
/*
*Análisis: Corre todos los traslados que quiera el usuario
*Pre: Arrecife y acuario creados, funciones cargadas, contador inicializado a 0
*Post: -1 si hubo algún error o 0 si pudo realizar todos los traslados pedidos
*/
int correr_simulacion(arrecife_t* arrecife, acuario_t* acuario, funciones_t funciones, int* contador){
  int se_traslada=0;
  bool quiere_trasladar=true;
  int n_seleccion=0;
  int n_mostrar=0;
  int cant_seleccion=0;
  
  censar_arrecife(arrecife, mostrar_detallado);
  quiere_trasladar = preguntar_si_traslada();
  while((quiere_trasladar) && (se_traslada!=ERROR)){
      mostrar_funciones(funciones);
      preguntar_elecciones(funciones, arrecife, &n_seleccion, &cant_seleccion, &n_mostrar);
      se_traslada=trasladar_pokemon(arrecife, acuario, funciones.seleccionar[n_seleccion]  , cant_seleccion);
      if(se_traslada != ERROR){
        (*contador)++;
        censar_arrecife(arrecife, funciones.mostrar[n_mostrar]);
        quiere_trasladar = preguntar_si_traslada();
      }
  }
  if(se_traslada == ERROR)
    return ERROR;
  return 0;
}

int main (int argc, char* argv[]){

  if(argc<3){
    if ((argc == 2) &&(strcmp(argv[1], AYUDA) == 0)){
      imprimir_ayuda();
      return 0;
    }else{
      printf( ROJO "No ingresaste la dirección de los archivos! (--help para ayuda)" RESET "\n");
      return ERROR;
    }
  }

  char ruta_arrecife[MAX_RUTA];
  char ruta_acuario[MAX_RUTA];
  strcpy(ruta_arrecife, argv[1]);
  strcpy(ruta_acuario, argv[2]);
  
  arrecife_t* arrecife = NULL;
  acuario_t* acuario = NULL;
  int se_guardo=ERROR;
  int estado_simulador=0;
  int traslados_hechos=0;
  funciones_t funciones;
  
  if (crear_simulacion(&(arrecife), &(acuario), ruta_arrecife) == ERROR)
      return ERROR;
  printf( VERDE "Se creó exitosamente el arrecife y el acuario dentro del simulador." RESET "\n");

  funciones = cargar_funciones();
  estado_simulador = correr_simulacion(arrecife, acuario, funciones, &traslados_hechos);

  if(traslados_hechos == 0){
    liberar_arrecife(arrecife);
    liberar_acuario(acuario);
    printf( AMARILLO "No se guardó ningún dato en el archivo %s" RESET "\n", ruta_acuario);
    return 0;
  }

  if(estado_simulador != ERROR)
    se_guardo = guardar_datos_acuario(acuario, ruta_acuario);

  liberar_arrecife(arrecife);
  liberar_acuario(acuario);

  if (se_guardo==ERROR){
    printf( ROJO "No se pudo guardar los datos en el archivo " AMARILLO " %s" RESET "\n", ruta_acuario);
    return ERROR;
  }
  printf( VERDE "Se pudo guardar EXITOSAMENTE los datos en el archivo" AMARILLO " %s " RESET "\n", ruta_acuario);
  
return 0;
}
