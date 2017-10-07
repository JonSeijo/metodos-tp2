#ifndef COVARIANZA_H
#define COVARIANZA_H

#include "Matriz.h"
#include "Auxiliares.h"

typedef double autovalor;
typedef vector<double> autovector;
typedef pair<autovalor, autovector> parAutov;

class MatrizCovarianza{

	public:
        // Vector de vectores que se pasa por referencia, se puede cambiar.
        MatrizCovarianza(vector<vector<double> >& v);

        //Devuelve V traspuesta (LOS AUTOVECTORES ESTÁN COMO FILAS)y un vector de los autovalores que irían en la diagonal, eso no se si es
        //necesario, podría sacarse
        pair<Matriz, vector<autovalor> > Diagonalizar(int alpha);



    private:
        Matriz cov;

        vector<double> media(vector<vector<double> >& v);
        void restarMedia(vector<vector<double> >& v);
        Matriz producto_traspuesta_orig(vector<vector<double> >& v);

        friend std::ostream& operator<<(std::ostream& os, const MatrizCovarianza &c){
            c.mostrar(os);
            return os;
        };

        void mostrar(std::ostream& os) const{
            os << this->cov;
        }
};

#endif