//============================================================================
// Name        : kNNProject.cpp
// Author      : apenas
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "kNN.h"
#include "ImageHandler.h"
using namespace std;

using std::vector;

int main() {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!


	ImageHandler imageHandler("data/train.csv");

	int cantImagenes = imageHandler.cantImagenes;
	cout<<"Cantidad de imagenes: "<<cantImagenes<<endl;
	vector<int> groups(900,0);
	vector<vector<double> > images(900,vector<double>());

	for(int i =0;i<900;i++){
		groups[i]=imageHandler.getLabel(i);
		images[i]=imageHandler.getImagen(i);
	}

	vector<int> groupsPrueba(100,0);
	vector<vector<double> > imagesPrueba(100,vector<double>());

	for(int i=1;i<100;i++){
		groupsPrueba[i]=imageHandler.getLabel(cantImagenes-i);
		imagesPrueba[i]=imageHandler.getImagen(cantImagenes-i);
	}
	cout<<"Imagenes cargadas para traning: "<<groups.size()<<endl;
	cout<<"Imagenes cargadas para prueba: "<<groupsPrueba.size()<<endl;
	KNN knnador;

	cout<<"Entrenando..."<<endl;
	knnador.train(groups,images);
	cout<<"Entrenamiento finalizado."<<endl;


	for(int i=1;i<100;i++){
		int grupo =knnador.getGroupOf(imagesPrueba[i],10);
		cout<<"Resultado: "<<grupo<<" para el label: "<<groupsPrueba[i]<<endl;
		if(grupo!=groupsPrueba[i]){
			cout<<"ESTE LE PIFIO!!!"<<endl;
		}
	}

	return 0;
}
