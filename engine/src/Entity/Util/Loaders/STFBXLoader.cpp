#include "STFBXLoader.h"

//TODO Implement
STFBXLoader::STFBXLoader() {

}

bool STFBXLoader::Validate(const std::string &fileName, bool *errFlag, std::vector<std::string> *tags,
                           std::vector<STMesh_Structure> *dataMesh) {
    //TODO Implement
    std::cout << "Loading FBX File: " << fileName << std::endl;
    return false;
}

STMesh_Structure STFBXLoader::Load(const std::string fileName) {


    return STMesh_Structure();
}
