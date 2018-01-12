#ifndef SWINGTECH1_STAABBCOMPONENT_H
#define SWINGTECH1_STAABBCOMPONENT_H

#include "STBoundsComponent.h"
#include "../../Math/Vertex.h"
#include "../../Math/Shape/BoundingBox.h"

#include <cereal/archives/binary.hpp>

class STAABBComponent : public STBoundsComponent{
public:
    STAABBComponent();
    STAABBComponent(STEntity* parent, Vector3<stReal> minPoint, Vector3<stReal> maxPoint);
    ~STAABBComponent();

    void init(std::shared_ptr<STEntity>& parent) override;

    void update() override;

    Vector3D getMinPoint()const{ return m_boundingBox->getMinPoint(); }
    Vector3D getMaxPoint()const{ return m_boundingBox->getMaxPoint(); }
    STBoundingBox* getBoundingBox();

    bool contains(STEntity* other) override;
    bool intersects(STEntity* other) override;
    void calculateBounds() override;

    template<class Archive> void serialize(Archive& ar){
        //TODO Implement this
    }

private:
    STBoundingBox* m_boundingBox;
    bool m_isCalculated;
};


#endif //SWINGTECH1_STAABBCOMPONENT_H
