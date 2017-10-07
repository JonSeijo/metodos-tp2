all: main

main: Main.cpp MetodoPotencia.cpp MetodoPotencia.h Matriz.cpp Matriz.h Auxiliares.cpp Auxiliares.h Covarianza.cpp Covarianza.h
	g++ -std=c++11 Main.cpp MetodoPotencia.cpp Matriz.cpp Auxiliares.cpp Covarianza.cpp -o main

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
	rm -f metodoPotencia cov main test_image_handler knn_test