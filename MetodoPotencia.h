#ifndef METODO_POTENCIA_H
#define METODO_POTENCIA_H

#include <bits/stdc++.h>
#include "Auxiliares.h"
#include "Matriz.h"

using namespace std;

typedef double autovalor;
typedef vector<double> autovector;
typedef pair<autovalor, autovector> parAutov;

class MetodoPotencia {
    public:
        // 40 iteraciones para converger es un poco arbitrario pero parece suficiente. Experimentar con esto.
        MetodoPotencia(int _iteracionesConvergencia=40);

        parAutov obtenerDominante(Matriz &B, vector<double> x0);
        vector<parAutov> deflacion(Matriz B, int alpha);

    private:
        int iteracionesConvergencia;
};

#endif