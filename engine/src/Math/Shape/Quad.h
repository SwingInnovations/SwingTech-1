#ifndef WAHOO_QUAD_H
#define WAHOO_QUAD_H

#include "Shape.h"



class STQuad : public Shape{
public:
    /**
     * Default constructor for Quad. Meant to act as a Screen Quad.
     */
    STQuad(){
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

    /**
     * Overload Constructor for Quad
     * Takes in Vector4 List.
     * @param data
     */
    STQuad(std::vector<Vector4<stReal>> data){
        std::vector<Vector3<stReal>> points;
        points.push_back(Vector3<stReal>(data[0].getX(), data[0].getY(), 0.f));
        points.push_back(Vector3<stReal>(data[1].getX(), data[1].getY(), 0.f));
        points.push_back(Vector3<stReal>(data[2].getX(), data[2].getY(), 0.f));
        points.push_back(Vector3<stReal>(data[3].getX(), data[3].getY(), 0.f));

        std::vector<Vector2<stReal>> texCoords;
        texCoords.push_back(Vector2<stReal>(data[0].getZ(), data[0].getW()));
        texCoords.push_back(Vector2<stReal>(data[1].getZ(), data[1].getW()));
        texCoords.push_back(Vector2<stReal>(data[2].getZ(), data[2].getW()));
        texCoords.push_back(Vector2<stReal>(data[3].getZ(), data[3].getW()));

        for(stUint i = 0; i < 4; i++) verticies.push_back(Vertex(points[i], texCoords[i], Vector3<stReal>(0.f, 0.f, 0.f)));

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
