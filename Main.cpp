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

    // @TODO: Hacer que sean parametros del ejecutable
    int tipo = TIPO_KNN_PSA;

    int k_knn = 15;
    int K_kfold = 4;
    int alpha = 20;

    int itersMetodoPotencia = 50;

    string filepathTrain = "data/train.csv";
    string filepathTest = "data/test.csv";

    // Lo mejor seria que considere las 42000;
    int cantImagenesTrain = 6000;

    // Carga y handle de imagenes de training
    ImageHandler imageTrainHandler(filepathTrain);

    // Agrupo las imagenes por su categoria
    vector<vector<imagen> > imagenesPorGrupo(10);
    for (int i = 0; i < cantImagenesTrain; i++) {
        imagenesPorGrupo[imageTrainHandler.getLabel(i)].push_back(imageTrainHandler.getImagen(i));
    }

    // Quiero que cada fold contenga aprox la misma cantidad de cada tipo, asi que reparto equitativamente
    // Guardo ademas su categoria original para conseguir estadisticas luego.

    vector<vector<imagen> > folds_imagenes(K_kfold);
    vector<vector<double> > folds_labels(K_kfold);
    for (int g = 0; g < 10; g++) {
        for (int i = 0; i < (int)imagenesPorGrupo[g].size(); i++) {
            folds_imagenes[i % K_kfold].push_back(imagenesPorGrupo[g][i]);
            folds_labels[i % K_kfold].push_back(g);
        }
    }


    for (int foldATestear = 0; foldATestear < K_kfold; foldATestear++) {
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
        PSA psa(matrizDatos, alpha, itersMetodoPotencia);

        vector<vector<double> > datosConvertidos(cantImagenesEntrenamiento, vector<double>(alpha, 0));

        cout << "Aplicando transformaciones a los datos..\n";
        for (int i = 0; i < (int)imagenesDato.size(); i++) {
            psa.Transformar(imagenesDato[i], datosConvertidos[i]);
        }

        KNN knnador;
        knnador.train(labelsDato, datosConvertidos);

        // Ahora voy a testear los el foldATestear

        // @TODO: RECOPILAR ESTADISTICAS, DIFERENCIADAS POR CLASE Y TIRARLAS EN UN CSV PARA DESPUES EXPERIMENTAR
        int errados = 0;

        cout << "Aplicando knn.\n";
        for (int j = 0; j < (int)folds_imagenes[foldATestear].size(); j++) {
            imagen convertida = vector<double>(alpha, 0);
            psa.Transformar(folds_imagenes[foldATestear][j], convertida);

            int labelObtenida = knnador.getGroupOf(convertida, k_knn);

            if (labelObtenida != folds_labels[foldATestear][j]) {
                errados++;
            }

        }

        cout << "\n\nFold numero: " << foldATestear << "    errados: " << errados << "\n\n";
    }
}