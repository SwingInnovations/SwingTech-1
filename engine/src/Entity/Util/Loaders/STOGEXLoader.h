#ifndef SWINGTECH1_STOGEXLOADER_H
#define SWINGTECH1_STOGEXLOADER_H

#include "STMeshCommon.h"
#include "../../../Graphics/STMaterial.h"

class STOGEXLoader {
public:
    static STMesh_Structure Load(const std::string& fileName);
    static bool Validate(const std::string& fileName, bool *errFlag, std::vector<STMesh_Structure>* meshes, std::map<std::string, STMaterial*>* materials);
};


#endif //SWINGTECH1_STOGEXLOADER_H
