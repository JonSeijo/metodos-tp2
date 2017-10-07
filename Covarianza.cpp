#include "Covarianza.h"
#include "MetodoPotencia.h"

// MatrizCovarianza::MatrizCovarianza(vector<vector<double> >& v) {
MatrizCovarianza::MatrizCovarianza(Matriz& datos) {
    // if(v.size() == 0 || v[0].size() == 0) {
    if(datos.cantFilas() == 0 || datos.cantCols() == 0) {
        throw std::runtime_error("Constructor covarianza: Vector no valido");
    }
/*
    for(unsigned int i = 0; i < v.size(); i++){
        if(v[i].size() != v[0].size()){
            throw std::runtime_error("Sub-vectores de distintos tamanios");
        }
    }
*/
    this-> media = calcularMedia(datos);

    // La matriz se modifica y en cada posición se le resta la media correspondiente
    this->restarMedia(datos);

    this->cov = producto_traspuesta_orig(datos);
}


vector<double> MatrizCovarianza::calcularMedia(Matriz &v){
	// vector<double> sumaTemporal(v[0].size(), 0);
	vector<double> sumaTemporal(v.cantCols(), 0);

	for(int i = 0; i < v.cantFilas(); i++){
		for(int j = 0; j < v.cantCols(); j++){
			sumaTemporal[j] += v.elemento(i, j);
		}
	}
	//Divido por cantidad de filas (datos) y devuelvo
	dividirPorCte(sumaTemporal, (double)v.cantFilas());
	return sumaTemporal;
}


void MatrizCovarianza::restarMedia(Matriz &v){
	//Resto la media que le corresponde a cada columna
	for(int i = 0; i < v.cantFilas(); i++){
		for(int j = 0; j < v.cantCols(); j++){
			v.asignar(i, j, v.elemento(i, j) - this->media[j]);
		}
	}
}


Matriz MatrizCovarianza::producto_traspuesta_orig(Matriz &v){

	int tam = v.cantCols();
	Matriz result(tam, tam);

	//Para no tener que copiar, trasponer y demás hago un producto interno
	//entre todas las columnas de la matriz original
	// ((A^t)*A)(i,j) = <Columna_i(A), Columna_j(A)>
	//Como se que el resultado va a ser una matriz simétrica, calculo de la diagonal para abajo
	// y después copio el resto



	//	TENGAN FE CIEGA, LO DE ABAJO HACE LO MISMO PERO ES EL DOBLE DE EFICIENTE

	// for(int i = 0; i < v.cantCols(); i++){
	// 	// cout << "i: " << i << "\n";
	// 	for(int j = 0; j <= i; j++){
	// 		//Recorrer por columnas hace llorar a la caché
	// 		result.asignar(i, j, v.elemento(0, i) * v.elemento(0, j));
	// 		for(int k = 1; k < v.cantFilas(); k++){
	// 			result.asignar(i, j, result.elemento(i, j) + v.elemento(k, i) * v.elemento(k, j));
	// 		}
	// 		//divido por n-1 a cada elemento
	// 		result.asignar(i, j, result.elemento(i, j)/(double)(v.cantFilas()-1));
	// 	}
	// }


	// Trasponer y hacerlo de esta manera resulta el doble de eficiente por magia de caché.
	// El costo del trasponer inicial se amortiza enseguida.
	Matriz tras = v.traspuesta();
	int cantTrasCols = tras.cantCols();
	int cantTrasFilas = tras.cantFilas();

	for(int i = 0; i < cantTrasFilas; i++) {
		for(int j = i; j < cantTrasFilas; j++) {

			double prodFila = 0;

			for(int k = 0; k < cantTrasCols; k++) {
				// prodFila += tras.elemento(i, k) * tras.elemento(j, k);
				prodFila += tras.m[i][k] * tras.m[j][k];
			}
			//divido por n-1 a cada elemento
			prodFila /= (double)(v.cantFilas()-1);

			// result.asignar(i, j, prodFila);
			result.m[i][j] = prodFila;

			// Simetria
			// result.asignar(j, i, prodFila);
			result.m[j][i] = prodFila;
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

