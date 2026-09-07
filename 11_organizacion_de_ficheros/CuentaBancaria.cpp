// CuentaBancaria.cpp
// Fichero fuente: contiene la implementacion (el cuerpo) de las funciones
// declaradas en CuentaBancaria.h

#include "CuentaBancaria.h"
#include <iostream>

CuentaBancaria::CuentaBancaria(const std::string& titular, double saldoInicial) {
    titular_ = titular;
    saldo_ = saldoInicial;
}

bool CuentaBancaria::ingresar(double cantidad) {
    if (cantidad <= 0) {
        return false;   // operacion invalida
    }
    saldo_ += cantidad;
    return true;
}

bool CuentaBancaria::retirar(double cantidad) {
    if (cantidad <= 0 || cantidad > saldo_) {
        return false;   // fondos insuficientes o cantidad invalida
    }
    saldo_ -= cantidad;
    return true;
}

std::ostream& operator<<(std::ostream& out, const CuentaBancaria& cuenta) {
    out << "Cuenta de " << cuenta.titular()
        << " | saldo: " << cuenta.saldo();
    return out;
}
