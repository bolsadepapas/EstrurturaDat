#include "b_tree.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>

int main() {
    BTreeNode *root = nullptr;
    std::ifstream file("dataset.csv");

    if (!file.is_open()) {
        std::cerr << "No se pudo abrir el archivo CSV.\n";
        return 1;
    }

    std::string line;
    int count = 0;

    // Medición de tiempo para la inserción de todos los datos
    auto start_insert = std::chrono::high_resolution_clock::now();

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string pos, value;
        if (std::getline(ss, pos, ',') && std::getline(ss, value)) {
            double key = std::stod(value);  // Lee todos los decimales del valor
            insert(&root, key);
            count++;
        }
    }

    auto end_insert = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration_insert = end_insert - start_insert;
    file.close();

    std::cout << "Se han insertado " << count << " claves en el B-tree.\n";
    std::cout << "Tiempo de insercion de todos los valores: " << duration_insert.count() << " segundos.\n";

    // Solicitar al usuario el valor a buscar
    double searchValue;
    std::cout << "Ingrese el valor a buscar en el B-tree: ";
    std::cin >> searchValue;

    // Medición de tiempo para la búsqueda
    auto start_search = std::chrono::high_resolution_clock::now();
    bool found = search(root, searchValue);
    auto end_search = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration_search = end_search - start_search;

    if (found) {
        std::cout << "Valor encontrado en el B-tree.\n";
    } else {
        std::cout << "Valor no encontrado en el B-tree.\n";
    }

    std::cout << "Tiempo de busqueda: " << duration_search.count() << " segundos.\n";

    return 0;
}
