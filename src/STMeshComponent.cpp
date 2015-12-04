#include "STMeshComponent.h"

STMeshComponent::STMeshComponent(const std::string &fileName, int type) {
    std::vector<Vector3<stReal>> vertex;
    std::vector<Vector2<stReal>> texCoord;
    std::vector<Vector3<stReal>> normal;
    std::vector<Vector3<stReal>> tangent;
    std::vector<Vector3<stReal>> biTangent;
    std::vector<int> index;

    int numVert = 0;

    if(type == STMesh::OBJ){
        auto tMesh = new OBJMesh(fileName);
        numVert = tMesh->getVerticiesSize();
        m_drawCount = tMesh->getIndiciesSize();
        vertex.reserve(numVert);
        texCoord.reserve(numVert);
        normal.reserve(numVert);
        for(unsigned int i = 0; i < numVert; i++){
            vertex.push_back(*tMesh->verticies[i].getVertex());
            texCoord.push_back(*tMesh->verticies[i].getTexCoord());
            normal.push_back(*tMesh->verticies[i].getNormal());
        }
        tangent = genTangent(vertex, texCoord);
        biTangent = genBiTangent(vertex, texCoord);
        delete tMesh;
        tMesh = 0;
    }

    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);

    glGenBuffers(NUM_BUFFERS, m_VBO);


    glBindBuffer(GL_ARRAY_BUFFER, m_VBO[VERTEX_BUFFER]);
    glBufferData(GL_ARRAY_BUFFER, numVert*sizeof(vertex[0]), &vertex[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO[TEXCOORD_BUFFER]);
    glBufferData(GL_ARRAY_BUFFER, numVert* sizeof(texCoord[0]), &texCoord[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO[NORMAL_BUFFER]);
    glBufferData(GL_ARRAY_BUFFER, numVert* sizeof(normal[0]), &normal[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO[TANGENT_BUFFER]);
    glBufferData(GL_ARRAY_BUFFER, numVert* sizeof(tangent[0]), &tangent[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO[BITANGENT_BUFFER]);
    glBufferData(GL_ARRAY_BUFFER, numVert*sizeof(&biTangent[0]), &biTangent[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    std::cout << "Added Mesh Component: " << fileName << std::endl;
}
/*-OBJ Mesh-*/
OBJMesh::OBJMesh() {

}

OBJMesh::OBJMesh(const std::string &filename) {
    std::ifstream in(filename.c_str(), std::ios_base::in);
    if(!in){
        std::cout << "Invalid File! Could not load: " << filename << std::endl;
        return;
    }
    std::string line;
    while(std::getline(in, line)){
        //Vertex Extraction
        if(line[0] == 'v' && line[1] == ' '){
            std::string vals = line.substr(2);
            stReal _x = 0.0f, _y = 0.0f, _z = 0.0f;

            std::cout << "Extracting vX. " << std::endl;
            std::string vX = vals.substr(0, vals.find(' '));
            _x = (stReal)atof(vX.c_str());

            std::cout << "Extracting vY. " << std::endl;
            std::string vY = vals.substr(vX.length()-1, vals.find(' '));
            _y = (stReal)atof(vY.c_str());

            std::cout << "Extracting vZ. " << std::endl;
            std::string vZ = vals.substr(vals.find_last_of(' ')+1);
            _z = (stReal)atof(vZ.c_str());
            _vertex.push_back(Vector3<stReal>(_x, _y, _z));
        }
        //Texcoord Extraction
        if(line[0] == 'v' && line[1] == 't' && line[2] == ' '){
            std::string vals = line.substr(3);
            stReal _u = 0.0f, _v = 0.0f;

            std::cout << "Extracting vU" << std::endl;
            std::string tU = vals.substr(0, vals.find(' '));
            _u = (stReal)atof(tU.c_str());

            std::cout << "Extracting vV" << std::endl;
            std::string tV = vals.substr(tU.length()+1, vals.find(' '));
            _v = (stReal)atof(tV.c_str());
            _texCoord.push_back(Vector2<stReal>(_u, _v));
        }
        //Normal Extraction
        if(line[0] == 'v' && line[1] == 'n'&& line[2] == ' '){
            std::string vals = line.substr(3);
            stReal _x = 0.0f, _y = 0.0f, _z = 0.0f;

            std::cout << "Extracting vNX" << std::endl;
            std::string nX = vals.substr(0, vals.find(' '));
            _x = (stReal)atof(nX.c_str());

            std::cout << "Extracting vNY" << std::endl;
            std::string nY = vals.substr(nX.length()-1, vals.find(' '));
            _y = (stReal)atof(nY.c_str());

            std::cout << "Extracting vNZ" << std::endl;
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
            i = (int)atoi(v1.c_str());
            int midLen1 = face1.find_last_of('/')-face1.find('/')+1;
            std::string t1 = face1.substr(face1.find('/')+1, midLen1);
            j = (int)atoi(t1.c_str());
            std::string n1 = face1.substr(face1.find_last_of('/')+1);
            k = (int)atoi(n1.c_str());
            i--; j--; k--;
            _index.push_back(i); _index.push_back(j); _index.push_back(k);
            int midLen = hLine.find_last_of(' ')-hLine.find(' ')+1;
            std::string face2 = hLine.substr(hLine.find(' ')+1, midLen);
            std::string v2 = face2.substr(0, face2.find('/'));
            i = (int)atoi(v2.c_str());
            int midLen2 = face2.find_last_of('/')-face2.find('/')+1;
            std::string t2 = face2.substr(v2.length()+1, midLen2);
            j = (int)atoi(t2.c_str());
            std::string n2 = face2.substr(face2.find_last_of('/')+1);
            k = (int)atoi(n2.c_str());
            i--; j--; k--;
            _index.push_back(i); _index.push_back(j); _index.push_back(k);
            std::string face3 = hLine.substr(hLine.find_last_of(' ')+1);
            std::string v3 = face3.substr(0, face3.find('/'));
            i = (int)atoi(v3.c_str());
            int midLen3 = face3.find_last_of('/')-face3.find('/')+1;
            std::string t3 = face3.substr(face3.find('/')+1, midLen3);
            j = (int)atoi(t3.c_str());
            std::string n3 = face3.substr(face3.find_last_of('/')+1);
            k = (int)atoi(n3.c_str());
            i--; j--; k--;
            _index.push_back(i); _index.push_back(j); _index.push_back(k);
        }
    }
    std::cout << "Finished Extracting verticies "<< std::endl;
    int inCount = 0;
    in.close();
    //TODO Handle if any of the parameters are invalid;

    for(unsigned int i = 0, S = (int)_index.size(); i < S; i+=3){
        verticies.push_back(Vertex(_vertex.at(_index.at(i)), _texCoord.at(_index.at(i+1)), _normal.at(_index.at(i+2))));
        indicies.push_back(inCount);
        inCount++;
    }
    std::cout << "Finished loading mesh. " << std::endl;
}

OBJMesh::~OBJMesh() {

}
