#include "PSA.h"

// PSA::PSA(vector<vector<double> > X, int alpha) {
PSA::PSA(Matriz &X, int alpha) {
    cout << "PSA: Empezando a calcular la matriz de covarianza..\n";
    MatrizCovarianza MX(X);
    cout << "PSA: Diagonalizando..\n";
    this->V = MX.Diagonalizar(alpha);
}

vector<double> PSA::Transformar(const vector<double> &x) {
    return (this->V.first).multiplicarPorVector(x);
}