# Informe del Trabajo Grupal - [Implementacion Heap]

## 1. Nombre de los Integrantes / Fecha / Link 

**Integrantes**:
- **Basurco Monrroy Luis Gonzalo**
- **Marquez Zuñiga Johan Leonardo**
- **Sanz Palomino Facundo Alejandro**

- **Fecha**: [18/11/2024]
- **Link de codigo**: [https://onlinegdb.com/Prw32fd_N]

## 1. Marco Teorico 

### ¿De que trata el laboratiorio-10?
- Lo que nos solicita el docente es que implementemos **enqueue** con valores **(V,K)**, lo que tenemos que hacer es insertar un elemento con un **V** en este caso un valor y un **K** en este caso un clave, en la estructura **Heap**, tambien lo que se nos solicita es que el programa deberia ser capaz de mostrar estos valores que esta siendo almancenados en un **Heap** esto a modo de comprobación.

### Entendiendo el codigo proporcionado

- En los siguientes segmentos de codigo veremos la implementacion tanto de **Arbol Binomial**  como tambien el **Heap** en el codigo que el profesor proporcino y que sirve como base para la implementacion de nuevas funciones: 

**Bt_node y Heap**
```c
// Este segmento de codigo sacado de "main.c"
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


```
-**Comentario:** Tenemos **Binomial_tree** que representa un nodo en un arbol binomial, este nodo tiene un "valor", un grado (K), un hijo que es un (puntero al primer hijo), un padre que es un (puntero al padre del nodo) y un hermano que es un (puntero al hermano derecho en el mismo nivel).Como segundo estructura tenemos a **Heap_t** que representa a un Heap Binomial que es una coleccion de 
arboles binomiales; esta contiene un campo unico que en este caso es **Head** que es un puntero al primer arbol de todos los arboles dentro del **Heap**. 

**Función para Inicializar un Nodo del Árbol Binomial**
```c
// Este segmento de codigo sacado de "main.c"
nodo_Bt *init_nodo(int valor) {
    nodo_Bt *nodo = malloc(sizeof(nodo_Bt)); 
    nodo->valor = valor;    
    nodo->k = 0;            
    nodo->hijo = NULL;      
    nodo->padre = NULL;    
    nodo->bro = NULL;      
    return nodo;           
}

```
-**Comentario:** Tenemos **Malloc** que asigna un espacio de memoria dinamica a un nodo, esperando el valor que se le tenga que dar. 

**Función para Inicializar un Heap Vacio**
```c
heap_t *heap_ini() {
    heap_t *heap = malloc(sizeof(heap_t)); 
    heap->head = NULL;  
    return heap;       
}

```
-**Comentario:** Este segmento de codigo inicializa un heap vacio, esto para que asi pueda arboles binomiales. 

## 2.Aplicando Nuevas Funcionalidades/ Lab10

- Para los siguientes pasos implementaremos las funcionalidades en este caso **enqueue(v, k)** que es solicitada por el docente para el desarrollo del laboratorio 10, en este segmento de informe explicaremos cuales fueron las logicas necesarias de implementar al codigo proporcionado para que se cumplan con los requerimientos del Profesor. 

**Función Enqueue valor (v)**
```c
void enqueue(heap_t *heap, int v) {
    nodo_Bt *nuevo_nodo = init_nodo(v);

    nuevo_nodo->bro = heap->head;
    heap->head = nuevo_nodo;
}
```
-**Comentario:** En este segmento de codigo podemos ver como la funcion inserta un **nodo** con un valor **(V)** en el Heap,en este caso usamos la función **init_nodo** para crear un nodo inicializado con los valores que se le asignan, luego el nodo es insertado al inicio de las listas de los arboles que contiene el **Heap**, esto apuntando a su nodo hermano. 

**Función para mostrar los los nodos raiz**
```c
void printHeap(heap_t *heap) {
    nodo_Bt *current = heap->head;

    while (current != NULL) {
        printf("Nodo valor: %d, Grado: %d\n", current->valor, current->k);
        current = current->bro; 
    }
}
```
-**Comentario:** En este segmento de codigo tenemos a esta funcion que lo que hace es recorrer y mostrar los nodos raiz del **Heap** binomial, comenzando desde el nodo apuntado por **Heap** a **Heap**. Imprimiendo el Valor (V) y el grado que en este caso es (K) esto de cada nodo raiz, asi podiendo visualizar el contenido del **Heap**, esto lo hace iterativamente usando el puntero **Bro** asi hasta llegar al final del **Heap**. 

## 3. Conclusión 

-  Como conclusión podemos decir que se logro implementar las funcionalidades solicitadas por el docente y que tambien pudimos ver y trabajar con las funcinalidades mas basicas de **Heap Binomial** enfocandonos en la creacion, insercion y por ultimo visualizacion de los nodos, Implementamos estructuras eficientes,utilizamos memoria dinamica para los nodos y listas de arboles dentro del **Heap**. Con este laboratorio pudimos ver una base que puede servir para poder ser expandida en un futuro asi añadiendole funcionalidades en el Heap. 