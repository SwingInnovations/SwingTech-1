#ifndef WAHOO_RECT_H
#define WAHOO_RECT_H

#include <vector>

#include "Shape.h"
#include "../Transform.h"

class SWRect : public Shape{
public:
    SWRect(){ ; }
    SWRect(stReal _x, stReal _y, stReal _width, stReal _height){
        stReal hWidth = _width / 2.0f;
        stReal hHeight = _height / 2.0f;

        std::vector<Vector3<stReal>> initialCoordinates;
        initialCoordinates.reserve(4);
        initialCoordinates.push_back(Vector3<stReal>(hWidth-hWidth, hHeight + hHeight, 0.0));
        initialCoordinates.push_back(Vector3<stReal>(hWidth+hWidth, hHeight + hHeight, 0.0));
        initialCoordinates.push_back(Vector3<stReal>(hWidth+hWidth, hHeight - hHeight, 0.0));
        initialCoordinates.push_back(Vector3<stReal>(hWidth - hWidth, hHeight - hHeight, 0.0));

        std::vector<Vector2<stReal>> texCoords;
        texCoords.reserve(4);
        texCoords.push_back(Vector2<stReal>(1.0, 0.0));
        texCoords.push_back(Vector2<stReal>(1.0, 1.0));
        texCoords.push_back(Vector2<stReal>(0.0, 1.0));
        texCoords.push_back(Vector2<stReal>(0.0, 0.0));

        Transform trans;
        trans.setTranslateX(_x);
        trans.setTranslateY(_y);

        Matrix4f transform = trans.getModel();
        //Transformed coordinates
        for(uint32_t i = 0; i < initialCoordinates.size(); i++){
            initialCoordinates[i] = initialCoordinates[i] * transform.toVector4().toVector3();
        }

        positions.reserve(4);
        for(unsigned int i = 0; i < positions.size(); i++){
            positions.push_back(Vertex(initialCoordinates[i], texCoords[i], Vector3<stReal>(0.0, 0.0, 1.0)));
        }

        index.reserve(6);
        index.push_back(0);
        index.push_back(1);
        index.push_back(2);
        index.push_back(3);
        index.push_back(2);
        index.push_back(0);
    }

    SWRect(Vector2<stReal> pos, Vector2<stReal> dim){
        stReal hWidth = (dim.getX() / 2.0f)/STGame::RES_WIDTH;
        stReal hHeight = (dim.getY() / 2.0f)/STGame::RES_HEIGHT;

        std::vector<Vector3<stReal>> initialCoordinates;
        initialCoordinates.push_back(Vector3<stReal>(pos.getX()-hWidth, pos.getY() + hHeight, 0.0));
        initialCoordinates.push_back(Vector3<stReal>(pos.getX()+hWidth, pos.getY() + hHeight, 0.0));
        initialCoordinates.push_back(Vector3<stReal>(pos.getX()+hWidth, pos.getY() - hHeight, 0.0));
        initialCoordinates.push_back(Vector3<stReal>(pos.getX() - hWidth, pos.getY() - hHeight, 0.0));

        std::vector<Vector2<stReal>> texCoords;
        texCoords.push_back(Vector2<stReal>(1.0, 0.0));
        texCoords.push_back(Vector2<stReal>(1.0, 1.0));
        texCoords.push_back(Vector2<stReal>(0.0, 1.0));
        texCoords.push_back(Vector2<stReal>(0.0, 0.0));

        Transform trans;
        trans.setTranslateX(pos.getX());
        trans.setTranslateY(pos.getY());

        Matrix4f transform = trans.getModel();
        //Transformed coordinates
//        for(uint32_t i = 0; i < initialCoordinates.size(); i++){
//            initialCoordinates[i] = initialCoordinates[i] * transform.toVector4().toVector3();
//        }

        positions.reserve(4);
        for(unsigned int i = 0; i < 4; i++){
            positions.push_back(Vertex(initialCoordinates[i], texCoords[i], Vector3<stReal>(0.0, 1.0, 0.0)));
        }

        index.reserve(6);
        index.push_back(0);
        index.push_back(1);
        index.push_back(2);
        index.push_back(3);
        index.push_back(2);
        index.push_back(0);
    }

    int getVertexSize(){
        return 4;
    }

    int getIndexSize(){
        return 6;
    }
    std::vector<Vertex> positions;
    std::vector<int> index;
private:

};

#endif //WAHOO_RECT_H
