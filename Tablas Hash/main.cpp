#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

class HashTable {
public:
    HashTable(int n, int (*hashFunc)(int, int)) : n(n), hashFunc(hashFunc) {
        table.resize(n);
    }

    void insertar(int x) {
        int index = hashFunc(x, n);
        table[index].push_back(x); 
    }

    void eliminar(int x) {
        int index = hashFunc(x, n);
        auto& bucket = table[index];
        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            if (*it == x) {
                bucket.erase(it); 
                break;
            }
        }
    }


    bool encontrar(int x) {
        int index = hashFunc(x, n);
        auto& bucket = table[index];
        for (int val : bucket) {
            if (val == x) {
                return true; 
            }
        }
        return false;
    }

private:
    int n; // Número de buckets
    int (*hashFunc)(int, int); // Función hash
    std::vector<std::vector<int>> table; // Tabla de buckets
};

// Función hash pseudo-aleatoria
int RandomHashFun(int x, int n) {
    // Usamos el valor de `x` como semilla para la aleatoriedad
    srand(x);
    return rand() % n; // Genera un valor aleatorio dentro del rango de los buckets
}

int main() {
    HashTable HT(10, RandomHashFun);

    // Insertar elementos
    HT.insertar(123);
    HT.insertar(76);

    // Verificar si los elementos están en la tabla
    std::cout << "Se encontro 123? " << (HT.encontrar(123) ? "Si" : "No") << std::endl;
    std::cout << "Se encontro 76? " << (HT.encontrar(76) ? "Si" : "No") << std::endl;

    // Eliminar un elemento
    HT.eliminar(123);

    // Verificar nuevamente
    std::cout << "Se encontro 123 despues de ser eliminado? " << (HT.encontrar(123) ? "Si" : "No") << std::endl;

    return 0;
}
