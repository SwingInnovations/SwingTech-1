#ifndef SWINGTECH1_STSERIALIZEABLE_H
#define SWINGTECH1_STSERIALIZEABLE_H

#include <fstream>
#include <string>
#include <c++/cstring>
#include "../../../Math/STCore.h"

class STSerializableUtility{
public:
    /**
     * Writes Stream to output buffer.
     * @param name
     * @param out
     */
    static void WriteString(const char* name, std::ofstream& out){
        auto len = (stUint)strlen(name)+1;
        out.write((char*)&len, sizeof(stUint));
        out.write(name, len);
    }

    /**
     * Helper Function. Reads String from Input Buffer
     * @param in
     * @return
     */
    static std::string ReadString(std::ifstream& in){
        stUint stringLength = 0;
        in.read((char*)&stringLength, sizeof(stringLength));
        auto stringBuffer = new char[stringLength];
        in.read(stringBuffer, stringLength);
        stringBuffer[stringLength-1] = '\0';
        std::string ret(stringBuffer);
        delete[] stringBuffer;
        return ret;
    }
};

#endif //SWINGTECH1_STSERIALIZEABLE_H
