#ifndef METODO_POTENCIA_H
#define METODO_POTENCIA_H

#include <bits/stdc++.h>
#include "Matriz.h"

using namespace std;

typedef double autovalor;
typedef vector<double> autovector;
typedef pair<autovalor, autovector> parAuto;

const double EPSILON = 1e-6;

class MetodoPotencia {
    public:
        pair<autovalor, autovector> obtenerDominante(
            Matriz B, vector<double> x0, int iters
        );

    private:

};

#endif