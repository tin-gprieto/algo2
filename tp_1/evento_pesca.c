#include "evento_pesca.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define ERROR -1
#define RESET "\e[0m"
#define ROJO "\e[31m"
#define VERDE "\e[32m"
#define AMARILLO "\e[33m"
#define FORMATO_ARCHIVO "%[^;];%i;%i;%[^\n]\n"
#define FORMATO_ARCHIVO_ESCRITURA "%s;%i;%i;%s\n"

const int ELEMENTOS_ARCH = 4;

/*
*Análisis:
*Pre:
*Post:
*/
pokemon_t* cargar_pokemones(FILE* archivo, pokemon_t* p_pokemon, int* tope_pokemon){
  pokemon_t aux;
  int leido = fscanf(archivo, FORMATO_ARCHIVO, aux.especie,
                                               &(aux.velocidad),
                                               &(aux.peso),
                                               aux.color);
  if (leido != ELEMENTOS_ARCH){
    printf( ROJO "El arrefice no tiene pokemones!" RESET "\n");
    return NULL;
  }

  bool se_agrando = true;
  pokemon_t* p_aux;
  while ((leido == ELEMENTOS_ARCH) && (se_agrando)){
    p_pokemon[*tope_pokemon] = aux;
    (*tope_pokemon) ++;
    p_aux = realloc(p_pokemon, (sizeof(pokemon_t)*((size_t)(*tope_pokemon) + 1)));
    if(p_aux == NULL){
      se_agrando = false;
    }else{
      p_pokemon=p_aux;
      leido = fscanf(archivo, FORMATO_ARCHIVO, aux.especie,
                                               &(aux.velocidad),
                                               &(aux.peso),
                                               aux.color);
    }
  }
  if(!se_agrando)
    return NULL;
  return p_pokemon;
}
/*
*Análisis:
*Pre:
*Post:
*/
arrecife_t* crear_espacio_pokemon(FILE* archivo, arrecife_t* p_arrecife){

  (*p_arrecife).cantidad_pokemon=0;
  (*p_arrecife).pokemon = malloc(sizeof(pokemon_t));
  if ((*p_arrecife).pokemon == NULL){
    printf( ROJO "No se pudo crear un espacio para los pokemones del arrecife!" RESET "\n");
    return NULL;
  }
  pokemon_t* p_aux = cargar_pokemones(archivo, (*p_arrecife).pokemon, &((*p_arrecife).cantidad_pokemon));
  if (p_aux == NULL){
    free((*p_arrecife).pokemon);
    printf( ROJO "No se pudo cargar todo el arrecife! (Problema en la memoria dinámica)" RESET "\n");
    return NULL;
  }
  (*p_arrecife).pokemon = p_aux;
  return p_arrecife;
}

arrecife_t* crear_arrecife(const char* ruta_archivo){

  FILE* archivo_arrecife = fopen(ruta_archivo, "r");
  if(archivo_arrecife == NULL){
    printf(ROJO "No se pudo abrir el archivo %s" RESET "\n", ruta_archivo);
    return NULL;
  }

  arrecife_t* arrecife = malloc(sizeof(arrecife_t));
  if (arrecife == NULL){
    printf(ROJO "La simulacion del arrefice no pudo asignarse a la memoria dinámica!" RESET "\n");
    fclose(archivo_arrecife);
    return NULL;
  }

  arrecife_t * arrecife_aux = crear_espacio_pokemon(archivo_arrecife, arrecife);
  if(arrecife_aux == NULL){
    free(arrecife);
  }
  fclose(archivo_arrecife);
  return arrecife_aux;
}

acuario_t* crear_acuario(){

  acuario_t* acuario_aux = malloc(sizeof(acuario_t));
  if(acuario_aux==NULL){
    printf(ROJO "La simulacion del acuario no pudo asignarse a la memoria dinámica!" RESET "\n");
    return NULL;
  }else{
    (*acuario_aux).pokemon = malloc(sizeof(pokemon_t));
    if ((*acuario_aux).pokemon == NULL){
      free(acuario_aux);
      printf( ROJO "No se pudo crear un espacio para los pokemones del acuario!" RESET "\n");
      return NULL;
    }else{
      (*acuario_aux).cantidad_pokemon = 0;
      return acuario_aux;
    }
  }

return NULL;
}

