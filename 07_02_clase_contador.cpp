// 07_clase_contador.cpp
// Objetivo: presentar una clase sencilla, con encapsulacion basica
// (miembros privados accesibles solo mediante funciones publicas).

#include <iostream>

class Contador {
public:
    Contador();                       // constructor por defecto
    explicit Contador(int inicial);   // constructor con valor inicial
    void incrementar(int paso = 1);   // metodo publico, con argumento por defecto
    void reiniciar();
    int valor() const;                // "getter": solo lectura, marcado const

private:
    int cuenta;                       // miembro de dato privado
};

Contador::Contador() {
    cuenta = 0;
}

Contador::Contador(int inicial) {
    cuenta = inicial;
}

void Contador::incrementar(int paso) {
    cuenta += paso;
}

void Contador::reiniciar() {
    cuenta = 0;
}

int Contador::valor() const {
    return cuenta;
}

int main() {
    Contador visitas;              // usa el constructor por defecto -> 0
    std::cout << "Visitas iniciales: " << visitas.valor() << '\n';

    visitas.incrementar();         // usa el paso por defecto (1)
    visitas.incrementar(5);
    std::cout << "Visitas tras incrementos: " << visitas.valor() << '\n';

    Contador puntuacion(100);      // usa el segundo constructor
    puntuacion.incrementar(-30);
    std::cout << "Puntuacion: " << puntuacion.valor() << '\n';

    puntuacion.reiniciar();
    std::cout << "Puntuacion tras reiniciar: " << puntuacion.valor() << '\n';

    // visitas.cuenta = 1000;   // ERROR de compilacion: 'cuenta' es privado

    return 0;
}
