#include "playlist.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <random>

// Constructor del nodo
BTreeNode::BTreeNode(int grado, bool esHoja) {
    t = grado;
    leaf = esHoja;
    keys = new Cancion[2 * t - 1];
    children = new BTreeNode *[2 * t];
    n = 0;
}

// Destructor del nodo
BTreeNode::~BTreeNode() {
    if (!leaf) {
        for (int i = 0; i <= n; ++i) {
            delete children[i];
        }
    }
    delete[] keys;
    delete[] children;
}

// Métodos del nodo
void BTreeNode::insertNonFull(const Cancion& k) {
    int i = n - 1;
    if (leaf) {
        while (i >= 0 && k.track_name < keys[i].track_name) {
            keys[i + 1] = keys[i];
            i--;
        }
        keys[i + 1] = k;
        n++;
    } else {
        while (i >= 0 && k.track_name < keys[i].track_name)
            i--;
        if (children[i + 1]->n == 2 * t - 1) {
            splitChild(i + 1, children[i + 1]);
            if (k.track_name > keys[i + 1].track_name)
                i++;
        }
        children[i + 1]->insertNonFull(k);
    }
}

void BTreeNode::splitChild(int i, BTreeNode *y) {
    BTreeNode *z = new BTreeNode(y->t, y->leaf);
    z->n = t - 1;
    for (int j = 0; j < t - 1; j++)
        z->keys[j] = y->keys[j + t];

    if (!y->leaf) {
        for (int j = 0; j < t; j++)
            z->children[j] = y->children[j + t];
    }

    y->n = t - 1;
    for (int j = n; j >= i + 1; j--)
        children[j + 1] = children[j];

    children[i + 1] = z;
    for (int j = n - 1; j >= i; j--)
        keys[j + 1] = keys[j];

    keys[i] = y->keys[t - 1];
    n++;
}

Cancion* BTreeNode::search(const std::string& term) {
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
    return nullptr;
}

void BTreeNode::collectSongs(std::vector<Cancion>& songs) {
    for (int i = 0; i < n; i++) {
        songs.push_back(keys[i]);
    }

    if (!leaf) {
        for (int i = 0; i <= n; i++) {
            children[i]->collectSongs(songs);  
        }
    }
}

// Destructor del árbol
BTree::~BTree() {
    delete root; // Esto llama al destructor de BTreeNode
}

// Métodos del árbol
void BTree::insert(const Cancion& k) {
    if (!root) {
        root = new BTreeNode(t, true);
        root->keys[0] = k;
        root->n = 1;
    } else {
        if (root->n == 2 * t - 1) {
            BTreeNode *s = new BTreeNode(t, false);
            s->children[0] = root;
            s->splitChild(0, root);

            int i = 0;
            if (s->keys[0].track_name < k.track_name)
                i++;
            s->children[i]->insertNonFull(k);
            root = s;
        } else {
            root->insertNonFull(k);
        }
    }
}

Cancion* BTree::search(const std::string& term) {
    if (root)
        return root->search(term);
    else
        std::cout << "No se encontraron coincidencias para: " << term << std::endl;
    return nullptr;
}

void BTree::shuffle() {
    if (!root) {
        std::cout << "No hay canciones en la lista de reproducción." << std::endl;
        return;
    }

    std::vector<Cancion> songs;
    root->collectSongs(songs); 

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(songs.begin(), songs.end(), g);

    std::cout << "Reproducción aleatoria:" << std::endl;
    for (const auto &song : songs) {
        std::cout << song.track_name << " - " << song.artist_name << std::endl;
    }
}

void BTree::sortSongs(const std::string& criterio, bool asc) {
    if (!root) {
        std::cout << "No hay canciones en la lista de reproducción." << std::endl;
        return;
    }

    std::vector<Cancion> songs;
    root->collectSongs(songs); 

    std::sort(songs.begin(), songs.end(), [&](const Cancion &a, const Cancion &b) {
        if (criterio == "popularidad") {
            return asc ? a.popularity < b.popularity : a.popularity > b.popularity;
        } else if (criterio == "año") {
            return asc ? a.year < b.year : a.year > b.year;
        } else if (criterio == "nombre") {
            return asc ? a.track_name < b.track_name : a.track_name > b.track_name;
        }
        return false; 
    });

    std::cout << "Canciones ordenadas por " << criterio << ":" << std::endl;
    for (const auto &song : songs) {
        std::cout << song.track_name << " - " << song.artist_name << std::endl;
    }
}

void PlaylistManager::crearPlaylist(const std::string& nombre, int grado) {
    if (nombre.empty()) {
        std::cout << "El nombre de la playlist no puede estar vacío.\n";
        return;
    }

    if (playlists.find(nombre) != playlists.end()) {
        std::cout << "La playlist \"" << nombre << "\" ya existe.\n";
        return;
    }

    playlists[nombre] = BTree(grado);
    std::cout << "Playlist \"" << nombre << "\" creada exitosamente.\n";
}

void PlaylistManager::eliminarPlaylist(const std::string& nombre) {
    if (playlists.erase(nombre)) {
        std::cout << "Playlist \"" << nombre << "\" eliminada.\n";
    } else {
        std::cout << "La playlist \"" << nombre << "\" no existe.\n";
    }
}

void PlaylistManager::renombrarPlaylist(const std::string& nombreActual, const std::string& nuevoNombre) {
    auto it = playlists.find(nombreActual);
    if (it == playlists.end()) {
        std::cout << "La playlist \"" << nombreActual << "\" no existe.\n";
        return;
    }
    playlists[nuevoNombre] = it->second;
    playlists.erase(it);
    std::cout << "Playlist \"" << nombreActual << "\" renombrada a \"" << nuevoNombre << "\".\n";
}

void PlaylistManager::transferirCancion(const std::string& origen, const std::string& destino, const std::string& cancion) {
    auto itOrigen = playlists.find(origen);
    auto itDestino = playlists.find(destino);
    if (itOrigen == playlists.end() || itDestino == playlists.end()) {
        std::cout << "Una de las playlists no existe.\n";
        return;
    }

    std::vector<Cancion> canciones;
    itOrigen->second.getRoot()->collectSongs(canciones);

    auto it = std::find_if(canciones.begin(), canciones.end(), [&](const Cancion& c) {
        return c.track_name == cancion;
    });

    if (it != canciones.end()) {
        itDestino->second.insert(*it);
        std::cout << "Canción \"" << cancion << "\" transferida de \"" << origen << "\" a \"" << destino << "\".\n";
    } else {
        std::cout << "La canción \"" << cancion << "\" no se encontró en la playlist \"" << origen << "\".\n";
    }
}

void PlaylistManager::mostrarPlaylists() {
    if (playlists.empty()) {
        std::cout << "No hay playlists disponibles.\n";
        return;
    }
    std::cout << "Playlists disponibles:\n";
    for (const auto& [nombre, _] : playlists) {
        std::cout << "- " << nombre << "\n";
    }
}

BTree* PlaylistManager::obtenerPlaylist(const std::string& nombre) {
    auto it = playlists.find(nombre);
    if (it != playlists.end()) {
        return &it->second;
    }
    return nullptr;
}
