#ifndef WAHOO_VERTEX_H
#define WAHOO_VERTEX_H

#include <string>
#include <sstream>

#include "Vector.h"

class Vertex{
public:
    Vertex(const Vector3<stReal>& vert, const Vector2<stReal>& tex, const Vector3<stReal> normal){
        this->_vertex = vert;
        this->_texCoord = tex;
        this->_normal = normal;
    }

    inline std::string info(){
        std::ostringstream buff;
        buff << "Vertex(X, Y, Z): " << _vertex.getX() << " , " << _vertex.getY() << " , " << _vertex.getZ() << "\n";
        buff << "Texcoord(X, Y, Z): " << _texCoord.getX()<< " , " << _texCoord.getY() << "\n";
        buff << "Normal(X, Y, Z): " << _normal.getX() << " , " << _normal.getY() << " , "<< _normal.getZ() << "\n";
        return buff.str();
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
