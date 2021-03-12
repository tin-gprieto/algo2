#include "hash.h"

//hash.h
hash_t* hash_crear(hash_destruir_dato_t destruir_elemento, size_t capacidad){

}
//hash.h
int hash_insertar(hash_t* hash, const char* clave, void* elemento){

}
//hash.h
int hash_quitar(hash_t* hash, const char* clave){

}
//hash.h
void* hash_obtener(hash_t* hash, const char* clave){

}
//hash.h
bool hash_contiene(hash_t* hash, const char* clave){

}
//hash.h
size_t hash_cantidad(hash_t* hash){

}
//hash.h
void hash_destruir(hash_t* hash){

}
//hash.h
size_t hash_con_cada_clave(hash_t* hash, bool (*funcion)(hash_t* hash, const char* clave, void* aux), void* aux){

}
