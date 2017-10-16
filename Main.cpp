#include "Auxiliares.h"
#include "Covarianza.h"
#include "MetodoPotencia.h"
#include "ImageHandler.h"
#include "kNN.h"
#include "PSA.h"

#include <unistd.h>

typedef vector<double> imagen;

const int TIPO_NADA = -1;
const int TIPO_KNN_SOLO = 0;
const int TIPO_KNN_PSA = 1;

void mostrarHelp() {
    cout << "-m <method>\n";
    cout << "    0 - kNN\n";
    cout << "    1 - PSA + kNN\n\n";
    cout << "-i <train_set>\n";
    cout << "    Path al archivo training.\n\n";
    cout << "-q <test_set>\n";
    cout << "    Path al archivo test. Puede estar etiquetado o no.\n\n";
    cout << "-o <classif>\n";
    cout << "    Archivo de salida donde se guardarán los resultados. Debe existir! \n\n";
    cout << "-p <porcentaje_train>\n";
    cout << "    DOUBLE entre 0 y 1, porcentaje de imagenes a entrenar. 1 significa todas.\n\n";
}

int main(int argc, char **argv) {

    // Valores por defecto
    string filepathTrain = "data/train.csv";
    string filepathTest = "data/test.csv";
    string filepathResultados = "resultados.csv";
    int tipo = TIPO_NADA;
    double procentajeTraining = 1;

    char opcion;
    while ((opcion = getopt (argc, argv, "hm:i:q:o:p:")) != -1) {
        switch(opcion) {
            case 'h':
                mostrarHelp();
                return 0;
                break;
            case 'm':
                if (optarg) tipo = atoi(optarg);
                break;
            case 'i':
                if (optarg) filepathTrain = optarg;
                break;
            case 'q':
                if (optarg) filepathTest = optarg;
                break;
            case 'o':
                if (optarg) filepathResultados = optarg;
                break;
            case 'p':
                if (optarg) procentajeTraining = stod(optarg);
                break;
        }
    }



    int itersMetodoPotencia = 50;
    int k_knn = 4;
    int alpha = 20;
    int cantImagenesTrain = 42000 * procentajeTraining;

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
    } else {
        cout << "No se especifico ningun tipo de entrenamiento. Ver help con opcion -h.\n";
    }

}