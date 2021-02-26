#include "tools.h"
#define MAX_BAR 10

void print_vector(int* array, size_t size){
    printf("    [");
    for(int i=0; i<size; i++)
        printf(" %i ", array[i]);
    printf("]\n");
}

bool comparar_vectores(int vector_1[], int vector_2[], size_t tamanio){
    size_t i=0;
    bool coincide=true;
    while (coincide && i<tamanio){
        if (vector_1[i] != vector_2[i])
            coincide=false;
        i++;
    }
    return coincide;
}

void print_barra_porcentaje(size_t cantidad, size_t total){
    if(cantidad > total){
        printf(ROJO " ERROR " RESET);
        return; 
    }
    float porcentaje = (((float)cantidad)/(float)total) * 100;
    char bar[MAX_BAR];
    for(int i = 0; i<(porcentaje/10); i++)
        bar[i] = '0';

    printf ("|");
    for(int i = 0; i< MAX_BAR; i++){
        if(bar[i] == '0'){
            printf (FVERDE "  " RESET);
        }else{
            printf ("  ");
        }
            
    }
    printf ("|");
    printf("%.1f \n", porcentaje);
}

void warning(const char * descripcion){
    printf(ROJO "   %s - Hubo un problema con %s" RESET "\n", CRUZ, descripcion);
}

int __test_cantidad_de_pruebas_corridas = 0;
int __test_cantidad_de_pruebas_fallidas = 0;
const char *__test_prueba_actual = NULL;

void __test_atajarse(void (*handler)(int)){
    signal(SIGABRT, handler);
    signal(SIGSEGV, handler);
    signal(SIGBUS, handler);
    signal(SIGILL, handler);
    signal(SIGFPE, handler);
}

void __test_morir(int signum){
    if (__test_prueba_actual)
        printf(ROJO "\n\nERROR MIENTRAS SE EJECUTABA LA PRUEBA: " AMARILLO "'%s'\n\n" BLANCO, __test_prueba_actual);
    else
        printf(ROJO "\n\nFINALIZACION ANORMAL DE LAS PRUEBAS\n\n" BLANCO);
    fflush(stdout);
    __test_atajarse(SIG_DFL);
}

void test_afirmar(int afirmacion, const char *descripcion){
    __test_prueba_actual = descripcion;
    __test_atajarse(__test_morir);
    if (afirmacion) {
        printf(VERDE "   %s " ,TILDE);
    }else{
        __test_cantidad_de_pruebas_fallidas++;
        printf(ROJO "   %s ",CRUZ);
    }
    printf(BLANCO " %s\n", __test_prueba_actual);
    fflush(stdout);
    __test_prueba_actual = NULL;
    __test_cantidad_de_pruebas_corridas++;
}

void test_nuevo_grupo(const char *descripcion){
    printf(AMARILLO "\n   %s\n", descripcion);
    while (*(descripcion++))
        printf("=");
    printf(BLANCO "\n");
}

void test_nuevo_sub_grupo(const char *descripcion){
    printf("   _________________________________");
    printf(CYAN "\n   %s\n" RESET, descripcion);
}

void test_mostrar_reporte(){
    printf(BLANCO "\n   ---------------------------------\n");
    printf("    %i pruebas corridas, %i errores - %s\n" RESET,
           __test_cantidad_de_pruebas_corridas,
           __test_cantidad_de_pruebas_fallidas,
           __test_cantidad_de_pruebas_fallidas == 0 ? "OK" : "D:");
}
