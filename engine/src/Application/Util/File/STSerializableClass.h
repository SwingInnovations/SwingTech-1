#ifndef SWINGTECH1_STSERIALIZABLECLASS_H
#define SWINGTECH1_STSERIALIZABLECLASS_H

#include <fstream>

class STSerializableClass{
public:
    virtual void save(std::ofstream& ostream) = 0;
    virtual void load(std::istream& istream) = 0;
};

#endif //SWINGTECH1_STSERIALIZABLECLASS_H
