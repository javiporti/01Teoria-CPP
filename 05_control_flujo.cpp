// 05_control_flujo.cpp
// Objetivo: practicar if/else, switch, while, do-while, for, break y continue.

#include <iostream>

int main() {
    // --- if / else if / else ---
    int temperatura = 18;
    if (temperatura < 10) {
        std::cout << "Hace frio\n";
    } else if (temperatura < 25) {
        std::cout << "Temperatura agradable\n";
    } else {
        std::cout << "Hace calor\n";
    }

    // --- switch ---
    char opcion = 'B';
    switch (opcion) {
        case 'A':
            std::cout << "Elegiste A\n";
            break;
        case 'B':
            std::cout << "Elegiste B\n";
            break;
        default:
            std::cout << "Opcion desconocida\n";
            break;
    }

    // --- while: suma hasta encontrar un numero negativo ---
    int datos[] = {4, 8, 15, 16, -1, 23, 42};
    int idx = 0, suma = 0;
    while (idx < 7 && datos[idx] >= 0) {
        suma += datos[idx];
        idx++;
    }
    std::cout << "\nSuma antes del primer negativo: " << suma << '\n';

    // --- do-while: se ejecuta al menos una vez ---
    int contador = 0;
    do {
        std::cout << "do-while contador = " << contador << '\n';
        contador++;
    } while (contador < 3);

    // --- for: recorrido con indice ---
    std::cout << "\nCuadrados del 1 al 5:\n";
    for (int n = 1; n <= 5; n++) {
        std::cout << n << "^2 = " << n * n << '\n';
    }

    // --- break y continue ---
    std::cout << "\nNumeros del 1 al 10, saltando los pares, "
                 "y parando al llegar a 9:\n";
    for (int n = 1; n <= 10; n++) {
        if (n % 2 == 0) continue;  // salta los pares
        if (n == 9) break;         // corta el bucle al llegar a 9
        std::cout << n << ' ';
    }
    std::cout << '\n';

    return 0;
}
