#ifndef SWINGTECH1_STAABBCOMPONENT_H
#define SWINGTECH1_STAABBCOMPONENT_H

#include "STBoundsComponent.h"
#include "../../Math/Vertex.h"
#include "../../Math/Shape/BoundingBox.h"

class STAABBComponent : public STBoundsComponent{
public:
    STAABBComponent();
    STAABBComponent(STEntity* parent, Vector3<stReal> minPoint, Vector3<stReal> maxPoint);
    ~STAABBComponent();

    void init(STEntity* parent) override;

    void update() override;

    Vector3<stReal> getMinPoint()const{ return m_boundingBox->getMinPoint(); }
    Vector3<stReal> getMaxPoint()const{ return m_boundingBox->getMaxPoint(); }

    bool contains(STEntity* other) override;
    bool intersects(STEntity* other) override;
    void calculateBounds() override;

private:
    STBoundingBox* m_boundingBox;
};


#endif //SWINGTECH1_STAABBCOMPONENT_H
