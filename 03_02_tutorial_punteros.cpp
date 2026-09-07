/*
 * Tutorial Completo de Punteros en C++
 * Universidad de Sevilla - ETSI Informática
 * 
 * Se mantienen los punteros "crudos" a proposito, porque el objetivo es entender la memoria a bajo
 * nivel. La alternativa moderna (std::vector, std::unique_ptr) se comenta
 * al final de cada seccion relevante.
 */

#include <iostream>
#include <iomanip>

void ejemplo_basico() {
    std::cout << "=== 1. Punteros Basicos ===\n\n";

    int a = 5;
    float f=3.14f;
    int array[2] = {10, 20};
    /* ¿Por qué no puedo hacer int* array={10,20};?  
    Porque el compilador no sabe cuántos elementos hay en la lista de inicialización. En cambio, con int array[2]={10,20}; le decimos que hay 2 elementos y el compilador lo acepta.
    Las llaves {10, 20} solo tienen sentido cuando se está creando almacenamiento para varios elementos: 
    un array (int arr[]={10,20}) o una reserva dinámica (new int[2]{10,20}). 
    Un int* a secas no crea ese almacenamiento —solo guarda una dirección—, así que no hay huecos que rellenar y el compilador lo rechaza. 
    Un puntero puede apuntar a varios valores, pero no contenerlos.
    */
    int* ptr = &a;

    std::cout << "Valor de a: " << a << '\n';
    std::cout << "Direccion de a: " << static_cast<void*>(&a) << '\n'; //Este casting es por seguridad, no es estrictamente necesario, pero evita warnings en compiladores estrictos. Sí es importante con char* porque puede interpretarse como cadena de caracteres.
    std::cout << "Direccion de f: " << static_cast<void*>(&f) << '\n';
    std::cout << "Direccion de array[0]: " << static_cast<void*>(array) << '\n';
    std::cout << "Direccion de array[1]: " << static_cast<void*>(array+1) << '\n';
    std::cout << "Valor de ptr (direccion que guarda): " << static_cast<void*>(ptr) << '\n';
    std::cout << "Valor apuntado por ptr: " << *ptr << '\n';

    // Modificar a a través del puntero
    *ptr = 100;
    std::cout << "\nDespues de *ptr = 100:\n";
    std::cout << "Valor de a: " << a << '\n';
    std::cout << '\n';
}

void ejemplo_arrays() {
    std::cout << "=== 2. Punteros y Arrays ===\n\n";

    int arr[5] = {10, 20, 30, 40, 50};

    std::cout << "Acceso con indices:\n";
    for (int i = 0; i < 5; i++) {
        std::cout << "arr[" << i << "] = " << arr[i] << '\n';
    }

    std::cout << "\nAcceso con punteros:\n";
    for (int i = 0; i < 5; i++) {
        std::cout << "*(arr + " << i << ") = " << *(arr + i) << '\n';
    }

    std::cout << "\nRecorrido con puntero incremental:\n";
    int* ptr = arr;
    for (int i = 0; i < 5; i++) {
        std::cout << "Elemento " << i << ": " << *ptr
                  << " (direccion: " << static_cast<void*>(ptr) << ")\n";
        ptr++;
    }
    std::cout << '\n';
}

void ejemplo_matriz_2d() {
    std::cout << "=== 3. Matriz con Array de Punteros ===\n\n";

    const int ROWS = 3, COLS = 4;

    // Array de punteros (memoria reservada con new[])
    int** matrix = new int*[ROWS];
    for (int i = 0; i < ROWS; i++) {
        matrix[i] = new int[COLS];
    }

    // Inicializar
    int value = 1;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            matrix[i][j] = value++;
        }
    }

    // Mostrar matriz
    std::cout << "Matriz " << ROWS << "x" << COLS << ":\n";
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            std::cout << std::setw(3) << matrix[i][j] << ' ';
        }
        std::cout << '\n';
    }

    std::cout << "\nEn memoria (NO contigua):\n";
    for (int i = 0; i < ROWS; i++) {
        std::cout << "Fila " << i << " en direccion: "
                  << static_cast<void*>(matrix[i]) << '\n';
    }

    // Liberar memoria: cada new[] necesita su delete[], en orden inverso
    for (int i = 0; i < ROWS; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
    std::cout << "\nMemoria liberada correctamente.\n";
    // Alternativa moderna sin gestion manual:
    //   std::vector<std::vector<int>> matrix(ROWS, std::vector<int>(COLS));
    std::cout << '\n';
}

void ejemplo_matriz_1d() {
    std::cout << "=== 4. Matriz con Array 1D (Optimizado) ===\n\n";

    const int ROWS = 3, COLS = 4;

    // Array contiguo (un solo bloque)
    int* matrix = new int[ROWS * COLS];

    // Inicializar
    int value = 1;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            matrix[i * COLS + j] = value++;
        }
    }

    // Mostrar matriz
    std::cout << "Matriz " << ROWS << "x" << COLS << ":\n";
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            std::cout << std::setw(3) << matrix[i * COLS + j] << ' ';
        }
        std::cout << '\n';
    }

    std::cout << "\nEn memoria (CONTIGUA):\n";
    std::cout << "Toda la matriz en: " << static_cast<void*>(matrix) << '\n';
    std::cout << "Tamano total: " << ROWS * COLS * sizeof(int) << " bytes\n";

    // Mostrar direcciones consecutivas
    std::cout << "\nDirecciones consecutivas:\n";
    for (int i = 0; i < ROWS * COLS; i++) {
        std::cout << "matrix[" << i << "] = " << std::setw(2) << matrix[i]
                  << " en " << static_cast<void*>(&matrix[i]) << '\n';
    }

    delete[] matrix;
    std::cout << "\nMemoria liberada correctamente.\n";
    // Alternativa moderna sin gestion manual y tambien contigua:
    //   std::vector<int> matrix(ROWS * COLS);
    std::cout << '\n';
}

