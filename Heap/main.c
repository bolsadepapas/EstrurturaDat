#include <stdio.h>
#include <stdlib.h>


typedef struct Binomial_Tree {
    int valor;              
    int k;                 
    struct Binomial_Tree *hijo; 
    struct Binomial_Tree *padre; 
    struct Binomial_Tree *bro;   
} nodo_Bt;


typedef struct _heap_ {
    nodo_Bt *head;
} heap_t;


nodo_Bt *init_nodo(int valor) {
    nodo_Bt *nodo = malloc(sizeof(nodo_Bt)); 
    nodo->valor = valor; 
    nodo->k = 0;        
    nodo->hijo = NULL;  
    nodo->padre = NULL;  
    nodo->bro = NULL;    
    return nodo;         
}

heap_t *heap_ini() {
    heap_t *heap = malloc(sizeof(heap_t)); 
    heap->head = NULL;  
    return heap;      
}

void enqueue(heap_t *heap, int v) {
    nodo_Bt *nuevo_nodo = init_nodo(v);
    nuevo_nodo->bro = heap->head;
    heap->head = nuevo_nodo;
}

void printHeap(heap_t *heap) {
    nodo_Bt *current = heap->head;

    while (current != NULL) {
        printf("Nodo valor: %d, Grado: %d\n", current->valor, current->k);

        current = current->bro;
    }
}

int main() {
    heap_t *heapp = heap_ini();

    enqueue(heapp, 13);
    enqueue(heapp, 7);
    enqueue(heapp, 10);
    enqueue(heapp, 9);

    printf("Elementos en el Heap:\n");
    printHeap(heapp);

    return 0;
}
