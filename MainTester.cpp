// time ./main_test < tests/test1.in > pruebas/res_test1.txt


#include "Auxiliares.h"
#include "Covarianza.h"
#include "MetodoPotencia.h"
#include "ImageHandler.h"
#include "kNN.h"
#include "PSA.h"

typedef vector<double> imagen;

const int TIPO_KNN_SOLO = 1;
const int TIPO_KNN_PSA = 2;

int main() {


    string dataPath; cin >> dataPath;

    // @TODO: Hacer que sean parametros del ejecutable
    int tipo = TIPO_KNN_PSA;

    int k_knn;
    int alpha;
    int K_kfold;

    // Leo variables
    cin >> k_knn >> alpha >> K_kfold;

    string filepathTrain = "data/train.csv";
    string filepathTest = "data/test.csv";

    // Lo mejor seria que considere las 42000;
    int cantImagenesTrain = 42000;

    // Carga y handle de imagenes de training
    ImageHandler imageTrainHandler(filepathTrain);



    vector<vector<imagen> > folds_imagenes(K_kfold);
    vector<vector<double> > folds_labels(K_kfold);


    for (int f = 0; f < K_kfold; f++) {
        for (int i = 0; i < 42000; i++) {
            int value; cin >> value;
            if (value == 0) {
                folds_imagenes[f].push_back(imageTrainHandler.getImagen(i));
                folds_labels[f].push_back(imageTrainHandler.getLabel(i));
            }
        }
    }

    // Quiero que cada fold contenga aprox la misma cantidad de cada tipo, asi que reparto equitativamente
    // Guardo ademas su categoria original para conseguir estadisticas luego.

    vector<double> TESTOUT;

    int ITERACIONES = 3;

    for (int foldATestear = 0; foldATestear < ITERACIONES; foldATestear++) {
        cout << "testeando fold: " << foldATestear << "\n";
        //  foldATestear será el fold a testear (increible), el resto se entrena.

        // Junto todos los datos que voy a utilizar para entrenar, excepto foldATestear
        vector<int> labelsDato;
        vector<imagen> imagenesDato;
        int cantImagenesEntrenamiento = 0;

        for (int f = 0; f < K_kfold; f++) {
            if (f == foldATestear) {
                continue;
            }

            for (int j = 0; j < (int)folds_imagenes[f].size(); j++) {
                imagenesDato.push_back(folds_imagenes[f][j]);
                labelsDato.push_back(folds_labels[f][j]);
                cantImagenesEntrenamiento++;
            }
        }

        // Ya tengo los datos del fold listos para entrenarlos con el metodo elegido
        Matriz matrizDatos(imagenesDato);
        PSA psa(matrizDatos, alpha);

        for (int autov = 0; autov < alpha; autov++) {
            TESTOUT.push_back(psa.V.second[autov]);
        }

    }

    int cantIguales = 0;

    ifstream testoutfile("tests/test1.expected");
    for (int i = 0; i < alpha*ITERACIONES; i++) {
        string valor_posta;
        getline(testoutfile, valor_posta);

        double valor_real = stod(valor_posta);
        double valor_mio = TESTOUT[i];

        if (abs(valor_real - valor_mio) < 1e-6) {
            cantIguales++;
        } else {
            cout << "i: " << i << "  valor_real - valor_mio: " << valor_real - valor_mio << "\n";
        }
    }

    cout << "\n\nCORRECTOS: " << cantIguales << "\n";

}