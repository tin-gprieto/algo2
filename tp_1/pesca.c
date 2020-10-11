#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "evento_pesca.h"

#define MAX_RUTA 100
#define RESET "/e[0m"
#define ROJO "/e[41m"
#define VERDE "/e[42m"
#define AMARILLO "/e[43m"


int main (int argc, char* argv[]){

  if(argc<1){
    printf( ROJO "No ingresaste la dirección del archivo!" RESET "\n");
    return -1;
  }

  char ruta_arrecife[MAX_RUTA];
  strcpy(ruta_arrecife, arg[1]);

  arrecife_t* arrecife = crear_arrecife(ruta_arrecife);
  if(arrecife == NULL){
    printf( ROJO "El programa falló al crear la simulación del" AMARILLO "ararrecife" RESET "\n");
    return -1;
  }

  acuario _t* acuario = crear_acuario();
  if(acuario == NULL){
    liberar_arrecife(arrecife);
    printf( ROJO "El programa falló al crear la simulación del" AMARILLO "acuario" RESET "\n");
    return -1;    }
  }

return 0;
}
