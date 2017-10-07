#ifndef MATRIZ_H
#define MATRIZ_H

#include <bits/stdc++.h>
#include "Auxiliares.h"

using namespace std;

class Matriz {
    public:
        Matriz();
        Matriz(int _cantFilas, int _cantCols);
        Matriz (vector<vector<double> > _m);

        // Representa k* (v1 * v2^t)
        Matriz(vector<double> v1, vector<double> v2, double k=1);

        vector<double> multiplicarPorVector(const vector<double> &x);
        void multiplicarPorVector(const vector<double> &x, vector<double> &rta);

        Matriz resta(Matriz m2);
        Matriz traspuesta();

        double elemento(int f, int c);
        void asignar(int f, int c, double valor);

        int cantFilas();
        int cantCols();

        vector<vector<double> > m;

    private:
        int filas, columnas;

        void mostrar(std::ostream& os) const{
            os << std::endl;
            if(filas == 0 || columnas == 0){
                os << "[]" << std::endl;
                return;
            }

            for(int i = 0; i < filas; i++){
                for(int j = 0; j < columnas; j++){
                    // os << (m[i][j] >= 0 ? " " : "");
                    //os << std::fixed << std::setprecision(4) << m[i][j] << " ";
                    // if (m[i][j] == 0) {
                        // os << "   ";
                    // } else {
                        os << std::fixed << std::setprecision(4) << m[i][j] << (m[i][j] > 9 ? " " : "  " );
                    // }
                }
                os << std::endl;
            }
            os << std::endl;
        }

        friend std::ostream& operator<<(std::ostream& os, const Matriz &c){
            c.mostrar(os);
            return os;
        };
};

#endif