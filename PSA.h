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
        PSA(Matriz &X, int alpha, int itersMetodoPotencia);

        PSA(){};

        void cargarCambioDeBase(Matriz &_V, vector<double> media, int tam);

        // vector<double> Transformar(const vector<double> &x);
        void Transformar(const vector<double> &x, vector<double> &rta);

        // Matriz V del cambio de base
        pair<Matriz, vector<autovalor> > V;

    private:

        vector<double> media;
        int tam;
};


#endif