all:
	g++ -std=c++11 TestMetodoPotencia.cpp MetodoPotencia.cpp Matriz.cpp Auxiliares.cpp -o metodoPotencia

clean:
	rm metodoPotencia