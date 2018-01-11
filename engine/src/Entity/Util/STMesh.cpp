#include <fstream>
#include <cmath>

#include "STMesh.h"
#include "../../Graphics/STGraphics.h"
//Loaders
#include "Loaders/STOBJLoader.h"
#include "Loaders/STMeshLoader.h"

/**
 * Validates the imported Mesh using Mesh Loader
 * @param fileName
 * @param errFlag
 * @param meshes
 * @param materials
 * @return
 */
bool STMesh::Validate(const std::string &fileName, bool* errFlag, std::vector<STMesh_Structure>* meshes,
                      std::map<std::string, std::shared_ptr<STMaterial>>* materials) {
    if(fileName.substr(fileName.length() - 9) == ".stEntity"){
        return false;
    }else{
        return MeshLoader::Validate(fileName, errFlag, meshes, materials);
    }
}
