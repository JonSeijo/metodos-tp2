#include "MetodoPotencia.h"

using namespace std;

int main() {
    // Necesario para generacion de vector aleatorio
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> randomUniforme(0, 1);

    MetodoPotencia metodoPotencia;

    // Los autovalores son 4, 2, 1
    // Los autovectores son (1, 0, -1), (1, -1, -1), (1, 0, -2)  (OJO, ESTOS SIN NORMALIZAR)
    Matriz matrizTest({
        {7, 2, 3},
        {0, 2, 0},
        {-6, -2, -2}
    });

    int repes = 40;// Un poco arbitrario, pero con 40 repeticiones converge muy bien
    vector<double> randomInicial = vectorAleatorio(3, randomUniforme, gen);
    parAutov resultTest = metodoPotencia.obtenerDominante(matrizTest, randomInicial, repes);
}