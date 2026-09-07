// 08_clase_con_memoria_dinamica.cpp
// Objetivo: ilustrar la "regla de los tres": cuando una clase reserva
// memoria dinamica, necesita destructor, constructor de copia
// y operador de asignacion propios, o se arriesga a copias superficiales,
// fugas de memoria y punteros colgantes.

#include <iostream>

class ListaEnteros {
public:
    explicit ListaEnteros(int capacidad); //Si no ponemos explicit, el compilador permite conversiones implícitas de int a ListaEnteros.
    /* Un ejemplo: Permitiría en el main lo siguiente:
    ListaEnteros ListaMal=5;
    ListaMal.imprimir();
    */
    ListaEnteros(const ListaEnteros& otra);            // constructor de copia
    ListaEnteros& operator=(const ListaEnteros& otra);  // operador de asignacion
    ~ListaEnteros();                                    // destructor

    void establecer(int indice, int valor);
    int obtener(int indice) const;
    int tamanio() const;
    void imprimir() const;

private:
    int* datos;
    int capacidad;
};

ListaEnteros::ListaEnteros(int cap) {
    capacidad = cap;
    datos = new int[capacidad];// datos = new int[capacidad](); Esto inicializa a 0 todos los elementos del array. Otra forma de hacerlo es con un bucle for:
    for (int i = 0; i < capacidad; i++) {
        datos[i] = 0;
    }
}

// Constructor de copia: reserva memoria NUEVA y copia el contenido,
// en vez de copiar solo el puntero (lo que haria el compilador por defecto).
ListaEnteros::ListaEnteros(const ListaEnteros& otra) {
    capacidad = otra.capacidad;
    datos = new int[capacidad];
    for (int i = 0; i < capacidad; i++) {
        datos[i] = otra.datos[i];
    }
}

// Operador de asignacion: libera lo que ya tenia, reserva memoria nueva
// y copia el contenido. Comprueba la auto-asignacion (a = a).
ListaEnteros& ListaEnteros::operator=(const ListaEnteros& otra) {
    if (this != &otra) {
        delete [] datos;
        capacidad = otra.capacidad;
        datos = new int[capacidad];
        for (int i = 0; i < capacidad; i++) {
            datos[i] = otra.datos[i];
        }
    }
    return *this;
}

ListaEnteros::~ListaEnteros() {
    delete [] datos;
}

void ListaEnteros::establecer(int indice, int valor) {
    if (indice >= 0 && indice < capacidad) {
        datos[indice] = valor;
    }
}

int ListaEnteros::obtener(int indice) const {
    return datos[indice];
}

int ListaEnteros::tamanio() const {
    return capacidad;
}

void ListaEnteros::imprimir() const {
    std::cout << "[ ";
    for (int i = 0; i < capacidad; i++) {
        std::cout << datos[i] << ' ';
    }
    std::cout << "]\n";
}

int main() {
    ListaEnteros original(3);
    original=ListaEnteros(5); // Asignación de un objeto temporal

    for (int i = 0; i < original.tamanio(); i++) {
        original.establecer(i, i * 10);
    }
    std::cout << "Original: ";
    original.imprimir();

    // Constructor de copia en accion:
    ListaEnteros copia(original);
    copia.establecer(0, 999);   // modificar la copia...

    std::cout << "Original tras modificar la copia: ";
    original.imprimir();        // ...no debe afectar al original
    std::cout << "Copia: ";
    copia.imprimir();

    // Operador de asignacion en accion:
    ListaEnteros tercera(2);
    tercera = original;
    tercera.establecer(1, -1);

    std::cout << "\nOriginal tras modificar 'tercera': ";
    original.imprimir();
    std::cout << "Tercera: ";
    tercera.imprimir();

    return 0;
    // Al salir de main, se llaman automaticamente los destructores
    // de 'original', 'copia' y 'tercera', liberando cada uno su propia memoria.
}
