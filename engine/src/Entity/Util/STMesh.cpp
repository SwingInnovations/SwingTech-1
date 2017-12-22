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
                      std::map<std::string, STMaterial *>* materials) {
    return MeshLoader::Validate(fileName, errFlag, meshes, materials);
}
