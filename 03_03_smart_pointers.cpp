/*
 * RAII y Smart Pointers en C++
 * Práctica 0 - Diseño de Algoritmos
 * Universidad de Sevilla - ETSI Informática
 */

#include <iostream>
#include <memory>
#include <vector>

using namespace std;

// ============= EJEMPLO 1: RAII con vector =============
void ejemplo_raii() {
    cout << "=== 1. RAII (Resource Acquisition Is Initialization) ===" << endl << endl;
    
    cout << "Creando vector con RAII..." << endl;
    {
        vector<int> arr(1000);
        arr[0] = 42;
        cout << "Vector creado y usado: arr[0] = " << arr[0] << endl;
        
        // NO necesitamos delete o free
    }  // ← Aquí se destruye automáticamente
    
    cout << "Vector destruido automáticamente al salir del scope." << endl;
    cout << "✓ Sin memory leaks!" << endl << endl;
}

// ============= EJEMPLO 2: unique_ptr =============
void ejemplo_unique_ptr() {
    cout << "=== 2. unique_ptr (Propiedad Única) ===" << endl << endl;
    
    // Crear unique_ptr
    cout << "Creando unique_ptr..." << endl;
    unique_ptr<int> ptr1 = make_unique<int>(42);
    
    cout << "Valor: " << *ptr1 << endl;
    cout << "Dirección: " << ptr1.get() << endl;
    
    // NO podemos copiar (propiedad única)
    // unique_ptr<int> ptr2 = ptr1;  // ❌ Error de compilación
    
    // Pero podemos mover
    cout << "\nMoviendo propiedad..." << endl;
    unique_ptr<int> ptr2 = move(ptr1);
    
    cout << "ptr1 ahora es: " << (ptr1 == nullptr ? "nullptr" : "válido") << endl;
    cout << "ptr2 tiene el valor: " << *ptr2 << endl;
    
    cout << "\n✓ Memoria se liberará automáticamente al salir del scope." << endl << endl;
}

// ============= EJEMPLO 3: shared_ptr =============
void ejemplo_shared_ptr() {
    cout << "=== 3. shared_ptr (Propiedad Compartida) ===" << endl << endl;
    
    cout << "Creando shared_ptr..." << endl;
    shared_ptr<int> ptr1 = make_shared<int>(100);
    
    cout << "ptr1 = " << *ptr1 << ", ref_count = " << ptr1.use_count() << endl;
    
    {
        cout << "\nEntrando a un scope interno..." << endl;
        shared_ptr<int> ptr2 = ptr1;  // Compartir
        
        cout << "ptr1 = " << *ptr1 << ", ref_count = " << ptr1.use_count() << endl;
        cout << "ptr2 = " << *ptr2 << ", ref_count = " << ptr2.use_count() << endl;
        
        *ptr2 = 200;  // Modificar
        cout << "\nDespués de modificar ptr2:" << endl;
        cout << "ptr1 = " << *ptr1 << " (mismo objeto)" << endl;
        
    }  // ptr2 destruido aquí
    
    cout << "\nDespués de salir del scope:" << endl;
    cout << "ptr1 = " << *ptr1 << ", ref_count = " << ptr1.use_count() << endl;
    
    cout << "\n✓ Memoria se liberará cuando ref_count llegue a 0." << endl << endl;
}

// ============= EJEMPLO 4: Comparación con C =============
void ejemplo_comparacion_con_c() {
    cout << "=== 4. Comparación: C vs C++ ===" << endl << endl;
    
    cout << "--- Versión C (Manual) ---" << endl;
    cout << "int *arr = (int *)malloc(100 * sizeof(int));" << endl;
    cout << "// ... usar arr ..." << endl;
    cout << "free(arr);  // ⚠️ Fácil de olvidar!" << endl;
    
    cout << "\n--- Versión C++ (Automático) ---" << endl;
    cout << "vector<int> arr(100);" << endl;
    cout << "// ... usar arr ..." << endl;
    cout << "// ✓ Destructor automático, sin free necesario" << endl << endl;
}

