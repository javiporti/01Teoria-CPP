// 01_primer_programa.cpp
// Objetivo: mostrar la estructura mínima de un programa en C++:
// directivas #include, la función main, entrada/salida y el valor de retorno.

#include <cstdlib>   // EXIT_SUCCESS
#include <iostream>  // std::cin, std::cout

int main() {
    int x, y;

    std::cout << "Introduce dos numeros enteros separados por espacio: ";
    std::cin >> x >> y;

    int suma = x + y;
    double promedio = (x + y) / 2.0;   // se usa 2.0 para forzar division real
    int producto = x * y;

    std::cout << "Suma: "      << suma      << '\n';
    std::cout << "Producto: "  << producto  << '\n';
    std::cout << "Promedio: "  << promedio  << '\n';

    return EXIT_SUCCESS;   // por convencion, 0 indica que todo fue bien
}
