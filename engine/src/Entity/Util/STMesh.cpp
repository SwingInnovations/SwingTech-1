#if __linux__
#include <fstream>
#else
#include <c++/fstream>
#endif

#include <cmath>

#include "STMesh.h"
#include "../../Graphics/STGraphics.h"
//Loaders
#include "Loaders/STOBJLoader.h"
#include "Loaders/STFBXLoader.h"


bool STMesh::Validate(const std::string &fileName, int *typeFlag, std::vector<std::string> *tags,
                      std::vector<STMesh_Structure> *meshes) {
    stUint extenPoint = (stUint)fileName.size() - 4;
    std::string fileExtension = fileName.substr(extenPoint);
    if(fileExtension == ".obj" || fileExtension == ".OBJ"){
        *typeFlag = STMesh::OBJ;
        //return OBJMesh::Validate(fileName, tags, meshes);
        return false;
    }
    else if(fileExtension == ".fbx" || fileExtension == ".FBX"){
        *typeFlag = STMesh::FBX;
        //TODO FBX File Validation and Splitup.
        return false;
    }else if(fileExtension == ".gex"){
        *typeFlag = STMesh::GEX;
        //TODO GEX File Validation and Splitup.
        return true;
    }
    return false;
}

bool STMesh::Validate(const std::string &fileName, bool *errFlag, std::vector<std::string> *tags,
                      std::vector<STMesh_Structure> *meshes) {
    stUint extenPoint = (stUint)fileName.size() - 4;
    std::string fileExtension = fileName.substr(extenPoint);
    if(fileExtension == ".obj" || fileExtension == ".OBJ"){
        return STOBJLoader::Validate(fileName, errFlag, tags, meshes);
    } else if(fileExtension == ".fbx" || fileExtension == ".FBX"){
        return STFBXLoader::Validate(fileName, errFlag, tags, meshes);
    }else if(fileExtension == ".gex"){
        //TODO GEX File Validation and Splitup.
        return true;
    }
    return false;
}

bool STMesh::Validate(const std::string &fileName, bool* errFlag, std::vector<STMesh_Structure>* meshes,
                      std::map<std::string, STMaterial *>* materials) {
    stUint extenPoint = fileName.size() - 4;
    std::string fileExtension = fileName.substr(extenPoint);
    if(fileExtension == ".obj" || fileExtension == ".OBJ"){
        return STOBJLoader::Validate(fileName, errFlag, meshes, materials);
    }
    return false;
}
