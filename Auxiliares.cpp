#include "Auxiliares.h"

void debug(vector<double> &v, string texto) {
    cout << texto << " ";
    for (int i = 0; i < (int)v.size(); i++) {
        cout << fixed << setprecision(8) << v[i] << " ";
    }
    cout << "\n";
}

void debug(double d, string texto) {
    cout << texto << " " << d << "\n";
}

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

void dividirPorCte(vector<double> &v, double cte){
    for(unsigned int i = 0; i < v.size(); i++){
        v[i] /= cte;
    }
}

vector<double> vectorAleatorio(int tam, std::uniform_real_distribution<double> &distribucion, std::mt19937 &generador) {
    vector<double> rta(tam);
    for (int i = 0; i < tam; i++) {
        rta[i] = distribucion(generador);
    }
    return rta;
}