#ifndef OBJIMPORTER
#define OBJIMPORTER

#include <iostream>
#include <fstream>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

class ObjImporter{
public:
    ObjImporter();
    void extract(string path);
    void getVertices(string line, double* vertices);
    void getNormals(string line, double* normals);
    void getTxtCoords(string line, double* txtCoords);
};

#endif 
