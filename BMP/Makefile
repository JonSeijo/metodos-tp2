CC=c99
CFLAGS= -Wall -fPIC -Wextra -pedantic -O0 -g -lm -Wno-unused-variable -Wno-unused-parameter -fPIC
LIBS = -lGL -lGLU -lglut -lpthread -lm 

all: main


main: main.c bmp.o
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

bmp.o: bmp.c bmp.h
	$(CC) $(CFLAGS) -c $< -o $@ $(LIBS)

clean:
	rm -f *.o
	rm -f main