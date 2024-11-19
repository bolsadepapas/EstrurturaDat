# Informe del Trabajo Grupal - [Implementacion Heap]

## 1. Nombre de los Integrantes / Fecha / Link 

**Integrantes**:
- **Basurco Monrroy Luis Gonzalo**
- **Marquez Zuñiga Johan Leonardo**
- **Sanz Palomino Facundo Alejandro**

- **Fecha**: [18/11/2024]
- **Link de codigo**: [https://github.com/bolsadepapas/EstrurturaDat.git]

## 1. Marco Teorico 

### ¿De que trata el laboratiorio-10?
- Lo que nos solicita el docente es que implementemos **enqueue** con valores **(V,K)**, lo que tenemos que hacer es insertar un elemento con un **V** en este caso un valor y un **K** en este caso un clave, en la estructura **Heap**, tambien lo que se nos solicita es que el programa deberia ser capaz de mostrar estos valores que esta siendo almancenados en un **Heap** esto a modo de comprobación.

### Entendiendo el codigo proporcionado

- En los siguientes segmentos de codigo veremos la implementacion tanto de **Arbol Binomial**  como tambien el **Heap** en el codigo que el profesor proporcino y que sirve como base para la implementacion de nuevas funciones: 

**Bt_node y Heap**
```cpp
// Este segmento de codigo sacado de "main.cpp"
typedef struct Binomial_Tree {
    int valor;            // Valor del nodo
    int k;                // Grado del nodo (número de hijos directos)
    struct Binomial_Tree *hijo;   // Puntero al primer hijo
    struct Binomial_Tree *padre;  // Puntero al padre
    struct Binomial_Tree *bro;    // Puntero al siguiente hermano derecho
} nodo_Bt;

typedef struct _heap_ {
    nodo_Bt *head; // Puntero al primer árbol binomial en el heap
} heap_t;


```
-**Comentario:** Tenemos **Binomial_tree** que representa un nodo en un arbol binomial, este nodo tiene un "valor", un grado (K), un hijo que es un (puntero al primer hijo), un padre que es un (puntero al padre del nodo) y un hermano que es un (puntero al hermano derecho en el mismo nivel).Como segundo estructura tenemos a **Heap_t** que representa a un Heap Binomial que es una coleccion de 
arboles binomiales; esta contiene un campo unico que en este caso es **Head** que es un puntero al primer arbol de todos los arboles dentro del **Heap**. 

**Función para Inicializar un Nodo del Árbol Binomial**
```cpp
// Este segmento de codigo sacado de "main.cpp"
nodo_Bt *init_nodo(int valor) {
    nodo_Bt *nodo = malloc(sizeof(nodo_Bt)); 
    nodo->valor = valor;    
    nodo->k = 0;            
    nodo->hijo = NULL;      // Inicializa puntero al hijo como NULL
    nodo->padre = NULL;     // Inicializa puntero al padre como NULL
    nodo->bro = NULL;       // Inicializa puntero al hermano como NULL
    return nodo;            // Devuelve el nodo creado
}

```
-**Comentario:** Tenemos **Binomial_tree** que representa un nodo en un arbol binomial, este nodo tiene un "valor", un grado (K), un hijo que es un (puntero al primer hijo), un padre que es un (puntero al padre del nodo) y un hermano que es un (puntero al hermano derecho en el mismo nivel).Como segundo estructura tenemos a **Heap_t** que representa a un Heap Binomial que es una coleccion de 
arboles binomiales; esta contiene un campo unico que en este caso es **Head** que es un puntero al primer arbol de todos los arboles dentro del **Heap**. 