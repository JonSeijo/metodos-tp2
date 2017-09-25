#include "Matriz.h"

Matriz::Matriz() {
    this->filas = 0;
    this->columnas = 0;
}

Matriz::Matriz(int _cantFilas, int _cantCols) {
    this->filas = _cantFilas;
    this->columnas = _cantCols;
    this->m = vector<vector<double> > (_cantFilas, vector<double> (_cantCols, 0));
}

Matriz::Matriz(vector<vector<double>> _m) {
    this->m = _m;
    this->filas = m.size();
    this->columnas = filas != 0 ? m[0].size() : 0;
}

// Representa k* (v1 * v2^t). k=1 por defecto.
Matriz::Matriz(vector<double> v1, vector<double> v2, double k) {
    this->filas = v1.size();
    this->columnas = v2.size();
    m.resize(this->filas, vector<double>(this->columnas));

    for (int f = 0; f < filas; f++) {
        for (int c = 0; c < columnas; c++) {
            m[f][c] = k * v1[f] * v2[c];
        }
    }
}

Matriz Matriz::resta(Matriz m2) {
    if (m2.cantFilas() != filas || m2.cantCols() != columnas) {
        cerr << "ERROR - Matriz::resta: No puedo restas dos matrices de diferente tamaño\n";
    }

    Matriz mrta(filas, columnas);
    for (int f = 0; f < filas; f++) {
        for (int c = 0; c < columnas; c++) {
            mrta.asignar(f, c, m[f][c] - m2.elemento(f, c));
        }
    }
    return mrta;
}

// Devuelve un vector con el producto
vector<double> Matriz::multiplicarPorVector(vector<double> x) {
    if (columnas != x.size()) {
        cerr << "MALAS DIMENSIONES: PRODUCTO POR VECTOR INDEFINIDO\n";
    }

    vector<double> rta(this->filas, 0);

    for (int f = 0; f < filas; f++) {
        double suma = 0;
        for (int i = 0; i < columnas; i++) {
            suma += m[f][i] * x[i];
        }
        rta[f] = suma;
    }

    return rta;
}

double Matriz::elemento(int f, int c) {
    if (f >= filas || c >= columnas) {
        cerr << "ERROR: Matriz::elemento: no puedo acceder a elemento inexistente\n";
    }
    return m[f][c];
}

void Matriz::asignar(int f, int c, double valor) {
    if (f >= filas || c >= columnas) {
        cerr << "ERROR: Matriz::asignar: no puedo acceder a elemento inexistente\n";
    }
    m[f][c] = valor;
}

int Matriz::cantCols() {
    return columnas;
}

int Matriz::cantFilas() {
    return filas;
}