#ifndef SWINGTECH1_STSERIALIZABLESTRUCT_H
#define SWINGTECH1_STSERIALIZABLESTRUCT_H

#include <fstream>

struct STSerializableStruct{
    virtual void save(std::ofstream& out) = 0;
    virtual void load(std::ifstream& in) = 0;
};

#endif //SWINGTECH1_STSERIALIZABLESTRUCT_H
