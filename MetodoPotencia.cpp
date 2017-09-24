#include "MetodoPotencia.h"

parAutov MetodoPotencia::obtenerDominante(Matriz &B, vector<double> x0, int iters) {
    autovector v = x0;
    for (int i = 0; i < iters; i++) {
        vector<double> nv = B.multiplicarPorVector(v);
        double normanv = Norma2(nv);
        v = multiplicarPorCte(nv, (1.0/normanv));
    }

    // v es el autovector
    autovalor lambda = productoPunto(v, B.multiplicarPorVector(v)) / productoPunto(v, v);

    return make_pair(lambda, v);
}