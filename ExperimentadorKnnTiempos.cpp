#include "Auxiliares.h"
#include "Covarianza.h"
#include "MetodoPotencia.h"
#include "ImageHandler.h"
#include "kNN.h"
#include "PSA.h"

typedef vector<double> imagen;

#define ya std::chrono::high_resolution_clock::now

int main() {

    // int k_knn = 15;
    int K_kfold = 4;
    int alpha = 20;

    int k_knn = 4;

    string filepathTrain = "data/train.csv";
    string filepathTest = "data/test.csv";


    // header:
    cout << "cantImagenes,accuracy,tiempo\n";

    for (int cantImagenesTrain = 500; cantImagenesTrain <= 15000; cantImagenesTrain += 500) {


        // Lo mejor seria que considere las 42000;

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

        // cout << "iters,";
        // for (int i = 0; i < 10; i++) {
        //     cout << totalesPorGr[]
        // }

        // fold:  grupo:  acertados
        int itersMetodoPotencia = 50;

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

            auto start = ya();

            KNN knnador;
            knnador.train(labelsDato, imagenesDato);
            // Ahora voy a testear los el foldATestear

            // @TODO: RECOPILAR ESTADISTICAS, DIFERENCIADAS POR CLASE Y TIRARLAS EN UN CSV PARA DESPUES EXPERIMENTAR

            vector<double> verdaderosPositivos(10, 0);
            vector<double> falsosPositivos(10, 0);
            vector<double> falsosNegativos(10, 0);

            double acertados = 0;
            // cout << "Aplicando knn.\n";
            for (int j = 0; j < (int)folds_imagenes[foldATestear].size(); j++) {

                int labelObtenida = knnador.getGroupOf(folds_imagenes[foldATestear][j], k_knn);
                int labelReal = folds_labels[foldATestear][j];

                if (labelObtenida == labelReal) {
                    verdaderosPositivos[labelObtenida]++;
                    acertados++;
                } else {
                    // falso positivo: si fue clasificado como i pero NO lo era
                    falsosPositivos[labelObtenida]++;

                    // falso negativo: si NO fue clasificado como i pero lo era
                    falsosNegativos[labelReal]++;
                }
            }
            auto end = ya();


            tiempo[foldATestear] = std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count();
            accuracy[foldATestear] = acertados / cantImagenesEntrenamiento;

            // for (int j = 0; j < 10; j++) {
            //     precision[foldATestear][j] = verdaderosPositivos[j] / (verdaderosPositivos[j] + falsosPositivos[j]);
            //     recall[foldATestear][j] = verdaderosPositivos[j] / (verdaderosPositivos[j] + falsosNegativos[j]);

            //     double pres = precision[foldATestear][j];
            //     double rec = recall[foldATestear][j];

            //     f1[foldATestear][j] = 2 * (pres * rec) / (pres + rec);
            // }
        }

        // Realizo un promedio entre los folds para obtener los resultados posta para este k

        // vector<double> precision_posta(10, 0);
        // vector<double> recall_posta(10, 0);
        // vector<double> f1_posta(10, 0);
        // for (int j = 0; j < 10; j++) {
        //     double sumaPres = 0;
        //     double sumaRec = 0;
        //     double sumaF1 = 0;
        //     for (int fold = 0; fold < K_kfold; fold++) {
        //         sumaPres += precision[fold][j];
        //         sumaRec += recall[fold][j];
        //         sumaF1 += f1[fold][j];
        //     }
        //     precision_posta[j] = sumaPres / (double)K_kfold;
        //     recall_posta[j] = sumaRec / (double)K_kfold;
        //     f1_posta[j] = sumaF1 / (double)K_kfold;
        // }

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
        // }
    }
}