#include "Matriz.h"

Matriz::Matriz() {
    this->filas = 0;
    this->columnas = 0;
}

Matriz::Matriz(int _cantFilas, int _cantCols) {
    this->filas = _cantFilas;
    this->columnas = _cantCols;
    this->m.resize(_cantFilas, vector<double> (_cantCols, 0));
}

Matriz::Matriz(vector<vector<double>> _m) {
    this->m = _m;
    this->filas = m.size();
    this->columnas = filas != 0 ? m[0].size() : 0;
}

// Representa k* (v1 * v2^t). k=1 por defecto.
Matriz::Matriz(vector<double> v1, vector<double> v2, double k) {
    this->filas = v1.size();
    this->columnas = v2.size();
    m.resize(this->filas, vector<double>(this->columnas));

    for (int f = 0; f < filas; f++) {
        for (int c = 0; c < columnas; c++) {
            m[f][c] = k * v1[f] * v2[c];
        }
    }
}

Matriz Matriz::resta(Matriz m2) {
    if (m2.cantFilas() != filas || m2.cantCols() != columnas) {
        cerr << "ERROR - Matriz::resta: No puedo restas dos matrices de diferente tamaño\n";
    }

    Matriz mrta(filas, columnas);
    for (int f = 0; f < filas; f++) {
        for (int c = 0; c < columnas; c++) {
            mrta.asignar(f, c, m[f][c] - m2.elemento(f, c));
        }
    }
    return mrta;
}

// Devuelve un vector con el producto
vector<double> Matriz::multiplicarPorVector(const vector<double> &x) {
    if (columnas != x.size()) {
        cerr << "MALAS DIMENSIONES: PRODUCTO POR VECTOR INDEFINIDO\n";
    }

    vector<double> rta(this->filas, 0);

    for (int f = 0; f < filas; f++) {
        double suma = 0;
        for (int i = 0; i < columnas; i++) {
            suma += m[f][i] * x[i];
        }
        rta[f] = suma;
    }

    return rta;
}

vector<double> Matriz::calcularMedia(){
    // vector<double> sumaTemporal(v[0].size(), 0);
    vector<double> sumaTemporal(this->cantCols(), 0);

    for(int i = 0; i < this->cantFilas(); i++){
        for(int j = 0; j < this->cantCols(); j++){
            sumaTemporal[j] += this->elemento(i, j);
        }
    }
    //Divido por cantidad de filas (datos) y devuelvo
    dividirPorCte(sumaTemporal, (double)this->cantFilas());
    return sumaTemporal;
}

void Matriz::multiplicarPorVector(const vector<double> &x, vector<double> &rta) {
    if (columnas != x.size() || filas != rta.size()) {
        cerr << "MALAS DIMENSIONES: PRODUCTO POR VECTOR INDEFINIDO\n";
        cerr << "rta.size: " << rta.size() << "\n";
    }
    for (int f = 0; f < filas; f++) {
        double suma = 0;
        for (int i = 0; i < columnas; i++) {
            suma += m[f][i] * x[i];
        }
        rta[f] = suma;
    }
}

double Matriz::elemento(int f, int c) {
    if (f >= filas || c >= columnas) {
        cerr << "ERROR: Matriz::elemento: no puedo acceder a elemento inexistente:  " << f << " " << c << "\n";
        cerr << "Mi tamaño es:  " << filas << " " << columnas << "\n";
        exit (EXIT_FAILURE);
    }
    return m[f][c];
}

void Matriz::asignar(int f, int c, double valor) {
    if (f >= filas || c >= columnas) {
        cerr << "ERROR: Matriz::asignar: no puedo acceder a elemento inexistente\n";
        cerr << "Mi tamaño es:  " << filas << " " << columnas << "\n";
        exit (EXIT_FAILURE);
    }
    m[f][c] = valor;
}

//La matriz original se mantiene, y retorna otra (que es la traspuesta de la original)
Matriz Matriz::traspuesta() {
    vector<vector<double> > coeficientes(columnas, vector<double>(filas, 0));
    for(int c = 0; c < columnas; c++){
        for(int f = 0; f < filas; f++){
            coeficientes[c][f] = this->m[f][c];
        }
    }
    return Matriz(coeficientes);
}


int Matriz::cantCols() {
    return columnas;
}

int Matriz::cantFilas() {
    return filas;
}