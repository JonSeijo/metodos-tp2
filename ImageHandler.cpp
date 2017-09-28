#include "ImageHandler.h"

ImageHandler::ImageHandler(string _path) {
    pathToFile = _path;
    cout << "path: " <<  pathToFile << "\n";
}

vector<double> ImageHandler::getImagen(int i) {
    if (i >= (int)imagenes.size()) {
        cerr << "ImageHandler::getImagen: La imagen " << i << " no existe! (posiblemente indice fuera de rango)\n";
    }
    return this->imagenes[i];
}

int ImageHandler::getLabel(int i) {
    if (i >= (int)labels.size()) {
        cerr << "ImageHandler::getLabel: No hay label para la imagen " << i << " (posiblemente indice fuera de rango)\n";
    }
    return this->labels[i];
}
