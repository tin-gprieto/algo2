#include "hash.h"
#include "toolbox/code/tools/tools.h"

void probar_creacion(){
    test_nuevo_grupo("Pruebas de Creación");
}

void probar_insercion(){
    test_nuevo_grupo("Pruebas con insertar");
    test_nuevo_sub_grupo("Insertar un elemento");
}

int main(){
    probar_creacion();
    //probar_insercion();
    //probar_borrado();
    test_mostrar_reporte();
}