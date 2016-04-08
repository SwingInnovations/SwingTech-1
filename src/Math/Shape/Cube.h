#ifndef WAHOO_CUBE_H
#define WAHOO_CUBE_H

#include "Shape.h"

class STCube : public Shape {
public:
    STCube() {
        std::vector<Vector3<stReal>> initialPositions;
        // Right Face
        initialPositions.push_back(Vector3<stReal>(1.0f, -1.0f, 1.0f));
        initialPositions.push_back(Vector3<stReal>(1.0f, -1.0f, -1.0f));
        initialPositions.push_back(Vector3<stReal>(1.0f, 1.0f, -1.0f));
        initialPositions.push_back(Vector3<stReal>(1.0f, 1.0f, 1.0f));

        //Left Face
        initialPositions.push_back(Vector3<stReal>(-1.0f, -1.0f, 1.0f));
        initialPositions.push_back(Vector3<stReal>(-1.0f, -1.0f, -1.0f));
        initialPositions.push_back(Vector3<stReal>(-1.0f, 1.0f, -1.0f));
        initialPositions.push_back(Vector3<stReal>(-1.0f, 1.0f, 1.0f));
        //Top Face
        initialPositions.push_back(Vector3<stReal>(-1.0f, 1.0f, 1.0f));
        initialPositions.push_back(Vector3<stReal>(-1.0f, 1.0f, -1.0f));
        initialPositions.push_back(Vector3<stReal>(1.0f, 1.0f, -1.0f));
        initialPositions.push_back(Vector3<stReal>(1.0f, 1.0f, 1.0f));
        // Bottom Face
        initialPositions.push_back(Vector3<stReal>(-1.0f, -1.0f, 1.0f));
        initialPositions.push_back(Vector3<stReal>(-1.0f, -1.0f, -1.0f));
        initialPositions.push_back(Vector3<stReal>(1.0f, -1.0f, -1.0f));
        initialPositions.push_back(Vector3<stReal>(1.0f, -1.0f, 1.0f));
        // Back
        initialPositions.push_back(Vector3<stReal>(-1.0f, -1.0f, 1.0f));
        initialPositions.push_back(Vector3<stReal>(1.0f, -1.0f, 1.0f));
        initialPositions.push_back(Vector3<stReal>(1.0f, 1.0f, 1.0f));
        initialPositions.push_back(Vector3<stReal>(-1.0f, 1.0f, 1.0f));
        //Front Face
        initialPositions.push_back(Vector3<stReal>(-1.0f, -1.0f,-1.0f));
        initialPositions.push_back(Vector3<stReal>(1.0f, -1.0f, -1.0f));
        initialPositions.push_back(Vector3<stReal>(1.0f, 1.0f, -1.0f));
        initialPositions.push_back(Vector3<stReal>(-1.0f, 1.0f,-1.0f));
        for (uint32_t i = 0, S = initialPositions.size(); i < S; i++) {
            vertex.push_back(Vertex(initialPositions[i], Vector2<stReal>(), Vector3<stReal>()));
        }

        indicies.push_back(0);
        indicies.push_back(1);
        indicies.push_back(2);
        indicies.push_back(2);
        indicies.push_back(3);
        indicies.push_back(0);

        indicies.push_back(4);
        indicies.push_back(5);
        indicies.push_back(6);
        indicies.push_back(6);
        indicies.push_back(7);
        indicies.push_back(4);

        indicies.push_back(8);
        indicies.push_back(9);
        indicies.push_back(10);
        indicies.push_back(10);
        indicies.push_back(11);
        indicies.push_back(8);

        indicies.push_back(12);
        indicies.push_back(13);
        indicies.push_back(14);
        indicies.push_back(14);
        indicies.push_back(15);
        indicies.push_back(12);

        indicies.push_back(16);
        indicies.push_back(17);
        indicies.push_back(18);
        indicies.push_back(18);
        indicies.push_back(19);
        indicies.push_back(16);

        indicies.push_back(20);
        indicies.push_back(21);
        indicies.push_back(22);
        indicies.push_back(22);
        indicies.push_back(23);
        indicies.push_back(20);
    }

    int getVertexSize() { return (int) vertex.size(); }

    int getIndexSize() { return (int) indicies.size(); }
};

#endif //WAHOO_CUBE_H
