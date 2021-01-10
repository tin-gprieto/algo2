#include "heap.h"

#define VACIO 0
#define RAIZ 0
#define NINGUNO 0
#define DERECHO 1
#define IZQUIERDO -1

heap_t* heap_crear(heap_condicion condicion, heap_destructor destructor){
    if(!condicion) return NULL;
    heap_t* aux = malloc(sizeof(heap_t));
    if(!aux) return NULL;
    aux->condicion = condicion;
    aux->destructor = destructor;
    aux->vector = NULL;
    aux->tope = VACIO;
    return aux;
}

bool heap_vacio(heap_t* heap){
    if(heap) return !(heap->tope);
    return true;
}

void heap_destruir(heap_t* heap){
    if(!heap) return;
    if(!heap_vacio(heap)){
        if(heap->destructor)
            for(int i = 0; i < heap->tope; i++)
                heap->destructor(heap->vector[i]); 
        free(heap->vector);
    }
    free(heap);
}

void* heap_raiz(heap_t* heap){
    if(heap && !heap_vacio(heap)) return heap->vector[RAIZ];
    return NULL;
}

void swap(void** vector, size_t elem_1, size_t elem_2){
    void* aux = vector[elem_1];
    vector[elem_1] = vector[elem_2];
    vector[elem_2] =aux;
}
size_t pos_padre(size_t pos){
    return (pos-1)/2;
}
size_t pos_hijo_derecho( size_t pos){
    return (2*pos) + 1;
}
size_t pos_hijo_izquierdo(size_t pos){
    return (2*pos) + 2;
}
void sift_up(heap_t* heap, size_t pos){
    if(!heap || pos == RAIZ) return;
    if(!(heap->condicion(heap->vector[pos_padre(pos)], heap->vector[pos]))){
        swap(heap->vector, pos, pos_padre(pos));
        sift_up(heap, pos_padre(pos));
    }
    return;
}


int hijo_incorrecto(heap_t* heap, size_t pos, heap_condicion condicion){
    if(!heap || pos == heap->tope) return NINGUNO;

    void* padre = heap->vector[pos];
    void* hijo_derecho = NULL;
    void* hijo_izquierdo = NULL;
    
    if(pos_hijo_derecho(pos) < heap->tope)
        hijo_derecho = heap->vector[pos_hijo_derecho(pos)];
    if(pos_hijo_izquierdo(pos) < heap->tope)
        hijo_izquierdo = heap->vector[pos_hijo_izquierdo(pos)];

    if(hijo_derecho && hijo_izquierdo){
        if(!condicion(padre, hijo_derecho) && !condicion(padre, hijo_izquierdo)){
            if(condicion(hijo_derecho, hijo_izquierdo))
                return DERECHO;
            return IZQUIERDO;
        }
    }

    if(hijo_derecho && !condicion(padre, hijo_derecho))
        return DERECHO;

    if(hijo_izquierdo && !condicion(padre, hijo_izquierdo))
        return IZQUIERDO;

    return NINGUNO;
}

void sift_down(heap_t* heap, size_t pos){
    if(!heap || pos == heap->tope) return;
    int hijo = hijo_incorrecto(heap, pos, heap->condicion);
    if(hijo == DERECHO){
        swap(heap->vector, pos, pos_hijo_derecho(pos));
        sift_down(heap,pos_hijo_derecho(pos));
    }else if(hijo == IZQUIERDO){
        swap(heap->vector,  pos, pos_hijo_izquierdo(pos));
        sift_down(heap,pos_hijo_izquierdo(pos));
    }
    return;
}

int heap_insertar(heap_t* heap, void* elemento){
    if(!heap) return ERROR;
    void** aux = realloc(heap->vector, (sizeof(void**) * (heap->tope + 1)));
    if(!aux) return ERROR;
    heap->vector = aux;
    heap->vector[heap->tope] = elemento;
    heap->tope++;
    sift_up(heap, heap->tope - 1);
    return EXITO;
}

int heap_borrar(heap_t* heap){
    if(!heap || heap_vacio(heap))
        return ERROR;
    if(heap->destructor)
        heap->destructor(heap->vector[RAIZ]);
    if(heap->tope > 1){
        swap(heap->vector, RAIZ, (heap->tope - 1));
        void** aux = realloc(heap->vector, (sizeof(void*)*(heap->tope - 1)));
        if(!aux) return ERROR;
        heap->vector = aux;
        heap->tope --;  
        sift_down(heap, RAIZ); 
    }else{
        free(heap->vector);
        heap->tope --;
    }
    return EXITO;
}

size_t heap_elementos(heap_t* heap){
    if(heap)
        return heap->tope;
    return VACIO;
}