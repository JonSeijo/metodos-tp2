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
    int tipo = TIPO_KNN_SOLO;

    int k_knn = 3;
    int alpha = 20;
    int itersMetodoPotencia = 50;

    string filepathTrain = "data/train.csv";
    string filepathTest = "data/test.csv";

    // Lo mejor seria que considere las 42000;
    int cantImagenesTrain = 42000;

    // Carga y handle de imagenes de training
    ImageHandler imageTrainHandler(filepathTrain);

    // @TODO: Asumo que el test no tiene labels, input podria tenerlo
    // Carga y handle de imagenes de test.
    ImageHandler imageTestHandler(filepathTest, false);
    int cantImagenesTest = imageTestHandler.cantImagenes;


    vector<imagen> imagenes(cantImagenesTrain);
    vector<int> labeles(cantImagenesTrain);

    for (int i = 0; i < cantImagenesTrain; i++) {
        imagenes[i] = imageTrainHandler.getImagen(i);
        labeles[i] = imageTrainHandler.getLabel(i);
    }

    if (tipo == TIPO_KNN_SOLO) {

        KNN knnador;
        knnador.train(labeles, imagenes);

        cout << "ImageId,Label\n";

        for (int j = 0; j < cantImagenesTest; j++) {
            imagen imagenTest = imageTestHandler.getImagen(j);
            int labelObtenida = knnador.getGroupOf(imagenTest, k_knn);
            cout << j+1 << "," << labelObtenida << "\n";
        }



    } else if (tipo == TIPO_KNN_PSA) {

         // Ya tengo los datos del fold listos para entrenarlos con el metodo elegido
        Matriz matrizDatos(imagenes);
        PSA psa(matrizDatos, alpha, itersMetodoPotencia);

        vector<vector<double> > datosConvertidos(cantImagenesTrain, vector<double>(alpha, 0));

        // Aplico transformaciones a los datos
        for (int i = 0; i < cantImagenesTrain; i++) {
            psa.Transformar(imagenes[i], datosConvertidos[i]);
        }

        // Entreno kNN
        KNN knnador;
        knnador.train(labeles, datosConvertidos);

        cout << "ImageId,Label\n";

        // Aplica transformadores a datos testeo y evaluo con knn
        for (int j = 0; j < cantImagenesTest; j++) {
            imagen convertida(alpha, 0);
            psa.Transformar(imageTestHandler.getImagen(j), convertida);

            int labelObtenida = knnador.getGroupOf(convertida, k_knn);
            cout << j+1 << "," << labelObtenida << "\n";
        }
    }

}