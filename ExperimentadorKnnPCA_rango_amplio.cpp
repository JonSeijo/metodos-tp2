#include "Auxiliares.h"
#include "Covarianza.h"
#include "MetodoPotencia.h"
#include "ImageHandler.h"
#include "kNN.h"
#include "PSA.h"
#include <fstream>

typedef vector<double> imagen;

#define ya std::chrono::high_resolution_clock::now

int main(){

    remove("result_knnPCA_rango_amplio.csv");
    ofstream archivo;
    archivo.open("result_knnPCA_rango_amplio.csv", ios::app | ios::out);
    archivo << "cant_entrenemiento,clase,precision,recall,f1,tiempo_por_fold,tiempo_total_knn_pca,tiempo_total_fold\n";
    archivo.close();

    int k_knn = 4;
    int K_kfold = 10;
    int alpha = 31;
    int itersMetodoPotencia = 50;

    string filepathTrain = "data/train.csv";
    string filepathTest = "data/test.csv";

    vector<unsigned int> cantImagenesTrain = {50, 75, 100, 125, 150, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000, 15000, 20000};
    //int cantImagenesTrain = 10000;
    // Carga y handle de imagenes de training
    ImageHandler imageTrainHandler(filepathTrain);
    ImageHandler imagenTest(filepathTest);

    for(int indice = 0; indice < cantImagenesTrain.size(); indice++){
        // Agrupo las imagenes por su categoria
        vector<vector<imagen> > imagenesPorGrupo(10);
        for (int i = 0; i < cantImagenesTrain[indice]; i++) {
            imagenesPorGrupo[imageTrainHandler.getLabel(i)].push_back(imageTrainHandler.getImagen(i));
        }

        // Quiero que cada fold contenga aprox la misma cantidad de cada tipo, asi que reparto equitativamente
        // Guardo ademas su categoria original para conseguir estadisticas luego.

        //Varío los k_kfolds
            auto inicioKfold = ya();

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

            vector<vector<double> > precision(K_kfold, vector<double>(10, 0));
            vector<vector<double> > recall(K_kfold, vector<double>(10, 0));
            vector<vector<double> > f1(K_kfold, vector<double>(10, 0));
            vector<double> tiempo(K_kfold, 0);
            double tiemFold;

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
                
                Matriz matrizDatos(imagenesDato);
                PSA psa(matrizDatos, alpha, itersMetodoPotencia);

                vector<vector<double> > datosConvertidos(cantImagenesEntrenamiento, vector<double>(alpha, 0));

                // cout << "Aplicando transformaciones a los datos..\n";
                for (int i = 0; i < (int)imagenesDato.size(); i++) {
                    psa.Transformar(imagenesDato[i], datosConvertidos[i]);
                }
                
                KNN knnador;
                //knnador.train(labelsDato, datosConvertidos);
                knnador.train(labelsDato, imagenesDato);
                // Ahora voy a testear los el foldATestear

                // @TODO: RECOPILAR ESTADISTICAS, DIFERENCIADAS POR CLASE Y TIRARLAS EN UN CSV PARA DESPUES EXPERIMENTAR
                int errados = 0;

                vector<double> verdaderosPositivos(10, 0);
                vector<double> falsosPositivos(10, 0);
                vector<double> falsosNegativos(10, 0);

                // cout << "Aplicando knn.\n";
                for (int j = 0; j < (int)folds_imagenes[foldATestear].size(); j++) {

                    int labelObtenida = knnador.getGroupOf(folds_imagenes[foldATestear][j], k_knn);
                    int labelReal = folds_labels[foldATestear][j];

                    if (labelObtenida == labelReal) {
                        verdaderosPositivos[labelObtenida]++;
                    } else {

                        // falso positivo: si fue clasificado como i pero NO lo era
                        falsosPositivos[labelObtenida]++;

                        // falso negativo: si NO fue clasificado como i pero lo era
                        falsosNegativos[labelReal]++;
                    }
                }
                auto end = ya();
                auto finKfold = ya();

                tiempo[foldATestear] = std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count();
                tiemFold = std::chrono::duration_cast<std::chrono::nanoseconds>(finKfold-inicioKfold).count();

                for (int j = 0; j < 10; j++) {
                    precision[foldATestear][j] = (verdaderosPositivos[j] + falsosPositivos[j]) != 0 ? (verdaderosPositivos[j] / (verdaderosPositivos[j] + falsosPositivos[j])) : 0.0f;
                    recall[foldATestear][j] = (verdaderosPositivos[j] + falsosNegativos[j]) != 0 ? (verdaderosPositivos[j] / (verdaderosPositivos[j] + falsosNegativos[j])) : 0.0f;

                    double pres = precision[foldATestear][j];
                    double rec = recall[foldATestear][j];

                    f1[foldATestear][j] = (pres + rec) != 0 ? 2 * (pres * rec) / (pres + rec) : 0.0f;
                }
            }

                cout << "Tamanio entrenamiento: " << cantImagenesTrain[indice] << "\n";
                ofstream archivo;
                archivo.open("result_knnPCA_rango_amplio.csv", ios::app | ios::out);
                //archivo << "\ncant_entrenemiento, clase, precision, recall, f1, tiempo por fold, tiempo total knn, tiempo total fold\n";
            
                //Promedio entre folds
                vector<double> precision_posta(10, 0);
                vector<double> recall_posta(10, 0);
                vector<double> f1_posta(10, 0);
                for (int j = 0; j < 10; j++) {
                    
                    double sumaPres = 0;
                    double sumaRec = 0;
                    double sumaF1 = 0;
                    for (int fold = 0; fold < K_kfold; fold++) {
                        sumaPres += precision[fold][j];
                        sumaRec += recall[fold][j];
                        sumaF1 += f1[fold][j];
                    }
                    
                    precision_posta[j] = sumaPres / (double)K_kfold;
                    recall_posta[j] = sumaRec / (double)K_kfold;
                    f1_posta[j] = sumaF1 / (double)K_kfold;
                    
                }

                double tiempo_posta = 0;
                for (int fold = 0; fold < K_kfold; fold++) {
                    tiempo_posta += tiempo[fold];
                }
                double tiempoTotal = tiempo_posta;
                tiempo_posta /= (double)K_kfold;


                for (int j = 0; j < 10; j++) {
                    archivo << cantImagenesTrain[indice] << "," << j << "," << precision_posta[j] << ",";
                    archivo << recall_posta[j] << "," << f1_posta[j] << "," << setprecision(35) << tiempo_posta << "," << tiempoTotal << "," << tiemFold << "\n";
                }

                archivo.close();    

    }

    return 0;
}