void ejemplo_peligros() {
    std::cout << "=== 5. Peligros Comunes con Punteros ===\n\n";

    // Peligro 1: Puntero no inicializado
    std::cout << "Peligro 1: Puntero no inicializado\n";
    int* ptr1 = nullptr;  // Correcto: inicializar a nullptr
    if (ptr1 != nullptr) {
        *ptr1 = 42;
    } else {
        std::cout << "  Puntero nullptr detectado, no se desreferencia.\n";
    }

    // Peligro 2: Memory leak (simulado)
    std::cout << "\nPeligro 2: Memory Leak\n";
    int* ptr2 = new int;
    *ptr2 = 100;
    std::cout << "  Valor asignado: " << *ptr2 << '\n';
    // Si NO hacemos delete ptr2, tenemos un memory leak
    delete ptr2;  // Correcto: liberamos la memoria
    std::cout << "  Memoria liberada correctamente.\n";

    // Peligro 3: Dangling pointer
    std::cout << "\nPeligro 3: Dangling Pointer\n";
    int* ptr3 = new int;
    *ptr3 = 200;
    std::cout << "  Valor antes de delete: " << *ptr3 << '\n';
    delete ptr3;
    ptr3 = nullptr;  // Correcto: asignar nullptr despues de delete
    if (ptr3 == nullptr) {
        std::cout << "  Puntero nullptr despues de delete, evita uso.\n";
    }

    // Peligro 4: Double free
    std::cout << "\nPeligro 4: Double Free\n";
    int* ptr4 = new int;
    delete ptr4;
    ptr4 = nullptr;
    // delete sobre nullptr es seguro (no hace nada), asi se evita el double free
    if (ptr4 == nullptr) {
        std::cout << "  No se hace double free porque ptr es nullptr.\n";
    }

    // Nota: en C++ moderno, std::unique_ptr libera la memoria de forma
    // automatica al salir de ambito, eliminando de raiz estos cuatro peligros:
    //   auto p = std::make_unique<int>(100);  // se libera solo, sin delete
    std::cout << '\n';
}

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void ejemplo_paso_por_referencia() {
    std::cout << "=== 6. Paso por Referencia con Punteros ===\n\n";
    int x = 10, y = 20;
    std::cout << "Antes: x = " << x << ", y = " << y << '\n';
    swap(&x, &y);
    std::cout << "Despues: x = " << x << ", y = " << y << '\n';
    // En C++ existen las referencias, que evitan trabajar con direcciones:
    //   void swap(int& a, int& b) { int t = a; a = b; b = t; }
    //   swap(x, y);   // sin &, mas legible
    // Y la biblioteca estandar ya ofrece std::swap(x, y).
    std::cout << '\n';
}

void ejemplo_char_especial() {
    std::cout << "=== 7. Por que char* es especial al imprimir ===\n\n";

    // std::cout NO tiene una sobrecarga de operator<< para "puntero generico".
    // Tiene una para const void* (imprime la DIRECCION) y otra especifica para
    // char* / const char* (imprime la CADENA hasta el primer '\0').

    int x = 42;
    int* pi = &x;
    std::cout << "int*  -> se convierte a void*, imprime la DIRECCION:\n";
    std::cout << "  con cast : " << static_cast<void*>(pi) << '\n';
    std::cout << "  sin cast : " << pi << "   (identico: no hay sobrecarga para int*)\n";

    char c = 'A';
    char* pc = &c;  // apunta a UN char suelto, NO a una cadena terminada en '\0'
    std::cout << "\nchar* -> gana la sobrecarga de cadena, NO imprime la direccion:\n";
    std::cout << "  con cast : " << static_cast<void*>(pc) << "   (la direccion)\n";
    std::cout << "  sin cast : ";
    std::cout << pc;  // comportamiento indefinido: lee memoria hasta topar un '\0'
    std::cout << "   <- intenta leerlo como cadena (basura / UB)\n";

    // Moraleja: para imprimir la direccion de un char* el cast a void* es
    // OBLIGATORIO; para el resto de punteros es solo una buena costumbre.
    std::cout << '\n';
}

int main() {
    std::cout << "==============================================================\n";
    std::cout << "     TUTORIAL COMPLETO DE PUNTEROS EN C++\n";
    std::cout << "     Universidad de Sevilla - ETSI Informatica\n";
    std::cout << "==============================================================\n\n";

    ejemplo_basico();
    ejemplo_arrays();
    ejemplo_matriz_2d();
    ejemplo_matriz_1d();
    ejemplo_peligros();
    ejemplo_paso_por_referencia();
    ejemplo_char_especial();

    std::cout << "==============================================================\n";
    std::cout << "                  FIN DEL TUTORIAL\n";
    std::cout << "==============================================================\n";

    return 0;
}
