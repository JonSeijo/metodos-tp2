#include "PSA.h"
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

    int alpha = 10;
    Matriz matrizDatos(imagenesDato);
    PSA psa(matrizDatos, alpha);

}