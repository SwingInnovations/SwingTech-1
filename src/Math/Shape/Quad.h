#ifndef WAHOO_QUAD_H
#define WAHOO_QUAD_H

#include "Shape.h"



class Quad : public Shape{
public:

private:
    std::vector<Vertex*> verticies;
    std::vector<int> indicies;
};

#endif //WAHOO_QUAD_H
