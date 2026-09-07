// 09_amistad_entre_clases.cpp
// Objetivo: ilustrar el uso de "friend" para permitir que una funcion
// (o clase) externa acceda a los miembros privados de una clase.
// Se usa con moderacion: normalmente para operadores de E/S o
// para un par de clases muy estrechamente relacionadas.

#include <iostream>

class Vector2D {
public:
    Vector2D(double x, double y) : x_(x), y_(y) {}

    // Declaramos el operador << como friend: necesita acceder a x_ e y_,
    // pero no puede definirse como metodo miembro porque el operando
    // izquierdo (ostream) no es un Vector2D.
    friend std::ostream& operator<<(std::ostream& out, const Vector2D& v);

    // Tambien concedemos amistad a una clase entera relacionada: Matriz2x2.
    friend class Matriz2x2;

private:
    double x_, y_;
};

std::ostream& operator<<(std::ostream& out, const Vector2D& v) {
    out << "(" << v.x_ << ", " << v.y_ << ")";
    return out;
}

class Matriz2x2 {
public:
    Matriz2x2(double a, double b, double c, double d)
        : a_(a), b_(b), c_(c), d_(d) {}

    // Gracias a la amistad declarada en Vector2D, podemos acceder
    // directamente a v.x_ y v.y_ desde aqui.
    Vector2D multiplicar(const Vector2D& v) const {
        double nuevoX = a_ * v.x_ + b_ * v.y_;
        double nuevoY = c_ * v.x_ + d_ * v.y_;
        return Vector2D(nuevoX, nuevoY);
    }

private:
    double a_, b_, c_, d_;
};

int main() {
    Vector2D v(3.0, 4.0);
    std::cout << "Vector original: " << v << '\n';

    Matriz2x2 identidadEscalada(2, 0, 0, 2);   // escala por 2
    Vector2D resultado = identidadEscalada.multiplicar(v);
    std::cout << "Vector escalado: " << resultado << '\n';

    return 0;
}
