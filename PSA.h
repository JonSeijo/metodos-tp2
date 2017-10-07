#ifndef _PSA_H_
#define _PSA_H_


#include "Matriz.h"
#include "Auxiliares.h"
#include "Covarianza.h"

class PSA {
    public:
        // X: matriz de datos
        // alpha: El alpha de PSAs
        // PSA(vector<vector<double> > X, int alpha);
        PSA(Matriz &X, int alpha);
        vector<double> Transformar(const vector<double> &x);

    private:
        // Matriz V del cambio de base
        pair<Matriz, vector<autovalor> > V;
};


#endif