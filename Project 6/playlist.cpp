#include "playlist.h"
#include <iostream>
#include <filesystem> 
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

BTree::~BTree() {
    delete root;
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
void BTree::getSongsByYear(int year, std::vector<Cancion>& songs) {
    if (root) {
        std::vector<Cancion> allSongs;
        root->collectSongs(allSongs);
        for (const auto& cancion : allSongs) {
            if (cancion.year == year) {
                songs.push_back(cancion);
            }
        }
    }
}

void PlaylistManager::eliminarPlaylist(const std::string& nombre) {
    if (playlists.erase(nombre)) {
        std::cout << "Playlist \"" << nombre << "\" eliminada.\n";
    } else {
        std::cout << "La playlist \"" << nombre << "\" no existe.\n";
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
void PlaylistManager::guardarPlaylist(const std::string& nombre) {
    // Crear archivo de texto para la playlist en la carpeta correcta
    std::ofstream archivo("./playlists/" + nombre + ".txt");  // Carpeta playlists/
    if (!archivo) {
        std::cerr << "No se pudo guardar la playlist " << nombre << std::endl;
        return;
    }

    // Guardar las canciones de la playlist en el archivo
    BTree* playlist = obtenerPlaylist(nombre);
    if (playlist) {
        std::vector<Cancion> canciones;
        playlist->getSongsByYear(0, canciones); // Obtener todas las canciones
        for (const auto& cancion : canciones) {
            archivo << cancion.order_id << ";" 
                    << cancion.artist_name << ";" 
                    << cancion.track_name << ";" 
                    << cancion.track_id << ";" 
                    << cancion.popularity << ";" 
                    << cancion.year << "\n";
        }
        archivo.close();
    }
}


void PlaylistManager::cargarPlaylists() {
    const std::string directory = "./playlists/";  // Carpeta específica para las playlists
    std::filesystem::create_directory(directory);  // Crear la carpeta si no existe

    for (const auto& entry : std::filesystem::directory_iterator(directory)) {
        if (entry.path().extension() == ".txt") {
            std::string playlistName = entry.path().stem().string(); 

            // Si la playlist no existe, la crea
            if (playlists.find(playlistName) == playlists.end()) {
                crearPlaylist(playlistName, 5); 
            }

            // Cargar las canciones desde el archivo de la playlist
            std::ifstream archivo(entry.path());
            if (archivo) {
                std::string linea;
                while (std::getline(archivo, linea)) {
                    std::stringstream ss(linea);
                    Cancion cancion;
                    std::string temp;

                    // Cargar cada campo de la canción desde el archivo
                    std::getline(ss, temp, ';');
                    cancion.order_id = std::stoi(temp);
                    std::getline(ss, cancion.artist_name, ';');
                    std::getline(ss, cancion.track_name, ';');
                    std::getline(ss, cancion.track_id, ';');
                    std::getline(ss, temp, ';');
                    cancion.popularity = std::stoi(temp);
                    std::getline(ss, temp);
                    cancion.year = std::stoi(temp);

                    // Insertar la canción en la playlist
                    BTree* playlist = obtenerPlaylist(playlistName);
                    if (playlist) {
                        playlist->insert(cancion);
                    }
                }
                archivo.close();
            }
        }
    }
}


void PlaylistManager::crearPlaylist(const std::string& nombre, int grado) {
    if (playlists.find(nombre) != playlists.end()) {
        std::cerr << "La playlist " << nombre << " ya existe." << std::endl;
        return;
    }
    playlists[nombre] = BTree(grado);
    guardarPlaylist(nombre);
}
BTree* PlaylistManager::obtenerPlaylist(const std::string& nombre) {
    auto it = playlists.find(nombre);
    if (it != playlists.end()) {
        return &it->second;
    }
    return nullptr;
}

Cancion buscarCancionEnBaseDatos(const std::string& termino) {
    std::ifstream archivo("canciones.csv");
    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir la base de datos (canciones.csv).\n";
        return Cancion();
    }

    std::vector<Cancion> resultados;
    std::string linea;
    
    getline(archivo, linea); // Leer cabecera

    while (getline(archivo, linea)) {
        std::stringstream ss(linea);
        Cancion cancion;
        std::string temp;

        // Leer los datos de la canción, similares a como se hace en cargarCancionesDesdeCSV
        getline(ss, temp, ',');  // Orden ID
        cancion.order_id = std::stoi(temp);
        
        getline(ss, cancion.artist_name, ',');
        getline(ss, cancion.track_name, ',');
        getline(ss, cancion.track_id, ',');
        
        // Leer popularidad y año
        ss >> cancion.popularity;
        ss.ignore();
        ss >> cancion.year;
        ss.ignore();

        // Verificar si la canción cumple con el término de búsqueda
        if (cancion.artist_name.find(termino) != std::string::npos || 
            cancion.track_name.find(termino) != std::string::npos) {
            resultados.push_back(cancion);
        }
    }

    archivo.close();

// Asumiendo que tienes la función para buscar y agregar canciones
if (resultados.size() > 1) {
    std::cout << "Se encontraron varias coincidencias:\n";
    for (size_t i = 0; i < resultados.size(); ++i) {
        std::cout << i + 1 << ". " << resultados[i].track_name
                  << " - " << resultados[i].artist_name << "\n";
    }

    int opcion;
    std::cout << "Seleccione el número de la canción que desea añadir: ";
    std::cin >> opcion;

    if (opcion < 1 || opcion > static_cast<int>(resultados.size())) {
        std::cerr << "Selección inválida.\n";
        return Cancion();
    }

    // Obtenemos la canción seleccionada
    Cancion selectedSong = resultados[opcion - 1];

    // Abre el archivo de la playlist en modo append
    std::ofstream playlistFile("ID_Folk.txt", std::ios::app);  // Cambia "ID_Folk.txt" por el nombre correcto de tu playlist
    
    if (playlistFile.is_open()) {
        // Escribimos la información de la canción en el archivo
        playlistFile << selectedSong.order_id << ","
                     << selectedSong.artist_name << ","
                     << selectedSong.track_name << ","
                     << selectedSong.track_id << ","
                     << selectedSong.popularity << ","
                     << selectedSong.year << std::endl;
        playlistFile.close();  // Cerramos el archivo después de escribir
        std::cout << "Canción añadida a la playlist \"" << "ID_Folk" << "\"." << std::endl;  // Asegúrate de poner el nombre correcto
    } else {
        std::cerr << "No se pudo abrir el archivo de la playlist para agregar la canción.\n";
    }
}

    return resultados.front();
}


void PlaylistManager::agregarCancionAPlaylist(const std::string& playlistNombre) {
    BTree* playlist = obtenerPlaylist(playlistNombre);
    if (!playlist) {
        std::cerr << "La playlist \"" << playlistNombre << "\" no existe.\n";
        return;
    }

    std::cout << "Ingrese el nombre del artista o la canción a buscar: ";
    std::string termino;
    std::cin.ignore();
    std::getline(std::cin, termino);

    Cancion cancion = buscarCancionEnBaseDatos(termino);
    if (cancion.track_name.empty()) return; // Canción no encontrada o selección inválida

    playlist->insert(cancion);
    guardarPlaylist(playlistNombre);
    std::cout << "Canción añadida a la playlist \"" << playlistNombre << "\".\n";
}

void PlaylistManager::mostrarCancionesDePlaylist(const std::string& playlistNombre) {
    BTree* playlist = obtenerPlaylist(playlistNombre);
    if (!playlist) {
        std::cerr << "La playlist \"" << playlistNombre << "\" no existe.\n";
        return;
    }

    std::vector<Cancion> canciones;
    playlist->getSongsByYear(0, canciones);

    if (canciones.empty()) {
        std::cout << "La playlist \"" << playlistNombre << "\" está vacía.\n";
        return;
    }

    std::cout << "Canciones en la playlist \"" << playlistNombre << "\":\n";
    for (const auto& cancion : canciones) {
        std::cout << "- " << cancion.track_name << " - " << cancion.artist_name << "\n";
    }
}