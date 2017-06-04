#ifndef SWINGTECH1_STOBJLOADER_H
#define SWINGTECH1_STOBJLOADER_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

#include "STMeshCommon.h"

/**
 * @author Nathan Danque
 * @brief Serves as the OBJ Loader for SwingTech1
 */


class STOBJLoader {
public:
    STOBJLoader();
    static bool Validate(const std::string& fileName, bool* errFlag, std::vector<std::string> *tags, std::vector<STMesh_Structure>* dataMesh);
};


#endif //SWINGTECH1_STOBJLOADER_H
