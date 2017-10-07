#include "PSA.h"
#include "kNN.h"
#include "ImageHandler.h"

int main() {

    ImageHandler imageHandler("data/train.csv");
    int cantImagenes = imageHandler.cantImagenes;
    // cout<<"Cantidad de imagenes: "<<cantImagenes<<endl;

    int cantImagenesTraining = 2000;

    vector<int> gruposDato(cantImagenesTraining,0);
    vector<vector<double> > imagenesDato(cantImagenesTraining,vector<double>());
    for(int i = 0; i < cantImagenesTraining; i++) {
        gruposDato[i] = imageHandler.getLabel(i);
        imagenesDato[i] = imageHandler.getImagen(i);
    }

    int alpha = 8;
    Matriz matrizDatos(imagenesDato);
    PSA psa(matrizDatos, alpha);

    vector<vector<double> > datosConvertidos((int)imagenesDato.size(), vector<double>(alpha, 0));

    cout << "Aplicando transformaciones a los datos..\n";
    for (int i = 0; i < (int)imagenesDato.size(); i++) {
        psa.Transformar(imagenesDato[i], datosConvertidos[i]);
    }

    KNN knnador;
    cout << "Entrenando knn...\n";
    knnador.train(gruposDato, datosConvertidos);


    int k = 15;

    cout << "LO SIGUEINTE ESTA MAL TEST NO HACER EN LA POSTA\n";

    int cantPifies = 0;

    for (int i = 0 ; i < 2000; i++) {
        int grupo = knnador.getGroupOf(datosConvertidos[i], k);
        // cout<< "Resultado: " << grupo << " para el label: " << gruposDato[i] << endl;
        if (grupo != gruposDato[i]) {
            // cout<<"ESTE LE PIFIO!!!"<<endl;
            cantPifies++;
        }
    }

    cout << "cantPifies: " << cantPifies << "\n";
    cout << "cantTotal: " << cantImagenesTraining << "\n";
    cout << "acaracy: " << cantPifies*1.0 / cantImagenesTraining*1.0 << "\n";

}