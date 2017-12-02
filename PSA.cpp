#include "PSA.h"
#include "Auxiliares.h"

// PSA::PSA(vector<vector<double> > X, int alpha) {
PSA::PSA(Matriz &X, int alpha, int itersMetodoPotencia) {

    tam = X.cantFilas();

    // cout << "PSA: Calculando la matriz de covarianza..\n";
    MatrizCovarianza MX(X);

    media = MX.media;

    // cout << "PSA: Diagonalizando..\n";
    this->V = MX.Diagonalizar(alpha, itersMetodoPotencia);
}

void PSA::cargarCambioDeBase(Matriz &_V, vector<double> _media, int _tam) {
    this->V = {_V, {}};
    this->media = _media;
    this->tam = _tam;
}

void PSA::Transformar(const vector<double> &orig, vector<double> &rta) {

    vector<double> x(orig);

    // Restar media y dividir por sqrt(n-1)
    restarVector(x, media);
    dividirPorCte(x, sqrt(tam - 1));

    (this->V.first).multiplicarPorVector(x, rta);
}