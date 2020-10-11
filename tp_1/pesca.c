#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "evento_pesca.h"

#define MAX_RUTA 100
#define RESET "\e[0m"
#define ROJO "\e[31m"
#define VERDE "\e[32m"
#define AMARILLO "\e[33m"

const char AYUDA[MAX_RUTA] = "--help";

const int ERROR = -1;
/*
*Análisis:
*Pre:
*Post:
*/
void mostrar_pokemon(pokemon_t pokemon){

}
/*
*Análisis:
*Pre:
*Post:
*/
int crear_simulacion( arrecife_t* arrecife, acuario_t* acuario, char ruta_arrecife[]){
  arrecife = crear_arrecife(ruta_arrecife);
  if(arrecife == NULL){
    printf( ROJO "El programa falló al crear la simulación del" AMARILLO " arrecife" RESET "\n");
    return ERROR;
  }
  acuario = crear_acuario();
  if(acuario == NULL){
    liberar_arrecife(arrecife);
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

int main (int argc, char* argv[]){

  if(argc<3){
    if (strcmp(argv[1], AYUDA) == 0){
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
  if (crear_simulacion(arrecife, acuario, ruta_arrecife) == ERROR){
      return ERROR;
  }


/*
  bool (*funciones_seleccion)(pokemon_t*)==NULL;
// asignar todas las funciones seleccionar al vector de funciones_seleccion
  int cant_funciones=0;

  int se_traslada=0;
  int i=0;
  while((se_traslada != ERROR) && (i < cant_funciones)){
    se_traslada=trasladar_pokemon(arrecife, acuario, funciones_seleccion[i] , (*arrecife).cantidad_pokemon);
    if(se_traslada == ERROR){
      printf(ROJO "Hubo un problema con un traslado de pokemones" RESET "\n");
    }else{
      censar_arrecife(arrecife, mostrar_pokemon);
      i ++;
    }
  }
*/
  int se_guardo=guardar_datos_acuario(acuario, ruta_acuario);
  liberar_arrecife(arrecife);
  liberar_acuario(acuario);

  if (se_guardo==ERROR){
      printf(ROJO "No se pudo guardar los datos en el archivo %s" RESET "\n", ruta_acuario);
      return -1;
  }

return 0;
}
