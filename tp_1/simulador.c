#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "evento_pesca.h"

#define MAX_RUTA 100
#define MAX_FUNCIONES 10
#define MAX_FIRMA 50
#define RESET "\e[0m"
#define ROJO "\e[31m"
#define VERDE "\e[32m"
#define AMARILLO "\e[33m"
#define COLOR "\e[34m"

const char AYUDA[MAX_RUTA] = "--help";
const char SI = 'S';
const char NO = 'N';
const int ERROR = -1;

typedef struct funciones_t{
  bool (*seleccionar[MAX_FUNCIONES])(pokemon_t*);
  char firma_seleccionar[MAX_FUNCIONES][MAX_FIRMA];
  int tope_seleccionar;
  void (*mostrar[MAX_FUNCIONES])(pokemon_t*);
  char firma_mostrar[MAX_FUNCIONES][MAX_FIRMA];
  int tope_mostrar;
} funciones_t;
/*
*Análisis:
*Pre:
*Post:
*/
bool seleccionar_livianos(pokemon_t* pokemon){
  return ((*pokemon).peso<10);
}
/*
*Análisis:
*Pre:
*Post:
*/
void mostrar_detallado(pokemon_t* pokemon){
  printf(" %s ; %i km/h ; %i kg ; Color: %s \n", (*pokemon).especie,
                                                                          (*pokemon).velocidad,
                                                                          (*pokemon).peso,
                                                                          (*pokemon).color);
}
/*
*Análisis: Crea los punteros de arrecife y acuario con su espacio asignado a la memoria dinamica
*Pre:
*Post:
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
  printf("Si desea utilizar" COLOR " arrecife.txt" RESET " y guardar en" COLOR " acuario.txt" RESET " utilice (Makefile necesario):\n");
  printf( AMARILLO "   make exe" RESET "\n");
}

/*
*Análisis:
*Pre:
*Post:
*/
void cargar_seleccionar(funciones_t* funciones, bool (*funcion_nueva)(pokemon_t*), char nueva_firma[]){
  (*funciones).seleccionar[(*funciones).tope_seleccionar]=*funcion_nueva;
  strcpy(((*funciones).firma_seleccionar[(*funciones).tope_seleccionar]), nueva_firma);
  (*funciones).tope_seleccionar++;
}
/*
*Análisis:
*Pre:
*Post:
*/
void cargar_mostrar(funciones_t* funciones, void (*funcion_nueva)(pokemon_t*), const char nueva_firma[]){
  (*funciones).mostrar[(*funciones).tope_mostrar]=*funcion_nueva;
  strcpy((*funciones).firma_mostrar[(*funciones).tope_mostrar] , nueva_firma);
  (*funciones).tope_mostrar++;
}
/*
*Análisis:
*Pre:
*Post:
*/
funciones_t cargar_funciones(){
  funciones_t funciones;
  funciones.tope_mostrar=0;
  funciones.tope_seleccionar=0;
  cargar_mostrar(&funciones, mostrar_detallado, "mostrar_detallado");
  cargar_seleccionar(&funciones, seleccionar_livianos, "seleccionar_livianos");
  return funciones;
}
/*
*Análisis:
*Pre:
*Post:
*/
void mostrar_funciones_por_tipo(const char* tipo, int tope_funcion, char firma_funciones[MAX_FUNCIONES][MAX_FIRMA]){
  printf("Funciones para %s los pokemones \n", tipo);
  for(int i=0; i<tope_funcion; i++){
    printf(AMARILLO "=> %i:" RESET " %s \n", i, firma_funciones[i]);
  }
}
/*
*Análisis:
*Pre:
*Post:
*/
void mostrar_funciones(funciones_t funciones){
  mostrar_funciones_por_tipo("SELECCIONAR", funciones.tope_seleccionar, funciones.firma_seleccionar);
  mostrar_funciones_por_tipo("MOSTRAR", funciones.tope_mostrar, funciones.firma_mostrar);
}
/*
*Análisis:
*Pre:
*Post:
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
*Análisis:
*Pre:
*Post:
*/
int preguntar_un_numero(int max, int min, const char* consigna){
  int eleccion;
  printf("%s", consigna);
  scanf("%i", &eleccion);
  while ((eleccion > max) || (eleccion < min)){
    printf(ROJO "La eleccion fuera de parámetros... \n" RESET);
    printf("%s", consigna);
    scanf("%i", &eleccion);
  }
  return eleccion;
}
/*
*Análisis:
*Pre:
*Post:
*/
void preguntar_elecciones(funciones_t funciones, arrecife_t* arrecife, int* n_seleccion, int* cant_seleccion, int* n_mostrar){
  *n_seleccion = preguntar_un_numero((funciones.tope_seleccionar-1), 0, "Elige el n° de funcion para seleccionar:");
  *cant_seleccion = preguntar_un_numero((*arrecife).cantidad_pokemon, 1, "Elige la cantidad de pokemones a trasladar:");
  *n_mostrar = preguntar_un_numero((funciones.tope_mostrar-1), 0,"Elige el n° de funcion para mostrar:");
  system("clear");
  printf("SELECCIONAR CON: %s ; CANTIDAD: %i ; MOSTRAR CON: %s \n", funciones.firma_seleccionar[*n_seleccion],
                                                                    *cant_seleccion,
                                                                    funciones.firma_mostrar[*n_mostrar]);
}
/*
*Análisis:
*Pre:
*Post:
*/
int correr_simulacion(arrecife_t* arrecife, acuario_t* acuario, funciones_t funciones, int* contador){
  int se_traslada=0;
  bool quiere_trasladar=true;
  int n_seleccion=0;
  int n_mostrar=0;
  int cant_seleccion;

  quiere_trasladar = preguntar_si_traslada();
  while((quiere_trasladar) && (se_traslada!=ERROR)){
      mostrar_funciones(funciones);
      preguntar_elecciones(funciones, arrecife, &n_seleccion, &cant_seleccion, &n_mostrar);
      se_traslada=trasladar_pokemon(arrecife, acuario, funciones.seleccionar[n_seleccion]  , cant_seleccion);
      if(se_traslada == ERROR){
        printf( ROJO "Hubo un problema con el traslado" RESET "\n");
      }else{
        (*contador)++;
        censar_arrecife(arrecife, funciones.mostrar[n_mostrar]);
        printf( VERDE "Se trasladó sin problemas. Traslados totales: %i " RESET "\n", *contador);
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
  arrecife_t* arrecife = NULL;
  acuario_t* acuario = NULL;
  int se_guardo=ERROR;
  int estado_simulador=0;
  int traslados_hechos=0;

  funciones_t funciones;

  strcpy(ruta_arrecife, argv[1]);
  strcpy(ruta_acuario, argv[2]);
  if (crear_simulacion(&(arrecife), &(acuario), ruta_arrecife) == ERROR)
      return ERROR;
  printf( VERDE "Se creó exitosamente el arrecife y el acuario dentro del simulador." RESET "\n");

  censar_arrecife(arrecife, mostrar_detallado);

  funciones = cargar_funciones();
  estado_simulador = correr_simulacion(arrecife, acuario, funciones, &traslados_hechos);

  if(traslados_hechos == 0){
    printf( AMARILLO "No se guardó ningún dato en el archivo %s" RESET "\n", ruta_acuario);
    return 0;
  }

  if(estado_simulador != ERROR)
    se_guardo = guardar_datos_acuario(acuario, ruta_acuario);

  liberar_arrecife(arrecife);
  liberar_acuario(acuario);

  if (se_guardo==ERROR){
    printf( ROJO "No se pudo guardar los datos en el archivo %s" RESET "\n", ruta_acuario);
    return ERROR;
  }

  printf( VERDE "Se realizaron %i traslados correctamente " RESET "\n", traslados_hechos);
  printf( VERDE "Se pudo guardar EXITOSAMENTE los datos en el archivo %s " RESET "\n", ruta_acuario);

return 0;
}
