#include "Auxiliares.h"

double productoPunto(const vector<double> &v1, const vector<double> &v2) {
    if (v1.size() != v2.size()) {
        cerr << "PRODUCTO PUNTO MAL DEFINIDO\n";
    }

    double suma = 0;
    int n = v1.size();
    for (int i = 0; i < n; i++) {
        suma += v1[i]*v2[i];
    }
    return suma;
}

double Norma2(const vector<double> &v) {
    return sqrt(productoPunto(v, v));
}

// Devuelve un nuevo vector multiplicado por la ce
vector<double> multiplicarPorCte(const vector<double> &v, double cte) {
    int n = v.size();
    vector<double> rta(n, 0);
    for (int i = 0; i < n; i++) {
        rta[i] = v[i] * cte;
    }
    return rta;
}