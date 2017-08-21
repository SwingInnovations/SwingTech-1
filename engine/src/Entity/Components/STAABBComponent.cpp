#include "STAABBComponent.h"
#include "../STEntity.h"
#include "STEventComponent.h"

STAABBComponent::STAABBComponent(){

}

void STAABBComponent::init(STEntity *parent) {
    this->parent = parent;
    calculateBounds();
}

STAABBComponent::STAABBComponent(STEntity *parent, Vector3<stReal> minPoint, Vector3<stReal> maxPoint) {
    this->parent = parent;
    m_boundingBox = new STBoundingBox(minPoint, maxPoint);
    calculateBounds();
}

void STAABBComponent::calculateBounds() {
    auto vertex = parent->get<STMeshComponent>()->getMesh()->getMeshStructure().m_vertices;
    auto transform = parent->transform()->getModel();
    Vector3<stReal> minPoint, maxPoint;
    minPoint = maxPoint = parent->transform()->getTranslate() * parent->transform()->getScaleF();
    for (auto &v : vertex) {
        minPoint = Vector3<stReal>::Min(minPoint, transform * *v.getVertex());
        maxPoint = Vector3<stReal>::Max(maxPoint, transform * *v.getVertex());
    }
    m_boundingBox->setMinPoint(minPoint);
    m_boundingBox->setMaxPoint(maxPoint);
}

void STAABBComponent::update() {
    calculateBounds();
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




