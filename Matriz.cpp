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