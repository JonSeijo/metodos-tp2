#ifndef IMAGE_HANDLER
#define IMAGE_HANDLER

#include <bits/stdc++.h>
using namespace std;

class ImageHandler {
    public:
        ImageHandler(string _path);
        vector<double> getImagen(int i);
        int getLabel(int i);

    private:
        string pathToFile;
        vector<vector<double> > imagenes;
        vector<int> labels;
};

#endif