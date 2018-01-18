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

/**
 *  @Author Nathan Danque
 *
 *  Purpose: Handle Mesh operations within the m_entity.
 *
 */
public:
    STMeshComponent();
    explicit STMeshComponent(STMesh_Structure structure);

    explicit STMeshComponent(Shape& shape);

    explicit STMeshComponent(STQuad*);

    explicit STMeshComponent(STRect*);

    explicit STMeshComponent(STCube*);
    STMeshComponent(float *vert, int vSize, float *tex, int tSize, int *ind, int indSize);
    ~STMeshComponent() override;

    void update() override;

    STMesh *getMesh() const;

    inline void draw() override {
        m_Mesh->draw();
    }

    void dispose() override;

    inline void draw(int drawMode){
        m_Mesh->draw(drawMode);
    }

private:
    std::shared_ptr<STMesh> m_Mesh;
};


#endif //WAHOO_STMESHCOMPONENT_H
