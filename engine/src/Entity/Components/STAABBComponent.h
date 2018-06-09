#ifndef SWINGTECH1_STAABBCOMPONENT_H
#define SWINGTECH1_STAABBCOMPONENT_H

#include "STBoundsComponent.h"
#include "../../Math/Vertex.h"
#include "../../Math/Shape/BoundingBox.h"
#include "../Util/Loaders/STMeshCommon.h"

class STAABBComponent : public STBoundsComponent{
public:
    STAABBComponent();
	explicit STAABBComponent(STMesh_Structure& meshStructure);
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

    void save(std::ofstream& out) override;
    void load(std::ifstream& in) override;

private:
    STBoundingBox*	m_boundingBox;
    bool			m_isCalculated;
};


#endif //SWINGTECH1_STAABBCOMPONENT_H
