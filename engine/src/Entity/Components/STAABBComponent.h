#ifndef SWINGTECH1_STAABBCOMPONENT_H
#define SWINGTECH1_STAABBCOMPONENT_H

#include "STBoundsComponent.h"

class STAABBComponent : public STBoundsComponent{
public:
    STAABBComponent(STEntity* parent, Vector3<stReal> minPoint, Vector3<stReal> maxPoint);

    void update();
    void adjustTransX(stReal x);
    void adjustTransY(stReal y);
    void adjustTransZ(stReal z);

    void reconstructBounds();
    bool contains(STEntity* other){
        return false;
    }

private:
    Vector3<stReal> m_MinPoint;
    Vector3<stReal> m_MaxPoint;
    Vector3<stReal> m_CalcMinPt;
    Vector3<stReal> m_CalcMaxPt;
    STEntity* m_Entity;
};


#endif //SWINGTECH1_STAABBCOMPONENT_H
