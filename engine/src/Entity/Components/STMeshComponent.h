#ifndef WAHOO_STMESHCOMPONENT_H
#define WAHOO_STMESHCOMPONENT_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "STComponent.h"
#include "../../Math/Vector.h"
#include "../../Math/Vertex.h"

#include "../../Math/Shape/Shape.h"
#include "../../Math/Shape/Rect.h"
#include "../../Math/Shape/Quad.h"
#include "../Util/STMesh.h"

class STComponent;

class STMeshComponent : public STComponent{

/*
 *  @Author Nathan Danque
 *
 *  Purpose: Handle Mesh operations within the m_entity.
 *
 */

public:
    STMeshComponent(const std::string& fileName, int type);
    STMeshComponent(const std::string& fileName);
    STMeshComponent(STMesh_Structure structure);
    STMeshComponent(Shape& shape);
    STMeshComponent(STQuad*);
    STMeshComponent(STRect*);
    STMeshComponent(STCube*);
    STMeshComponent(float *vert, int vSize, float *tex, int tSize, int *ind, int indSize);
    ~STMeshComponent();

    void update();

    inline void draw(){
        m_mesh->draw();
    }

    inline void draw(int drawMode){
        m_mesh->draw(drawMode);
    }

private:

    STMesh* m_mesh;
};


#endif //WAHOO_STMESHCOMPONENT_H
