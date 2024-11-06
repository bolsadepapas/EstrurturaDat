# Informe del Trabajo Grupal - [Tablas-Hash]

## 1. Nombre de los Integrantes / Fecha / Link 

**Integrantes**:
- **Basurco Monrroy Luis Gonzalo**
- **Marquez Zuñiga Johan Leonardo**
- **Sanz Palomino Facundo Alejandro**

- **Fecha**: [05/11/2024]
- **Link de codigo**: [https://github.com/bolsadepapas/EstrurturaDat.git]


## 1. Marco Teorico 

### ¿Qué es una Tabla Hash?

Una **tabla hash** es una estructura de datos utilizada para almacenar datos de manera eficiente, de tal forma que la búsqueda, inserción y eliminación de elementos se realicen en tiempo promedio constante, es decir, **O(1)**.El principio básico de una tabla hash esta  en una **función hash**, que mapea una clave ("key") a una posición específica en una tabla de almacenamiento. Cada posición en la tabla se llama un  **bucket**, y cada **bucket** puede almacenar uno o más elementos.

### Propiedades
- **Clave (Key)**: El valor que se utiliza para identificar de manera única un elemento en la tabla.
- **Valor (Value)**:El dato que se almacena en la tabla, asociado a una clave.
- **Función hash**: Es una función matemática que toma una clave y la convierte en un índice de la tabla. Idealmente, esta función distribuye las claves de manera uniforme en la tabla para evitar colisiones.
- **Tabla**:  El número de hijos de un nodo es igual a su número de claves más 1.


### Funcionamiento
- **Inserción**: Cuando se quiere agregar un nuevo elemento a la tabla, la función hash toma la clave del elemento, calcula el índice correspondiente y coloca el valor en el bucket correspondiente a ese índice.

- **Búsqueda**: Para encontrar un elemento en la tabla, se aplica la función hash sobre la clave, lo que nos da la posición en la tabla, y luego buscamos el valor asociado en esa posición.

- **Eliminación**: Para eliminar un elemento, se aplica la función hash sobre la clave, se localiza el índice de la tabla, y se elimina el elemento de esa posición.

---
## 2. Explicación del Problema 

- El objetivo del siguiente laboratorio,es implementar las distintas funciones dadas por el docente mediante segmentos de codigo de lenguaje **.Py** ; en un programa que impmenente las mismas funciones pero que sean en lenguaje **.c++**  
---
## 3.Funciones Base

- En los siguientes segmentos de codigo podremos ver las funciones que dio el docente  **Laboratorio07 - Hash (Mediante Google Collab)**: 

**Función insertar()**
```py
def insertar(self, x):
    # Calcula el índice utilizando la función hash para determinar
    # en qué bucket se debe insertar el elemento 'x'.
    index = self.h(x, self.n)
    
    # Inserta el valor 'x' en el bucket correspondiente al índice
    # calculado, utilizando el método 'append' para agregarlo a la lista.
    self.bucket[index].append(x)
    print(f"Elemento {x} insertado en el bucket {index}")
```
- **Comentario**: Calcula el índice de inserción con la función hash y agrega el valor al bucket.

**Función eliminar()**
```py
def eliminar(self, x):
    # Calcula el índice del bucket donde puede estar el
    # elemento 'x' utilizando la función hash
    index = self.h(x, self.n)
    
    # Verifica si el elemento 'x' está en el bucket
    # y lo elimina si es encontrado
    bucket = self.bucket[index]
    if x in bucket:
        bucket.remove(x)
        print(f"Elemento {x} eliminado del bucket {index}")
    else:
        print(f"Elemento {x} no encontrado en el bucket {index}")

```
- **Comentario**: Calcula el índice del valor y lo elimina si está presente en el bucket, de lo contrario muestra un mensaje.


**Función encontrar()**
```py
def encontrar(self, x):
    # Calcula el índice del bucket donde debería estar el
    # elemento 'x' utilizando la función hash
    index = self.h(x, self.n)
    
    # Verifica si el elemento 'x' está presente en el bucket
    # correspondiente y retorna True si lo encuentra
    bucket = self.bucket[index]
    if x in bucket:
        print(f"Elemento {x} encontrado en el bucket {index}")
        return True
    else:
        print(f"Elemento {x} no encontrado en el bucket {index}")
        return False

```
- **Comentario**: Calcula el índice y verifica si el valor está en el bucket, retornando un mensaje adecuado.

--- 
## 4. Output/Consola del codigo **.py**.
```py
Elemento 123 insertado en el bucket 3
Elemento 456 insertado en el bucket 6
Elemento 123 encontrado en el bucket 3
Elemento 789 no encontrado en el bucket 9
Elemento 123 eliminado del bucket 3
Elemento 789 no encontrado en el bucket 9

```
- **Comentario**: Esto es lo que nos muestra en consola al correr el codigo, como podemos ver trabaja con las 3 funciones principales, desde insertar, pasando por buscar, y luego eliminar.

--- 

## 5. Implementacion del codigo, en lenganje **.c++** / Output de Consola.

- Acontinuacion veremos las mismas Funciones implementadas pero en este caso para el lenguaje **c++**: 

**Función Insertar()**
```cpp
void insertar(int x) {
    // Calcula el índice del bucket usando la función hash y determina dónde insertar el valor 'x'.
    // Inserta 'x' en el bucket correspondiente utilizando el método 'push_back' de la lista.
    int index = h(x, n);
    bucket[index].push_back(x);
    cout << "Elemento " << x << " insertado en el bucket " << index << endl;
}

```
- **Comentario**: Calcula el índice de inserción con la función hash y agrega el valor al bucket.

**Función Eliminar()**
```cpp
void eliminar(int x) {
    // Calcula el índice del bucket donde puede estar el valor 'x' usando la función hash.
    // Si 'x' se encuentra en el bucket, lo elimina; de lo contrario, imprime un mensaje de error.
    int index = h(x, n);
    auto& b = bucket[index];
    auto it = find(b.begin(), b.end(), x);
    if (it != b.end()) {
        b.erase(it);
        cout << "Elemento " << x << " eliminado del bucket " << index << endl;
    } else {
        cout << "Elemento " << x << " no encontrado en el bucket " << index << endl;
    }
}

```
- **Comentario**: Calcula el índice de inserción con la función hash y agrega el valor al bucket.

**Función Encontrar()**
```cpp
bool encontrar(int x) {
    // Calcula el índice del bucket donde debería estar el valor 'x' usando la función hash.
    // Verifica si el valor 'x' está en el bucket y retorna true si lo encuentra, sino false.
    int index = h(x, n);
    auto& b = bucket[index];
    if (find(b.begin(), b.end(), x) != b.end()) {
        cout << "Elemento " << x << " encontrado en el bucket " << index << endl;
        return true;
    } else {
        cout << "Elemento " << x << " no encontrado en el bucket " << index << endl;
        return false;
    }
}
```
- **Comentario**: Calcula el índice de inserción con la función hash y agrega el valor al bucket.

# 5.1 Output de Consola. 
```py
PS C:\Users\facun\EstrurturaDat\Tablas Hash> .\hash.exe
Se encontro 123? Si
Se encontro 76? Si
Se encontro 123 despues de ser eliminado? No 
```
- Este output, responde logicamente a este segemento de codigo en especifico, que implementa las funciones basicas de Hash: 

**Main()**: 

```cpp
{
    HashTable HT(10, RandomHashFun);

    HT.insertar(123);
    HT.insertar(76);

    std::cout << "Se encontro 123? " << (HT.encontrar(123) ? "Si" : "No") << std::endl;
    std::cout << "Se encontro 76? " << (HT.encontrar(76) ? "Si" : "No") << std::endl;

    HT.eliminar(123);

    std::cout << "Se encontro 123 despues de ser eliminado? " << (HT.encontrar(123) ? "Si" : "No") << std::endl;

    return 0;
}
```
## 6. Conculsiones y Recomendaciones  

**Conclusiones**
- Las tablas hash son estructuras de datos fundamentales que permiten almacenar y recuperar información de manera extremadamente eficiente. Utilizan una función hash para convertir las claves en índices de un arreglo, lo que facilita el acceso directo a los valores asociados a esas claves. Su principal ventaja es la búsqueda de tiempo constante (O(1)), lo que las hace ideales para aplicaciones que requieren una recuperación rápida de datos.







