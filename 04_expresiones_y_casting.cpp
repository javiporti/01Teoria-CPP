// 04_expresiones_y_casting.cpp
// Objetivo: practicar operadores y conversion de tipos (casting).

#include <iostream>

int main() {
    // --- Aritmetica entera vs. real ---
    int a = 7, b = 2;
    std::cout << "7 / 2 (entero)          = " << (a / b) << '\n';
    std::cout << "7 % 2 (resto)           = " << (a % b) << '\n';
    std::cout << "static_cast<double>(7)/2 = "
              << (static_cast<double>(a) / b) << '\n';

    // --- Incremento pre y post ---
    int i = 5;
    int j = i++;   // j toma 5, luego i pasa a 6
    int k = ++i;   // i pasa a 7, k toma 7
    std::cout << "\ni=" << i << " j=" << j << " k=" << k << '\n';

    // --- Cortocircuito logico ---
    int* puntero = nullptr;
    if (puntero != nullptr && *puntero > 0) {
        std::cout << "esto nunca se imprime\n";
    } else {
        std::cout << "\nEl cortocircuito evito desreferenciar un puntero nulo\n";
    }

    // --- Operador condicional (ternario) ---
    int x = 15, y = 42;
    int menor = (x < y) ? x : y;
    std::cout << "\nEl menor entre " << x << " y " << y << " es " << menor << '\n';

    // --- Asignacion compuesta ---
    double saldo = 100.0;
    saldo += 25.5;
    saldo -= 10.0;
    saldo *= 2;
    std::cout << "\nSaldo final: " << saldo << '\n';

    return 0;
}
