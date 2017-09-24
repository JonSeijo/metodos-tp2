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

        vector<double> multiplicarPorVector(vector<double> x);

    private:
        int filas, columnas;
        vector<vector<double> > m;
};

#endif