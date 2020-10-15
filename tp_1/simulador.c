#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "evento_pesca.h"

#define MAX_RUTA 100
#define MAX_FUNCIONES 10
#define RESET "\e[0m"
#define ROJO "\e[31m"
#define VERDE "\e[32m"
#define AMARILLO "\e[33m"

const char AYUDA[MAX_RUTA] = "--help";
const int ERROR = -1;

typedef struct funciones_t{
  void (*mostrar[MAX_FUNCIONES])(pokemon_t*);
  bool (*seleccionar[MAX_FUNCIONES])(pokemon_t*);
  int tope_funciones;
} funciones_t;

/*
*Análisis:
*Pre:
*Post:
*/
void mostrar_pokemon(pokemon_t* pokemon){
  printf("Pokemón: %s Velocidad: %i km/h Peso: %i kg Color: %s \n", (*pokemon).especie,
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
  printf("Ayuda xd \n");
}

/*
*Análisis:
*Pre:
*Post:
*/
void cargar_funciones(funciones_t* funciones){

}
/*
*Análisis:
*Pre:
*Post:
*/
void mostrar_funciones(){

}
/*
*Análisis:
*Pre:
*Post:
*/
void preguntar_si_traslada(bool* traslada){

}
/*
*Análisis:
*Pre:
*Post:
*/
void preguntar_elecciones(int* n_seleccion, int* cant_seleccion, int* n_mostrar){

}
/*
*Análisis:
*Pre:
*Post:
*/
void correr_simulacion(arrecife_t* arrecife, acuario_t* acuario, funciones_t funciones){
  int se_traslada=0;
  bool quiere_trasladar=true;
  int n_seleccion=0;
  int n_mostrar=0;
  int cant_seleccion;

  while(quiere_trasladar){
    mostrar_funciones();
    preguntar_si_traslada(&quiere_trasladar);
    if(quiere_trasladar){
      preguntar_elecciones(&n_seleccion, &cant_seleccion, &n_mostrar);
      system("clear");
      se_traslada=trasladar_pokemon(arrecife, acuario, funciones.seleccionar[n_seleccion]  , cant_seleccion);
      if(se_traslada == ERROR){
        printf( ROJO "Hubo un problema con el traslado n°%i de pokemones" RESET "\n", n_seleccion);
      }else{
        printf( VERDE "Se trasladó sin problemas" RESET "\n");
        censar_arrecife(arrecife, funciones.mostrar[n_mostrar]);
      }
    }
  }
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

  if (crear_simulacion(&(arrecife), &(acuario), ruta_arrecife) == ERROR)
      return ERROR;

  printf( VERDE "Se creó exitosamente el arrecife y el acuario dentro del simulador." RESET "\n");

  funciones_t funciones;

  cargar_funciones(&funciones);
  correr_simulacion(arrecife, acuario, funciones);

  int se_guardo=guardar_datos_acuario(acuario, ruta_acuario);
  liberar_arrecife(arrecife);
  liberar_acuario(acuario);

  if (se_guardo==ERROR){
  printf( ROJO "No se pudo guardar los datos en el archivo %s" RESET "\n", ruta_acuario);
  return -1;
  }
  printf( VERDE "Se pudo guardar EXITOSAMENTE los datos en el archivo %s" RESET "\n", ruta_acuario);

return 0;
}
