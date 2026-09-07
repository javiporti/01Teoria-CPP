#include <iostream>
using namespace std;

class Persona {
    private:
        string nombre;
        int edad;
    
    public:
        Persona(string n, int e) : nombre(n), edad(e) {}  // constructor
        /*Importante: Con la lista de inicialización, cada miembro se construye directamente con su valor final. Un solo paso.
        Con la asignación en el cuerpo, 
        Persona(string n, int e) {
            nombre = n;   // asignación
            edad = e;     // asignación
        }
        Ocurren dos pasos: 
         1º el miembro se construye con su valor por defecto (al entrar al constructor, antes de la primera llave), 
         2º luego lo sobreescribes con =.
        */
    
        string getNombre() const { return nombre; }
        /*const al final de la función indica que no modificará el objeto, lo que permite llamar a esta función en objetos const.
        No se podrán tocar los atributos de la clase ni llamar a funciones no const desde esta función.
        */
        int getEdad() const { return edad; }
    
        void cumplirAños() { edad++; }
    
        void saludar() const {
            cout << "Hola, soy " << nombre << " y tengo " << edad << " años." << endl;
        }
};

int main() {
    Persona p("Ana", 20); // objeto creado en el stack
 
    p.saludar();          // Hola, soy Ana y tengo 20 años.
    p.cumplirAños();
    p.saludar();          // Hola, soy Ana y tengo 21 años.
 
    return 0;
}
