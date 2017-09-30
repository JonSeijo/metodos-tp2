#include "MetodoPotencia.h"

using namespace std;

int main() {
    MetodoPotencia metodoPotencia;

    // Los autovalores son 4, 2, 1
    // Los autovectores (SIN NORMALLIZAR) son (1, 0, -1), (1, -1, -1), (1, 0, -2)
    Matriz matrizTest({
        {7, 2, 3},
        {0, 2, 0},
        {-6, -2, -2}
    });

    auto valores = metodoPotencia.deflacion(matrizTest, 3);

    // Debug
    cout << "autovalores:  ";
    for (int i = 0; i < (int)valores.size(); i++) {
        cout << valores[i].first << "  ";
    }
    cout << "\n";
}