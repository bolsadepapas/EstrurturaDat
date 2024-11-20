#include<stdio.h>
#include<stdlib.h>

typedef struct Binomial_Tree{
    int valor;
    int k;
    struct Binomial_Tree *hijo;
    struct Binomial_Tree *padre;
    struct Binomial_Tree *bro;

} nodo_Bt;

typedef struct _heap_{
    nodo_Bt *head;
}heap_t;
//inicializa un BT
nodo_Bt *init_nodo(int valor){
    nodo_Bt *nodo = malloc(sizeof(nodo_Bt));
    nodo->valor = valor;
    nodo->k=0;
    return nodo;
}

// inici--- un heap (vacio)
heap_t *heap_ini(){
    heap_t *heap = malloc(sizeof(heap_t));
    heap->head=NULL;
    return heap;

}

int main(){
    heap_t *heapp= heap_ini(); // heap
    nodo_Bt *nodo_ini = init_nodo(13);// nodo
    printf("valor del nodo es %d",nodo_ini->valor);
    return 0;

}