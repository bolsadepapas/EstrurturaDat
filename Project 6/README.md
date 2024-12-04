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
- La orientacion del proyecto va a la gestión eficiente de una base de datos en este caso **canciones.csv** utilizando herramientas e algoritmos de ordenamintos optimos aprendidos a lo largo del curso de **Estructura de Datos**, lo que nos permite cargar canciones desde un archivo CSV, buscar canciones/artistas rápidamente
y agregar nuevas canciones que se almacenan en alguna estructura que permite una manejo rapido de toda la data proporcionada, aparte de que se implementa **CRUD** que es un conjunto de operaciones base para la manipulacion de informacion/datos en valga la redundancia **Base de Datos** y distintas aplicaciones que gestionan infomacion en grandes cantidades
tambien se segmento el codigo en 3 arhivos distintos; **main.cpp**; **playlist.cpp**; **playlist.h**. 

### Caracteristicas clave del proyecto

- **Agregar canciones a la lista de reproducción** 
- **Eliminar canciones de la lista de reproducción**
- **Cambiar el orden de las canciones en la lista** 
- **Reproducción aleatoria de canciones**  
- **Ajuste dinámico del tamaño de la lista de reproducción de acuerdo a cambios**
    
---
## 2. Explicación del Avance temprano del proyecto.  

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

## 7.Implementaciones nuevas en el codigo (26/11/2024)

- Para esta fecha el codigo tuvo bastantes mojoras con respecto a la implementacion intuitiva de nuevas funciolandidades, a continuacion veremos cuales son algunas des las funciones mas inportantes en cuanto a la escalavilidad que se espero implementar por parte del codigo en general. 


### Muestra de las canciones que se reprodicirian en aleatorio **Visual Estudio Code**

-Al seleccionar una opccion, en este caso la 3 lo que nos muestra es lo siguiente : 

```py
--- Menú ---
1. Buscar canción
2. Agregar canción
3. Reproducción Aleatoria
4. Gestión de Playlists
5. Mostrar Top 100 canciones de un año
6. Salir
Seleccione una opción: 3

Reproducción Aleatoria: Estas son las canciones que se reproducirán:
1. SNBRN - Home
2. Epik High - I Remember
3. Wolfgang Amadeus Mozart - "Requiem in D Minor
4. Maria Papadopoulou - To Teleftaio Gramma
5. Rauw Alejandro - Algo Mágico
6. Danger Zone - I to I
7. Beck - Jack-Ass
8. Richard Cheese - Buddy Holly
9. Mayte Gaos - Tic Tac Twist
10. The Body - Tied Up and Locked In
```
-**Comentario**: Como podemos ver al seleccionar la opcion lo que nos muestra es la cola de canciones que contienen la cancion que se esta reproduciendo de forma aleatoria y las que esperan ser reproducidas, todas bajo la logica de la aleatoriedad. 


### Top 100 mejores canciones del año **Visual Estudio Code**

-Al seleccionar una opccion, en este caso la 5 lo que nos muestra es lo siguiente : 

```py
--- Menú ---
1. Buscar canción
2. Agregar canción
3. Reproducción Aleatoria
4. Gestión de Playlists
5. Mostrar Top 100 canciones de un año
6. Salir
Seleccione una opción: 5
Ingrese el año para mostrar las 100 mejores canciones: 2023

Top 100 canciones del año 2023:
1. Flowers - Miley Cyrus (Popularidad: 100)
2. Die For You - Remix - The Weeknd (Popularidad: 95)
3. OMG - NewJeans (Popularidad: 92)
4. PRC - Peso Pluma (Popularidad: 90)
5. Tormenta (feat. Bad Bunny) - Gorillaz (Popularidad: 89)
6. Last Night - Morgan Wallen (Popularidad: 88)
7. on the street (with J. Cole) - j-hope (Popularidad: 88)
8. Love Again - The Kid LAROI (Popularidad: 87)
9. Shorty Party - Cartel De Santa (Popularidad: 87)
10. Heaven - Niall Horan (Popularidad: 86)
```
-**Comentario**: En este caso, se aprobecha mucho la implementacion de orden de las canciones en un B-tree, ya que al mostrar el top de mejores canciones, nos basamos en el nivel de popularidad de la cancion, lo cual es un valor que toma importancia para la logica que surge en respuesta para la seleccion de la opcion 5. 

### Submenu implementacion de Funciones para Playlist, de usuario **Visual Estudio Code**

-Al seleccionar una opccion, en este caso la 4ta opcion nos despliega un submenu que nos muestra es lo siguiente : 

```py
--- Menú ---
1. Buscar canción
2. Agregar canción
3. Reproducción Aleatoria
4. Gestión de Playlists
5. Mostrar Top 100 canciones de un año
6. Salir
Seleccione una opción: 4

--- Submenú de Gestión de Playlists ---
1. Crear nueva playlist
2. Eliminar playlist
3. Mostrar playlists disponibles
4. Buscar y agregar canciones a una playlist
5. Regresar al menú principal
Seleccione una opción:
```
-**Comentario**: Cuando se selelciona esta opcion, lo que nos muestra es un submeni especializado en la gestion unica de playlist dedicada a usuarios, donde se pueden realizar acciones como crear una nueva playlist, eliminar una playlist, mostrar las playlists disponibles, buscar y agregar canciones a una playlist, este submenu esta orientado a ofrecer una experiencia mas completa y personalizada para el usuario. 

## 8. Exploracion del submenu de gestion de Playlist de usuario (30/11/2024)

- Para la fecha el codigo ya tiene un submenu corregido y con las funciones totalmente pulidas para la gestion de las playlist que desee crear, buscar, y eliminar el usuario, este menu lo que buscar es crear una mejor experiencia con los usuarios que vaya a tener este codigo. 

-Aqui podemos ver las funciones que tiene ofrece el sumenu iteractivo de gestion de Playlists : 

```py
--- Submenú de Gestión de Playlists ---
1. Crear nueva playlist
2. Eliminar playlist
3. Mostrar playlists disponibles
4. Buscar y agregar canciones a una playlist
5. Regresar al menú principal
Seleccione una opción:
```
-**Comentario**: Al seleccionar cualquiera de las opciones lo que se despliega es la logica que implica el que se haya seleccionado alguno de los items del submenu, por ejemplo si se selecciona la opcion 1, se despliega la logica para crear una nueva playlist, si se selecciona la opcion 2, se despliega la logica para eliminar una playlist, y asi sucesivamente. es importante recalcar que el codigo aun puede presentar fallas. 






