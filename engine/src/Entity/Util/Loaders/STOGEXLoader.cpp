#include <fstream>
#include "STOGEXLoader.h"

#include "OpenGEX/OpenGEX/OpenGEX.h"

STMesh_Structure STOGEXLoader::Load(const std::string &fileName) {
    //TODO Implement This
    return STMesh_Structure();
}

bool STOGEXLoader::Validate(const std::string &fileName, bool *errFlag, std::vector<STMesh_Structure> *meshes,
                            std::map<std::string, STMaterial *> *materials) {
    OGEX::OpenGexDataDescription ogxDataDescrip;
    std::ifstream ifs(fileName.c_str());
    std::string contents((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
    DataResult res = ogxDataDescrip.ProcessText(contents.c_str());
    if(res == kDataOkay){
        const Structure* structure = ogxDataDescrip.GetRootStructure()->GetFirstSubnode();
        while(structure){

            structure = structure->Next();
        }
    }
    return false;
}
