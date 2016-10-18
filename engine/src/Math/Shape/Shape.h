#ifndef WAHOO_SHAPE_H
#define WAHOO_SHAPE_H

#include <vector>

#include "../Vertex.h"


/*
 *  TODO - Refractor this to only contain point information
 */
class Shape{
public:
    Shape(){ }

    Vertex* getVerticies(){
        return &vertex[0];
    }

    int* getIndicies(){
        return &indicies[0];
    }

    virtual int getVertexSize(){ return -1; }
    virtual int getIndexSize(){ return -1; }


    bool intersects(Vector2<stReal>& point){
        return false;
    }

    bool intersects(Shape& other){
        return false;
    }

    virtual bool contains(Vector2<stReal>& point){ return false; }
protected:
    std::vector<int> indicies;
    std::vector<Vertex> vertex;
};

#endif //WAHOO_SHAPE_H
