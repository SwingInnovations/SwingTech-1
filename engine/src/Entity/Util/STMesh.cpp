#include <c++/fstream>
#include "STMesh.h"
#include "../../Graphics/STGraphics.h"

/*-OBJ Mesh-*/
OBJMesh::OBJMesh() {

}

OBJMesh::OBJMesh(const std::string &filename) {
    std::ifstream in(filename.c_str(), std::ios_base::in);

    if(!in){
        std::cout << "Invalid File! Could not load: " << filename << std::endl;
        return;
    }

    unsigned int counter = 0;

    std::string line; //Store line from text file here.
    if(in.good()){
        while(std::getline(in, line)){
            counter++;
            //Vertex Extraction
            if(line[0] == 'v' && line[1] == ' '){
                std::string vals = line.substr(2);
                stReal _x = 0.0f, _y = 0.0f, _z = 0.0f;

                std::string vX = vals.substr(0, vals.find(' '));
                _x = (stReal)atof(vX.c_str());

                std::string vY = vals.substr(vX.length()+1, vals.find(' '));
                _y = (stReal)atof(vY.c_str());

                std::string vZ = vals.substr(vals.find_last_of(' ')+1);
                _z = (stReal)atof(vZ.c_str());

                _vertex.push_back(Vector3<stReal>(_x, _y, _z));
            }
            //Texcoord Extraction
            if(line[0] == 'v' && line[1] == 't' && line[2] == ' '){
                std::string vals = line.substr(3);
                stReal _u = 0.0f, _v = 0.0f;
                std::string tU = vals.substr(0, vals.find(' '));
                _u = (stReal)atof(tU.c_str());
                std::string tV = vals.substr(tU.length()+1, vals.find(' '));
                _v = (stReal)atof(tV.c_str());

                _texCoord.push_back(Vector2<stReal>(_u, _v));
            }
            //Normal Extraction
            if(line[0] == 'v' && line[1] == 'n'&& line[2] == ' '){
                std::string vals = line.substr(3);
                stReal _x = 0.0f, _y = 0.0f, _z = 0.0f;
                std::string nX = vals.substr(0, vals.find(' '));

                _x = (stReal)atof(nX.c_str());
                std::string nY = vals.substr(nX.length()+1, vals.find(' '));

                _y = (stReal)atof(nY.c_str());
                std::string nZ = vals.substr(vals.find_last_of(' ')+1);

                _z = (stReal)atof(nZ.c_str());

                _normal.push_back(Vector3<stReal>(_x, _y, _z));
            }

            //Index Extraction
            if(line[0] == 'f' && line[1] == ' '){
                std::string hLine = line.substr(2);
                int i = 0, j = 0, k = 0;
                //first element
                std::string face1 = hLine.substr(0, hLine.find(' '));
                std::string v1 = face1.substr(0, face1.find('/'));
                i = atoi(v1.c_str());
                int midLen1 = face1.find_last_of('/') - face1.find('/')+1;
                std::string t1 = face1.substr(face1.find('/')+1, midLen1);
                j = atoi(t1.c_str());
                std::string n1 = face1.substr(face1.find_last_of('/') + 1);
                k = atoi(n1.c_str());
                i--; j--; k--;
                _index.push_back(i); _index.push_back(j); _index.push_back(k);
                int midLen = hLine.find_last_of(' ') - hLine.find(' ') + 1;
                std::string face2 = hLine.substr(hLine.find(' ') + 1, midLen);
                std::string v2 = face2.substr(0, face2.find('/'));
                i = atoi(v2.c_str());
                int midLen2 = face2.find_last_of('/') - face2.find('/') + 1;
                std::string t2 = face2.substr(v2.length()+1, midLen2);
                j = atoi(t2.c_str());
                std::string n2 = face2.substr(face2.find_last_of('/') + 1);
                k = atoi(n2.c_str());
                i--; j--; k--;
                _index.push_back(i); _index.push_back(j); _index.push_back(k);
                std::string face3 = hLine.substr(hLine.find_last_of(' ') + 1);
                std::string v3 = face3.substr(0, face3.find('/'));
                i = atoi(v3.c_str());
                int midLen3 = face3.find_last_of('/')-face3.find('/') + 1;
                std::string t3 = face3.substr(face3.find('/')+1, midLen3);
                j = atoi(t3.c_str());
                std::string n3 = face3.substr(face3.find_last_of('/')+1);
                k = atoi(n3.c_str());
                i--; j--; k--;
                _index.push_back(i); _index.push_back(j); _index.push_back(k);
            }
        }
        in.close();
    }

    std::cout << "Found: " << counter << " lines." << std::endl;

    int inCount = 0;

    for(unsigned int i = 0, S = (int)_index.size(); i < S; i+=3){
        Vertex vert(_vertex.at((int)_index.at(i)), _texCoord.at((int)_index.at(i+1)), _normal.at((int)_index.at(i+2)));
        verticies.push_back(vert);
        indicies.push_back(inCount);
        inCount++;
    }
    std::cout << "Finished loading mesh. " << std::endl;
}

OBJMesh::~OBJMesh() {

}

//void OBJMesh::SplitUp(const std::string &filename, std::vector<Vector2> bounds, std::vector<std::string> tags) {
//    int counter = 0;
//    std::ifstream in(filename.c_str(), std::ios_base::in);
//    std::vector<int> ind;
//    if(in.good()){
//        std::string line;
//        while(std::getline(in, line)) {
//            if (line[0] == 'g') {
//                ind.push_back(counter);
//                tags.push_back(line.substr(1));
//                if (counter != 0) ind.push_back(counter - 1);
//            }
//            if(ind.size() >= 2){ bounds.push_back(Vector2(ind[0], ind[1])); }
//            counter++;
//        }
//    }
//}
