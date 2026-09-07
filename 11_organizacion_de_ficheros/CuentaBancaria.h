// CuentaBancaria.h
// Fichero de cabecera: declara la clase, sin implementar los metodos "grandes".
// El guardian de inclusion (#ifndef / #define / #endif) evita que este
// fichero se procese dos veces si varios .cpp lo incluyen (directa o
// indirectamente).

#ifndef CUENTA_BANCARIA_H
#define CUENTA_BANCARIA_H

#include <string>

class CuentaBancaria {
public:
    CuentaBancaria(const std::string& titular, double saldoInicial = 0.0);

    std::string titular() const { return titular_; }   // trivial: en linea
    double saldo() const { return saldo_; }             // trivial: en linea

    bool ingresar(double cantidad);          // implementadas en el .cpp
    bool retirar(double cantidad);

private:
    std::string titular_;
    double saldo_;
};

// Operador de salida declarado fuera de la clase, implementado en el .cpp
std::ostream& operator<<(std::ostream& out, const CuentaBancaria& cuenta);

#endif // CUENTA_BANCARIA_H
