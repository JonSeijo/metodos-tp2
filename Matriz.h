#ifndef MATRIZ_H
#define MATRIZ_H

#include <bits/stdc++.h>
#include "Auxiliares.h"

using namespace std;

class Matriz {
    public:
        Matriz();
        Matriz(int _cantFilas, int _cantCols);
        Matriz (vector<vector<double> > _m);

        // Representa k* (v1 * v2^t)
        Matriz(vector<double> v1, vector<double> v2, double k=1);

        vector<double> multiplicarPorVector(vector<double> x);

        Matriz resta(Matriz m2);

        double elemento(int f, int c);
        void asignar(int f, int c, double valor);

        int cantFilas();
        int cantCols();

    private:
        int filas, columnas;
        vector<vector<double> > m;
};

#endif