// ============= EJEMPLO 5: Matriz con unique_ptr =============
void ejemplo_matriz_smart_ptr() {
    cout << "=== 5. Matriz con Smart Pointers ===" << endl << endl;
    
    const int ROWS = 3, COLS = 4;
    
    // Array de unique_ptrs
    cout << "Creando matriz con unique_ptr..." << endl;
    auto matrix = make_unique<unique_ptr<int[]>[]>(ROWS);
    for (int i = 0; i < ROWS; i++) {
        matrix[i] = make_unique<int[]>(COLS);
    }
    
    // Inicializar
    int value = 1;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            matrix[i][j] = value++;
        }
    }
    
    // Mostrar
    cout << "Matriz " << ROWS << "x" << COLS << ":" << endl;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    
    cout << "\n✓ Toda la memoria se liberará automáticamente." << endl << endl;
}

// ============= EJEMPLO 6: Clase con RAII =============
class ResourceManager {
private:
    int *data;
    size_t size;
    
public:
    // Constructor (adquiere recurso)
    ResourceManager(size_t n) : size(n) {
        cout << "  Constructor: Adquiriendo " << size << " enteros" << endl;
        data = new int[size];
        for (size_t i = 0; i < size; i++) {
            data[i] = i;
        }
    }
    
    // Destructor (libera recurso)
    ~ResourceManager() {
        cout << "  Destructor: Liberando " << size << " enteros" << endl;
        delete[] data;
    }
    
    // Prevenir copia (regla de los tres/cinco)
    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;
    
    // Permitir movimiento
    ResourceManager(ResourceManager&& other) noexcept 
        : data(other.data), size(other.size) {
        other.data = nullptr;
        other.size = 0;
    }
    
    int& operator[](size_t index) {
        return data[index];
    }
    
    size_t get_size() const {
        return size;
    }
};

void ejemplo_clase_raii() {
    cout << "=== 6. Clase con RAII ===" << endl << endl;
    
    cout << "Creando ResourceManager..." << endl;
    {
        ResourceManager rm(100);
        rm[0] = 42;
        cout << "  Valor asignado: rm[0] = " << rm[0] << endl;
        cout << "  Tamaño: " << rm.get_size() << endl;
    }  // Destructor llamado automáticamente aquí
    
    cout << "\n✓ Recurso liberado automáticamente." << endl << endl;
}

// ============= EJEMPLO 7: Ventajas de C++ Moderno =============
void ejemplo_ventajas() {
    cout << "=== 7. Ventajas de C++ Moderno ===" << endl << endl;
    
    cout << "✓ RAII: Adquisición = Inicialización, Liberación = Destrucción" << endl;
    cout << "✓ Smart pointers: Evitan memory leaks y dangling pointers" << endl;
    cout << "✓ unique_ptr: Propiedad única, zero overhead" << endl;
    cout << "✓ shared_ptr: Propiedad compartida, reference counting" << endl;
    cout << "✓ No más malloc/free manual" << endl;
    cout << "✓ Exception safety automática" << endl;
    cout << "✓ Más seguro que C, igual de rápido" << endl << endl;
}

int main() {
    cout << "╔════════════════════════════════════════════════════════════╗" << endl;
    cout << "║        RAII Y SMART POINTERS EN C++                       ║" << endl;
    cout << "║        Práctica 0 - Diseño de Algoritmos                  ║" << endl;
    cout << "║        Universidad de Sevilla - ETSI Informática          ║" << endl;
    cout << "╚════════════════════════════════════════════════════════════╝" << endl << endl;
    
    ejemplo_raii();
    ejemplo_unique_ptr();
    ejemplo_shared_ptr();
    ejemplo_comparacion_con_c();
    ejemplo_matriz_smart_ptr();
    ejemplo_clase_raii();
    ejemplo_ventajas();
    
    cout << "╔════════════════════════════════════════════════════════════╗" << endl;
    cout << "║                    FIN DEL TUTORIAL                        ║" << endl;
    cout << "╚════════════════════════════════════════════════════════════╝" << endl;
    
    return 0;
}
