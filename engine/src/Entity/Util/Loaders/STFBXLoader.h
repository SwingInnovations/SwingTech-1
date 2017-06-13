#ifndef SWINGTECH1_STFBXLOADER_H
#define SWINGTECH1_STFBXLOADER_H

/**
 * @author Nathan Danque
 */

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>

#include "STMeshCommon.h"

class STFBXLoader {
    //Helper Classes
    class FBXVariant{
        enum class Type{Int, Float, String, Obj};
    public:
        Type type;
        union{ int value; float floatValue; const char* strValue; FBXVariant* _OBJ; };
        int asInt(){ return value; }
        float asFloat(){ return floatValue; }
        void operator=(int n){ value = n; type = Type::Int; }
        void operator=(float f){ floatValue = f; type = Type::Float; }
        void operator=(const char* str){ strValue = strdup(str); type=Type::String;}
        FBXVariant(){;}
    };

    struct FBXNode{
        struct FBXNodeProperty{
            std::string dataType;
            std::string dataValue;
        };
    };

    enum class LoadMode{ ASCII, BINARY };
public:
    STFBXLoader();
    static STMesh_Structure Load(const std::string fileName);
    static bool Validate(const std::string& fileName, bool* errFlag, std::vector<std::string>* tags, std::vector<STMesh_Structure>* dataMesh);
};


#endif //SWINGTECH1_STFBXLOADER_H
