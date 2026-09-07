// 10_stl_vector_string.cpp
// Objetivo: practicar std::vector y std::string, dos piezas centrales
// de la Biblioteca Estandar de Plantillas (STL).

#include <algorithm>   // std::sort
#include <iostream>
#include <string>
#include <vector>

int main() {
    // --- std::vector ---
    std::vector<int> numeros;              // vector vacio
    for (int i = 1; i <= 5; i++) {
        numeros.push_back(i * i);          // añade al final
    }

    std::cout << "Cuadrados: ";
    for (int n : numeros) {                // bucle basado en rango
        std::cout << n << ' ';
    }
    std::cout << "\nTamanio: " << numeros.size() << '\n';

    numeros.at(0) = 1000;                  // acceso con comprobacion de limites
    std::cout << "Tras modificar numeros.at(0): " << numeros[0] << '\n';

    // --- std::string ---
    std::string nombre = "Ada";
    std::string saludo = "Hola, " + nombre + "!";
    std::cout << "\n" << saludo << '\n';
    std::cout << "Longitud: " << saludo.size() << '\n';
    std::cout << "Posicion de 'Ada': " << saludo.find("Ada") << '\n';

    // --- Vector de strings + ordenacion ---
    std::vector<std::string> nombres = {"Turing", "Lovelace", "Hopper", "Knuth"};

    std::cout << "\nAntes de ordenar:\n";
    for (const std::string& n : nombres) {
        std::cout << "  " << n << '\n';
    }

    std::sort(nombres.begin(), nombres.end());

    std::cout << "Despues de ordenar alfabeticamente:\n";
    for (const std::string& n : nombres) {
        std::cout << "  " << n << '\n';
    }

    return 0;
}
