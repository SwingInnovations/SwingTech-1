#ifndef SWINGTECH1_STMESHLOADER_H
#define SWINGTECH1_STMESHLOADER_H

#include <map>
#include "STMeshCommon.h"
#include "../../../Graphics/STMaterial.h"

/**
 * @brief Refer to this file when making a custom loader.
 */

class MeshLoader{
public:
    /**
     * Loads a mesh from path.
     * @param fileName
     * @return
     */
    //static STMesh_Structure Load(const std::string fileName) = 0;
    /**
     * Loads a mesh from the specified path, and all its submeshes. Submeshes will be children of the "Root" object.
     * @param fileName Path to File
     * @param errFlag  If an error occured somewhere in import, stored here
     * @param tags     Names of Submesh
     * @param dataMesh - MeshData itself.
     * @return
     */
    //Implement this overload.
    //static bool Validate(const std::string& fileName, bool* errFlag, std::vector<STMesh_Structure>* dataMeshes, std::map<std::string, STMaterial>* materials) = 0;
};

#endif //SWINGTECH1_STMESHLOADER_H
