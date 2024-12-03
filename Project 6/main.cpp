#include "playlist.h"
#include <fstream>
#include <sstream>
#ifdef _WIN32
#include <windows.h>
#endif

std::string usuario = "Edson";

void mostrarBienvenida() {
    std::cout << "\033[1mBienvenido a Apple Music, " << usuario << "!\033[0m" << std::endl;
    std::cout << "Presiona Enter para continuar..." << std::endl;
}

void cargarCancionesDesdeCSV(const std::string &filename, BTree &tree, int &ultimoOrderID) {
    std::ifstream file(filename);
    std::string line;
    getline(file, line); // Leer cabecera

    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string order;
        Cancion c;

        getline(ss, order, ',');  
        c.order_id = std::stoi(order);
        if (c.order_id > ultimoOrderID) ultimoOrderID = c.order_id;

        getline(ss, c.artist_name, ',');
        getline(ss, c.track_name, ',');
        getline(ss, c.track_id, ',');
        ss >> c.popularity;
        ss.ignore();
        ss >> c.year;
        ss.ignore();

        tree.insert(c);
    }
}

void agregarCancion(BTree &tree, const std::string &filename, int &ultimoOrderID) {
    Cancion nuevaCancion;
    std::cout << "Ingrese el nombre del artista: ";
    std::getline(std::cin, nuevaCancion.artist_name);
    std::cout << "Ingrese el nombre de la canción: ";
    std::getline(std::cin, nuevaCancion.track_name);
    std::cout << "Ingrese el ID de la canción: ";
    std::getline(std::cin, nuevaCancion.track_id);
    std::cout << "Ingrese la popularidad (0-100): ";
    std::cin >> nuevaCancion.popularity;
    std::cout << "Ingrese el año de lanzamiento: ";
    std::cin >> nuevaCancion.year;
    std::cin.ignore();

    nuevaCancion.order_id = ++ultimoOrderID;

    tree.insert(nuevaCancion);

    std::ofstream file(filename, std::ios::app);
    if (file.is_open()) {
        file << nuevaCancion.order_id << "," << nuevaCancion.artist_name << "," 
             << nuevaCancion.track_name << "," << nuevaCancion.track_id << "," 
             << nuevaCancion.popularity << "," << nuevaCancion.year << "\n";
        file.close();
    }

    std::cout << "Canción agregada exitosamente!" << std::endl;
}

void buscarCancion(BTree &tree) {
    std::string query;
    std::cout << "Ingrese término de búsqueda (nombre de canción o artista): ";
    std::getline(std::cin, query);
    tree.search(query);
}

void reproduccionAleatoria(BTree &tree) {
    std::vector<Cancion> canciones;
    BTreeNode* root = tree.getRoot();
    if (root) {
        root->collectSongs(canciones);
    }

    std::shuffle(canciones.begin(), canciones.end(), std::default_random_engine(std::random_device()()));

    int maxMostrar = std::min(15, (int)canciones.size());
    std::cout << "\nReproducción Aleatoria: Estas son las canciones que se reproducirán:" << std::endl;
    for (int i = 0; i < maxMostrar; i++) {
        std::cout << i + 1 << ". " << canciones[i].artist_name << " - " << canciones[i].track_name << std::endl;
    }
}

void submenuGestionPlaylists(PlaylistManager &manager, int &ultimoOrderID) {
    int opcionSubmenu = 0;

    while (opcionSubmenu != 5) {
        std::cout << "\n--- Submenú de Gestión de Playlists ---\n";
        std::cout << "1. Crear nueva playlist\n";
        std::cout << "2. Eliminar playlist\n";
        std::cout << "3. Mostrar playlists disponibles\n";
        std::cout << "4. Buscar y agregar canciones a una playlist\n";
        std::cout << "5. Regresar al menú principal\n";
        std::cout << "Seleccione una opción: ";
        std::cin >> opcionSubmenu;
        std::cin.ignore();

        if (opcionSubmenu == 1) {
            std::string nombre;
            std::cout << "Nombre de la nueva playlist: ";
            std::getline(std::cin, nombre);
            manager.crearPlaylist(nombre, 5);
        } else if (opcionSubmenu == 2) {
            std::string nombre;
            std::cout << "Nombre de la playlist a eliminar: ";
            std::getline(std::cin, nombre);
            manager.eliminarPlaylist(nombre);
        } else if (opcionSubmenu == 3) {
            manager.mostrarPlaylists();
        } else if (opcionSubmenu == 4) {
            std::string playlistNombre;
            std::cout << "Nombre de la playlist a la que desea agregar canciones: ";
            std::getline(std::cin, playlistNombre);

            if (manager.obtenerPlaylist(playlistNombre)) {
                manager.agregarCancionAPlaylist(playlistNombre);
            } else {
                std::cout << "La playlist \"" << playlistNombre << "\" no existe.\n";
            }
        } else if (opcionSubmenu == 5) {
            std::cout << "Regresando al menú principal...\n";
        } else {
            std::cout << "Opción no válida. Intente de nuevo.\n";
        }
    }
}

void mostrarTopCancionesPorAno(BTree& tree) {
    int year;
    std::cout << "Ingrese el año para mostrar las 100 mejores canciones: ";
    std::cin >> year;

    std::vector<Cancion> cancionesDelAno;
    tree.getSongsByYear(year, cancionesDelAno);

    std::sort(cancionesDelAno.begin(), cancionesDelAno.end(), [](const Cancion& a, const Cancion& b) {
        return a.popularity > b.popularity;
    });

    std::cout << "\nTop 100 canciones del año " << year << ":\n";
    int limite = std::min(100, (int)cancionesDelAno.size());
    for (int i = 0; i < limite; ++i) {
        const auto& cancion = cancionesDelAno[i];
        std::cout << i + 1 << ". " << cancion.track_name << " - " << cancion.artist_name 
                  << " (Popularidad: " << cancion.popularity << ")\n";
    }

    if (limite == 0) {
        std::cout << "No se encontraron canciones para el año " << year << ".\n";
    }
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

     BTree tree(5);
    int ultimoOrderID = 0;
    cargarCancionesDesdeCSV("canciones.csv", tree, ultimoOrderID); 
    PlaylistManager manager;
    manager.cargarPlaylists();
    mostrarBienvenida();
    std::cin.ignore();

    int opcion;
    do {
        std::cout << "\n--- Menú ---\n";
        std::cout << "1. Buscar canción\n";
        std::cout << "2. Agregar canción\n";
        std::cout << "3. Reproducción Aleatoria\n";
        std::cout << "4. Gestión de Playlists\n";
        std::cout << "5. Mostrar Top 100 canciones de un año\n";
        std::cout << "6. Salir\n";
        std::cout << "Seleccione una opción: ";
        std::cin >> opcion;
        std::cin.ignore();

        switch (opcion) {
            case 1:
                buscarCancion(tree);
                break;
            case 2:
                agregarCancion(tree, "canciones.csv", ultimoOrderID);
                break;
            case 3:
                reproduccionAleatoria(tree);
                break;
            case 4:
                submenuGestionPlaylists(manager, ultimoOrderID);
                break;
            case 5:
                mostrarTopCancionesPorAno(tree);
                break;
            case 6:
                std::cout << "Saliendo del programa...\n";
                break;
            default:
                std::cout << "Opción no válida. Intente de nuevo.\n";
        }
    } while (opcion != 6);

    return 0;
}

