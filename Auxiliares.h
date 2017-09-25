#ifndef AUXILIARES_H
#define AUXILIARES_H

#include <bits/stdc++.h>

using namespace std;

const double EPSILON = 1e-9;

void debug(vector<double> &v, string texto="");
void debug(double d, string texto="");

double productoPunto(const vector<double> &v1, const vector<double> &v2);

double Norma2(const vector<double> &v);

// Devuelve un nuevo vector multiplicado por la ce
vector<double> multiplicarPorCte(const vector<double> &v, double cte);

vector<double> vectorAleatorio(int tam, std::uniform_real_distribution<double> &distribucion, std::mt19937 &generador);

#endif