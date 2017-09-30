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
        MatrizCovarianza(vector<vector<double> >& v){
            if(v.size() == 0 || v[0].size() == 0){
                throw std::runtime_error("Constructor covarianza: Vector no valido");
            }
     /*
            for(unsigned int i = 0; i < v.size(); i++){
                if(v[i].size() != v[0].size()){
                    throw std::runtime_error("Sub-vectores de distintos tamanios");
                }
            }
     */  
            //El vector de vectores se modifica y en cada posición se le resta la media correspondiente
            restarMedia(v);
            cov = producto_traspuesta_orig(v);
        };

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