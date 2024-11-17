# Informe del Trabajo Grupal - [Trabajo Final]

## 1. Nombre de los Integrantes / Fecha / Link 

**Integrantes**:
- **Basurco Monrroy Luis Gonzalo**
- **Marquez Zuñiga Johan Leonardo**
- **Sanz Palomino Facundo Alejandro**

- **Fecha**: [14/11/2024]
- **Link de codigo**: [https://github.com/bolsadepapas/EstrurturaDat.git]

## 1. Marco Teorico 

### ¿De que trata el proyecto?
- La orientacion del proyecto va a la gestión eficiente de una base de datos en este caso **canciones.csv** utilizand herramientas e algoritmos de ordenamintos optimos aprendidos a lo largo del curso de **Estructura de Datos**, lo que nos permite cargar canciones desde un archivo CSV, buscar canciones/artistas rápidamente
y agregar nuevas canciones que se almacenan en alguna estructura que permite una manejo rapido de toda la data proporcionada, aparte de que se implementa **CRUD** que es un conjunto de operaciones base para la manipulacion de informacion/datos en valga la redundancia **Base de Datos** y distintas aplicaciones que gestionan infomacion en grandes cantidades
tambien se segmento el codigo en 3 arhivos distintos; **main.cpp**; **playlist.cpp**; **playlist.h**. 

### Caracteristicas clave del proyecto

- **Agregar canciones a la lista de reproducción** 
- **Eliminar canciones de la lista de reproducción**
- **Cambiar el orden de las canciones en la lista** 
- **Reproducción aleatoria de canciones**  
- **Ajuste dinámico del tamaño de la lista de reproducción de acuerdo a cambios**
    
---
## 2. Explicación del Abance temprano del proyecto.  

El primer enfoque del proyecto fue el desarrolar/implementar una estructura capaz de manejar datos masivos como en este caso **Canciones.csv**; y la primera idea que surgio fue la de implementar *B-tree* tenemos diferentes motivos, los cuales son que ya hemos desarrolado/implementado esta estructura de busqueda, otro de los grandes motivos es su rapideza en cuanto a la insercion de los datos que se desean manejar y aun mas la busqueda de los mismo teniendo un tiempo de busqueda, insercion y eliminacion de **O(logn)**, lo que es muy util en este proyecto. 

---
## 3.Implementacion de B-tree e implentacion de dos funciones del CRUD. 

- En los siguientes segmentos de codigo veremos la implementacion mas basica de **B-tree** en conjunto con el sistema **CRUD** estos segmentos de codigo representan el primer avance realizado **14 de Noviembre del 2024**: 

**Create(Crear)**
```cpp
// Este segmento de codigo sacado de "main.cpp"
case 2: {
    Cancion nuevaCancion;
    std::cout << "Ingrese nombre del artista: ";
    std::getline(std::cin, nuevaCancion.artist_name);
    std::cout << "Ingrese nombre de la canción: ";
    std::getline(std::cin, nuevaCancion.track_name);
    std::cout << "Ingrese popularidad: ";
    std::cin >> nuevaCancion.popularity;
    std::cout << "Ingrese año: ";
    std::cin >> nuevaCancion.year;
    std::cin.ignore();

    agregarCancion(tree, nuevaCancion, "canciones.csv");
    break;
}

```
```cpp
// Este segmento de codigo sacado de "playlist.cpp"
void agregarCancion(BTree &tree, Cancion &cancion, const std::string &filename) {
    tree.insert(cancion);

    std::ofstream file(filename, std::ios::app);
    if (file.is_open()) {
        file << obtenerSiguienteID(filename) << "," 
             << cancion.artist_name << "," 
             << cancion.track_name << "," 
             << cancion.popularity << "," 
             << cancion.year << "\n";
        file.close();
    }
}
```
- En el primero segmento de codigo se le pide al usuario que ingrese los detalles/parametros importantes de la nueva canción.Continuamos con el siguiente segmento de codigo una vez se llama a la función **agregarCancion**,esta añade la canción tanto al B-tree como al archivo CSV para su almacenamiento en la base de datos y como funcionalidad de orden se le asigna el siguiente numero de orden del ultimo dentro del CSV, para no sobrecargar las lineas con los datos. 

**Read (Leer)**
```cpp
// Este segmento de codigo sacado de "main.cpp" busqueda en el B-tree 
case 1: {
    std::string query;
    std::cout << "Ingrese término de búsqueda (nombre de canción o artista): ";
    std::getline(std::cin, query);
    tree.search(query);
    break;
}

```
```cpp
// Este segmento de codigo sacado de "playlist.cpp" funcion Search  
void BTreeNode::search(const std::string &term) {
    for (int i = 0; i < n; i++) {
        if (keys[i].track_name.find(term) != std::string::npos || 
            keys[i].artist_name.find(term) != std::string::npos) {
            std::cout << "Artista: " << keys[i].artist_name 
                      << " - Canción: " << keys[i].track_name << std::endl;
        }
    }
    if (!leaf) {
        for (int i = 0; i <= n; i++) {
            children[i]->search(term);
        }
    }
}

```
- En el primer segmento de codigo se le permite al usuario buscar canciones en el B-tree por el nombre del artista o de la canción. En el segundo es donde se implemta la logica detras de la busqueda en este caso; El método **search()** recorre el **B-tree** para encontrar coincidencias según el término de búsqueda proporcionado. 

## 6. Output/Consola **14 de Noviembre 2024**.

### Menu principal del codigo terminal **Visual Estudio Code**

```py
PS C:\Users\facun\EstrurturaDat\Project 6> .\BCD.exe
Bienvenido a Apple Music, Edson!
Presiona Enter para continuar...


--- Menú ---
1. Buscar canción      
2. Agregar canción     
3. Salir
Seleccione una opción: 
```
### Busqueda de canciones atravez de la terminal **Visual Estudio Code**

-Al seleccionar una opccion por ejemplo la opción 1, nos muestra lo siguiente: 

```py
--- Menú ---
1. Buscar canción      
2. Agregar canción     
3. Salir
Seleccione una opción: 1
Ingrese término de búsqueda (nombre de canción o artista): A Rush of Blood to the Head
Artista: Coldplay - Canción: A Rush of Blood to the Head

--- Menú ---
1. Buscar canción      
2. Agregar canción     
3. Salir
Seleccione una opción: 1
Ingrese término de búsqueda (nombre de canción o artista): Alternative Outro

--- Menú ---
1. Buscar canción      
2. Agregar canción     
3. Salir
Seleccione una opción: 1
Ingrese término de búsqueda (nombre de canción o artista): The Spins 
Artista: Hepcat - Canción: The Spins
Artista: Mac Miller - Canción: The Spins
```
- **Comentario**: Como podemos ver tanto el primer intento de busqueda como en el ultimo se encontro la cancion que se deseaba, pero en el segundo no se encontro esto se debe a que dentro de nuestra base de datos no hay una cancion con el nombre de "Alternative Outro" y por lo tanto no se puede mostrar. 

### Inserción de canciones atravez de la terminal **Visual Estudio Code**

-Al seleccionar una opccion por ejemplo la opción 2, nos muestra lo siguiente: 

```py
--- Menú ---
1. Buscar canción      
2. Agregar canción     
3. Salir
Seleccione una opción: 2
Ingrese el nombre del artista: Guitarricadelafuente
Ingrese el nombre de la canción: Ya mi mamá me decía 
Ingrese el ID de la canción: 20018
Ingrese la popularidad (0-100): 70
Ingrese el año de lanzamiento: 2022
Canción agregada exitosamente!
```
-Muestra de incersion exitosa dentro del .CSV: 

```py
1473395,Mo' Horizons,Hit the Road Jack (Pé Na Éstrada),4oMiOwhDZEdBuzAfhzRHbi,3,2011,trip-hop,0.782,0.861,1,-7.292,0,0.125,0.22,8.43e-06,0.0581,0.857,89.987,212227,4
1473396,Guitarricadelafuente,Ya mi mamá me decía ,20018,70,2022,0.0,0.0,0.0
```
-**Comentario**: Como podemos ver aun falta pulir mucho mas los paramentros que se le piden al usuario pero como primer avance es algo significativo, algo importante antes nombrado es que se le agrega el siguiente numero de orden dentro de las filas del **.CSV** lo que es importante para no sobrecargar las filas con informacion sobrescrita. 







