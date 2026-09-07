// main.cpp
// Programa principal de prueba: usa la clase CuentaBancaria definida
// en CuentaBancaria.h / CuentaBancaria.cpp
//
// Para compilar (desde esta carpeta):
//   g++ -std=c++17 -Wall -o prueba_cuenta main.cpp CuentaBancaria.cpp
//   ./prueba_cuenta

#include "CuentaBancaria.h"
#include <iostream>

int main() {
    CuentaBancaria cuenta("Grace Hopper", 500.0);
    std::cout << cuenta << '\n';

    cuenta.ingresar(150.0);
    std::cout << "Tras ingresar 150: " << cuenta << '\n';

    bool exito = cuenta.retirar(1000.0);   // deberia fallar: fondos insuficientes
    std::cout << "Intento de retirar 1000 -> "
              << (exito ? "conseguido" : "rechazado") << '\n';

    cuenta.retirar(200.0);
    std::cout << "Tras retirar 200: " << cuenta << '\n';

    return 0;
}
