#ifndef WAHOO_QUAD_H
#define WAHOO_QUAD_H

#include "Shape.h"



class Quad : public Shape{
public:
    Quad(){
        std::vector<Vector3<stReal>> points;
        points.push_back(Vector3<stReal>(-1.0f, 1.0f, 0.0f));
        points.push_back(Vector3<stReal>(-1.0f, -1.0f, 0.0f));
        points.push_back(Vector3<stReal>(1.0f, -1.0f, 0.0f));
        points.push_back(Vector3<stReal>(1.0f, 1.0f, 0.0f));

        std::vector<Vector2<stReal>> texCoords;
        texCoords.push_back(Vector2<stReal>(0.0f, 1.0f));
        texCoords.push_back(Vector2<stReal>(0.0f, 0.0f));
        texCoords.push_back(Vector2<stReal>(1.0f, 0.0f));
        texCoords.push_back(Vector2<stReal>(1.0f, 1.0f));

        for(unsigned int i = 0; i <4; i++){
            verticies.push_back(Vertex(points[i], texCoords[i], Vector3<stReal>(0.0f, 0.0f, 0.0f)));
        }

        indicies.push_back(0);
        indicies.push_back(1);
        indicies.push_back(2);
        indicies.push_back(2);
        indicies.push_back(3);
        indicies.push_back(0);

        vertSize = 4;
        indSize = 6;
    }

    int getIndSize(){ return indSize; }
    int getVertSize(){ return vertSize; }

    std::vector<Vertex> verticies;
    std::vector<int> indicies;
private:
    int vertSize;
    int indSize;

};

#endif //WAHOO_QUAD_H
