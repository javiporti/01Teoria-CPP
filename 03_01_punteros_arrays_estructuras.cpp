// 03_punteros_arrays_estructuras.cpp
// Objetivo: practicar punteros, arrays, structs y memoria dinamica.

#include <iostream>

struct Punto {
    double x;
    double y;
};

void imprimirPunto(const Punto& p) {   // referencia constante: no copia, no modifica
    std::cout << "(" << p.x << ", " << p.y << ")";
}

// Recibe un array y su tamanio; devuelve un puntero al mayor elemento.
float* direccionDelMayor(float datos[], int n) {
    std::cout << "Tamanio int datos[]:" <<datos <<"= "<<sizeof(datos)<<'\n';
    float* mejor = &datos[0];
    for (int i = 1; i < n; i++) {
        if (datos[i] > *mejor) {
            mejor = &datos[i];
        }
    }
    return mejor;
}

int main() {
    // --- Punteros basicos ---
    int x = 10;
    int* p = &x;
    std::cout << "x = " << x << ", *p = " << *p << '\n';
    *p = 20;
    std::cout << "Tras *p = 20, x vale " << x << '\n';

    // --- Arrays ---
    float notas[5] = {7, 9, 5, 9.9, 8};
    std::cout << "Tamanio notas[5]:" <<notas <<"= "<<sizeof(notas);
    std::cout << "\nNotas: ";
    for (int i = 0; i < 5; i++) {
        std::cout << notas[i] << ' ';
    }
    std::cout << '\n';

    float* mejor = direccionDelMayor(notas, 5);
    std::cout << "La mejor nota es " << *mejor << '\n';
    if (*mejor>9.5){
        *mejor=10;
    }
    std::cout << "\nNotas: ";
    for (int i = 0; i < 5; i++) {
        std::cout << notas[i] << ' ';
    }

    // --- Estructuras ---
    Punto origen = {0.0, 0.0};
    Punto destino = {3.0, 4.0};
    std::cout << "\nOrigen: ";
    imprimirPunto(origen);
    std::cout << "  Destino: ";
    imprimirPunto(destino);
    std::cout << '\n';

    Punto* pd = &destino;
    pd->x += 1.0;   // equivalente a (*pd).x += 1.0;
    std::cout << "Destino tras mover: ";
    imprimirPunto(destino);
    std::cout << '\n';

    // --- Memoria dinamica ---
    int* dinamico = new int;
    *dinamico = 99;
    std::cout << "\nValor dinamico: " << *dinamico << " tamanio de dinamico: " << sizeof(dinamico) << '\n';
    delete dinamico;   // liberar cuando ya no se necesita

    int n = 5;
    int* arrayDinamico = new int[n];
    for (int i = 0; i < n; i++) {
        arrayDinamico[i] = i * i;
    }
    std::cout << "Array dinamico: ";
    for (int i = 0; i < n; i++) {
        std::cout << arrayDinamico[i] << ' ';
    }
    std::cout << '\n';
    delete [] arrayDinamico;   // los arrays se liberan con delete[]

    return 0;
}
