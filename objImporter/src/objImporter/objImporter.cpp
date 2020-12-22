#include "objImporter/objImporter.hpp"

ObjImporter::ObjImporter(){
    cout << "OBJIMPORTER::ObjImporter()" << endl;
    fstream file;
    /*std::string path = "./resources/object";
    for (const auto & entry : fs::directory_iterator(path)){
        std::cout << entry.path() << std::endl;
        file.open(entry.path());
        if(file.is_open()) cout << "File " << entry.path() << " openned." << endl;
        else cout << "File " << entry.path() << " failed to open." << endl;
        file.close();
    }*/
}

void ObjImporter::extract(string path){
    fstream file;
    file.open(path);
    if(file.is_open()) cout << "File "+path+" openned." << endl;
    else cout << "File "+path+" failed to open." << endl;

    string line;
    char tmp;
    string name;
    stringstream ss;

    double coords[3], norm[3], txtCoords[2];

    while(getline(file, line)){
        switch(line.at(0)){
            case 'o':
                ss << line;
                ss >> tmp >> name;
                cout << "Object: "+name << endl;
                break;

            case 'v':
                switch(line.at(1)){
                    case ' ':
                        getVertices(line, &coords[0]);
                        break;

                    case 't':
                        getTxtCoords(line, &txtCoords[0]);
                        break;
                    
                    case 'n':
                        getNormals(line, &norm[0]);
                        break;
                }
                break;

            case 'f':
                cout << line << endl;
        }
    }

    file.close();
}

void ObjImporter::getVertices(string line, double* vertices){
    char c;
    string tmp;
    int index = 2;
    bool flag = false;
    while(index < line.length()){
        c = line.at(index);
        if(c != ' ')
            tmp+=c;
        else{
            if(!flag){
                vertices[0] = stod(tmp);
                flag = true;
            }else vertices[1] = stod(tmp);
            tmp = "";
        }
        index++;
    }
    vertices[2] = stod(tmp);
    cout << "Vertices x: " << vertices[0] << " y: " << vertices[1] << " z: " << vertices[2] << endl;
}

void ObjImporter::getNormals(string line, double* normals){
    char c;
    string tmp;
    int index = 3;
    bool flag = false;
    while(index < line.length()){
        c = line.at(index);
        if(c != ' ')
            tmp+=c;
        else{
            if(!flag){
                normals[0] = stod(tmp);
                flag = true;
            }else normals[1] = stod(tmp);
            tmp = "";
        }
        index++;
    }
    normals[2] = stod(tmp);
    cout << "Normals x: " << normals[0] << " y: " << normals[1] << " z: " << normals[2] << endl;
}

void ObjImporter::getTxtCoords(string line, double* txtCoords){
    char c;
    string tmp;
    int index = 3;
    bool flag = false;
    while(index < line.length()){
        c = line.at(index);
        if(c != ' ')
            tmp+=c;
        else{
            txtCoords[0] = stod(tmp);
            tmp = "";
        }
        index++;
    }
    txtCoords[1] = stod(tmp);
    cout << "TxtCoords x: " << txtCoords[0] << " y: " << txtCoords[1] << endl;
}