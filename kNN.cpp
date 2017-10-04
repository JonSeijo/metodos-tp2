#include "kNN.h"

	void KNN::train(vector<int> groups, vector<vector<double> > images){
		groups_=groups;
		images_=images;
	}

	const vector<int> &KNN::getGroups(){
		return groups_;
	}

	const vector<vector<double> > &KNN::getImages(){
		return images_;
	}

	double KNN::getDifference(const vector<double> &a, const vector<double> &b){
		// Hago la suma de los cuadrados de las componentes, en otras palabras (||x||_2)^2 (con p=2)
		double x = 0.0;
		for(int i = 0; i < a.size(); i++){
			x += pow((a[i] - b[i]), 2);
		}

		// Retorno la raiz cuadrada para que me quede ||x||_2
		return sqrt(x);
	}

	bool comp (const imageDiff &i,const imageDiff &j) { return (i.diff<j.diff); }

	int KNN::getGroupOf(vector<double> &image, int k){

		int cantImagenes = this->images_.size();

		vector< std::pair<double, int > > differences(cantImagenes);

		// El vector de diferencia guarda pares <diff, indice>
		// El indice original es guardado porque como luego tomaré los k menores,
		//    necesito una forma de recuperar la informacion original

		for (int i = 0; i < cantImagenes; i++){
			differences[i].first = this->getDifference(image, this->getImages()[i]);
			differences[i].second = i;
		}

		std::priority_queue<      // Cola de prioridad (heap)
			pair<double, int >,          // Guardo pares <diff, indice>
			vector< std::pair <double, int> >,    // Usa un vector de pares como contenedor principal
			std::greater<std::pair<double, int > > >   // Comparacion inversa para obtener minimos en vez de maximos (por defecto)

				min_heap(differences.begin(), differences.end());   // Armo el min_heap con todos los pares de diferencias


		// Creo el vector de grupos, se que son 10, del 0 al 9.
		vector<int> groups(10,0);

		// Cuento la cantidad de incidencias de cada grupo en los K mas cercanos
		int cantMejorGrupo = 0;
		int mejorGrupo = 0;
		for(int i = 0; i < k ; i++){

			int indiceOrig = min_heap.top().second; // El top es el minimo,  .second me da el indice original
			min_heap.pop();  // Lo quito del heap, ya fue usado

			int grupoAct = this->getGroups()[indiceOrig];  // Guardo el grupo del indice original

			groups[grupoAct]++;   // Hay uno mas del grupo

			if (groups[grupoAct] > cantMejorGrupo) {   // Reviso si es un nuevo maximo
				cantMejorGrupo = groups[grupoAct];
				mejorGrupo = grupoAct;
			}
		}

		return mejorGrupo;
	}
