#ifndef WAHOO_RECT_H
#define WAHOO_RECT_H

#include <vector>

#include "Shape.h"
#include "../Transform.h"
#include "../../STGame.h"

class STRect : public Shape{
public:
    STRect(){
        std::vector<Vector3<stReal>> initialCoords;
        initialCoords.push_back(Vector3<stReal>(-1.0f, 1.0f, 0.0f));
        initialCoords.push_back(Vector3<stReal>(-1.0f, -1.0f, 0.0f));
        initialCoords.push_back(Vector3<stReal>( 1.0f, -1.0f, 0.0f));
        initialCoords.push_back(Vector3<stReal>( 1.0f, 1.0f, 0.0f));

        std::vector<Vector2<stReal>> texCoords;
        texCoords.push_back(Vector2<stReal>( 0.0f, 1.0f ));
        texCoords.push_back(Vector2<stReal>( 0.0f, 0.0f ));
        texCoords.push_back(Vector2<stReal>( 1.0f, 0.0f ));
        texCoords.push_back(Vector2<stReal>( 1.0f, 1.0f ));

        for(int i = 0; i < 4; i++){
            positions.push_back(Vertex(initialCoords[i], texCoords[i], Vector3<stReal>(0.0f, 0.0f, 0.0f)));
        }

        index.push_back(0);
        index.push_back(1);
        index.push_back(2);
        index.push_back(2);
        index.push_back(3);
        index.push_back(0);
    }

    STRect(stReal x, stReal y, stReal width, stReal height) {
        stReal tX = 0.0f, tY = 0.0f;
        if(x == 0.0f){
            tX = -1.0f;
        }else if( x > (STGame::RES_WIDTH/2)){
            tX = 1.0f - (x / ((STGame::RES_WIDTH/2.0f)));
        }else{
            tX = -(1.0f - (x / (STGame::RES_WIDTH/2.0f)));
        }

        if(y == 0.0f){
            tY = 1.0f;
        }else if(y > (STGame::RES_HEIGHT/2)){
            tY = -(1.0f - (y / ((STGame::RES_WIDTH/2.0f))));
        }else{
            tY = 1.0f - (y / ((STGame::RES_WIDTH/2.0f)));
        }

        stReal hWidth = (width / STGame::RES_WIDTH) * 0.5f;
        stReal hHeight = (height / STGame::RES_HEIGHT) * 0.5f;

        std::vector<Vector3<stReal>> inititalCoords;
        inititalCoords.push_back(Vector3<stReal>(tX, tY, 0.0));
        inititalCoords.push_back(Vector3<stReal>(tX, tY - hHeight, 0.0));
        inititalCoords.push_back(Vector3<stReal>(tX + hWidth, tY - hHeight, 0.0));
        inititalCoords.push_back(Vector3<stReal>(tX + hWidth, tY, 0.0));

        std::vector<Vector2<stReal>> texCoords;
        texCoords.push_back(Vector2<stReal>( 0.0f, 1.0f ));
        texCoords.push_back(Vector2<stReal>( 0.0f, 0.0f ));
        texCoords.push_back(Vector2<stReal>( 1.0f, 0.0f ));
        texCoords.push_back(Vector2<stReal>( 1.0f, 1.0f ));

        for(int i = 0; i < 4; i++){
            positions.push_back(Vertex(inititalCoords[i], texCoords[i], Vector3<stReal>(0.0f, 0.0f, 0.0f)));
        }

        index.push_back(0);
        index.push_back(1);
        index.push_back(2);
        index.push_back(2);
        index.push_back(3);
        index.push_back(0);
    }

    int getVertexSize(){ return 4; }
    int getIndexSize(){ return 6; }

    std::vector<Vertex> positions;
    std::vector<int> index;
private:
    Transform* m_transform;
};

#endif //WAHOO_RECT_H
