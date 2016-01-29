#ifndef WAHOO_SHAPE_H
#define WAHOO_SHAPE_H

#include <vector>

#include "../Vertex.h"

class Shape{
public:
    Shape(){ }

    Vertex* getVerticies(){
        return &vertex[0];
    }

    int* getIndicies(){
        return &indicies[0];
    }
protected:
    std::vector<int> indicies;
    std::vector<Vertex> vertex;
};

#endif //WAHOO_SHAPE_H
