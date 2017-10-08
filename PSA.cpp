#include "PSA.h"
#include "Auxiliares.h"

// PSA::PSA(vector<vector<double> > X, int alpha) {
PSA::PSA(Matriz &X, int alpha) {

    tam = X.cantFilas();

    // cout << "PSA: Calculando la matriz de covarianza..\n";
    MatrizCovarianza MX(X);

    media = MX.media;

    // cout << "PSA: Diagonalizando..\n";
    this->V = MX.Diagonalizar(alpha);
}

void PSA::Transformar(const vector<double> &orig, vector<double> &rta) {

    vector<double> x(orig);

    // Restar media y dividir por sqrt(n-1)
    restarVector(x, media);
    dividirPorCte(x, sqrt(tam - 1));

    (this->V.first).multiplicarPorVector(x, rta);
}