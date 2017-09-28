all: main


#kNN no compila, arreglar eso y después meter kNN.cpp acá abajo	
main:
	g++ -std=c++11 Main.cpp MetodoPotencia.cpp Matriz.cpp Auxiliares.cpp Covarianza.cpp -o main

test_potencia:
	g++ -std=c++11 TestMetodoPotencia.cpp MetodoPotencia.cpp Matriz.cpp Auxiliares.cpp -o metodoPotencia

test_cov: 
	g++ -std=c++11 TestCovarianza.cpp Covarianza.cpp MetodoPotencia.cpp Matriz.cpp Auxiliares.cpp -o cov

clean:
	rm -f *.o
	rm -f metodoPotencia cov main