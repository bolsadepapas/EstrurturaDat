#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <map>

/// **Estructura Cancion** ///
struct Cancion {
    int order_id;
    std::string artist_name;
    std::string track_name;
    std::string track_id;
    int popularity;
    int year;

    Cancion() : order_id(0), popularity(0), year(0) {}
};

/// **Clase BTreeNode** ///
class BTreeNode {
    int t;                      // Grado mínimo del árbol.
    Cancion* keys;              // Arreglo de claves.
    BTreeNode** children;       // Arreglo de punteros a hijos.
    int n;                      // Número actual de claves.
    bool leaf;

public:
    BTreeNode(int grado, bool esHoja);
    ~BTreeNode();                 // Destructor para liberar memoria.
    void insertNonFull(const Cancion& k);      // Inserta en un nodo que no está lleno.
    void splitChild(int i, BTreeNode *y);      // Divide un nodo hijo lleno.
    Cancion* search(const std::string &term);  // Busca una canción en el nodo.
    void collectSongs(std::vector<Cancion>& songs); // Recolecta canciones del nodo.

    // Declaramos a la clase BTree como amiga.
    friend class BTree;
};

/// **Clase BTree** ///
class BTree {
    BTreeNode* root; // Puntero a la raíz del árbol.
    int t;

public:
    BTree() : root(nullptr), t(2) {} 
    BTree(int grado) : root(nullptr), t(grado) {}
    ~BTree();          // Destructor para liberar la memoria del árbol.

    // Métodos principales
    void insert(const Cancion& k);                  // Inserta una canción en el árbol.
    Cancion* search(const std::string& term);       // Busca una canción por término.
    void shuffle();                                 // Reproduce canciones aleatoriamente.
    void sortSongs(const std::string& criterio, bool asc); // Ordena canciones por criterio.
    void getSongsByYear(int year, std::vector<Cancion>& songs); // Filtra canciones por año.

    // Getter de la raíz
    BTreeNode* getRoot() { return root; }
};


class PlaylistManager {
    std::map<std::string, BTree> playlists; 

    void guardarPlaylist(const std::string& nombre);
    void cargarPlaylist(const std::string& nombre);

public:
    void crearPlaylist(const std::string& nombre, int grado); // Crear playlist.
    void eliminarPlaylist(const std::string& nombre);         // Eliminar playlist.
    void mostrarPlaylists();                                   // Mostrar todas las playlists.
    void agregarCancionAPlaylist(const std::string& playlistNombre);
    void mostrarCancionesDePlaylist(const std::string& playlistNombre);
    BTree* obtenerPlaylist(const std::string& nombre);         // Obtener una playlist por nombre.

    void cargarPlaylists(); 
};

#endif // PLAYLIST_H