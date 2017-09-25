#include "MetodoPotencia.h"

MetodoPotencia::MetodoPotencia(int _iteracionesConvergencia) {
    this->iteracionesConvergencia = _iteracionesConvergencia;
}

parAutov MetodoPotencia::obtenerDominante(Matriz &B, vector<double> x0) {
    autovector v = x0;
    for (int i = 0; i < iteracionesConvergencia; i++) {
        vector<double> nv = B.multiplicarPorVector(v);
        double normanv = Norma2(nv);
        v = multiplicarPorCte(nv, (1.0/normanv));
    }

    // v es el autovector
    autovalor lambda = productoPunto(v, B.multiplicarPorVector(v)) / productoPunto(v, v);

    return make_pair(lambda, v);
}

// Devuelve los mayores alpha autovectores
// B se modifica por eso se pasa por copia
vector<parAutov> MetodoPotencia::deflacion(Matriz B, int alpha) {
    if (alpha > B.cantFilas()) {
        cerr << "MetodoPotencia::deflacion: ALPHA MUY GRANDE. No hay tantos autovalores\n";
    }

    if (B.cantFilas() != B.cantCols()) {
        cerr << "MetodoPotencia::deflacion: QUIERO UNA MATRIZ CUADRADA\n";
    }

    // Necesario para generacion de vector aleatorio
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> randomUniforme(0, 1);

    int tamMatriz = B.cantFilas();

    vector<parAutov> rta(alpha);

    // Implementacion de metodo de deflacion, devuelve alpha autovectores
    for (int i = 0; i < alpha; i++) {
        parAutov autov_i = obtenerDominante(B, vectorAleatorio(tamMatriz, randomUniforme, gen));
        rta[i] = autov_i;
    }

    return rta;
}