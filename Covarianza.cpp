#include "Covarianza.h"
#include "MetodoPotencia.h"



MatrizCovarianza::MatrizCovarianza(vector<vector<double> >& v) {
    if(v.size() == 0 || v[0].size() == 0) {
        throw std::runtime_error("Constructor covarianza: Vector no valido");
    }
/*
    for(unsigned int i = 0; i < v.size(); i++){
        if(v[i].size() != v[0].size()){
            throw std::runtime_error("Sub-vectores de distintos tamanios");
        }
    }
*/
    this-> media = calcularMedia(v);

    //El vector de vectores se modifica y en cada posición se le resta la media correspondiente
    restarMedia(v);
    cov = producto_traspuesta_orig(v);
}

vector<double> MatrizCovarianza::calcularMedia(vector<vector<double> >& v){
	vector<double> sumaTemporal(v[0].size());

	//Sumo todas las columnas
	for(int j = 0; j < (int)v[0].size(); j++){
		sumaTemporal[j] = v[0][j];
	}

	for(int i = 1; i < (int)v.size(); i++){
		for(int j = 0; j < (int)v.size(); j++){
			sumaTemporal[j] += v[i][j];
		}
	}
	//Divido por cantidad de filas (datos) y devuelvo
	dividirPorCte(sumaTemporal, (double)v.size());
	return sumaTemporal;
}

void MatrizCovarianza::restarMedia(vector<vector<double> >& v){
	//Resto la media que le corresponde a cada columna
	for(int i = 0; i < (int)v.size(); i++){
		for(int j = 0; j < (int)v[0].size(); j++){
			v[i][j] -= this->media[j];
		}
	}
}

Matriz MatrizCovarianza::producto_traspuesta_orig(vector<vector<double> >& v){
	Matriz result = Matriz(v[0].size(), v[0].size());
	//Para no tener que copiar, trasponer y demás hago un producto interno
	//entre todas las columnas de la matriz original
	// ((A^t)*A)(i,j) = <Columna_i(A), Columna_j(A)>
	//Como se que el resultado va a ser una matriz simétrica, calculo de la diagonal para abajo
	// y después copio el resto
	for(unsigned int i = 0; i < v[0].size(); i++){
		for(unsigned int j = 0; j <= i; j++){
			//Recorrer por columnas hace llorar a la caché
			result.asignar(i, j, v[0][i] * v[0][j]);
			for(unsigned int k = 1; k < v.size(); k++){
				result.asignar(i, j, result.elemento(i, j) + v[k][i] * v[k][j]);
			}
			//divido por n-1 a cada elemento
			result.asignar(i, j, result.elemento(i, j)/(float)(v.size()-1));
		}
	}
	//Copia de los elementos arriba de la diagonal
	for(unsigned int i = 0; i < result.cantFilas(); i++){
		for(unsigned int j = 0; j < i; j++){
			result.asignar(j, i, result.elemento(i, j));
		}
	}

	return result;
}

pair<Matriz, vector<autovalor> > MatrizCovarianza::Diagonalizar(int alpha){
	if(alpha > this->cov.cantFilas()){
		throw std::runtime_error("Alpha muy grande");
	}

	vector<vector<double> > Vect(alpha);
	vector<autovalor> D(alpha);
	MetodoPotencia m;

	vector<parAutov> result = m.deflacion(this->cov, alpha);

	for(unsigned int i = 0; i < alpha; i++){
		Vect[i] = result[i].second;
		D[i] = result[i].first;
	}

	return make_pair(Matriz(Vect), D);


}

