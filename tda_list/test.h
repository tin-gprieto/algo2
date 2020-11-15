#ifndef __TEST_H_
#define __TEST_H_

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#define BLANCO "\x1b[37m"
#define VERDE "\x1b[32m"
#define ROJO "\x1b[31m"
#define AMARILLO "\x1b[33m"
#define CYAN "\x1b[34m"
#define NORMAL "\x1b[0m"

#define TILDE "✓"
#define CRUZ "✗"

/*
*Imprime por pantalla una prueba con su descripcion
*Si la afirmación no se cumple se considera un error
*/
void test_afirmar(int afirmacion, const char *descripcion);

/*
*Muestra por pantalla el título para un nuevo grupo
*/
void test_nuevo_grupo(const char *descripcion);

/*
*Muestra por pantalla el título y una separación para un
*nuevo subgrupo
*/
void test_nuevo_sub_grupo(const char *descripcion);

/*
*Muestra por pantall la cantidad de pruebas corridas y errores
*/
void test_mostrar_reporte();

#endif // __TEST_H_