#include "kNN.h"

	void KNN::train(vector<int> groups, vector<vector<double> > images){
		groups_=groups;
		images_=images;
	}

	vector<int> KNN::getGroups(){
		return groups_;
	}
	vector<vector<double> > KNN::getImages(){
		return images_;
	}

	double KNN::getDifference(const vector<double> &a,const vector<double> &b){
		vector<double> c(a.size());

		//Creo el vector de las diferencias entre a y b
		for(int i =0; i<a.size(); i++){
			c[i]=a[i] - b[i];
		}

		double x=0.0;
		//Hago la suma de los cuadrados de las componentes, en otras palabras (||x||_2)^2 (con p=2)
		for(int i =0; i<c.size(); i++){
			x+=pow(c[i],2);
		}
		//Hago la raiz cuadrada para que me quede ||x||_2
		x=sqrt(x);

		return x;
	}

	bool comp (const imageDiff &i,const imageDiff &j) { return (i.diff<j.diff); }

	int KNN::getGroupOf(vector<double> &image, int k){

		vector<imageDiff> differences(this->images_.size());

		//Creo un vector donde guardo una estructura que me dice a que grupo pertenece, a que distancia esta de la imagen
		//que quiero averiguar y el vector de esa imagen.
		//Inicialmente el de infdice i tiene el grupo de indice i en el vector de los grupos, pero luego se hace un sort
		//por lo que se pierde ese invariante, por eso me guardo en cada estructura a que grupo pertenece.
		for(int i =0; i< this->images_.size();i++){
			differences[i].group= this->getGroups()[i];
			differences[i].vectorImage= this->getImages()[i];
			differences[i].diff = this->getDifference(image, differences[i].vectorImage);
		}
		//Hago sort con un comparador Ad Hoc para esta estructura.
		//Se ordenan de menor a mayor comparando las differencias con image.
		sort(differences.begin(),differences.end(), comp);

		//Creo el vector de grupos, se que son 10, del 0 al 9.
		vector<int> groups(10,0);

		//Cuento la cantidad de incidencias de cada grupo en los K mas cercanos
		for(int i=0; i<k ; i++){
			groups[differences[i].group]++;
		}

		//Busco el grupo que mas incidencia tubo en los primeros K.
		int bestGroup;
		for(int i=0;i<groups.size();i++){
			if(groups[i]>groups[bestGroup]){
				bestGroup=i;
			}
		}

		return bestGroup;
	}
