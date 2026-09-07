// 02_tipos_fundamentales.cpp
// Objetivo: repasar los tipos basicos de C++, sizeof, y una enumeracion.

#include <iostream>

// Una enumeracion da nombre a un conjunto cerrado de valores relacionados.
// Es preferible a usar numeros "magicos" sueltos por el codigo.
enum Cardinal { NORTE, ESTE, SUR, OESTE };

// Dado un punto cardinal, devuelve el siguiente girando en sentido horario.
Cardinal siguienteEnSentidoHorario(Cardinal actual) {
    switch (actual) {
        case NORTE: return ESTE;
        case ESTE:  return SUR;
        case SUR:   return OESTE;
        case OESTE: return NORTE;
    }
    return NORTE; // nunca deberia llegar aqui
}

const char* nombreDe(Cardinal c) {
    switch (c) {
        case NORTE: return "Norte";
        case ESTE:  return "Este";
        case SUR:   return "Sur";
        case OESTE: return "Oeste";
    }
    return "?";
}

int main() {
    bool activo = true;
    char inicial = 'A';
    short pequenio = 100;
    int entero = 123456;
    long grande = 3141592653L;
    float simple = 3.14f;
    double doble = 3.14159265358979;

    std::cout << "bool activo    = " << activo   << " (ocupa " << sizeof(bool)   << " bytes)\n";
    std::cout << "char inicial   = " << inicial  << " (ocupa " << sizeof(char)   << " bytes)\n";
    std::cout << "short pequenio = " << pequenio << " (ocupa " << sizeof(short)  << " bytes)\n";
    std::cout << "int entero     = " << entero   << " (ocupa " << sizeof(int)    << " bytes)\n";
    std::cout << "long grande    = " << grande   << " (ocupa " << sizeof(long)   << " bytes)\n";
    std::cout << "float simple   = " << simple   << " (ocupa " << sizeof(float)  << " bytes)\n";
    std::cout << "double doble   = " << doble    << " (ocupa " << sizeof(double) << " bytes)\n";

    std::cout << "\n--- Enumeracion Cardinal ---\n";
    Cardinal direccion = ESTE;
        
    for (int i = 0; i < 5; i++) {
        std::cout << "Direccion actual: " << nombreDe(direccion) << '\n';
        direccion = siguienteEnSentidoHorario(direccion);
    }

    return 0;
}
