#if __linux__
#include <fstream>
#else
#include <c++/fstream>
#endif

#include <cmath>

#include "STMesh.h"
#include "../../Graphics/STGraphics.h"
#include "Loaders/STOBJLoader.h"


bool STMesh::Validate(const std::string &fileName, int *typeFlag, std::vector<std::string> *tags,
                      std::vector<STMesh_Structure> *meshes) {
    stUint extenPoint = (stUint)fileName.size() - 4;
    std::string fileExtension = fileName.substr(extenPoint);
    if(fileExtension == ".obj"){
        *typeFlag = STMesh::OBJ;
        //return OBJMesh::Validate(fileName, tags, meshes);
        return false;
    }
    else if(fileExtension == ".fbx"){
        *typeFlag = STMesh::FBX;
        //TODO FBX File Validation and Splitup.
        return true;
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
    if(fileExtension == ".obj"){
        return STOBJLoader::Validate(fileName, errFlag, tags, meshes);
    }
    else if(fileExtension == ".fbx"){
        //TODO FBX File Validation and Splitup.
        return true;
    }else if(fileExtension == ".gex"){
        //TODO GEX File Validation and Splitup.
        return true;
    }
    return false;
}
