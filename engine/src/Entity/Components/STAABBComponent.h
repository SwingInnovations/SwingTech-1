#ifndef SWINGTECH1_STAABBCOMPONENT_H
#define SWINGTECH1_STAABBCOMPONENT_H

#include "STBoundsComponent.h"
#include "../../Math/Vertex.h"

class STAABBComponent : public STBoundsComponent{
public:
    STAABBComponent();
    STAABBComponent(STEntity* parent, Vector3<stReal> minPoint, Vector3<stReal> maxPoint);

    void init(STEntity* parent);

    void update() override;

    Vector3<stReal> getMinPoint()const{ return m_MinPoint; }
    Vector3<stReal> getMaxPoint()const{ return m_MaxPoint; }

    bool contains(STEntity* other) override {
        return false;
    }

    void calculateBounds();

private:
    Vector3<stReal> m_MinPoint;
    Vector3<stReal> m_MaxPoint;
    Vector3<stReal> m_CalcMinPt;
    Vector3<stReal> m_CalcMaxPt;
    STEntity* m_Entity;
};


#endif //SWINGTECH1_STAABBCOMPONENT_H
