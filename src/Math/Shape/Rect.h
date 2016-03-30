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
        stReal tX = x / STGame::RES_WIDTH;
        stReal tY = y / STGame::RES_HEIGHT;

        std::vector<Vector3<stReal>> initialCoords;
    }

    int getVertexSize(){ return 4; }
    int getIndexSize(){ return 6; }

    std::vector<Vertex> positions;
    std::vector<int> index;
private:
    Transform* transform;
};
#endif //WAHOO_RECT_H