/*
*Análisis:
*Pre:
*Post:
*/
bool sacar_del_arrecife(arrecife_t* arrecife,  int pos_pokemon){
  (*arrecife).pokemon[pos_pokemon] = (*arrecife).pokemon[((*arrecife).cantidad_pokemon)-1];
  (*arrecife).cantidad_pokemon--;

  pokemon_t* pokemon_aux;
  pokemon_aux = realloc((*arrecife).pokemon, (sizeof(pokemon_t)*((size_t)(*arrecife).cantidad_pokemon)));
  if(pokemon_aux == NULL){
    printf( ROJO "No se pudo ajustar el tamaño del" AMARILLO " arrecife" RESET "\n");
    return false;
  }
  (*arrecife).pokemon = pokemon_aux;
  return true;
}
/*
*Análisis:
*Pre:
*Post:
*/
bool pasar_al_acuario(acuario_t* acuario, pokemon_t trasladado){

  pokemon_t* pokemon_aux;
  pokemon_aux = realloc((*acuario).pokemon, sizeof(pokemon_t)*((size_t)(*acuario).cantidad_pokemon + 1));
  if(pokemon_aux == NULL){
    printf(ROJO "No se pudo agrandar el espacio para los pokemones en el" AMARILLO " acuario" RESET "\n");
    return false;
  }
  (*acuario).pokemon = pokemon_aux;
  (*acuario).pokemon[(*acuario).cantidad_pokemon] = trasladado;
  (*acuario).cantidad_pokemon++;
  return true;
}

/*
*Análisis:
*Pre:
*Post:
*/
int hacer_traslado(arrecife_t* arrecife, acuario_t* acuario, bool (*seleccionar_pokemon) (pokemon_t*)){
  int i = 0;
  bool sin_error = true;
  while((i < (*arrecife).cantidad_pokemon) && sin_error){
    if (seleccionar_pokemon(&((*arrecife).pokemon[i]))) {
      sin_error = pasar_al_acuario(acuario, (*arrecife).pokemon[i]);
      if(sin_error)
        sin_error = sacar_del_arrecife(arrecife, i);
    }else{
      i++;
    }
  }
  if(sin_error)
    return 0;
  return ERROR;
}
/*
*Análisis:
*Pre:
*Post:
*/
int contar_transferibles(arrecife_t* arrecife, bool (*seleccionar_pokemon) (pokemon_t*)){
  int contador = 0;
  for(int i = 0; i < ((*arrecife).cantidad_pokemon); i++){
    if (seleccionar_pokemon(&((*arrecife).pokemon[i]))) {
      contador++;
    }
  }
  return contador;
}

int trasladar_pokemon(arrecife_t* arrecife, acuario_t* acuario, bool (*seleccionar_pokemon) (pokemon_t*), int cant_seleccion){
  int trasladables = contar_transferibles(arrecife, seleccionar_pokemon);
  if(trasladables >= cant_seleccion)
    return hacer_traslado(arrecife, acuario, seleccionar_pokemon);
  printf(ROJO "No hay pokemones suficientes para el traslado" RESET "\n");
  return ERROR;
}

void censar_arrecife(arrecife_t* arrecife, void (*mostrar_pokemon)(pokemon_t*)){
  for(int i=0; i<(*arrecife).cantidad_pokemon; i++){
    (*mostrar_pokemon)(&((*arrecife).pokemon[i]));
  }
}

int guardar_datos_acuario(acuario_t* acuario, const char* nombre_archivo){
  FILE* archivo_acuario = fopen(nombre_archivo, "w");
  if(archivo_acuario == NULL){
    printf(ROJO "No se pudo abrir el archivo %s" RESET "\n", nombre_archivo);
    return ERROR;
  }
  for(int i=0; i<((*acuario).cantidad_pokemon); i++){
    fprintf(archivo_acuario, FORMATO_ARCHIVO_ESCRITURA, (*acuario).pokemon[i].especie,
                                                        (*acuario).pokemon[i].velocidad,
                                                        (*acuario).pokemon[i].peso,
                                                        (*acuario).pokemon[i].color);
  }
  fclose(archivo_acuario);
return 0;
}

void liberar_acuario(acuario_t* acuario){
  if(((*acuario).pokemon) != NULL)
    free((*acuario).pokemon);
  free(acuario);
}

void liberar_arrecife(arrecife_t* arrecife){
  free((*arrecife).pokemon);
  free(arrecife);
}
