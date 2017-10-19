#include "Auxiliares.h"
#include "Covarianza.h"
#include "MetodoPotencia.h"
#include "ImageHandler.h"
#include "kNN.h"
#include "PSA.h"

typedef vector<double> imagen;

#define ya std::chrono::high_resolution_clock::now

string getFilename(int cantImagenesTrain, int alpha, int fold) {
    string res = "pruebas/psa/";
    res += "psa_";
    res += to_string(cantImagenesTrain);
    res += "_alpha_";
    res += to_string(alpha);
    res += "_fold_";
    res += to_string(fold);
    res += ".txt";
    return res;
}

string getFilenameTiempo(int cantImagenesTrain, int alpha) {
    string res = "pruebas/psa/";
    res += "psa_";
    res += to_string(cantImagenesTrain);
    res += "_alpha_";
    res += to_string(alpha);
    res += "tiempo";
    res += ".txt";
    return res;
}

int main() {

    int k_knn = 4;
    int K_kfold = 4;
    int alpha = 31;

    string filepathTrain = "data/train.csv";
    string filepathTest = "data/test.csv";

    // Lo mejor seria que considere las 42000;
    // int cantImagenesTrain = 42000;

    cout << "cantImagenes,accuracy,tiempo\n";

    for (int cantImagenesTrain = 500; cantImagenesTrain <= 15000; cantImagenesTrain += 500) {

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

        // fold:  grupo:   total   (10 total)
        map<int, map<int,int> > totalesPorFold;

        for (int g = 0; g < 10; g++) {
            for (int i = 0; i < (int)imagenesPorGrupo[g].size(); i++) {
                folds_imagenes[i % K_kfold].push_back(imagenesPorGrupo[g][i]);
                folds_labels[i % K_kfold].push_back(g);

                totalesPorFold[i % K_kfold][g]++;
                totalesPorFold[i % K_kfold][10]++;
            }
        }

        int itersMetodoPotencia = 200;


        vector<vector<double> > precision(K_kfold, vector<double>(10, 0));
        vector<vector<double> > recall(K_kfold, vector<double>(10, 0));
        vector<vector<double> > f1(K_kfold, vector<double>(10, 0));
        vector<double> tiempo(K_kfold, 0);
        vector<double> accuracy(K_kfold, 0);

        for (int foldATestear = 0; foldATestear < K_kfold; foldATestear++) {
            //  foldATestear será el fold a testear (increible), el resto se entrena.

            // Junto todos los datos que voy a utilizar para entrenar, excepto foldATestear
            vector<int> labelsDato;
            vector<imagen> imagenesDato;
            int cantImagenesTrainFold = 0;

            for (int f = 0; f < K_kfold; f++) {
                if (f == foldATestear) {
                    continue;
                }

                for (int j = 0; j < (int)folds_imagenes[f].size(); j++) {
                    imagenesDato.push_back(folds_imagenes[f][j]);
                    labelsDato.push_back(folds_labels[f][j]);
                    cantImagenesTrainFold++;
                }
            }

            // Ya tengo los datos del fold listos para entrenarlos con PSA

            auto start = ya();

            Matriz matrizDatos(imagenesDato);
            PSA psa(matrizDatos, alpha, itersMetodoPotencia);

            vector<vector<double> > datosConvertidos(cantImagenesTrainFold, vector<double>(alpha, 0));

            // Aplico transformaciones a los datos
            for (int i = 0; i < cantImagenesTrainFold; i++) {
                psa.Transformar(imagenesDato[i], datosConvertidos[i]);
            }

            // Entreno kNN
            KNN knnador;
            knnador.train(labelsDato, datosConvertidos);

            // Ahora voy a testear los el foldATestear

            double acertados = 0;

            vector<double> verdaderosPositivos(10, 0);
            vector<double> falsosPositivos(10, 0);
            vector<double> falsosNegativos(10, 0);

            // cout << "Aplicando knn.\n";
            for (int j = 0; j < (int)folds_imagenes[foldATestear].size(); j++) {

                imagen convertida(alpha, 0);
                psa.Transformar(folds_imagenes[foldATestear][j], convertida);

                int labelObtenida = knnador.getGroupOf(convertida, k_knn);
                int labelReal = folds_labels[foldATestear][j];

                if (labelObtenida == labelReal) {
                    verdaderosPositivos[labelObtenida]++;
                    acertados++;
                }
            }

            auto end = ya();


            tiempo[foldATestear] = std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count();
            accuracy[foldATestear] = acertados / cantImagenesTrainFold;
        }

        double tiempo_posta = 0;
        double accuracy_posta = 0;
        for (int fold = 0; fold < K_kfold; fold++) {
            tiempo_posta += tiempo[fold];
            accuracy_posta += accuracy[fold];
        }
        tiempo_posta /= (double)K_kfold;
        accuracy_posta /= (double)K_kfold;

        // Termine de hacer los folds y de tomar datos, los imprimo
        // "k,clase,precision,recall,f1,tiempo\n";

        // for (int j = 0; j < 10; j++) {
        cout << cantImagenesTrain << "," << accuracy_posta << "," << tiempo_posta << "\n";
    }
}