// 06_funciones.cpp
// Objetivo: practicar paso por valor, por referencia, referencia constante
// y sobrecarga de funciones.

#include <iostream>

// Paso por valor: la copia local no afecta al argumento original.
void incrementarPorValor(int x) {
    x++;
}

// Paso por referencia: modifica directamente la variable del llamador.
/* Aquí se declara una referencia a un entero, lo que significa que x es un alias de la variable original. 
No se hace una copia, y cualquier cambio en x afectará a la variable original. 
El compilador maneja esto automáticamente, y no es necesario usar punteros ni desreferenciación explícita.
El & en int& x no es el operador de dirección: forma parte del tipo y significa "referencia a int" */
void incrementarPorReferencia(int& x) {
    x++;
}

// Intercambia dos enteros por referencias (sobrecarga 1).
void intercambiar(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

// Intercambia dos enteros usando punteros (sobrecarga 2).
void intercambiar(int* a, int* b) {
    int temp = *a; // Guarda el valor al que apunta 'a'
    *a = *b;       // Asigna el valor de 'b' a 'a'
    *b = temp;     // Asigna el valor guardado a 'b'
}

// Intercambia dos numeros reales por referencias(sobrecarga 3, mismo nombre distinta firma).
void intercambiar(double& a, double& b) {
    double temp = a;
    a = b;
    b = temp;
}

// Referencia constante: eficiente (no copia la cadena) y segura
// (el compilador impide que la modifiquemos por error).
void saludar(const char* nombre) {
    std::cout << "Hola, " << nombre << "!\n";
}

int main() {
    int n = 10;
    incrementarPorValor(n);
    std::cout << "Tras incrementarPorValor: n = " << n << " (no cambio)\n";

    incrementarPorReferencia(n);
    std::cout << "Tras incrementarPorReferencia: n = " << n << " (si cambio)\n";

    int p = 1, q = 2;
    std::cout << "\nAntes de intercambiar: p=" << p << " q=" << q << '\n';
    intercambiar(p, q);
    std::cout << "Despues de intercambiar: p=" << p << " q=" << q << '\n';
    intercambiar(&p,&q);
  	std::cout << "Despues de intercambiar: p=" << p << " q=" << q << '\n';
    
    double r = 1.5, s = 2.5;
    intercambiar(r, s);   // el compilador elige automaticamente la version double
    std::cout << "Despues de intercambiar (double): r=" << r << " s=" << s << '\n';

    saludar("Estudiante de AED I");

    return 0;
}
