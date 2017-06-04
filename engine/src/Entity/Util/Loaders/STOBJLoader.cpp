#include "STOBJLoader.h"

STOBJLoader::STOBJLoader() {

}

/**
 * @author Loads the OBJ Mesh(s) from File.
 * @param fileName
 * @param errFlag
 * @param tags
 * @param dataMesh
 * @return True if more than one mesh was loaded, otherwise false.
 */
bool STOBJLoader::Validate(const std::string &fileName, bool *errFlag, std::vector<std::string> *tags,
                           std::vector<STMesh_Structure> *dataMesh) {
    stUint vertCount, texCount, normCount, objCount, lastVertCount, lastTexCount, lastNormCount;
    vertCount = texCount = normCount = objCount = lastVertCount = lastNormCount = lastTexCount = 0;
    std::string lastTag = "";
    std::vector<Vector3<stUint>> vertCounts;
    std::vector<Vector3<stReal>> _vertex;
    std::vector<Vector2<stReal>> _texCoord;
    std::vector<Vector3<stReal>> _normal;
    std::vector<int> _index;

    stInt counter = 0;

    auto extractVector3 = [](std::string str){
        stReal arr[3];
        stInt counter = 0;
        stReal temp;
        std::stringstream buff(str);
        while(buff >> temp){
            arr[counter] = temp;
            counter++;
        }
        return Vector3<stReal>(arr[0], arr[1], arr[2]);
    };

    auto extractVector2 = [](std::string str){
        stReal arr[2];
        stInt counter = 0;
        stReal temp;
        std::stringstream buff(str);
        while(buff >> temp){
            arr[counter] = temp;
            counter++;
        }

        return Vector2<stReal>(arr[0], arr[1]);
    };

    //Internal function to extract face and store in Vector3
    auto extractFace = [](std::string &str) {
        std::vector<stInt> ext_ind;
        stInt temp;
        for (stUint i = 0, L = (stUint) str.length(); i < L; i++) {
            if (str[i] == '/') str[i] = ' ';
        }
        std::stringstream buff(str);
        while (buff >> temp) ext_ind.push_back(temp);

        return Vector3<stInt>(ext_ind[0], ext_ind[1], ext_ind[2]);
    };

    auto splitFace = [](std::string str) {
        std::vector<std::string> ret;
        std::string temp;
        std::stringstream buff(str);
        while (buff >> temp) ret.push_back(temp);

        return ret;
    };

    std::ifstream in(fileName.c_str(), std::ios_base::in);
    if (!in) {
        std::cerr << "Invalid file! Could not load: " << fileName << std::endl;
        *errFlag = false;
        return false;
    }
    std::string line;
    if (in.good()) {
        while (std::getline(in, line)) {
            //Vertex Extraction
            if (line[0] == 'g') {
                (*tags).push_back(line.substr(2));
            }

            if (line[0] == 'v' && line[1] == ' ') {
                if (lastTag == "f") {
                    if(_vertex.empty()){
                        *errFlag = false;
                        return false;
                    }
                    if(_texCoord.empty()){
                        *errFlag = false;
                        return false;
                    }
                    if(_normal.empty()){
                        *errFlag = false;
                        return false;
                    }
                    if(_index.size() % 3 != 0){
                        *errFlag = false;
                        return false;
                    }
                    std::vector<int> adjustedIndicies;
                    adjustedIndicies.reserve(_index.size());
                    std::vector<Vertex> vertexList;
                    std::vector<int> indexList;
                    stUint ind = 0;

                    lastVertCount++;
                    lastTexCount++;
                    lastNormCount++;

                    if ((*dataMesh).size() > 0) {
                        for (stUint i = 0, S = (stUint) _index.size(); i < S; i += 3) {
                            adjustedIndicies.push_back(_index.at(i) - lastVertCount);
                            adjustedIndicies.push_back(_index.at(i + 1) - lastTexCount);
                            adjustedIndicies.push_back(_index.at(i + 2) - lastNormCount);
                        }
                    } else adjustedIndicies = _index;
                    for (stUint i = 0, S = (stUint) adjustedIndicies.size(); i < S; i += 3) {
                        Vertex vert(_vertex[adjustedIndicies.at(i)], _texCoord[adjustedIndicies.at(i + 1)],
                                    _normal[_index.at(i + 2)]);
                        vertexList.push_back(vert);
                        indexList.push_back(ind);
                        ind++;
                    }
                    STMesh_Structure mesh;
                    mesh.m_vertices = vertexList;
                    mesh.m_indices = indexList;
                    (*dataMesh).push_back(mesh);//Mesh has been added to the list.

                    lastVertCount = vertCount - 1;
                    lastTexCount = texCount - 1;
                    lastNormCount = normCount - 1;

                    _vertex.clear();
                    _texCoord.clear();
                    _normal.clear();
                    _index.clear();
                    adjustedIndicies.clear();
                }

                _vertex.push_back(extractVector3(line.substr(2)));
                vertCount++;
                lastTag = "v";
            }
            //Texcoord Extraction
            if (line[0] == 'v' && line[1] == 't' && line[2] == ' ') {
                _texCoord.push_back(extractVector2(line.substr(3)));
                texCount++;
            }
            //Normal Extraction
            if (line[0] == 'v' && line[1] == 'n' && line[2] == ' ') {
                _normal.push_back(extractVector3(line.substr(3)));
                normCount++;
            }

            //Index Extraction
            if (line[0] == 'f' && line[1] == ' ') {
                auto faceStrings = splitFace(line.substr(2));
                Vector3<stInt> values;
                Vector3<stInt> cached[3];
                stUint cachedCounter = 0;
                for(stUint i = 0; i < 3; i++){
                    values = extractFace(faceStrings.at(i));
                    if(i == 0 || i == 2){
                        cached[cachedCounter++] = values;
                    }
                    _index.push_back(values.getX() - 1);
                    _index.push_back(values.getY() - 1);
                    _index.push_back(values.getZ() - 1);
                }
                if(faceStrings.size() > 3){
                    cached[cachedCounter] = extractFace(faceStrings.at(3));
                    for(stUint i = 0; i < 3; i++){
                        _index.push_back(cached[i].getX() - 1);
                        _index.push_back(cached[i].getY() - 1);
                        _index.push_back(cached[i].getZ() - 1);
                    }
                }
                lastTag = "f";
            }
            counter++;
        }
        in.close();

        if (lastTag == "f") {
            std::vector<int> adjustedIndicies;
            auto check = adjustedIndicies.empty();
            std::vector<Vertex> vertexList;
            std::vector<int> indexList;
            stUint ind = 0;
            lastVertCount++;
            lastTexCount++;
            lastNormCount++;
            if ((*dataMesh).size() > 0) {
                for (stUint i = 0, S = (stUint) _index.size(); i < S; i += 3) {
                    adjustedIndicies.push_back(_index.at(i) - lastVertCount);
                    adjustedIndicies.push_back(_index.at(i + 1) - lastTexCount);
                    adjustedIndicies.push_back(_index.at(i + 2) - lastNormCount);
                }
            } else {
                adjustedIndicies = _index;
            }
            auto adSize = adjustedIndicies.size();
            for (stUint i = 0, S = (stUint) adjustedIndicies.size(); i < S; i += 3) {
                Vertex vert(_vertex[adjustedIndicies.at(i)], _texCoord[adjustedIndicies.at(i + 1)],
                            _normal[_index.at(i + 2)]);
                vertexList.push_back(vert);
                indexList.push_back(ind);
                ind++;
            }
            STMesh_Structure mesh;
            mesh.m_vertices = vertexList;
            mesh.m_indices = indexList;
            (*dataMesh).push_back(mesh);//Mesh has been added to the list.

            _vertex.clear();
            _texCoord.clear();
            _normal.clear();
            _index.clear();
        }
    }
    return (*dataMesh).size() > 1;
}


