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

    int k_knn = 10;
    int K_kfold = 4;
    int alpha = 10;
    string filepathTrain = "data/train.csv";
    string filepathTest = "data/test.csv";

    // Lo mejor seria que considere las 42000;
    int cantImagenesTrain = 10000;

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


}