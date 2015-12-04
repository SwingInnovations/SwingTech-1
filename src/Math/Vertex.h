#ifndef WAHOO_VERTEX_H
#define WAHOO_VERTEX_H

#include "Vector.h"

class Vertex{
public:
    Vertex(const Vector3<stReal>& vert, const Vector2<stReal>& tex, const Vector3<stReal> normal){
        this->_vertex = vert;
        this->_texCoord = tex;
        this->_normal = normal;
    }

    Vector3<stReal> *getVertex(){ return &_vertex; }
    Vector2<stReal> *getTexCoord(){ return &_texCoord; }
    Vector3<stReal> *getNormal(){ return &_normal; }
private:
    Vector3<stReal> _vertex;
    Vector2<stReal> _texCoord;
    Vector3<stReal> _normal;
};

#endif //WAHOO_VERTEX_H
