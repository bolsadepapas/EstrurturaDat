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

        getline(ss, order, ',');  // Leer y descartar el primer valor
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
        file << nuevaCancion.order_id << ","
             << nuevaCancion.artist_name << ","
             << nuevaCancion.track_name << ","
             << nuevaCancion.track_id << ","
             << nuevaCancion.popularity << ","
             << nuevaCancion.year << "\n";
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

void menuOrdenamiento(BTree &tree) {
    std::string criterio;
    bool asc;
    std::cout << "Seleccione el criterio de ordenamiento (popularidad, año, nombre): ";
    std::cin >> criterio;
    std::cout << "Orden ascendente (1) o descendente (0): ";
    std::cin >> asc;
    tree.sortSongs(criterio, asc);
}

main() {
    #ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    #endif

    BTree tree(5);
    int ultimoOrderID = 0;
    cargarCancionesDesdeCSV("canciones.csv", tree, ultimoOrderID);

    mostrarBienvenida();
    std::cin.ignore();

    int opcion;
    do {
        std::cout << "\n--- Menú ---\n";
        std::cout << "1. Buscar canción\n";
        std::cout << "2. Agregar canción\n";
        std::cout << "3. Reproducción Aleatoria\n";  
        std::cout << "4. Salir\n";
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
                std::cout << "Saliendo del programa...\n";
                break;
            default:
                std::cout << "Opción no válida. Intente de nuevo.\n";
        }
    } while (opcion != 4);

    return 0;
}
