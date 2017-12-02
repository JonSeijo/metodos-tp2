#ifndef IMAGE_HANDLER
#define IMAGE_HANDLER

#include <bits/stdc++.h>
#include "Auxiliares.h"

using namespace std;

class ImageHandler {
    public:
        ImageHandler(string _path, bool training=true, int pixels=784);
        vector<double> getImagen(int i);
        int getLabel(int i);
        int cantImagenes;
        void printImage(int i);

    private:
        string pathToFile;
        vector<vector<double> > imagenes;
        vector<int> labels;
};

#endif