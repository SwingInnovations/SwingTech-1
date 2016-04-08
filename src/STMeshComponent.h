#ifndef WAHOO_STMESHCOMPONENT_H
#define WAHOO_STMESHCOMPONENT_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "STComponent.h"
#include "Math/Vector.h"
#include "Math/Vertex.h"

#include "Math/Shape/Shape.h"
#include "Math/Shape/Rect.h"
#include "Math/Shape/Quad.h"
#include "STMesh.h"

class STMeshComponent : public STComponent{

/*
 *  @Author Nathan Danque
 *
 *  Purpose: Handle Mesh operations within the entity.
 *
 */

public:
    STMeshComponent(const std::string& fileName, int type);
    STMeshComponent(Shape& shape);
    STMeshComponent(STQuad*);
    STMeshComponent(STRect*);
    STMeshComponent(STCube*);
    STMeshComponent(float *vert, int vSize, float *tex, int tSize, int *ind, int indSize);
    ~STMeshComponent();

    void draw(){
        mesh->draw();
    }

    void draw(int drawMode){
        mesh->draw(drawMode);
    }

private:

    STMesh* mesh;
};


#endif //WAHOO_STMESHCOMPONENT_H
