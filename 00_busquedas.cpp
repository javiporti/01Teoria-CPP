// busquedas.cpp
// Objetivo: comparar busqueda lineal y binaria contando cuantas veces
// cada algoritmo examina un elemento del array. Asi se ve de forma
// empirica la diferencia entre O(n) (lineal) y O(log n) (binaria).

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

// Cada version recibe una referencia 'comparaciones' que se incrementa
// una vez por cada elemento del array que se compara con el objetivo.

int busquedaLineal(const int datos[], int tam, int obj, int& comparaciones) {
    comparaciones = 0;
    for (int i = 0; i < tam; i++) {
        comparaciones++;              // examinamos datos[i]
        if (datos[i] == obj) return i;
    }
    return -1;
}

int busquedaBinaria(const int datos[], int tam, int obj, int& comparaciones) {
    comparaciones = 0;
    int izq = 0, der = tam - 1;
    while (izq <= der) {
        int medio = izq + (der - izq) / 2;
        comparaciones++;              // examinamos datos[medio]
        if (datos[medio] == obj) return medio;
        else if (datos[medio] < obj) izq = medio + 1;
        else der = medio - 1;
    }
    return -1;
}

// Imprime una fila de la tabla comparando ambos metodos para un objetivo.
void probar(const int datos[], int tam, int obj) {
    int compLineal = 0, compBinaria = 0;
    int posL = busquedaLineal(datos, tam, obj, compLineal);
    int posB = busquedaBinaria(datos, tam, obj, compBinaria);

    // Ambos metodos deben coincidir en si el elemento existe o no.
    string encontrado = (posL == -1) ? "NO existe" : ("indice " + to_string(posL));

    cout << setw(10) << obj
         << setw(16) << encontrado
         << setw(16) << compLineal
         << setw(16) << compBinaria << '\n';

    (void)posB;  // posB solo se usa para comprobar coherencia; ver assert mental
}

int main() {
    // Array ORDENADO de 1000 pares: 2, 4, 6, ..., 2000.
    // (La busqueda binaria EXIGE que el array este ordenado.)
    const int N = 1000;
    int nums[N];
    for (int i = 0; i < N; i++) {
        nums[i] = (i + 1) * 2;   // nums[0]=2, nums[499]=1000, nums[999]=2000
    }

    cout << "Array ordenado de " << N << " elementos: 2, 4, 6, ..., " << nums[N - 1] << "\n\n";

    cout << setw(10) << "Objetivo"
         << setw(16) << "Resultado"
         << setw(16) << "Comp. lineal"
         << setw(16) << "Comp. binaria" << '\n';
    cout << string(58, '-') << '\n';

    probar(nums, N, 2);      // primer elemento  -> mejor caso lineal
    probar(nums, N, 1000);   // elemento central -> mejor caso binaria
    probar(nums, N, 2000);   // ultimo elemento  -> peor caso lineal
    probar(nums, N, 1001);   // numero impar: NO existe -> peor caso ambos
    probar(nums, N, 777);    // otro valor ausente

    cout << string(58, '-') << '\n';
    cout << "\nCota teorica del PEOR caso para N = " << N << ":\n";
    cout << "  Lineal : hasta N            = " << N << " comparaciones\n";
    cout << "  Binaria: hasta floor(log2 N)+1 = "
         << static_cast<int>(floor(log2(N))) + 1 << " comparaciones\n";

    cout << "\nObserva como la lineal oscila entre 1 y " << N
         << " segun donde este el objetivo,\n"
         << "mientras que la binaria se mantiene siempre en torno a "
         << static_cast<int>(floor(log2(N))) + 1 << ".\n";

    return 0;
}
