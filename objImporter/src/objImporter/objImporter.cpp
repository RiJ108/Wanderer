#include "objImporter/objImporter.hpp"

ObjImporter::ObjImporter(){
    cout << "OBJIMPORTER::ObjImporter()" << endl;
    /*std::string path = "./resources";
    for (const auto & entry : fs::directory_iterator(path))
        std::cout << entry.path() << std::endl;*/
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
    //**Function that read the file and direct what to do with them
    fstream file;
    file.open(path);
    if(file.is_open()) cout << "File "+path+" openned." << endl;
    else cout << "File "+path+" failed to open." << endl;

    string line;
    char tmp;
    string name;
    stringstream ss;

    double *coords, *norms, *txtCoords;
    int *order;

    //**Main loop which get each line of the obj file
    while(getline(file, line)){
        //**Test to determine what the current line is coding for
        switch(line.at(0)){
            case 'o':
                ss << line;
                ss >> tmp >> name;
                cout << "Object: "+name << endl;
                break;

            case 'v':
                switch(line.at(1)){
                    case ' ':
                        coords = (double*)malloc(sizeof(double)*3);
                        getVertices(line, coords);
                        Vertices.push_back(coords);
                        break;

                    case 't':
                        txtCoords = (double*)malloc(sizeof(double)*2);
                        getTxtCoords(line, txtCoords);
                        TxtCoords.push_back(txtCoords);
                        break;
                    
                    case 'n':
                        norms = (double*)malloc(sizeof(double)*3);
                        getNormals(line, norms);
                        Normals.push_back(norms);
                        break;
                }
                break;

            case 'f':
                order = (int*)malloc(sizeof(int)*3);
                getOrder(line, order);
                break;
        }
    }

    //**Simple debug prompt of the Data vector
    cout << "Data size = " << Data.size() << endl;
    file.close();
}

void ObjImporter::getVertices(string line, double* vertices){
    //Cheap and dirty way of retriving the double for the coordinates form a string
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
    //Cheap and dirty way of retriving the double for the normals form a string
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
    //Cheap and dirty way of retriving the double for the textures coordinates form a string
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

void ObjImporter::getOrder(string line, int* order){
    //**Function which get the reference of coordinates, textures coordinates
    //**and normals for the vertices by group of three is provided by the obj file
    //**and stack the data in the Data vector
    stringstream ss;
    ss << line;
    int x0, y0, z0, x1, y1, z1, x2, y2, z2, i;
    string tmp;
    char c;

    //**Exctraction of the indices for coordinates, textures coordinates
    //**and normals for the three vertices of the triangle
    ss >> tmp >> x0 >> c >> y0 >> c >> z0 >> x1 >> c >> y1 >> c >> z1 >> x2 >> c >> y2 >> c >> z2;

    
    //**Storing of datas for the first vertex
    //**TxtCoords temporaly ignored (indexted by y)
    for(i = 0 ; i < 3 ; i++)//Coordinates loop
        Data.push_back(Vertices.at(x0-1)[i]);
    for(i = 0 ; i < 3 ; i++)//Normals loop
        Data.push_back(Normals.at(z0-1)[i]);

    //**Storing of datas for the second vertex
    for(i = 0 ; i < 3 ; i++)//Coordinates loop
        Data.push_back(Vertices.at(x1-1)[i]);
    for(i = 0 ; i < 3 ; i++)//Normals loop
        Data.push_back(Normals.at(z1-1)[i]);

    //**Storing of datas for the third vertex
    for(i = 0 ; i < 3 ; i++)//Coordinates loop
        Data.push_back(Vertices.at(x2-1)[i]);
    for(i = 0 ; i < 3 ; i++)//Normals loop
        Data.push_back(Normals.at(z2-1)[i]);
}

vector<float> ObjImporter::getData(){
    return Data;
}

int ObjImporter::getDataSize(){
    return Data.size();
}