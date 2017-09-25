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

int Matriz::cantCols() {
    return columnas;
}

int Matriz::cantFilas() {
    return filas;
}