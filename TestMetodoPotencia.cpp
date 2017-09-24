#include "MetodoPotencia.h"

using namespace std;

int main() {

    MetodoPotencia metodoPotencia;

    // Los autovalores son 4, 2, 1
    // Los autovectores son (1, 0, -1), (1, -1, -1), (1, 0, -2)  (OJO, ESTOS SIN NORMALIZAR)
    Matriz matrizTest({
        {7, 2, 3},
        {0, 2, 0},
        {-6, -2, -2}
    });

    int repes = 30;
    // TODO: Hacerlo random posta ..
    vector<double> randomInicial = {4, 3, 2};

    parAutov resultTest = metodoPotencia.obtenerDominante(matrizTest, randomInicial, repes);
    debug(resultTest.first, "autovalor: ");
    debug(resultTest.second, "autovector: ");

}