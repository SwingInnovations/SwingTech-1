#include "STAABBComponent.h"
#include "../STEntity.h"
#include "STEventComponent.h"

STAABBComponent::STAABBComponent(){

}

void STAABBComponent::init(STEntity *parent) {
    this->m_entity = parent;
    this->m_boundingBox = new STBoundingBox();
    m_isCalculated = false;
    calculateBounds();
}

STAABBComponent::STAABBComponent(STEntity *parent, Vector3<stReal> minPoint, Vector3<stReal> maxPoint) {
    this->m_entity = parent;
    m_boundingBox = new STBoundingBox(minPoint, maxPoint);
    calculateBounds();
}

void STAABBComponent::calculateBounds() {
    if(!m_isCalculated){
        auto vertex = m_entity->get<STMeshComponent>()->getMesh()->getMeshStructure().m_vertices;
        Vector3<stReal> minPoint, maxPoint;
        minPoint = maxPoint = Vector3D();
        for (auto &v : vertex) {
            minPoint = Vector3D::Min(minPoint, *v.getVertex());
            maxPoint = Vector3D::Max(maxPoint, *v.getVertex());
        }
        m_boundingBox->setMinPoint(m_entity->transform()->getModel() * minPoint);
        m_boundingBox->setMaxPoint(m_entity->transform()->getModel() * maxPoint);
        m_isCalculated = true;
    }
}

void STAABBComponent::update() {
    calculateBounds();
    if(m_isCalculated){
        m_boundingBox->update(*m_entity->transform());
    }
}

bool STAABBComponent::contains(STEntity *other) {
    auto position = other->transform()->getTranslate();
    auto minPt = m_boundingBox->getMinPoint();
    auto maxPt = m_boundingBox->getMaxPoint();
    return (position >= minPt) && (position <= maxPt);
}

bool STAABBComponent::intersects(STEntity *other) {
    //TODO Implement this
    return false;
}

STAABBComponent::~STAABBComponent() {
    delete m_boundingBox;
}

STBoundingBox *STAABBComponent::getBoundingBox() {
    return m_boundingBox;
}




