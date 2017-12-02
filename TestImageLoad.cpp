#include "ImageHandler.h"
#include "Auxiliares.h"

using namespace std;

int main() {
    ImageHandler imageHandler("data/train.csv");
    // ImageHandler imageHandler("pruebas/csvtest.csv");

    int cantImagenes = imageHandler.cantImagenes;

    imageHandler.printImage(0);
    imageHandler.printImage(1);
    imageHandler.printImage(2);
    imageHandler.printImage(3);
    imageHandler.printImage(4);
    imageHandler.printImage(cantImagenes-1);

}