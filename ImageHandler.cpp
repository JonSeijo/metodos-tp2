#include "ImageHandler.h"

// 784 pixels por defecto
ImageHandler::ImageHandler(string _filePath, int pixels) {
    pathToFile = _filePath;
    ifstream file(_filePath);

    // El header no me interesa
    string header;
    getline(file, header);

    cantImagenes = 0;

    while (file.good()) {

        // Guardo el label correspondiente
        string label;
        getline(file, label, ',');

        // Importante para terminar bien las iteraciones
        if (label.size() == 0) {
            break;
        }

        labels.push_back(stoi(label));

        string lineaDato;
        vector<double> imagen(pixels, 0);

        string dato;
        for (int p = 0; p < pixels-1; p++) {
            getline(file, dato, ',');
            imagen[p] = stoi(dato);
        }
        // Ultimo pixel aparte pues csv no termina con ','
        getline(file, dato, '\n');
        imagen[pixels-1] = stoi(dato);

        imagenes.push_back(imagen);
        cantImagenes++;
        // cout << "Cargando imagen: " << cantImagenes << "\n";
    }
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

void ImageHandler::printImage(int i) {
    vector<double> imagen = getImagen(i);
    cout << "\n\n\nLabel: " << getLabel(i) << "\n";
    for (int i = 0; i < 28; i++) {
        for (int j = 0; j < 28; j++) {
            cout << (imagen[j + 28*i] != 0 ? "1" : " ") << " ";
        }
        cout << "\n";
    }
}