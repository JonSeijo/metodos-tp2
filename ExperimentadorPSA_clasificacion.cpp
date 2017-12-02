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

string getFilenameResult(int cantImagenesTrain, int alpha) {
    string res = "pruebas/psa/";
    res += "psa_";
    res += to_string(cantImagenesTrain);
    res += "_alpha_";
    res += to_string(alpha);
    res += "result.txt";
    return res;
}

int main() {

    int K_kfold = 4;
    int cantImagenesTrain = 42000;
    // int alpha = 20;

    string filepathTrain = "data/train.csv";
    string filepathTest = "data/test.csv";

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

    int itersMetodoPotencia = 50;

    // header:

    for (int alpha = 37; alpha <= 40; alpha += 1) {

    ofstream outresfile;
    outresfile.open(getFilenameResult(cantImagenesTrain, alpha), fstream::out);
    outresfile << "k,clase,precision,recall,f1,tiempo\n";
    outresfile.close();

    // for (int k_knn = 1; k_knn < 40; k_knn++) {


        for (int k_knn = 1; k_knn < 8; k_knn++) {
            cout << "k: " << k_knn << "\n";

            vector<vector<double> > precision(K_kfold, vector<double>(10, 0));
            vector<vector<double> > recall(K_kfold, vector<double>(10, 0));
            vector<vector<double> > f1(K_kfold, vector<double>(10, 0));
            vector<double> tiempo(K_kfold, 0);

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


                // ACA CARGO UNA MATRIZ DEL TXT GUARDADO ANTERIORMENTE
                ifstream fileMatriz(getFilename(cantImagenesTrain, alpha, foldATestear));
                vector<vector<double> > cambioBase(alpha, vector<double>(784, 0));
                for (int i = 0; i < (int)cambioBase.size(); i++) {
                    for (int j = 0; j < (int)cambioBase[0].size(); j++) {
                        fileMatriz >> cambioBase[i][j];
                    }
                }
                fileMatriz.close();

                Matriz matrizCambioBase(cambioBase);

                PSA psa;
                psa.cargarCambioDeBase(matrizCambioBase, Matriz(imagenesDato).calcularMedia(), cantImagenesEntrenamiento);

                // Ya tengo los datos del fold listos para entrenarlos con el metodo elegido
                auto start = ya();

                vector<vector<double> > datosConvertidos(cantImagenesEntrenamiento, vector<double>(alpha, 0));

                // Aplico transformaciones a los datos
                for (int i = 0; i < cantImagenesEntrenamiento; i++) {
                    psa.Transformar(imagenesDato[i], datosConvertidos[i]);
                }

                // Entreno kNN
                KNN knnador;
                knnador.train(labelsDato, datosConvertidos);

                // Ahora voy a testear los el foldATestear

                // @TODO: RECOPILAR ESTADISTICAS, DIFERENCIADAS POR CLASE Y TIRARLAS EN UN CSV PARA DESPUES EXPERIMENTAR
                int errados = 0;

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
                    } else {

                        // falso positivo: si fue clasificado como i pero NO lo era
                        falsosPositivos[labelObtenida]++;

                        // falso negativo: si NO fue clasificado como i pero lo era
                        falsosNegativos[labelReal]++;
                    }
                }
                auto end = ya();


                tiempo[foldATestear] = std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count();

                for (int j = 0; j < 10; j++) {

                    double denom1 = (verdaderosPositivos[j] + falsosPositivos[j]);
                    precision[foldATestear][j] = denom1 > 0 ? verdaderosPositivos[j] / denom1 : 0;

                    double denom2 = (verdaderosPositivos[j] + falsosNegativos[j]);
                    recall[foldATestear][j] = denom2 > 0 ? verdaderosPositivos[j] / denom2 : 0;

                    double pres = precision[foldATestear][j];
                    double rec = recall[foldATestear][j];

                    f1[foldATestear][j] = (pres + rec) > 0 ? 2 * (pres * rec) / (pres + rec) : 0;
                }
            }

            // Realizo un promedio entre los folds para obtener los resultados posta para este k

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

                // cout << "sumaPres: " << sumaPres << "\n";
                // cout << "sumaRec: " << sumaRec << "\n";
                // cout << "sumaF1: " << sumaF1 << "\n";

                precision_posta[j] = sumaPres / (double)K_kfold;
                recall_posta[j] = sumaRec / (double)K_kfold;
                f1_posta[j] = sumaF1 / (double)K_kfold;
            }

            double tiempo_posta = 0;
            for (int fold = 0; fold < K_kfold; fold++) {
                tiempo_posta += tiempo[fold];
            }
            tiempo_posta /= (double)K_kfold;

            // Termine de hacer los folds y de tomar datos, los imprimo
            // "k,clase,precision,recall,f1,tiempo\n";
            outresfile.open(getFilenameResult(cantImagenesTrain, alpha), std::ios_base::app);
            for (int j = 0; j < 10; j++) {
                outresfile << k_knn << "," << j << "," << precision_posta[j] << ",";
                    outresfile << recall_posta[j] << "," << f1_posta[j] << "," << tiempo_posta << "\n";
            }
            outresfile.close();

        }
    }
}