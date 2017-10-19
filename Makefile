all: main

main: Main.cpp PSA.cpp PSA.h kNN.cpp kNN.h ImageHandler.cpp ImageHandler.h Covarianza.cpp Covarianza.h MetodoPotencia.cpp MetodoPotencia.h Matriz.cpp Matriz.h Auxiliares.cpp Auxiliares.h
	g++ -std=c++11 -O2 Main.cpp PSA.cpp kNN.cpp ImageHandler.cpp Covarianza.cpp MetodoPotencia.cpp Matriz.cpp Auxiliares.cpp -o main

exp_iters: ExperimentadorIters.cpp PSA.cpp PSA.h kNN.cpp kNN.h ImageHandler.cpp ImageHandler.h Covarianza.cpp Covarianza.h MetodoPotencia.cpp MetodoPotencia.h Matriz.cpp Matriz.h Auxiliares.cpp Auxiliares.h
	g++ -std=c++11 -O2 ExperimentadorIters.cpp PSA.cpp kNN.cpp ImageHandler.cpp Covarianza.cpp MetodoPotencia.cpp Matriz.cpp Auxiliares.cpp -o exp_iters

exp_knn: ExperimentadorKnn.cpp PSA.cpp PSA.h kNN.cpp kNN.h ImageHandler.cpp ImageHandler.h Covarianza.cpp Covarianza.h MetodoPotencia.cpp MetodoPotencia.h Matriz.cpp Matriz.h Auxiliares.cpp Auxiliares.h
	g++ -std=c++11 -O2 ExperimentadorKnn.cpp PSA.cpp kNN.cpp ImageHandler.cpp Covarianza.cpp MetodoPotencia.cpp Matriz.cpp Auxiliares.cpp -o exp_knn

exp_knn_tiempo: ExperimentadorKnnTiempos.cpp PSA.cpp PSA.h kNN.cpp kNN.h ImageHandler.cpp ImageHandler.h Covarianza.cpp Covarianza.h MetodoPotencia.cpp MetodoPotencia.h Matriz.cpp Matriz.h Auxiliares.cpp Auxiliares.h
	g++ -std=c++11 -O2 ExperimentadorKnnTiempos.cpp PSA.cpp kNN.cpp ImageHandler.cpp Covarianza.cpp MetodoPotencia.cpp Matriz.cpp Auxiliares.cpp -o exp_knn_tiempo

exp_psa_creacion: ExperimentadorPSA_creacion.cpp PSA.cpp PSA.h kNN.cpp kNN.h ImageHandler.cpp ImageHandler.h Covarianza.cpp Covarianza.h MetodoPotencia.cpp MetodoPotencia.h Matriz.cpp Matriz.h Auxiliares.cpp Auxiliares.h
	g++ -std=c++11 -O2 ExperimentadorPSA_creacion.cpp PSA.cpp kNN.cpp ImageHandler.cpp Covarianza.cpp MetodoPotencia.cpp Matriz.cpp Auxiliares.cpp -o exp_psa_creacion

exp_psa_tiempos: ExperimentadorPSA_tiempos.cpp PSA.cpp PSA.h kNN.cpp kNN.h ImageHandler.cpp ImageHandler.h Covarianza.cpp Covarianza.h MetodoPotencia.cpp MetodoPotencia.h Matriz.cpp Matriz.h Auxiliares.cpp Auxiliares.h
	g++ -std=c++11 -O2 ExperimentadorPSA_tiempos.cpp PSA.cpp kNN.cpp ImageHandler.cpp Covarianza.cpp MetodoPotencia.cpp Matriz.cpp Auxiliares.cpp -o exp_psa_tiempos

exp_psa_clasificar: ExperimentadorPSA_clasificacion.cpp PSA.cpp PSA.h kNN.cpp kNN.h ImageHandler.cpp ImageHandler.h Covarianza.cpp Covarianza.h MetodoPotencia.cpp MetodoPotencia.h Matriz.cpp Matriz.h Auxiliares.cpp Auxiliares.h
	g++ -std=c++11 -O2 ExperimentadorPSA_clasificacion.cpp PSA.cpp kNN.cpp ImageHandler.cpp Covarianza.cpp MetodoPotencia.cpp Matriz.cpp Auxiliares.cpp -o exp_psa_clasificar

exp_knn_kfold: ExperimentoKnnKfold.cpp PSA.cpp PSA.h kNN.cpp kNN.h ImageHandler.cpp ImageHandler.h Covarianza.cpp Covarianza.h MetodoPotencia.cpp MetodoPotencia.h Matriz.cpp Matriz.h Auxiliares.cpp Auxiliares.h
	g++ -std=c++11 -O2 ExperimentoKnnKfold.cpp PSA.cpp kNN.cpp ImageHandler.cpp Covarianza.cpp MetodoPotencia.cpp Matriz.cpp Auxiliares.cpp -o exp_knn_kfold

main_test: MainTester.cpp PSA.cpp PSA.h kNN.cpp kNN.h ImageHandler.cpp ImageHandler.h Covarianza.cpp Covarianza.h MetodoPotencia.cpp MetodoPotencia.h Matriz.cpp Matriz.h Auxiliares.cpp Auxiliares.h
	g++ -std=c++11 MainTester.cpp PSA.cpp kNN.cpp ImageHandler.cpp Covarianza.cpp MetodoPotencia.cpp Matriz.cpp Auxiliares.cpp -o main_test

knn_test: kNNTest.cpp kNN.cpp kNN.h ImageHandler.cpp ImageHandler.h
	g++ -std=c++11 kNNTest.cpp kNN.cpp ImageHandler.cpp -O2 -o knn_test

test_image_handler: TestImageLoad.cpp ImageHandler.cpp ImageHandler.h Auxiliares.cpp Auxiliares.h
	g++ -std=c++11 TestImageLoad.cpp ImageHandler.cpp Auxiliares.cpp -o test_image_handler

test_potencia:
	g++ -std=c++11 TestMetodoPotencia.cpp MetodoPotencia.cpp Matriz.cpp Auxiliares.cpp -o metodoPotencia

psa_test: PSATest.cpp PSA.cpp PSA.h kNN.cpp kNN.h ImageHandler.cpp ImageHandler.h Covarianza.cpp Covarianza.h MetodoPotencia.cpp MetodoPotencia.h Matriz.cpp Matriz.h Auxiliares.cpp Auxiliares.h
	g++ -std=c++11 PSATest.cpp PSA.cpp kNN.cpp ImageHandler.cpp Covarianza.cpp MetodoPotencia.cpp Matriz.cpp Auxiliares.cpp -o psa_test

test_cov:
	g++ -std=c++11 TestCovarianza.cpp Covarianza.cpp MetodoPotencia.cpp Matriz.cpp Auxiliares.cpp -o cov

clean:
	rm -f *.o
	rm -f metodoPotencia cov main test_image_handler knn_test exp_iters exp_knn exp_psa_creacion exp_psa_clasificar exp_knn_tiempo exp_psa_tiempos exp_knn_kfold

